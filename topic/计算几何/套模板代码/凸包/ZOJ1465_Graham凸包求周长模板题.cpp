/// 凸包求周长，模板题，整型坐标
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
int const SIZE = 130;
#else
int const SIZE = 1.1E6+10;
#endif

using Real = long double;
using llt = long long;

Real const EPS = 1E-9; // 根据需要调整
Real const PI = acos(-1);
Real const INF = 1E9;  // 根据需要调整

inline int sgn(Real x){return x >= EPS ? 1 : (x <= -EPS ? -1 : 0);}
inline bool is0(Real x){return 0 == sgn(x);}

inline int sgn(llt x){return x > 0 ? 1 : (x < 0 ? -1 : 0);}
inline bool is0(llt x){return 0 == x;}

/// 表位置关系的常数
int const OUT = 0; // 没有公共点，即不相交
int const IN = 1; // 点在各种图形内
int const JIAO = 2; // 直线与直线，线段与线段，直线与线段
int const PINGXING = 4; // 直线与直线
int const CHONGHE = 8; // 直线与直线
int const VERTEX = 0x10; // 表示点还在图形的端点上
int const EDGE = 0x20; // 表示点还在图形的边上

/** 2. 处理边界的数学库函数 **/
inline Real mysqrt(Real x){
    assert(sgn(x) >= 0);
    if(0 == sgn(x)) return 0;
    return sqrt(x);
}

inline Real myacos(Real x){
    assert(sgn(fabs(x) - 1) <= 0);
    if(0 == sgn(x - 1)) x = 1;
    else if(0 == sgn(x + 1)) x = -1;
    return acos(x);
}

inline Real myasin(Real x){
    assert(sgn(fabs(x) - 1) <= 0);
    if(0 == sgn(x - 1)) x = 1;
    else if(0 == sgn(x + 1)) x = -1;
    return asin(x);
}

using T = llt;

struct Point{

T x, y;
Point() = default;
Point(T a, T b):x(a),y(b){}

void input(){
    this->x = getInt();
    this->y = getInt();
}

T square() const {return x * x + y * y;} // 整型小心超范围

bool operator == (const Point & r) const {return x == r.x && y == r.y;}

const Point operator - (const Point & r) const {return Point(x - r.x, y - r.y);}

T dot(const Point & r) const {return x * r.x + y * r.y;}

T dot(const Point & A, const Point & B) const {return (A - *this).dot(B - *this);}

T cross(const Point & r) const {return x * r.y - y * r.x;}

T cross(const Point & A, const Point & B) const {return (A - *this).cross(B - *this);}

Real length() const {return (Real)sqrt((Real)this->square());}

Real dist(const Point & r) const {return (*this - r).length();}

/**
 * this与线段AB的关系，确保AB不退化
 * 如果this是A、B之一，返回IN|VERTEX
 * 如果this在AB上，返回IN|EDGE
 * 否则返回OUT
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
 * 返回this与线段AB之间的距离
 */
Real dist(const Point & A, const Point & B) const {
    if(IN & this->relate(A, B)) return 0;
    if(sgn(A.dot(*this, B)) <= 0) return this->dist(A);
    if(sgn(B.dot(*this, A)) <= 0) return this->dist(B);
    /// 距离为高
    return fabs(this->cross(A, B)) / (A - B).length();
}

};

struct Convex{

vector<Point> pts; // 编号从0开始

void input(int n){
    this->pts.assign(n, Point());
    for(auto & p : this->pts){
        p.x = getInt();
        p.y = getInt();
    }
}

/// Graham凸包算法, nlog
/// 事先把点集塞到pts中, 会改变点集的内容
/// 该算法保证结果中没有任意三点共线，这一点对计算面积和周长其实没用
/// 返回凸包上点的数量
int Graham(){    
    auto & pts = this->pts;
    int n = pts.size();

    /// 特判 
    if(1 == n) return 1;

    /// 求最下最左点
    auto lowleft = min_element(pts.begin(), pts.end(), [](const Point&a, const Point &b)->bool{
        int tmp = sgn(a.y - b.y);
        if(tmp) return tmp < 0;
        return a.x < b.x;
    });

    /// 将最下最左点设为pts[0]
    swap(*lowleft, pts[0]);

    /// 相对于最下最左点进行排序
    sort(++pts.begin(), pts.end(), [&](const Point&a, const Point&b)->bool{
        const int tmp = sgn(pts[0].cross(a, b));
        if(tmp) return tmp > 0; // 角度小的排在前面
        /// 角度一样，距离小的排在前面
        return sgn((a - pts[0]).square() - (b - pts[0]).square()) < 0;
    });

    /// 真正的Graham循环，本质上是一个栈
    int top = 2;
    for(int i=2;i<n;++i){
        while(top > 1 && sgn(pts[top-2].cross(pts[top-1], pts[i])) <= 0) --top;
        pts[top++] = pts[i];
    }
    pts.erase(pts.begin()+top, pts.end());
    
    // 验证一下
    n = pts.size();
    for(int i=0;i<n;++i){
        int prv = (i-1+n)%n;
        int nxt = (i+1)%n;
        if(is0(pts[i].cross(pts[prv], pts[nxt]))){
            throw runtime_error(to_string(i));
        }
    }

    return top;   
}


};

int N, L;
Convex Con;

Real proc(){
    int n = Con.Graham();
    Real ans = (PI + PI) * L;
    for(int i=0;i<n;++i){
        ans += Con.pts[i].dist(Con.pts[(i+1)%n]);
    }
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    int nofkase = getInt();
    while(nofkase--){
        N = getInt(); L = getInt();
        Con.input(N);
        printf("%.0Lf\n", proc());
        if(nofkase)printf("\n");
    }
    return 0;
}

