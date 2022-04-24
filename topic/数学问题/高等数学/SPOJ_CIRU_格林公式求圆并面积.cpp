/**
 * 求圆并的面积。求面积就是计算面积分，使用格林公式将面积分转换为路径积分
 * 圆并的边缘肯定是圆弧，求出每一段圆弧求一个积分即可
 * 该积分能够算出原函数，所以很容易计算
 * O(N^2logN)
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
int const SIZE = 7;
#else
int const SIZE = 2010;
#endif

using Real = double;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<Real, Real>;
using vpii = vector<pii>;

Real const EPS = 1E-8;
Real const PI = acos(-1.0);
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
    /// 角度范围为[-Pi, Pi)
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

/// 求圆并，索引从0开始
Real unite_circles(const Circle c[], int n){
    /// 首先求各圆相交的情况
    vvi status(n, vi());
    vi han(n, 0);
    for(int i=0;i<n;++i){
        if(han[i]) continue; // i被包含
        auto ci = c + i;
        if(is0(ci->radius)){
            han[i] = 1; continue;
        }

        for(int j=i+1;j<n;++j){
            auto cj = c + j;
            if(is0(cj->radius)){
                han[j] = 1; continue;
            }
            Real u = ci->center.dist(cj->center);
            Real v1 = fabs(ci->radius - cj->radius);
            Real v2 = ci->radius + cj->radius;
            if(sgn(v1-u) >= 0){ // 包含
                if(sgn(ci->radius - cj->radius) >= 0){
                    han[j] = 1; // j被包含
                }else{
                    han[i] = 1; // i被j包含，i就不用再算了
                    break;
                }
            }else if(sgn(v2-u) > 0){ // 相交
                status[i].push_back(j);
                status[j].push_back(i);
            }
        }        
    }
    /// 处理每个圆
    Real ans = 0;
    vpii vec;
    for(int i=0;i<n;++i){
        if(han[i]) continue; // 说明是被包含的
        const Circle * ci = c + i;
        const vi & st = status[i];
        if(st.empty()){ // 说明整个圆都是边界
            ans += diff(f, *ci, -PI, PI);
            continue;
        }
        vec.clear(); 
        vec.reserve(st.size());
        /// 对每个相交的圆求相交区间
        for(int j: st){
            auto tmp = ci->inter(c[j]);
            vec.insert(vec.end(), tmp.begin(), tmp.end());
        }
        /// 相交区间排序
        sort(vec.begin(), vec.end());
        /// 对每一段露在外面的圆弧做积分
        Real left = -PI;
        for(const auto &p: vec){
            if(left < p.first){ // 说明有一段边缘
                ans += diff(f, *ci, left, p.first);  
                left = p.second;
            }else if(left < p.second){ // 更新边界的起点
                left = p.second;
            }
        }
        /// 最后再加上一段，无论有没有
        ans += diff(f, *ci, left, PI);
    }
    return 0.5 * ans; // 最后乘0.5
}

int N;
Circle C[SIZE];

Real proc(){
    Real ans = unite_circles(C, N);
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt();
    for(int i=0;i<N;++i) C[i].center.x = getInt(), C[i].center.y = getInt(), C[i].radius = getInt();
    printf("%.3f\n", proc());
    return 0;
}