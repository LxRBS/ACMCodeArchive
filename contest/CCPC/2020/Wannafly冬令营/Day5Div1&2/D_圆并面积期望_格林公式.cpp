/**
 * N(1000)个圆，每个圆有一个出现的概率，问圆并的面积的期望。
 * 对于圆并而言，面积出现的概率*面积分 = 圆弧作为边界的概率*路径积分
 * 因此对每个圆的每一段圆弧进行计算即可，可以用格林公式推一下。
 * 要注意其他圆对当前圆的相交的圆弧，是先乘再除一个概率，所以概率为0时需要特判
 * 特判比较麻烦，可以直接令零概率为EPS，这样就能正常进行乘除。
 */
#include <bits/stdc++.h>
using namespace std;
 
char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}
 
#ifndef ONLINE_JUDGE
int const SIZE = 1003;
#else
int const SIZE = 1E3+10;
#endif

using Real = double;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<Real, Real>;
using vpii = vector<pii>;

Real const EPS = 1E-10;
Real const PI = acos(-1.0);
Real const INF = 1E10;
inline int sgn(Real x){return x>EPS?1:(x<-EPS?-1:0);}
inline bool is0(Real x){return 0 == sgn(x);} 
inline Real myacos(Real x){
    if(x > 1) x = 1.0;
    if(x < -1) x = -1.0;
    return acos(x);
}

struct Point{
    Real x, y;
    Real dist(const Point &b)const{
        Real u = x - b.x, v = y - b.y;
        return sqrt(u*u+v*v);
    }
};

struct Circle{
    Point center;
    Real radius;
    /// 两个圆相交，返回圆弧角度的区间,可能是一段，也可能是两段
    /// 角度范围为[-Pi, Pi)，确保相交
    vpii inter(const Circle &b)const{
        Real d123 = center.dist(b.center);
        Real u111 = fabs(radius - b.radius);
        Real u222 = radius + b.radius;
        assert(sgn(u222-d123) > 0 && sgn(d123 - u111) > 0);

        Real cosvalue = (radius * radius + d123 * d123 - b.radius * b.radius) / (2.0 * radius * d123);
        Real jiao = myacos(cosvalue);
        Real anchor = atan2(b.center.y - center.y, b.center.x - center.x);
        Real from = anchor - jiao, to = anchor + jiao;

        vpii ans;
        if(sgn(to - PI) >= 0){ // 分两段
            ans.emplace_back(-PI, to-PI-PI);
            ans.emplace_back(from, PI);
            return ans;
        }
        if(sgn(from+PI) < 0){ // 分两段
            ans.emplace_back(-PI, to);
            ans.emplace_back(from+PI+PI, PI);
            return ans;
        }
        ans.emplace_back(from, to);
        return ans;
    }

    /// 两圆的关系，分别是包含、被包含、相交、无关
	enum Relation{BAOHAN, BEIHAN, INTER, NOTHING};
    /// this与圆b的关系
	Relation relate(const Circle &b)const{
		Real d123 = this->center.dist(b.center);
		if(sgn(d123 + this->radius - b.radius) <= 0) return BEIHAN;
		if(sgn(d123 + b.radius - this->radius) <= 0) return BAOHAN;
		if(sgn(this->radius + b.radius - d123) <= 0) return NOTHING;
		return INTER;
	}

	void read(){
		this->center.x = getInt();
		this->center.y = getInt();
		this->radius = getInt();
	}
};

Real cross(const Point &O, const Point &A, const Point &B){
    Real xoa = A.x - O.x, yoa = A.y - O.y;
    Real xob = B.x - O.x, yob = B.y - O.y;
    return xoa * yob - xob * yoa;
}

/// 原函数求差值
inline Real diff(Real (*f)(const Circle&, Real), const Circle&c, Real alpha, Real beta){
    return  f(c, beta) - f(c, alpha); 
}

/// 求面积的函数，缺一个0.5的因子
Real f(const Circle &c, Real theta){
    return c.radius * (c.radius * theta + c.center.x * sin(theta) - c.center.y * cos(theta));
}

int N;
Circle Cir[SIZE];
Real Prob[SIZE];
Real Qb[SIZE], IQ[SIZE];

using t3t = tuple<int, int, int>;
template<> struct std::hash<t3t>{
    size_t operator()(const t3t&t)const{
		size_t ans = get<0>(t);
		ans = ans * 1331 + get<1>(t);
		ans = ans * 1331 + get<2>(t);
        return ans;
	}
};

Real proc(int pos){ // 处理第pos个圆
    const Circle & cir = Cir[pos];
	vpii vec; // first是交点，second是概率，进要乘，出要除
	Real p = 1.0;
    for(int i=0;i<N;++i)if(i!=pos){
		auto r = cir.relate(Cir[i]);
		if(Circle::BEIHAN == r){ // 如果是被包含关系
			p *= Qb[i];
		}else if(Circle::INTER == r){ // 求相交段
			auto inter = cir.inter(Cir[i]);
			for(const auto &p: inter){
				vec.emplace_back(p.first, Qb[i]);
				vec.emplace_back(p.second, IQ[i]);
			}			
		}
	}

    /// 如果该圆没有和任何圆相交
	if(vec.empty()){ // 
        return p * Prob[pos] * diff(f, cir, -PI, PI);
	}

	sort(vec.begin(), vec.end());

    Real q = 1.0;
	Real ans = 0.0;
	/// 第一段，如果起点没有被盖住的话
	if(!is0(vec.begin()->first + PI)){
		ans = q * diff(f, cir, -PI, vec.begin()->first);
	}
	for(int i=0,n1=vec.size()-1;i<n1;++i){
		q *= vec[i].second;
		ans += q * diff(f, cir, vec[i].first, vec[i+1].first);
	}
	/// 最后一段，如果终点没有被盖住的话
	if(!is0(vec.back().first-PI)){
		q *= vec.back().second;
		ans += q * diff(f, cir, vec.back().first, PI);
	}else{
		q *= vec.back().second;
	}
	assert(is0(q - 1));	
	/// 还要乘以本身的概率
	ans *= p * Prob[pos];
	return ans;
}

Real proc(){
	Real ans = 0;
	for(int i=0;i<N;++i){
		ans += proc(i); 
	}
	return ans * 0.5;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt();

	/// 确保没有重合的圆
	unordered_map<t3t, Real> mm;
	for(int x,y,r,i=0;i<N;++i){
        x = getInt(), y = getInt(), r = getInt();
        t3t t = {x, y, r};
		Real p = 1.0 - getInt() / 1000.0;
		auto it = mm.find(t);
		if(it == mm.end()){
            it = mm.insert(it, {t, 1.0});
		}
		it->second *= p;
	}

    N = 0;
    for(auto &p: mm){
		Cir[N] = {(Real)get<0>(p.first), (Real)get<1>(p.first), (Real)get<2>(p.first)};
		if(is0(p.second)) p.second = EPS;
		Prob[N] = 1.0 - (Qb[N] = p.second);
		IQ[N++] = 1.0 / p.second;  
	}
	
	cout<<fixed<<setprecision(12)<<proc()<<endl;
    return 0;
}