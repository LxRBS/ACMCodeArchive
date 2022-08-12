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
    if(A == *this || B == *this) return IN & VERTEX;
    if(sgn(this->dot(A, B)) <= 0 && 0 == sgn(this->cross(A, B))){
        return IN & EDGE;
    }
    return OUT;
}
/// this与线段AB的距离
Real dist(const Point &A, const Point &B) const {
    if(IN & this->relate(A, B)) return 0;
    if(sgn(A.dot(*this, B)) <= 0) return this->dist(A);
    if(sgn(B.dot(*this, A)) <= 0) return this->dist(B);
    /// 距离为高
    return sqrt(this->cross(A, B) / (A - B).square());
}


};

/** 4. 直线的结构体 **/
template<typename T>struct Line{

using Dian = Point<T>;
using Zhixian = Line<T>;

T a, b, c; // 对于整点而言, 必然存在满足条件的abc为整数

Line() = default;

/// 两点确定一条直线
Line(const Dian &A, const Dian &B, bool needNorm=false){
    assert(!(A == B));
    /// 用仿射坐标生成
    this->a = A.y - B.y;
    this->b = B.x - A.x;
    this->c = A.x * B.y - B.x * A.y; 
    
    if(needNorm) normSelf();
}

/// 给定基点p和方向向量d, 生成直线
static Zhixian create(const Dian &p, const Dian &d, bool needNorm=false){
    return Zhixian(p, p+d, needNorm);
}

/// 归一化, 可以用于stl的数据结构, 必须是整型
void normSelf() {
    // T aa = a >= 0 ? a : -a;
    // T bb = b >= 0 ? b : -c;
    // T cc = c >= 0 ? b : -c;
    // T g = 0;
    // if(0 == aa){ // bb 必然不为0
    //     if(0 == cc) g = bb;
    //     else g = __gcd(bb, cc);
    // }else if(0 == bb){
    //     if(0 == cc) g = aa;
    //     else g = __gcd(aa, cc);
    // }else{
    //     g = __gcd(aa, bb);
    //     if(cc) g = __gcd(g, cc);
    // }
    // this->a /= g, this->b /= g, this->c /= g;
    // if(a < 0 || (0 == a && b < 0)) {a = -a, b = -b, c = -c;}
}

T eval(const Dian &p) const {return a * p.x + b * p.y + c;}

/// 两条直线的位置关系, 相交还能返回交点, 交点只能是实型 
int relate(const Line & r, Point<Real> *pk=nullptr) const {
    T x = b * r.c - c * r.b; // 整型有可能溢出
    T y = r.a * c - r.c * a;
    T t = a * r.b - b * r.a;
    if(is0(t)){
        if(is0(x) && is0(y)) return CHONGHE;
        return PINGXING;
    }
    if(pk) pk->x = (Real)x / t, pk->y = (Real)y / t;
    return JIAO;
}

};

/** 5. 线段的结构体，线段有时也用两点表示 **/
template<typename T>struct LineSeg{

/// 为了节约模板参数, 重命名
using Dian = Point<T>;
using Xianduan = LineSeg<T>;
Dian s, e; // s和e不区分顺序


/// 线段与线段的位置关系, 只返回JIAO或者OUT
/// 要判断是否交于端点需要额外判断
int relate(const Dian &A, const Dian &B) const {
    return sgn(min(s.x, e.x) - max(A.x, B.x)) <= 0
        && sgn(min(s.y, e.y) - max(A.y, B.y)) <= 0
        && sgn(min(A.x, B.x) - max(s.x, e.x)) <= 0
        && sgn(min(A.y, B.y) - max(s.y, e.y)) <= 0
        && sgn(s.cross(A, e)) * sgn(s.cross(e, B)) >= 0
        && sgn(A.cross(s, B)) * sgn(A.cross(B, e)) >= 0
        ? JIAO : OUT;
}


};

