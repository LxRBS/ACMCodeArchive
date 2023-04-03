#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_cxx;
using namespace __gnu_pbds;

/** 1. typdef和常数 **/
using Real = long double;
using llt = long long;

Real const EPS = 1E-8; // 根据需要调整
Real const PI = acos(-1);
Real const INF = 1E12;  // 根据需要调整

inline int sgn(Real x){return x >= EPS ? 1 : (x <= -EPS ? -1 : 0);}
inline bool is0(Real x){return 0 == sgn(x);}

/// 表位置关系的常数
int const OUT = 0; // 没有公共点，即不相交
int const IN = 1; // 点在各种图形内
int const JIAO = 2; // 直线与直线，线段与线段，直线与线段
int const PINGXING = 4; // 直线与直线
int const CHONGHE = 8; // 直线与直线
int const VERTEX = 0x10; // 表示点还在图形的端点上
int const EDGE = 0x20; // 表示点还在图形的边上

using T = Real;

struct Point{

T x, y;
Point() = default;
Point(T a, T b):x(a),y(b){}

void input(){
    cin >> this->x >> this->y;
}

T square() const {return x * x + y * y;} // 整型小心超范围

bool operator == (const Point & r) const {return x == r.x && y == r.y;}

const Point operator - (const Point & r) const {return Point(x - r.x, y - r.y);}

const Point operator + (const Point & r) const {return Point(x + r.x, y + r.y);}

T dot(const Point & r) const {return x * r.x + y * r.y;}

T dot(const Point & A, const Point & B) const {return (A - *this).dot(B - *this);}

T cross(const Point & r) const {return x * r.y - y * r.x;}

T cross(const Point & A, const Point & B) const {return (A - *this).cross(B - *this);}

Real length() const {return (Real)sqrt((Real)this->square());}

Real dist(const Point & r) const {return (*this - r).length();}

/**
 * @brief 返回this与线段AB的关系，保证A!=B 
 * @return this是A、B之一，返回IN|VERTEX,this在AB上，返回IN|EDGE,否则返回OUT
 */
int relate(const Point & A, const Point & B) const {
    assert(!(A == B));
    if(A == *this || B == *this) return IN | VERTEX;
    if(sgn(this->dot(A, B)) <= 0 && 0 == sgn(this->cross(A, B))){
        return IN | EDGE;
    }
    return OUT;    
}

/**
 * @brief 返回this到线段AB之间的距离
 * @return 距离 
 */
Real dist(const Point & A, const Point & B) const {
    if(IN & this->relate(A, B)) return 0;
    if(sgn(A.dot(*this, B)) <= 0) return this->dist(A);
    if(sgn(B.dot(*this, A)) <= 0) return this->dist(B);
    /// 距离为高
    return fabs(this->cross(A, B)) / (A - B).length();
}

};

struct LineSeg{

Point s, e;
LineSeg() = default;
LineSeg(const Point & A, const Point & B):s(A),e(B){}

/**
 * @brief this与线段AB的位置关系，两线段的位置关系
 * @return JIAO或者OUT，如果需要进一步知道相交的位置，需要额外判断
 */
int relate(const Point &A, const Point &B) const {
    return sgn(min(s.x, e.x) - max(A.x, B.x)) <= 0
        && sgn(min(s.y, e.y) - max(A.y, B.y)) <= 0
        && sgn(min(A.x, B.x) - max(s.x, e.x)) <= 0
        && sgn(min(A.y, B.y) - max(s.y, e.y)) <= 0
        && sgn(s.cross(A, e)) * sgn(s.cross(e, B)) >= 0
        && sgn(A.cross(s, B)) * sgn(A.cross(B, e)) >= 0
        ? JIAO : OUT;
}

};

struct Polygon{

vector<Point> pts; // 编号从0开始

Polygon() = default;

void input(int n){
    this->pts.assign(n, Point());
    for(auto & p : this->pts){
        p.input();
    }
}

/**
 * @brief 判断点p是否在this里，this是简单多边形，顺逆时针均可，O(N)
 * @return 如果在端点上返回IN|VERTEX，在边上返回IN|EDGE，在里返回IN，否则返回OUT 
 */
int relate(const Point & p) const {
    int n = pts.size();

    /// 特判
    if(1 == n) return (p == pts[0]) ? (IN | VERTEX) : OUT;

    /// 无穷远点构成的线段 
    LineSeg ls(p, Point(INF, p.y));
    int ans = 0;
    for(int r,nxt,i=0;i<n;++i){
        nxt = (i+1) % n;
        /// 首先看点本身与边的位置关系
        r = p.relate(pts[i], pts[nxt]);
        if(r) return r;

        /// 水平边忽略
        int t = sgn(pts[nxt].y - pts[i].y);
        if(0 == t) continue;

        /// 线段与边不交也忽略
        r = ls.relate(pts[i], pts[nxt]);
        if(OUT == r) continue;

        /// 交于较高的点也忽略
        if(t > 0 && pts[nxt].relate(ls.s, ls.e)) continue;
        if(t < 0 && pts[i].relate(ls.s, ls.e)) continue;

        ++ans;
    }
    /// 奇内偶外
    return (ans & 1) ? IN : OUT;
}

};

int N, M;
Polygon Poly;
Point P;


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif	
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	for(int kase=1;(cin >> N, N);++kase){
		if(kase != 1) cout << endl;

		cin >> M;
		Poly.input(N);
  
         cout << "Problem " << kase << ":"  << endl;
		for(int i=0;i<M;++i){
			P.input();
			auto tmp = Poly.relate(P);
			if(tmp & IN) cout << "Within" << endl;
            else cout << "Outside" << endl;
		}
	}
    return 0;
}
