/**
 * 凸多边形碰撞检测，做闵可夫斯基差，转为
 * 点与凸多边形碰撞检测的问题
 * 转为线段与多边形相交的问题
 * 如果有交点，求距离最小的
 * 坐标达到1E9, 用longlong只能对30%
 * 要用int128，或者使用longdouble
 * 另外INF也要设置到1E10, 设置到1E9只能AC99%
 */
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
using llt = __int128_t;

Real const EPS = 1E-9; // 根据需要调整
Real const PI = acos(-1);
Real const INF = 1E10;  // 根据需要调整

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
/// 极角排序, [0, 36)
template<typename T> struct ArgCmp{
using Dian = Point<T>;

const Dian center; // 中心点, 默认是原点

ArgCmp(const Dian &a = Dian()):center(a){}

bool operator () (const Dian &a, const Dian &b) const {
    auto calLoc = [&](const Dian &p)->int{ // 计算象限        
        if(sgn(p.y) > 0) return 2; // (0, 180)
        if(sgn(p.y) < 0) return 4; // (180, 360)
        if(sgn(p.x) > 0) return 1; // 0度
        if(sgn(p.x) < 0) return 3; // 180度
        return 0; // 原点
    };

    const Dian da(a - center);
    const Dian db(b - center);
    const int aloc = calLoc(da);
    const int bloc = calLoc(db);
    if(aloc != bloc) return aloc < bloc;

    const auto chaji = sgn(da.cross(db));
    if(chaji) return chaji > 0; // 从a到b是逆时针 
    /// 到此说明幅角一致, 看长度
    return sgn(da.square() - db.square()) < 0;
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
    // T bb = b >= 0 ? b : -b;
    // T cc = c >= 0 ? c : -c;
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

/// 直线与点的位置关系
int relate(const Dian & p) const {
    return is0(a * p.x + b * p.y + c) ? IN : OUT;
}

/// 直线与线段AB的位置关系
int relate(const Dian & A, const Dian & B) const {
    int ra = sgn(this->eval(A));
    int rb = sgn(this->eval(B));
    if(0 == ra && 0 == rb) return JIAO & CHONGHE;
    if(0 == ra || 0 == rb) return JIAO & VERTEX;
    return ra * rb < 0 ? JIAO : OUT;
}

/// 点到直线的距离
Real dist(const Dian & p) const {
    return this->eval(p) / sqrt(a * a + b * b);
}

};

/** 5. 线段的结构体，线段有时也用两点表示 **/
template<typename T>struct LineSeg{

/// 为了节约模板参数, 重命名
using Dian = Point<T>;
using Xianduan = LineSeg<T>;
Dian s, e; // s和e不区分顺序

LineSeg(const Dian &A, const Dian &B):s(A),e(B){}

/// 点与线段的位置关系
int relate(const Dian & p) const {
    return p.relate(this->s, this->e);
}

/// 点与线段的距离
Real dist(const Dian & p) const {
    return p.dist2(this->s, this->e);
}

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

/// 线段与线段的位置关系, 只返回JIAO或者OUT
/// 要判断是否交于端点需要额外判断
int relate(const Xianduan & r) const {
    return this->relate(r.s, r.e);         
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

void init(int n){pts.resize(n);}

/// 点与简单多边形位置关系, O(N), 顺时针逆时针都能用
int relate(const Dian & p) const {
    int n = pts.size();

    /// 无穷远点构成的线段 
    Xianduan ls(p, Dian(INF, p.y));
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
        if(t > 0 && ls.relate(pts[nxt])) continue;
        if(t < 0 && ls.relate(pts[i])) continue;

        ++ans;
    }
    /// 奇内偶外
    return (ans & 1) ? IN : OUT;
}

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

/// 闵可夫斯基和，只能用于凸的
/// 对于两个凸多边形a和b,凸多边形c=a+b，即a和b中的所有点对相加
/// 返回一个凸多边形，为闵可夫斯基和，可能存共线点
const Tu operator + (const Convex & r) const {
    /// 极角排序，0-360 
    ArgCmp<T> cmp;
    /// 最下最左
    auto lowleft = [](const Dian &u, const Dian &v)->bool{
        int t = sgn(u.y - v.y);
        if(t) return t < 0;
        return u.x < v.x;
    };

    /// 主计算过程，将输入的多边形p拆分成向量,放入ans
    /// ans中的向量最终按照极角排序, 返回最下最左的编号
    auto calc = [&](const vt &p, int n, Dian ans[])->int{
        int kll = 0; // 最下最左
        int jll = 0; // 最小角
        for(int i=0;i<n;++i){
            ans[i] = p[(i+1)%n] - p[i];
            if(lowleft(p[i], p[kll])) kll = i;
            if(cmp(ans[i], ans[jll])) jll = i;
        }
        rotate(ans, ans+jll, ans+n);
        return kll;
    };
    
    /// 参数
    const auto & pa = this->pts;
    const auto & pb = r.pts;
    int na = pa.size(), nb = pb.size();

    /// 返回值
    Tu ret(na+nb);
    auto & pc = ret.pts;
    int nc = pc.size();    

    /// 先拆pa, 再拆pb
    int ka = calc(pa, na, pc.data());
    int kb = calc(pb, nb, pc.data()+na);
    /// 归并
    inplace_merge(pc.begin(), pc.begin()+na, pc.begin()+na+nb, cmp);
    /// 再将pc依次连接起来即可，pc中可能存在共线的点
    pc[0].x += pa[ka].x + pb[kb].x;
    pc[0].y += pa[ka].y + pb[kb].y;

    for(int i=1;i<nc;++i){
        pc[i].x += pc[i-1].x;
        pc[i].y += pc[i-1].y;
    }
    return ret;    
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

using Vector = Point64I;

int N, M;

Convex<llt> Ca, Cb, Cc;

auto & A = Ca.pts;
auto & B = Cb.pts;

Vector SpeedA, SpeedB;
Vector Speed;


void proc(){
    /// 求闵可夫斯基和
    Cc = Ca + Cb;

    /// 原点是否在多边形内
    static const Point64I origin(0, 0);
    if(IN & Cc.relate(origin)){
        return (void)puts("0");
    }

    /// 求原点的速度
    Vector speed(SpeedB - SpeedA);
    /// 取轨迹上的无穷远点
    Point64I inf(speed.x * INF, speed.y * INF);
    /// 轨迹的直线和线段
    Line<llt> track(origin, inf);
    LineSeg<llt> xianduan(origin, inf);

    /// 求线段(origin, inf)与多边形的最近的交点
    Real ans = -1, tmp;
    Point64F p;
    for(int t,i=0,n=Cc.pts.size();i<n;++i){
        /// 如果线段相交则求一个交点
        if(JIAO & xianduan.relate(Cc.pts[i], Cc.pts[(i+1)%n])){
            t = track.relate(Line<llt>(Cc.pts[i], Cc.pts[(i+1)%n]), &p);
            if(t & JIAO){
                tmp = p.length();
            }else if(t & CHONGHE){
                /// 碰撞点必然是C[i]或者C[i+1]
                tmp = min(Cc.pts[i].length(), Cc.pts[(i+1)%n].length());
            }else{
                throw runtime_error("XX");
            }            
            if(ans < 0 || tmp < ans) ans = tmp;
        }
    }
    if(ans < 0) return (void)puts("-1");
    return (void)(cout << fixed << setprecision(12) << ans / speed.length() << endl);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    Ca.init(N = getInt());
    for(int i=0;i<N;++i) A[i].x = getInt(), A[i].y = getInt();
    Cb.init(M = getInt());
    for(int i=0;i<M;++i) B[i].x = -getInt(), B[i].y = -getInt();

    SpeedA.x = getInt(), SpeedA.y = getInt();
    SpeedB.x = getInt(), SpeedB.y = getInt();

    proc();
    return 0;
}
