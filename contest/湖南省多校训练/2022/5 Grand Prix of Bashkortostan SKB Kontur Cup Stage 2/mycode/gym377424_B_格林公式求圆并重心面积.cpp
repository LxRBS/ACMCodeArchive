/**
 * 给定一个凸多边形形状的薄木板，上面有很多圆洞，圆洞可能会重叠
 * 薄木板初始位于竖直平面内，给定每个点的坐标，给定圆洞的圆心和半径
 * 现在将薄木板的第V个点固定住，然后让其在重力作用下达到平衡位置
 * 问此时凸多边形的N个顶点的坐标
 * 只需求出重心坐标，再做一个坐标变换即可。
 * 首先可以求出完整凸多边形的重心，再可以求出圆并的重心，于是可以求出薄木板的重心坐标
 * 圆并的重心坐标及面积均使用格林公式，将面积分转换为路径积分进行计算
 * 均有解析原函数，可以直接算得
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
inline Real sqr(Real x){return x * x;}
inline Real cub(Real x){return x * x * x;}
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

/// 求重心的x坐标的原函数，缺一个0.5的因子
Real fx(const Circle &c, Real theta){
    Real sint = sin(theta);
    Real r2 = sqr(c.radius);
    return c.radius * ((sqr(c.center.x)+r2)*sint + c.radius*c.center.x*(theta+0.5*sin(theta+theta)) - r2*cub(sint)/3.0);
}

/// 求重心的y坐标的原函数，缺一个0.5的因子
Real fy(const Circle &c, Real theta){
    Real cost = cos(theta);
    Real r2 = sqr(c.radius);
    return c.radius * (r2*cub(cost)/3.0 + c.radius*c.center.y*(theta-0.5*sin(theta+theta)) - (r2+sqr(c.center.y))*cost);
}

/// 求圆并，索引从0开始
tuple<Real, Real, Real> unite_circles(const Circle c[], int n){
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
    Real ans = 0, ansx = 0, ansy = 0;
    vpii vec;
    for(int i=0;i<n;++i){
        if(han[i]) continue; // 说明是被包含的
        const Circle * ci = c + i;
        const vi & st = status[i];
        if(st.empty()){ // 说明整个圆都是边界
            ans += diff(f, *ci, -PI, PI);
            ansx += diff(fx, *ci, -PI, PI);
            ansy += diff(fy, *ci, -PI, PI);
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
                ansx += diff(fx, *ci, left, p.first);
                ansy += diff(fy, *ci, left, p.first);
                left = p.second;
            }else if(left < p.second){ // 更新边界的起点
                left = p.second;
            }
        }
        /// 最后再加上一段，无论有没有
        ans += diff(f, *ci, left, PI);
        ansx += diff(fx, *ci, left, PI);
        ansy += diff(fy, *ci, left, PI);
    }
    return {ans, ansx, ansy}; // 都不用0.5，会抵消
}

int N, C, V;
Circle Cir[SIZE];
Point P[SIZE];

void proc(){
    /// 求圆并的重心
    auto ans = unite_circles(Cir, C);
    /// 求多边形的重心和面积
    Real cgx = 0, cgy = 0, area = 0;
    for(int i=2;i<N;++i){
        Real tmp = cross(P[0], P[i-1], P[i]);
        area += tmp;
        cgx += tmp * (P[0].x+P[i-1].x+P[i].x)/3.0;
        cgy += tmp * (P[0].y+P[i-1].y+P[i].y)/3.0;
    }
    /// 求薄木板的重心
    Real leftarea = area - get<0>(ans);
    Real leftx = (cgx - get<1>(ans)) / leftarea;
    Real lefty = (cgy - get<2>(ans)) / leftarea;
    /// 凸多边形做一个坐标平移
    Point origin = P[V];
    for(int i=0;i<N;++i) P[i].x -= origin.x, P[i].y -= origin.y;
    leftx -= origin.x, lefty -= origin.y;
    /// 旋转
    Real theta = atan2(lefty, leftx);
    theta = -0.5 * PI - theta;
    Real ca = cos(theta), sa = sin(theta);
    for(int i=0;i<N;++i){
        Real x = P[i].x, y = P[i].y;
		P[i].x = x * ca - y * sa + origin.x;
		P[i].y = y * ca + x * sa + origin.y; 
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); C = getInt(); V = getInt() - 1;
    for(int i=0;i<N;++i) P[i].x = getInt(), P[i].y = getInt();
    for(int i=0;i<C;++i) Cir[i].center.x = getInt(), Cir[i].center.y = getInt(), Cir[i].radius = getInt();
    proc();
    for(int i=0;i<N;++i) printf("%.7f %.7f\n", P[i].x, P[i].y);
    return 0;
}

