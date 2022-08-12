#include <bits/stdc++.h>
using namespace std;

/**
 * @brief 二维平面几何
 * @version 20220810
 * 1. typedef和常数
 * 2. 处理边界的数学库函数
 * 3. 点与向量的结构体以及基本运算，相等，叉积，点积
 * 4. 线段、直线、参数线的结构体，线段有时也用两个点表示, 多边形一律用点的数组表示
 * 5. 位置关系函数，一律用relation做函数名，
 * 6. 求距离，一律用dist做函数名
 * 7. Graham凸包算法
 * 8. 半平面交排序增量法
 * 9. 闵可夫斯基和，凸多边形之间的距离
 * 10. 旋转卡壳法，凸多边形的直径，凸多边形的最大三角形，凸多边形的最小矩形覆盖，函数名都以rc开头
 * 持续更新...
 * 题目列表:
 * 基础运算
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
using coor = llt;  // 默认是整数坐标
// using coor = Real; // 有时需要使用实数坐标

Real const EPS = 1E-9; // 根据需要调整
Real const PI = acos(-1);
coor const INF = 1E9;  // 根据需要调整

inline int sgn(Real x){return x >= EPS ? 1 : (x <= -EPS ? -1 : 0);}
inline bool is0(Real x){return 0 == sgn(x);}

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
struct Point{
    coor x, y;
    Point(coor a=0, coor b=0):x(a),y(b){}
    coor square() const { // 有时数据会超范围, 即使使用longlong
        return this->x * this->x + this->y * this->y;
    }
    Real length() const { // 算长度肯定用实数
        return sqrt((Real)this->square());
    }
    void normSelf() { // 单位化, 只有实数坐标才能单位化
        Real tmp = this->square();
        if(is0(tmp - 1)) return;
        tmp = sqrt(tmp);
        this->x /= tmp, this->y /= tmp;
    }
    bool isZero()const{
        return is0(x) && is0(y);
    }
};
using Vector = Point;

/// 相等
bool operator == (const Vector & a, const Vector & b){
    // return a.x == b.x && a.y == b.y;
    return is0(a.x - b.x) && is0(a.y - b.y);
}

/// 向量的加法
const Vector operator + (const Vector &u, const Vector &v){
    return Vector(u.x + v.x, u.y + v.y);
}

/// 向量的减法 
const Vector operator - (const Vector &u, const Vector &v){
    return Vector(u.x - v.x, u.y - v.y);
}

/// 向量的倍乘
const Vector operator * (const Vector &u, coor k){
    return Vector(u.x * k, u.y * k);
}

/// OA 叉 OB
coor cross(const Point &O, const Point &A, const Point &B){
    auto xoa = A.x - O.x, yoa = A.y - O.y;
    auto xob = B.x - O.x, yob = B.y - O.y;
    return xoa * yob - xob * yoa;
}

/// OA 点 OB
coor dot(const Point &O, const Point &A, const Point &B){
    auto xoa = A.x - O.x, yoa = A.y - O.y;
    auto xob = B.x - O.x, yob = B.y - O.y;
    return xoa * xob + yoa * yob;
}

/// 向量的点积
coor dot(const Vector &u, const Vector &v){
    return u.x * v.x + u.y * v.y;
}

/// 向量的叉积
coor cross(const Vector &u, const Vector &v){
    return u.x * v.y - v.x * u.y;
}

/** 5 位置关系函数 **/
int const OUT = 0; // 没有公共点，即不相交
int const IN = 1; // 点在各种图形内
int const INTER = 2; // 直线与直线，线段与线段，直线与线段
int const PINGXING = 4; // 直线与直线
int const CHONGHE = 8; // 直线与直线
int const VERTEX = 0x10; // 表示点还在图形的端点上
int const EDGE = 0x20; // 表示点还在图形的边上

