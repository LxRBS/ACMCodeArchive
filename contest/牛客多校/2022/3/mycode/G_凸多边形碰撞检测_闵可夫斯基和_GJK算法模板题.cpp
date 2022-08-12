/**
 * 凸多边形碰撞检测，做闵可夫斯基差，转为
 * 点与凸多边形碰撞检测的问题
 * 转为线段与多边形相交的问题
 * 如果有交点，求距离最小的
 */
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
 * 牛客220476: 线段相交
 * 牛客207032: 直线的位置关系
 * 牛客232575: 线段与简单多边形相交
 * 牛客233135: 凸包求周长
 * 牛客233136: 凸包旋转卡壳求直径
 * 牛客20057: 凸包最小矩形覆盖求矩形
 * 牛客232791: 凸包最小矩形覆盖求面积
 * 牛客233186: 凸多边形的距离，闵可夫斯基和，GJK算法
 * 牛客2022暑假3G: 凸多边形碰撞检测, 闵可夫斯基何, GJK算法
 * 牛客233737: 点在凸多边形内，log算法
 * 牛客19905: 半平面交求面积
 * 牛客233170UVA1396UVALive3890: 半平面移动, 半平面交, 二分
 * 牛客233171: 半平面交求周长
 * 牛客234015: 半平面交二分
 */

/** 1. typdef和常数 **/
using Real = long double;
using llt = long long;
// using coor = llt;  // 默认是整数坐标
using coor = Real; // 有时需要使用实数坐标

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

/** 4. 线段、直线、参数线的结构体 **/
struct LineSeg{
    Point s, e; // 不区分端点的顺序
    LineSeg(){}
    LineSeg(const Point &a, const Point &b):s(a), e(b){
        assert(!(a == b));
    }
};

struct Line{
    coor a, b, c; // ax+by+c=0, 如果生成点是整点, 则abc必有整数解
    Point s, e; // 保存两个生成点
    Line(){}
    /// 两点确定一条直线，保证u!=v
    /// 给定整点必然存在整数abc确定直线
    Line(const Point &u, const Point &v):s(u),e(v){
        assert(!(u == v));
        /// 用仿射坐标生成
        this->a = u.y - v.y;
        this->b = v.x - u.x;
        this->c = u.x * v.y - v.x * u.y;
    }
};

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

/// 点p是否在线段ls上
int relation(const Point &p, const LineSeg &ls){
    return relation(p, ls.s, ls.e);
}

