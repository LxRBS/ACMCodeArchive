/**
 * @file 判直线的平行与重合，哈希得到话需要归一化a和b
 */
#include <bits/stdc++.h>
using namespace std;

/**
 * @brief 二维平面几何
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

/// 直线的参数方程
/// 直线上的点 p = b + d * t
/// 坐标必须采用实数, 参数是实数
struct ArgLine{
    Point base;
    Vector direction; // 方向向量
    /// 方向向量是否需要单位化, 如果比较不同直线, 最好单位化
    ArgLine(const Point &b, const Vector &d, bool needNorm=true):base(b),direction(d){
        assert(!d.isZero());
        if(needNorm) {
            this->direction.normSelf();
        }
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

/// 点p与参数直线line的关系, 如果在直线上还能返回参数, 必须是实数坐标
int relation(const Point &p, const ArgLine &line, Real *pk=nullptr){
    Real tmp;
    if(fabs(line.direction.x) >= fabs(line.direction.y)){
        assert(sgn(line.direction.x));
        tmp = (p.x - line.base.x) / line.direction.x;
        /// 如果y也相等
        if(is0(line.base.y + line.direction.y * tmp - p.y)){
            if(pk != nullptr) *pk = tmp;
            return IN;
        }
        return OUT;
    }
    

    assert(sgn(line.direction.y));
    tmp = (p.y - line.base.y) / line.direction.y;
    /// 如果x也相等
    if(is0(line.base.x + line.direction.x * tmp - p.x)){
        if(pk != nullptr) *pk = tmp;
        return IN;        
    }
    return OUT;
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

/// 参数直线u和v的位置关系，如果相交，还可以返回交点
int relation(const ArgLine &u, const ArgLine &v, Point * pk=nullptr){
    if(is0(cross(u.direction, v.direction))){
        if(IN & relation(u.base, v)){
            assert(IN & relation(v.base, u));
            return CHONGHE;
        }
        return PINGXING;
    }
    /// 求交点
    if(pk != nullptr){
        const auto ua = -u.direction.y;
        const auto ub = u.direction.x;
        const auto uc = u.base.x * (u.base.y + u.direction.y) - (u.base.x + u.direction.x) * u.base.y;
        const auto va = -v.direction.y;
        const auto vb = v.direction.x;
        const auto vc = v.base.x * (v.base.y + v.direction.y) - (v.base.x + v.direction.x) * v.base.y;
        const auto x = ub * vc - vb * uc;
        const auto y = va * uc - ua * vc;
        const auto t = ua * vb - va * ub;
        assert(sgn(t));   
        pk->x = x / t, pk->y = y / t; 
        assert(IN & relation(*pk, u) & relation(*pk, v));    
    }
    return INTER;
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
int const SIZE = 210;
#endif

int N;
Point P[SIZE];
Line L[SIZE*SIZE];

llt gcd(llt a,llt b){
    while( b ){
        llt r = b;
        b = a % b;
        a = r;
    }
    return a;
}

llt gcd(llt a, llt b, llt c){
    if(a < 0) a = -a;
    if(b < 0) b = -b;
    if(0 == a) return b;
    if(0 == b) return a;
    return gcd(a, b);
}

using pii = pair<llt, llt>;
template<>struct std::hash<pii>{
	inline size_t operator()(const pii&p)const{
		return p.first * 1331 + p.second;
	}
};

unordered_set<pii> Set;

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    N = getInt();
    for(int i=0;i<N;++i) P[i].x = getInt(), P[i].y = getInt();
    for(int i=0;i<N;++i)for(int j=i+1;j<N;++j){
        Line line(P[i], P[j]);   
        llt g = gcd(line.a, line.b, line.c);
        llt a = line.a / g, b = line.b / g;
        if(a < 0){
            a = -a, b = -b;
        }else if(0 == a && b < 0){
            b = -b;
        }
        Set.insert({a, b});
    }
    cout << Set.size() << endl;
    return 0;
}