/// 点p是否在线段AB上, 返回IN表示在, 附带有VERTEX|EDGE表示在点上或者边上
/// 返回OUT表示点与线段AB没有公共点
int relation(const Point &p, const Point &A, const Point &B){
    assert(!(A == B));
    if(p == A || p == B) return VERTEX | IN;
    return 0 == cross(p, A, B)
        && sgn(min(A.x, B.x) - p.x) <= 0 && sgn(p.x - max(A.x, B.x)) <= 0
        && sgn(min(A.y, B.y) - p.y) <= 0 && sgn(p.y - max(A.y, B.y)) <= 0
        ? (IN | EDGE) : OUT;
}

/// 点p是否在凸多边形内，这是一个O(logN)的算法
/// 注意log算法要求poly必须是逆时针
/// 如果是顺时针需要改变叉积的判断
/// 返回IN | VERTEX | EDGE, 或者OUT
int relation(const Point &p, const Point poly[], int n){
    /// 特判
    if(1 == n) return p == poly[0] ? (IN | VERTEX) : OUT;
    if(2 == n) return relation(p, poly[0], poly[1]);

    /// p到poly[1]是逆时针，p必然在外面
    if(sgn(cross(poly[0], p, poly[1])) > 0) return OUT;
    /// 同理
    if(sgn(cross(poly[0], poly[n-1], p)) > 0) return OUT;
    
    int left = 1, right = n - 2, mid;
    do{
        mid = (left + right) >> 1;
        assert(mid > 0 && mid + 1 < n);
        const auto t1 = cross(poly[0], poly[mid], p);
        const auto t2 = cross(poly[0], poly[mid+1], p);
        if(sgn(t1) >= 0 && sgn(t2) <= 0){ // 说明p必然在(mid,mid+1)之间
            /// 要特判是否在(0,1)边上
            if(1 == mid){
                int r = relation(p, poly[0], poly[1]);
                if(r != OUT) return r;
            }
            /// 要特判是否在(n-1, 0)边上
            if(mid + 1 == n - 1){
                int r = relation(p, poly[n-1], poly[0]);
                if(r != OUT) return r;
            }
            /// 算叉积
            const auto chaji = cross(p, poly[mid], poly[mid+1]);
            int r = sgn(chaji);
            if(r > 0) return IN;
            if(r < 0) return OUT;
            /// 此时必然在(mid, mid+1)边上
            r = relation(p, poly[mid], poly[mid+1]);
            assert(r == (IN | VERTEX) || r == (IN | EDGE));
            return r;
        }
        if(t1 < 0) right = mid - 1;
        else left = mid + 1; 
    }while(left <= right);
    return OUT;
}

/// 线段AB和CD是否相交, 快速排斥和跨立, Real版本
int relation(const Point &A, const Point &B, const Point &C, const Point &D){
    return sgn(min(A.x, B.x) - max(C.x, D.x)) <= 0
        && sgn(min(A.y, B.y) - max(C.y, D.y)) <= 0
        && sgn(min(C.x, D.x) - max(A.x, B.x)) <= 0
        && sgn(min(C.y, D.y) - max(A.y, B.y)) <= 0
        && sgn(cross(A, C, B)) * sgn(cross(A, B, D)) >= 0
        && sgn(cross(C, B, D)) * sgn(cross(C, D, A)) >= 0
        ? INTER : OUT;
}

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

Point Poly[4], P;

int proc(){    
    if(cross(Poly[0], Poly[1], Poly[2]) < 0) swap(Poly[1], Poly[2]);
    int r = relation(P, Poly, 3);
    if(r & VERTEX) return 4;
    if(r & EDGE) return 3;
    if(r & IN) return 1;
    assert(OUT == r);
    return 2;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    for(int i=0;i<3;++i){
        Poly[i].x = getInt();
        Poly[i].y = getInt();
    }
    P.x = getInt(), P.y = getInt();
    cout << proc() << endl;
    return 0;
}

