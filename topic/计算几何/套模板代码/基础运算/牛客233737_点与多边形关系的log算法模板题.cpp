#include <bits/stdc++.h>
using namespace std;

/**
 * @brief 二维平面几何
 * @version 20220812, 模板类, 函数尽量作为成员函数, 可以少写模板参数
 * 1. typedef和常数
 * 2. 处理边界的数学库函数
 * 3. 点与向量的结构体以及基本运算，算术运算, 关系运算, 点积和叉积
 * 4. 直线的结构体
 * 5. 线段的结构体，线段有时也用两点表示
 * 6. 多边形与凸多边形, 凸包, 闵可夫斯基和与旋转卡壳法
 * 7. 半平面交排序增量法
 * 持续更新...
 * 题目列表:
 * 基础运算
 * LuoguP1355: 点在三角形内
 * 牛客207032: 直线的位置关系, 2个方法
 * 牛客220476: 线段相交, 2个方法
 * 牛客233186: 凸多边形的距离，闵可夫斯基和，GJK算法
 * 牛客233737: 点在凸多边形内，log算法
 * 半平面
 * 牛客233170UVA1396UVALive3890: 半平面移动, 半平面交, 二分
 * 牛客234015: 半平面交二分
 * 凸包
 * 牛客233135: 凸包求周长
 * 旋转卡壳
 * 牛客232791: 凸包最小矩形覆盖求面积
 * 牛客233136: 凸包旋转卡壳求直径
 * contest
 * 牛客20057: 凸包最小矩形覆盖求矩形
 * 牛客19905: 半平面交求面积
 * 牛客233171: 半平面交求周长
 * 牛客2022暑假3G: 凸多边形碰撞检测, 闵可夫斯基何, GJK算法
 */

/** 1. typdef和常数 **/
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

/** 3. 点与向量的结构体以及基本运算，相等，叉积，点积 **/
/// 模板类, 可以实例化成整型或者实型
template<typename T>struct Point{

T x, y;
Point(T a=0, T b=0):x(a),y(b){}
/// 整型注意有可能超范围
T square() const {return x * x + y * y;}
/// 长度必须是实型
Real length() const {return sqrt((Real)this->square());}
void normSelf() { // 单位化, 必须是实型
    T tmp = this->square();
    if(is0(tmp - 1)) return;
    Real t = sqrt((Real)tmp);
    this-> x /= t, this->y /= t;
}
bool isZero() const {return is0(x) && is0(y);}
/// 算术运算加减乘
const Point operator + (const Point & r) const {return Point(x + r.x, y + r.y);}
const Point operator - (const Point & r) const {return Point(x - r.x, y - r.y);}
const Point operator * (T k) const {return Point(x * k, y * k);}
/// 关系运算
bool operator == (const Point & r) const {return is0(x - r.x) && is0(y - r.y);}
/// 向量叉积, this 叉 r
T cross(const Point & r) const {return x * r.y - y * r.x;}
/// 向量点积
T dot(const Point & r) const {return x * r.x + y * r.y;}
/// 点的叉积, this作为点O, OA 叉 OB
T cross(const Point &A, const Point &B) const {return (A - *this).cross(B - *this);}
/// 点的点积
T dot(const Point &A, const Point &B) const {return (A - *this).dot(B - *this);}
/// 距离的平方
T dist2(const Point & r) const {return (*this-r).square();}
/// 距离, 必须是实数
Real dist(const Point & r) const {return (*this-r).length();}
/// this与线段AB的位置关系
int relate(const Point &A, const Point &B) const {
    assert(!(A == B));
    if(A == *this || B == *this) return IN | VERTEX;
    if(sgn(this->dot(A, B)) <= 0 && 0 == sgn(this->cross(A, B))){
        return IN | EDGE;
    }
    return OUT;
}
/// this与线段AB的距离
Real dist(const Point &A, const Point &B) const {
    if(IN & this->relate(A, B)) return 0;
    if(sgn(A.dot(*this, B)) <= 0) return this->dist(A);
    if(sgn(B.dot(*this, A)) <= 0) return this->dist(B);
    /// 距离为高
    return fabs(this->cross(A, B)) / (A - B).length();
}


};