/** 6. 多边形, 简单多边形和凸多边形和凸包 **/
/// 简单多边形
template<typename T>struct Polygon{

using Dian = Point<T>;
using Xianduan = LineSeg<T>;
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
using Zhixian = Line<T>;
using vt = vector<Dian>;
using Tu = Convex<T>;

Convex():Polygon<T>(){}
Convex(int n):Polygon<T>(n){}

/// 点是否在凸多边形内, log算法, 必须是逆时针
int relate(const Dian & p) const {
    const auto & pts = this->pts;
    int n = pts.size();

    /// 特判
    if(1 == n) return (p == pts[0]) ? (IN & VERTEX) : OUT;
    if(2 == n) return p.relate(pts[0], pts[1]);
    /// 一点点保证
    assert(sgn(pts[0].cross(pts[1], pts[2])) >= 0);
    /// p到点1是逆时针，则p必然在外面
    if(sgn(pts[0].cross(p, pts[1])) >= 0) return OUT;
    /// p到点n-1是顺时针，则p必然在外面
    if(sgn(pts[0].cross(p, pts[n-1])) <= 0) return OUT;
    // 二分
    int left = 0, right = n - 2, mid;
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

/// Graham凸包算法, 
/// 事先把点集塞到pts中, 会改变点集的内容
/// 该算法保证结果中没有任意三点共线，这一点对计算面积和周长其实没用
/// nlogn
int Graham(){    
    auto & pts = this->pts;
    int n = pts.size();

    /// 特判 
    if(1 == n) return 1;

    /// 求最下最左点
    auto lowleft = min_element(pts.begin(), pts.end(), [](const Dian&a, const Dian &b)->bool{
        int tmp = sgn(a.y - b.y);
        if(tmp) return tmp < 0;
        return a.x < b.x;
    });

    /// 将最下最左点设为pts[0]
    swap(*lowleft, pts[0]);

    /// 相对于最下最左点进行排序
    sort(++pts.begin(), pts.end(), [&](const Dian&a, const Dian&b)->bool{
        const int tmp = sgn(pts[0].cross(a, b));
        if(tmp) return tmp > 0; // 角度小的排在前面
        /// 角度一样，距离小的排在前面
        return sgn((a - pts[0]).square() - (b - pts[0]).square()) < 0;
    });

    /// 真正的Graham循环，本质上是一个栈
    int top = 2;
    for(int i=2;i<n;++i){
        while(top > 1 && sgn(pts[top-2].cross(pts[top-1], pts[i])) <= 0){
            --top;
        }
        pts[top++] = pts[i];
    }
    /// 去掉最后一条边上有可能共线的点
    if(top >= 3 && 0 == sgn(pts[0].cross(pts[top-1], pts[top-2]))){
        --top;
    }
    pts.erase(pts.begin()+top, pts.end());
    return top; // 一定要赋值    
}

/// 旋转卡壳法求最小覆盖矩形, 
/// 即找到一个矩形完全盖住凸多边形p, 且该矩形面积是最小的
/// 返回最小面积, pans中记录4个点，为矩形, 点必须是实型
/// p保证是逆时针, 顺时针需要更改while中的关系符号
Real rcRecatangle(Point<Real> pans[] = nullptr, const Real inf=INF) const {
    const auto & p = this->pts;
    int const n = p.size();

    if(1 == n){ // 一个点的特殊情况
        return 0;
    }
    if(2 == n){ // 二个点的特殊情况
        return 0;
    }
    /// 初步确定最上点
    int t = 1; // 分别是最左、最右、最上点
    while(t < n && sgn(p[0].cross(p[1], p[t]) - p[0].cross(p[1], p[(t+1)%n])) <= 0){
        ++t;
    }
    if(t == n){ /// 说明都在一条直线上
        return 0;
    }
    /// 初步最左和最右
    int l = t, r = 1;
    Real ans = inf;
    for(int i=0;i<n;++i){
        /// 找另外三个卡点
        const auto vec = p[(i+1)%n] - p[i];
        while(vec.dot(p[(r+1)%n]-p[r]) >= 0){
            r = (r + 1) % n;
        }
        while(sgn(p[i].cross(p[(i+1)%n], p[t]) - p[i].cross(p[(i+1)%n], p[(t+1)%n])) <= 0){
            t = (t + 1) % n;
        }
        while(vec.dot(p[(l+1)%n]-p[l]) <= 0){
            l = (l + 1) % n;
        }
        /// 矩形为(i,i+1)边所在的直线且卡住t,l,r三个点
        /// 矩形的面积就是t到(i,i+1)的距离乘以向量(l, r)在(i,i+1)上投影的长度
        Real chang = fabs(p[i].cross(p[(i+1)%n], p[t]) / vec.length()); 
        Real kuan = fabs(vec.dot(p[r] - p[l]) / vec.length());
        Real tmp = chang * kuan;
        if(tmp < ans){
            ans = tmp;
            /// 记录点
            if(pans != nullptr){
                /// 底部的方向向量, 和左右的方向向量
                Dian diDirection(p[(i+1)%n].x - p[i].x, p[(i+1)%n].y - p[i].y);
                Dian zuoDirection(-diDirection.y, -diDirection.x);
                /// 底部的直线
                Zhixian bLine(p[i], diDirection);
                /// 右侧的直线
                Zhixian rLine(p[r], zuoDirection);
                /// 上部直线
                Zhixian tLine(p[t], diDirection);
                /// 左侧直线
                Zhixian lLine(p[l], zuoDirection);
                /// 4个交点
                int c919 = bLine.relate(rLine, pans);
                c919 &= rLine.relate(tLine, pans+1);
                c919 &= tLine.relate(lLine, pans+2);
                c919 &= lLine.relate(bLine, pans+3);
                assert(IN & c919);
            }
        }
    }
    return ans;
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

int N;
Convex<Real> Con;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    scanf("%d", &N);
	Con.init(N);
	auto & P = Con.pts;
    for(int i=0;i<N;++i)scanf("%Lf%Lf", &P[i].x, &P[i].y);
    
    int n = Con.Graham();
    Real ans = Con.rcRecatangle();
    cout << fixed << setprecision(12) << ans << endl;
    return 0;
}