/// 点p是否在直线line上
int relation(const Point &p, const Line &line){
    // return 0 == p.x * line.a + p.y * line.b + line.c ? IN : OUT;
    return is0(p.x * line.a + p.y * line.b + line.c) ? IN : OUT;
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

/// 点是否在简单多边形poly内, 保证poly[n] == poly[0]
/// 简单的说就是线段(p, inf)与多边形的交点的数量, O(n)
int relationSimple(const Point &p, const Point poly[], int n){
    assert(poly[n] == poly[0]);
    /// 无穷远点
    Point inf(INF, p.y);
    int ans = 0;
    /// 依次相交
    for(int t,r,i=0;i<n;++i){
        r = relation(p, poly[i], poly[i+1]);
        if(r) return r; // 表示点在该边上

        /// 如果是水平边, 忽略
        t = sgn(poly[i].y - poly[i+1].y);
        if(0 == t) continue;

        /// 不相交忽略
        r = relation(p, inf, poly[i], poly[i+1]);
        if(OUT == r) continue;

        /// 如果交点是该边比较高的那个点也忽略
        if(t > 0 && relation(poly[i], p, inf) != OUT) continue;
        if(t < 0 && relation(poly[i+1], p, inf) != OUT) continue;

        /// 到此需要计数
        ++ans;
    }
    /// 奇数在内, 偶数在外
    return (ans & 1) ? IN : OUT;
}

/// 线段a和b是否相交
int relation(const LineSeg &a, const LineSeg &b){
    return relation(a.s, a.e, b.s, b.e);
}

/// 线段和直线是否相交，跨立即可
int relation(const LineSeg &ls, const Line &line){
    if((IN & relation(ls.s, line)) && (IN & relation(ls.e, line))){
        return IN; // 如果线段的两个点都在直线上，在线段也在直线上
    }
    return sgn(cross(line.s, ls.s, line.e)) * sgn(cross(line.s, line.e, ls.e)) >= 0 ? INTER : OUT;
}

/// 线段与凸多边形的关系
/// poly是n凸多边形,且必须保证poly[n]==poly[0]!!!
int relation(const LineSeg &ls, const Point poly[], int n){
    int rs = relation(ls.s, poly, n);
    int re = relation(ls.e, poly, n);
    if(IN & rs){
        if(IN & re) return IN; // 都在内部，则线段肯定在内部
        return INTER; // 一内一外是相交
    }else if(IN & re){ // 仍然是一内一外
        return INTER;
    }
    /// 两外的情况
    for(int i=0;i<n;++i){
        if(INTER & relation(ls.s, ls.e, poly[i], poly[i+1])){
            return INTER; // 相交
        }
    }
    return OUT; // 没有公共点
}

/// 直线u和v的位置关系，如果相交，还可以返回交点
/// 直线可以用整点, 但交点不能保证整数, 用一个pair带出来
/// 仿射坐标算法
int relation(const Line &u, const Line &v, pair<Real, Real> *pk=nullptr){
    const auto x = u.b * v.c - v.b * u.c;
    const auto y = v.a * u.c - u.a * v.c;
    const auto t = u.a * v.b - v.a * u.b;
    if(is0(t)){
        if(is0(x) && is0(y)) return CHONGHE; // 重合
        return PINGXING; // 平行
    } 
    if(pk != nullptr) pk->first = (Real)x / (Real)t, pk->second = (Real)y / (Real)t;
    return INTER; // 相交
}

/** 6 求距离 dist函数 **/
/// 点点距离的平方, 有可能超范围
coor dist2(const Point &u, const Point &v){
    const auto x = u.x - v.x;
    const auto y = u.y - v.y;
    return x * x + y * y;
}

/// 点点之间的距离
Real dist(const Point &u, const Point &v){
    return sqrt(Real(dist2(u, v)));
}

/// 点p到线段AB的距离
Real dist(const Point &p, const Point &A, const Point &B){
    assert(!(A == B));
    if(IN & relation(p, A, B)) return 0;
    /// 计算点积
    auto tmp = dot(A, B, p);
    if(sgn(tmp) < 0) return dist(A, p);
    tmp = dot(B, A, p);
    if(sgn(tmp) < 0) return dist(B, p);
    /// 到此处说明是垂直距离
    return fabs(cross(p, A, B)) / dist(A, B);
}

/// 点到线段的距离
Real dist(const Point &p, const LineSeg &ls){
    return dist(p, ls.s, ls.e);
}

/// 点到直线的距离
Real dist(const Point &p, const Line &line){
    return fabs(cross(p, line.s, line.e)) / dist(line.s, line.e);
}

/** 9 闵可夫斯基和 **/
/// 闵可夫斯基和，只能用于凸的
/// 对于两个凸多边形a和b,凸多边形c=a+b，即a和b中的所有点对相加
/// 保证pa[na]==pa[0]且pb[nb]==pb[0]
/// 返回一个凸多边形，为闵可夫斯基和，可能存共线点
int Minkowski(const Point pa[], int na, const Point pb[], int nb, Point pc[]){
    /// 最下最左
    auto lowleft = [](const Point &u, const Point &v)->bool{
        int t = sgn(u.y - v.y);
        if(t) return t < 0;
        return u.x < v.x;
    };
    /// 计算象限
    auto loc = [](const Point &p)->int{
        if(is0(p.y)) return p.x > 0 ? 0 : 4;
        if(is0(p.x)) return p.y > 0 ? 2 : 6;
        if(p.x > 0) return p.y > 0 ? 1 : 7;
        return p.y > 0 ? 3 : 5;
    };
    /// 极角排序，0-360 
    auto cmp = [&](const Point &u, const Point &v)->bool{
        int uloc = loc(u), vloc = loc(v);
        if(uloc != vloc) return uloc < vloc;
        /// 同一个区域计算叉积
        auto chaji = sgn(u.x * v.y - v.x * u.y);
        return chaji > 0;
    };
    /// 主计算过程，将输入的多边形p拆分成向量,放入ans
    /// ans中的向量最终按照极角排序, 返回最下最左的编号
    auto calc = [&](const Point p[], int n, Point ans[])->int{
        int kll = 0; // 最下最左
        int jll = 0; // 最小角
        for(int i=0;i<n;++i){
            ans[i] = {p[i+1].x - p[i].x, p[i+1].y - p[i].y};
            if(lowleft(p[i], p[kll])) kll = i;
            if(cmp(ans[i], ans[jll])) jll = i;
        }
        rotate(ans, ans+jll, ans+n);
        return kll;
    };
    
    /// 保证
    assert(pa[na] == pa[0] && pb[nb] == pb[0]);

    /// 先拆pa, 再拆pb
    int ka = calc(pa, na, pc);
    int kb = calc(pb, nb, pc+na);
    /// 归并
    inplace_merge(pc, pc+na, pc+na+nb, cmp);
    /// 再将pc依次连接起来即可，pc中可能存在共线的点
    pc[0].x += pa[ka].x + pb[kb].x;
    pc[0].y += pa[ka].y + pb[kb].y;

    int nc = na + nb;
    for(int i=1;i<nc;++i){
        pc[i].x += pc[i-1].x;
        pc[i].y += pc[i-1].y;
    }
    return nc;
}

/// 两个凸多边形的距离
/// GJK算法，凸多边形距离等于原点到闵可夫斯基差的距离
/// 空着
Real dist(const Point pa[], int na, const Point pb[], int nb){
    assert(0);
    return -1;
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

int N, M;
Point A[SIZE], B[SIZE];
Point C[SIZE+SIZE];
Vector SpeedA, SpeedB;
Vector Speed;

void proc(){
    /// 求闵可夫斯基和
    A[N] = A[0]; B[M] = B[0];
    int n = Minkowski(A, N, B, M, C);
    C[n] = C[0];

    /// 原点是否在多边形内
    Point origin(0, 0);
    if(IN & relation(origin, C, n)){
        return (void)puts("0");
    }

    /// 求原点的速度
    Vector speed(SpeedB - SpeedA);
    /// 取轨迹上的无穷远点
    Point inf(speed.x * 1E10, speed.y * 1E10);
    /// 轨迹的直线
    Line track(origin, inf);

    /// 求线段(origin, inf)与多边形的最近的交点
    Real ans = 1E15, tmp;
    Point p;
    for(int t,i=0;i<n;++i){
        /// 如果线段相交则求一个交点
        if(INTER & relation(origin, inf, C[i], C[i+1])){
            pair<Real, Real> pp;
            t = relation(track, Line(C[i], C[i+1]), &pp);
            p = {pp.first, pp.second};
            if(t & INTER){
                tmp = p.length();
            }else if(t & CHONGHE){
                /// 碰撞点必然是C[i]或者C[i+1]
                tmp = min(C[i].length(), C[i+1].length());
            }else{
                throw runtime_error("XX");
            }            
            if(tmp < ans) ans = tmp;
        }
    }
    if(ans > 1E14) return (void)puts("-1");
    return (void)(cout << fixed << setprecision(12) << ans / speed.length() << endl);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt();
    for(int i=0;i<N;++i) A[i].x = getInt(), A[i].y = getInt();
    M = getInt();
    for(int i=0;i<M;++i) B[i].x = -getInt(), B[i].y = -getInt();

    SpeedA.x = getInt(), SpeedA.y = getInt();
    SpeedB.x = getInt(), SpeedB.y = getInt();

    proc();
    return 0;
}