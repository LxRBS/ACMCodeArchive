/**
 * 大凸多边形套小凸多边形，在多边形的边上等概率选择一点放置点光源，照亮小多边形
 * 问照亮长度的期望是多少
 * E = SIGMA{Pi * 照亮长度}
 * 考虑到一条边被照亮，肯定是整条被照亮的，因此
 * E = SIGMA{边长 * 边被照亮的概率}
 * 每条边被照亮的概率 = 能够照亮边的长度 / 大多边形的周长
 * 因此只需求出小多边形每条边所在直线交大多边形的异侧长度即可
 * 每条边在大多边形上有两个交点，求第一对交点需要O(N)
 * 以后的每条边的交点必然是连续变化的，因此也只需要O(N)
 * 长度可以在求交点过程中一并计算 
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000-1,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

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
int const SIZE = 55;
#else
int const SIZE = 2E5+5;
#endif

typedef long double Real;
typedef tuple<Real, Real, Real> Line;

Real const INF = 1E9 + 1E8;
Real const EPS = 1E-12;
inline int sgn(Real x){return x>=EPS?1:(x<=-EPS?-1:0);}
inline bool is0(Real x){return 0 == sgn(x);}

struct Point{
    Real x, y;
	Point(Real a=0, Real b=0):x(a),y(b){}
};

const Point O(0, 0);

struct LineSeg{
	Point s, e;
	LineSeg(const Point&a, const Point&b):s(a),e(b){}
};

inline Real cross(const Point&O, const Point&A, const Point&B){
	Real xoa = A.x - O.x;
	Real yoa = A.y - O.y;
	Real xob = B.x - O.x;
	Real yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}

inline Real dot(const Point&O, const Point&A, const Point&B){
	Real xoa = A.x - O.x;
	Real yoa = A.y - O.y;
	Real xob = B.x - O.x;
	Real yob = B.y - O.y;	
	return xoa * yoa + xob * yob;
}

inline Real dist(const Point&A, const Point&B){
	Real x = A.x - B.x, y = A.y - B.y;
	return sqrt(x*x+y*y);
}

/// 求多边形的重心，保证p[0] == p[n]
Point gravity(const Point p[], int n){
    vector<Point> vec;
	vec.reserve(n);
	Real a = 0;
	Point ans;
	for(int i=1;i<n-1;++i){
		Real tx = (p[0].x + p[i].x + p[i+1].x) / 3.0;
		Real ty = (p[0].y + p[i].y + p[i+1].y) / 3.0;
		Real w = cross(p[0], p[i], p[i+1]);
		a += w;
        ans.x += tx * w;
		ans.y += ty * w;
	}
	ans.x /= a; ans.y /= a;
	return ans;
}

/// 线段AB与线段CD是否相交
inline bool isInter(const Point&A, const Point&B, const Point&C, const Point&D){
    if(min(A.x, B.x) > max(C.x, D.x)) return false;
	if(min(A.y, B.y) > max(C.y, D.y)) return false;
	if(min(C.x, D.x) > max(A.x, B.x)) return false;
	if(min(C.y, D.y) > max(A.y, B.y)) return false;
	if(sgn(cross(C, B, D) * cross(C, D, A)) < 0) return false;
	if(sgn(cross(A, C, B) * cross(A, B, D)) < 0) return false;
	return true;
}

/// 实际上就是求直线AB
inline Line cross(const Point&A, const Point&B){
    Real a = A.y - B.y;
	Real b = B.x - A.x;
	Real c = A.x * B.y - B.x * A.y;
	return {a, b, c};
}

inline Real eval(const Point&p, const Line&line){
	return p.x * get<0>(line) + p.y * get<1>(line) + get<2>(line);
}

/// p是否在直线line上
inline bool isIn(const Point &p, const Line&line){
    Real t = eval(p, line);
	if(is0(t)) return true;
	return false;
}

/// 判断点A和B是否在直线的同侧，AB保证不在直线上
inline bool isTong(const Point &A, const Point&B, const Line&line){
    Real ta = eval(A, line);
	Real tb = eval(B, line);
	int sa = sgn(ta), sb = sgn(tb);
	// assert(sa && sb); // 严格同侧，因为点在直线上的已经被剔除了，并不肯定这样写是对的，只是AC了
	return sa * sb > 0;
}

/// 直线u和v的交点，确保有交点
inline Point inter(const Line&u, const Line&v){
	Real ua = get<0>(u), ub = get<1>(u), uc = get<2>(u);
	Real va = get<0>(v), vb = get<1>(v), vc = get<2>(v);
    Real x = ub * vc - vb * uc;
	Real y = va * uc - ua * vc;
	Real t = ua * vb - va * ub;
	if(is0(x) && is0(y) && is0(t)){
		throw runtime_error("XXXXX");
	}
	assert(!is0(t));
	return {x/t, y/t};
}

int N, M;

Point P[SIZE], Q[SIZE];
Point GQ;

/// 直线Q[idx]Q[idx+1]与多边形P相交的交点以及交点所在的边的序号
/// 假设返回是<A, B, i, j>
/// 则A是(i,i+1)上的点，且i+1看不到线段Q(idx,idx+1)
/// B是(j, j+1)上的点，且j看不到线段Q(idx,idx+1)
tuple<Point, Point, int, int> inter(int idx){
    /// 先将Q[idx]Q[idx+1]变成一条直线
	Line line = cross(Q[idx], Q[idx+1]);
	vector<int> vec;
    /// 判断多边形的顶点P是否恰好在直线上
	for(int i=0;i<N;++i){
		if(isIn(P[i], line)){
            vec.push_back(i);
		}
	}

    tuple<Point, Point, int, int> ans = {Point(), Point(), -1, -1};
	if(2 == vec.size()){ // 说明两个交点都找到了	    
        /// Pi在直线上，看P[i+1]和P[i-1]谁看不到线段Q(idx,idx+1)
		int i = vec.front();
		if(isTong(GQ, P[i+1], line)){ // 说明P[i+1]看不到线段
		    assert(!isTong(GQ, P[i?i-1:N-1], line)); // 必然再另一边
            get<0>(ans) = P[i];
			get<2>(ans) = i;
		}else if(isTong(GQ, P[i?i-1:N-1], line)){ // 说明i-1看不到
            get<1>(ans) = P[i];
            get<3>(ans) = i?i-1:N-1;
		}else{
			throw runtime_error("line171");
		}

		int j = vec.back();
		if(isTong(GQ, P[j+1], line)){ // 说明P[i+1]看不到
            assert(!isTong(GQ, P[j?j-1:N-1], line)); // 必然再另一边
			assert(-1 == get<2>(ans)); // 上一个答案必然是另外一边的
			get<0>(ans) = P[j];
			get<2>(ans) = j;
		}else if(isTong(GQ, P[j?j-1:N-1], line)){
			assert(-1 == get<3>(ans));
			get<1>(ans) = P[j];
			get<3>(ans) = j?j-1:N-1;
		}else{
			throw runtime_error("185");
		}
		return ans;
	}

	if(1 == vec.size()){
        /// Pi在直线上，看P[i+1]和P[i-1]谁看不到线段Q(idx,idx+1)
		int i = vec.front();
		if(isTong(GQ, P[i+1], line)){ // 说明P[i+1]看不到线段
		    assert(!isTong(GQ, P[i?i-1:N-1], line)); // 必然再另一边
            get<0>(ans) = P[i];
			get<2>(ans) = i;
		}else if(isTong(GQ, P[i?i-1:N-1], line)){ // 说明i-1看不到
            get<1>(ans) = P[i];
            get<3>(ans) = i?i-1:N-1;
		}else{
			throw runtime_error("line171");
		}
		/// 找剩下的一个交点即可，如果某条边分居直线的两侧即可
		for(int i=0;i<N;++i){
            if(i == vec.front() || i + 1 == vec.front()) continue;
			if(isTong(P[i], P[i+1], line)) continue;
			/// 说明Pi和P[i+1]分居两侧，交点在这上面，先求交点
			Point jiaodian = inter(line, cross(P[i], P[i+1]));
			/// 再验证一下
			if(isTong(GQ, P[i], line)){ // 说明P[i+1]是看得见的一侧
			    assert(-1 == get<3>(ans));
                get<3>(ans) = i;
				get<1>(ans) = jiaodian;
			}else if(isTong(GQ, P[i+1], line)){ // 说明Pi看得见
                assert(-1 == get<2>(ans));
				get<2>(ans) = i;
				get<0>(ans) = jiaodian;
			}else{
				throw runtime_error("211");
			}
			break;
		}		
		return ans;
	}

	/// 两个交点均在中段
	for(int i=0;i<N;++i){
		if(isTong(P[i], P[i+1], line)) continue;
		/// 先求一个交点
		Point jiaodian = inter(line, cross(P[i], P[i+1]));
        if(isTong(GQ, P[i+1], line)){
			assert(-1 == get<2>(ans));
            get<0>(ans) = jiaodian;
			get<2>(ans) = i;
		}else if(isTong(GQ, P[i], line)){
			assert(-1 == get<3>(ans));
			get<1>(ans) = jiaodian;
			get<3>(ans) = i;
		}else{
			throw runtime_error("232");
		}
		if(-1 != get<2>(ans) && -1 != get<3>(ans)) break;
	}

    return ans;
}

/// 计算Q[idx]Q[idx+1]与多边形P的交点，
/// 令Q[idx-1]Q[idx]是上一条边记作e，abuv是e与P的交点，分别表示
/// e交P[u,u+1]于a，且P[u+1]看不见,e交P[v,v+1]于b，且P[v]看不见
/// 因此上一个可见部分是从b到v+1到u到a
/// light是上一个可见部分的长度
void inter(int idx, Point&a, Point &b, int&u, int&v, Real&light){
    /// 首先确定当前边的直线方程
	Line line = cross(Q[idx], Q[idx+1]);
	/// 推进u，Pu看得见边，P[u+1]看不见
	int t = 0;
	/// 首先将ua的距离减去
	light -= dist(P[u], a);
	while(1){
		/// 首先检查P[u+1]是否落在直线上
		if(isIn(P[(u+1)%N], line)){ // 答案是u+1和u+2
		    light += dist(P[u], P[(u+1)%N]);
            u = (u + 1)%N; a = P[u];			
			break;
		}
		/// 检查u,u+1是否满足条件
		if(!isTong(P[u], GQ, line) && isTong(P[(u+1)%N], GQ, line)){
            // u = u;
			a = inter(line, cross(P[u], P[(u+1)%N])); 
			light += dist(P[u], a);
			break;
		}
		light += dist(P[u], P[(u+1)%N]);
		u = (u+1) % N;		
		++t;
		if(t > N){
			throw runtime_error("269");
		}
	}
    light += dist(P[v], b);
	t = 0;
	while(1){ // 推进v
        /// 首先检查v+1是否落在直线上
		if(isIn(P[(v+1)%N], line)){ // 答案是v和v+1
            // v = v;			
			b = P[(v+1)%N];
			light -= dist(P[v], b);
			break;
		}
		/// 检查v/v+1
		if(isTong(P[v], GQ, line) && !isTong(P[(v+1)%N], GQ, line)){
			// v = v;
			b = inter(line, cross(P[v], P[(v+1)%N]));
			light -= dist(P[v], b);
			break;
		}
		light -= dist(P[v], P[(v+1)%N]);
		v = (v+1) % N;
		++t;
		if(t > N){
			throw runtime_error("290");
		}
	}
	return;
}

Real proc(){
	P[N] = P[0]; Q[M] = Q[0];
	GQ = gravity(Q, M);
    auto t4t = inter(0);
	Point a = get<0>(t4t), b = get<1>(t4t);
	int u = get<2>(t4t), v = get<3>(t4t);

	/// 先求P的周长
	Real total = 0;
    for(int i=0;i<N;++i){
		total += dist(P[i], P[i+1]);
	}

	/// b到从v+1到u到a是可见部分，求长度
	Real cur = dist(b, P[(v+1)%N]);
	for(int i=(v+1)%N;i!=u%N;(i+=1)%=N){
		cur += dist(P[i], P[(i+1)%N]);
	}
	cur += dist(P[u], a);
	
	Real ans = cur / total * dist(Q[0], Q[1]);
	for(int i=1;i<M;++i){		
		/// 计算下一个t4t
		inter(i, a, b, u, v, cur);
		ans += cur / total * dist(Q[i], Q[i+1]);
	}
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif        
    N = getInt(); M = getInt();
	for(int i=0;i<N;++i) P[i].x = getInt(), P[i].y = getInt();
	for(int i=0;i<M;++i) Q[i].x = getInt(), Q[i].y = getInt();
	cout<<fixed<<setprecision(12)<<proc()<<endl;
    return 0;
}