/** 6. 多边形, 简单多边形和凸多边形和凸包 **/
/// 简单多边形
template<typename T>struct Polygon{

using Dian = Point<T>;
// using Xianduan = LineSeg<T>;
using vt = vector<Dian>;

vt pts; // 端点数组, 保证没有多余的长度, 即size() == n

Polygon() = default;
Polygon(int n):pts(n, Dian()){}

/// 前一个点和后一个点的编号, 这样就无需设计pts[n] == pts[0]
int next(int i) const {return this->pts.size() == ++i ? 0 : i;}
int prev(int i) const {return -1 == --i ? this->pts.size() - 1 : i;}

void init(int n){pts.resize(n);}

};

/// 凸多边形和凸包
template<typename T>struct Convex : public Polygon<T>{

using Dian = Point<T>;
// using Zhixian = Line<T>;
using vt = vector<Dian>;
using Tu = Convex<T>;

Convex():Polygon<T>(){}
Convex(int n):Polygon<T>(n){}

/// 点是否在凸多边形内, log算法, 必须是逆时针
int relate(const Dian & p) const {
    const auto & pts = this->pts;
    int n = pts.size();

    /// 特判
    if(1 == n) return (p == pts[0]) ? (IN | VERTEX) : OUT;
    if(2 == n) return p.relate(pts[0], pts[1]);
    /// 一点点保证
    assert(sgn(pts[0].cross(pts[1], pts[2])) >= 0);
    /// p到点1是逆时针，则p必然在外面
    if(sgn(pts[0].cross(p, pts[1])) > 0) return OUT;
    /// p到点n-1是顺时针，则p必然在外面
    if(sgn(pts[0].cross(p, pts[n-1])) < 0) return OUT;
    // 二分
    int left = 1, right = n - 2, mid;
    do{
        mid = (left + right) >> 1;
        assert(mid > 0 && mid + 1 < n);
        T t1 = pts[0].cross(pts[mid], p);
        T t2 = pts[0].cross(pts[mid+1], p);
        /// p 必然在(mid, mid+1)之间
        if(sgn(t1) >= 0 && sgn(t2) <= 0){
            /// 要特判是否在(0,1)边上
            if(1 == mid){
                int r = p.relate(pts[0], pts[1]);
                if(r != OUT) return r;
            }
            /// 要特判是否在(n-1, 0)边上
            if(mid + 1 == n - 1){
                int r = p.relate(pts[n-1], pts[0]);
                if(r != OUT) return r;
            }
            /// 算叉积
            T chaji = p.cross(pts[mid], pts[mid+1]);
            int r = sgn(chaji);
            if(r > 0) return IN;
            if(r < 0) return OUT;
            /// 此时必然在(mid, mid+1)边上
            r = p.relate(pts[mid], pts[mid+1]);
            assert(r == (IN | VERTEX) || r == (IN | EDGE));
            return r;
        }
        /// 二分
        if(t1 < 0) right = mid - 1;
        else left = mid + 1;         
    }while(left <= right);
    return OUT;
}


};

using Point64I = Point<llt>;
using Point64F = Point<Real>;

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
int const SIZE = 1E5+10;
#endif

int N, M;
Convex<llt> Con;
auto & A = Con.pts;

char Output[2][10] = {"NO", "YES"};

char const * const proc(){
    M = getInt();
    Point64I p;
    for(int t,i=0;i<M;++i){
        p.x = getInt(), p.y = getInt();
        t = Con.relate(p);
        if(IN != t){
            return Output[0];
        }
    }
    return Output[1];
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    Con.init(N = getInt());
    /// 题目是顺时针，反过来读取保证逆时针
    for(int i=N-1;i>=0;--i){
        A[i].x = getInt();
        A[i].y = getInt();
    }
    puts(proc());
    return 0;
}
