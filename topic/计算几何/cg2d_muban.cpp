#include <bits/stdc++.h>
using namespace std;

/**
 * @brief 二维平面几何
 * @version 20220812, 模板类, 函数尽量作为成员函数, 可以少写模板参数
 * 注意： 如果多边形退化成一个点或者一个线段，或者多边形存在三点共线，都需要慎重考虑
 * 1. typedef和常数
 * 2. 处理边界的数学库函数
 * 3. 点与向量的结构体以及基本运算，算术运算, 关系运算, 点积和叉积, 极角排序的functor
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

/** 3. 点与向量的结构体以及基本运算，相等，叉积，点积, 极角排序 **/
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
    T aa = a >= 0 ? a : -a;
    T bb = b >= 0 ? b : -b;
    T cc = c >= 0 ? c : -c;
    T g = 0;
    if(0 == aa){ // bb 必然不为0
        if(0 == cc) g = bb;
        else g = __gcd(bb, cc);
    }else if(0 == bb){
        if(0 == cc) g = aa;
        else g = __gcd(aa, cc);
    }else{
        g = __gcd(aa, bb);
        if(cc) g = __gcd(g, cc);
    }
    this->a /= g, this->b /= g, this->c /= g;
    if(a < 0 || (0 == a && b < 0)) {a = -a, b = -b, c = -c;}
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

    /// 特判
    if(1 == n) return (p == pts[0]) ? (IN | VERTEX) : OUT;

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

/// 点到简单多边形的, O(N)
Real dist(const Dian & p, Real const inf=INF) const {
    if(this->relate(p)) return 0;

    int n = pts.size();
    Real ans = inf;
    for(int i=0;i<n;++i){
        ans = min(ans, p.dist(pts[i], pts[(i+1)%n]));
    }
    return ans;
}

/// 有向面积的二倍
T area2() const {
    int n = pts.size();    
    T ans = 0;
    for(int i=1;i<n-1;++i){
        ans += pts[0].cross(pts[i], pts[(i+1)%n]);
    }
    return ans;
}

/// 周长, 必然为实型
Real circum() const {
    Real ans = 0.0;
    for(int i=0,n=pts.size();i<n;++i){
        ans += pts[i].dist(pts[(i+1)%n]);
    }
    return ans;
}

/// 规范化, 删除共线点
void normSelf(){
    auto &p = pts;
    int n = pts.size();
    if(n <= 2) return;

    if(this->isDegenerate()){
        auto lowleft = [](const Dian &a, const Dian &b){
            int t = sgn(a.y - b.y);
            if(t) return t < 0;
            return sgn(a.x - b.x) < 0;
        };
        int k = 0;
        for(int i=1;i<n;++i){
            if(lowleft(pts[i], pts[k])){
                k = i;
            }
        }
        /// 保存最小最左及其前一个点即可
        const Dian tmp[] = {pts[k], pts[(k-1+n)%n]};
        pts.assign(tmp, tmp+2);
        return;
    }
    
    int top = 1;
    int k = 1;
    while(1){
        while(k < n && is0(p[top-1].cross(p[k], p[(k+1)%n]))) ++k;
        if(k == n) {p[top++] = p[n-1]; break;}
        p[top++] = p[k++];
        if(k == n) break;
    }

    /// 后处理top
    while(top >= 3 && is0(p[0].cross(p[top-1], p[top-2]))){
        --top;
    }
    
    /// 删除
    p.erase(p.begin() + top, p.end());
    if(p.size() <= 2) return;

    // 处理0点 
    if(is0(p[0].cross(p[p.size()-1], p[1]))) p.erase(p.begin());
    /// assert
    assert([&]()->bool{
        int n = p.size();
        for(int i=0;i<n;++i){
            if(is0(p[i].cross(p[(i-1+n)%n], p[(i+1)%n]))){
                return false;
            }
        }
        return true;
    }());
}

/// 是否退化, O(N)
/// 一般不会有退化，直接返回false即可
/// 感觉退化情况下意义不大, 特别是对凸多边形 
bool isDegenerate() const {
    if(1 == pts.size()) return true; // 退化成一个点
    for(int i=2,n=pts.size();i<n;++i){
        if(sgn(pts[0].cross(pts[1], pts[i]))){
            return false;
        }
    }
    return true; // 退化成一条线段
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
/// 凸多边形不能退化成一大条线段
/// 0点所在的边不能存在三点共线
int relate(const Dian & p) const {
    const auto & pts = this->pts;
    int n = pts.size();

    /// 特判
    if(1 == n) return (p == pts[0]) ? (IN | VERTEX) : OUT;
    if(2 == n) return p.relate(pts[0], pts[1]);
    /// 一点点保证
    assert(sgn(pts[0].cross(pts[1], pts[2])) >= 0);
    /// 特判是否与0点重合，否则以后只会返回IN, 而不会返回端点
    if(p == pts[0]) return IN | VERTEX;
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
/// 凸多边形的直径，即凸多边形内最长的线段, O(N), 旋转卡壳法
/// 返回直径的长度的平方，pans里保存构成直径的两个端点的序号, 可能有很多对, 只保存其中一对
T rcDiameter2(int pans[] = nullptr) const {
     
    auto f = [](const Dian &u, const Dian &v)->T{
        auto x = u.x - v.x, y = u.y - v.y;
        return x * x + y * y;
    };
    
    const auto & p = this->pts;
    int const n = p.size();

    T d = 0;
    int k1 = 0, k2 = 1;
    for(k1=0;k1<n;++k1){
        while(sgn(p[(k1+1)%n].cross(p[(k2+1)%n], p[k1]) - p[(k1+1)%n].cross(p[k2], p[k1])) > 0){
            k2 = (k2+1)%n;
        }
        auto tmp = f(p[k1], p[k2]);
        if(tmp > d){
            d = tmp;
            if(pans){
                pans[0] = k1;
                pans[1] = k2;
                if(k1 > k2) swap(pans[0], pans[1]);
            }
        }
    }
    return d;

}

/// 旋转卡壳法求凸多边形中的最大三角形, O(N^2)
/// 返回最大面积的两倍
T rcTriangle2(int pans[] = nullptr) const {
    const auto & p = this->pts;
    int const n = p.size();
     

    T edge = 0;
    T ans = 0;
    for(int k,j,i=0;i<n-2;++i){
        j = i + 1;
        k = j + 1;
LL_rcTriangle:
        edge = 0;
        while(k < n){
            auto chaji = cross(p[i], p[j], p[k]);
            if(chaji < 0) chaji = -chaji;
            if(edge > chaji) break;
            edge = chaji;
            ++k;
        }
        /// edge记录的是以ij为边"所能达到的最大三角形"
        if(ans < edge) {
            ans = edge;
            if(pans){
                pans[0] = i, pans[1] = j, pans[2] = k;
            }
        }
        /// 更新j,继续循环
        --k, ++j;
        if(n - 1 == j) continue;
        goto LL_rcTriangle;
    }
    assert(is0(fabs(p[pans[0]].cross(p[pans[1]], p[pans[2]]) - ans)));
    sort(pans, pans+3);
    return ans;
}

/// 旋转卡壳法求最小覆盖矩形, 
/// 即找到一个矩形完全盖住凸多边形p, 且该矩形面积是最小的
/// 返回最小面积, pans中记录4个点，为矩形, 点必须是实型
/// p保证是逆时针, 顺时针需要更改while中的关系符号
Real rcRectangle(Point<Real> pans[] = nullptr, const Real inf=INF) const {
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
                Dian diDirection(p[(i+1)%n] - p[i]);
                Dian zuoDirection(-diDirection.y, diDirection.x);
                /// 底部的直线, 注意这里不能用构造函数
                Zhixian bLine = Zhixian::create(p[i], diDirection);
                /// 右侧的直线
                Zhixian rLine = Zhixian::create(p[r], zuoDirection);
                /// 上部直线
                Zhixian tLine = Zhixian::create(p[t], diDirection);
                /// 左侧直线
                Zhixian lLine = Zhixian::create(p[l], zuoDirection);
                /// 4个交点
                int c919 = bLine.relate(rLine, pans);
                c919 &= rLine.relate(tLine, pans+1);
                c919 &= tLine.relate(lLine, pans+2);
                c919 &= lLine.relate(bLine, pans+3);
                assert(JIAO & c919);
            }
        }
    }
    return ans;
}

/// 返回某一个方向上的极值点, 即过该点以该方向做一个半平面
/// 凸多边形的所有点都在该半平面内
/// 返回值为点在凸多边形中的序号
/// 如果要得到平行直线的点对, 需要正反调用两次
/// 保证凸多边形本身是逆时针, 且不能退化成一大条线段
/// https://codeforces.com/blog/entry/48868
/// O(logN), dir为计算方向的函数
int extreme(function<Dian(const Dian &)> dir) const {
    const auto &p=this->pts;
    int const n = p.size(); 
    
    const auto check=[&](const size_t i){return sgn(dir(p[i]).cross(p[(i+1)%n]-p[i]))>=0;};
    const auto dir0=dir(p[0]); const auto check0=check(0);
    if (!check0 && check(p.size()-1)) return 0;
    const auto cmp=[&](const Dian &v){
        const int vi=&v-p.data();
        const auto checkv=check(vi);
        const auto t=sgn(dir0.cross(v-p[0]));
        return checkv^(checkv==check0 && ((!check0 && t<=0) || (check0 && t<0)));
    };
    return partition_point(p.begin(),p.end(),cmp)-p.begin();
}

/// 设极点为i，令(i-1,i)边记作prv, 后边记作nxt
/// 则从prv转向nxt需要跨越direction的正方向print
int extreme(const Dian & direction) const {
    const auto & p = this->pts;
    int const n = p.size();
  
    /// 特判
    if(1 == n) return 0;
    if(2 == n) {
        int t = sgn(direction.cross(p[1] - p[0]));
        if(t > 0) return 0;
        if(t < 0) return 1;
        t = sgn(direction.dot(p[1] - p[0]));
        assert(t);
        if(t > 0) return 0;
        return 1;
    }

    /// 检查i点前后边的情况, 每条边返回4位, 分别表示左右同向异向
    /// 前一条边为高位，后一条边为低位
    auto f = [&](int i)->int{
        int tprv = sgn(direction.cross(p[i] - p[(i-1+n)%n]));
        int tnxt = sgn(direction.cross(p[(i+1)%n] - p[i]));
        int ret = 0;
        if(tnxt > 0) ret |= 1;
        else if(tnxt < 0) ret |= 2;
        else {
            int t = sgn(direction.dot(p[i] - p[(i-1+n)%n]));
            assert(t);
            if(t > 0) ret |= 4;
            else ret |= 8;
        } 
        if(tprv > 0) ret |= 0x10;
        else if(tprv < 0) ret |= 0x20;
        else{
            int t = direction.dot(p[(i+1)%n] - p[i]);
            assert(t);
            if(t > 0) ret |= 0x40;
            else ret |= 0x80;
        }

        /// 只有10种可能性
        assert(
            0x41 == ret || 0x44 == ret
         || 0x11 == ret || 0x18 == ret || 0x12 == ret
         || 0x82 == ret || 0x88 == ret
         || 0x22 == ret || 0x24 == ret || 0x21 == ret  
        );  

        return ret;
    };

    /// 首先检查0点
    const int t0 = f(0);
  
    /// 说明(n-1,0,1)刚好从右侧转到了direction左侧或者转到了direction正向
    if((t0 & 0x21) || (t0 & 0x24)){ 
        return 0;
    }

    /// 如果0不是答案，则答案必然在[1, n-1]中，令答案为ans, 则
    /// [0, ans)均满足某个条件,[ans, n-1]均不满足某个条件
    auto cmp = [&](const Dian & dian)->bool{
        const int i = &dian - p.data(); // 获取点的索引
        const int ti = f(i);
        /// 就是极值点，肯定不满足条件
        if((ti & 0x21) || (ti & 0x24)) return false;
        if(t0 & 0x1){ // 说明01边相对于direction向左
            /// 所有向右转的边都符合条件
            if(ti & 0x2) return true;
            /// 所有负方向边符合
            if(ti & 0x8) return true;
            /// 所有正方向不符合
            if(ti & 0x4) return false;
            /// 最后剩下同为向左的, 此时如果i在0点左边，则符合
            int c919 = direction.cross(dian - p[0]);
            if(c919 > 0) return true;
            /// 因为01边是向左转的，在右边或者同一条线上都不符合
            /// 同一条线上的必然在负方向
            if(0 == c919) assert(sgn(direction.dot(dian - p[0])) < 0);
            return false;

        }else if(t0 & 0x2){ // 01边相对于d方向向右
            /// 只有也是向右转的才有可能是true，其他都是false
            if(ti & 0x2){ // 需要在0点的右边才是true
                int c919 = sgn(direction.cross(dian - p[0]));
                assert(c919);
                if(c919 < 0) return true;
                return false;
            }
            return false;
        }else if(t0 & 0x4){ // 01边刚好是d正方向
            if(ti & 0x4){ // 只有ti也朝上且i在0的下方才是false
                int c919 = sgn(direction.dot(dian - p[0]));
                assert(c919);
                if(c919 < 0) return false;
                return true;
            }
            return true;
        }else if(t0 & 0x8){ // 01边刚好是d的负方向
            if(ti & 0x2) return true; // 向右的都对
            if(ti & (0x1 | 0x4)) return false; // 向左或者正方向的都不对
            if(ti & 0x8){ // 负方向且在0的下方才对
                int c919 = sgn(direction.dot(dian - p[0]));
                assert(c919);
                if(c919 < 0) return true;
                return false;
            } 
            throw runtime_error("hehe");
        }

        throw runtime_error("XX");
        return false;
    };
    int ret = partition_point(p.begin(), p.end(), cmp) - p.begin();
    return ret;
}

/// 保证点p在凸多边形外, 返回两条切线
/// 即[first, second]之间的点为p的可见点
pair<int, int> qiexian(const Dian &p) const{
    int a = this->extreme([&](const Dian &q){return q - p;});
    int b = this->extreme([&](const Dian &q){return p - q;});
    return {a, b};
}

/// 求与直线AB平行的切线的切点
pair<int, int> qiexian(const Dian &A, const Dian &B) const{
    int a = this->extreme([&](const Dian &q){return B - A;});
    int b = this->extreme([&](const Dian &q){return A - B;});
    return {a, b};
}

/// 点到凸多边形的距离, O(logN)
/// 首先求出所有可见点, 然后三分
Real dist(const Dian & p) const {
    const auto & pts = this->pts;
    int const n = pts.size();

    /// 特判
    if(1 == n) return p.dist(pts[0]);
    if(2 == n) return p.dist(pts[0], pts[1]);
    /// 先判内, 这也是log算法
    int r = this->relate(p);
    if(r & IN) return 0;

    /// 求可见点范围
    auto pp = this->qiexian(p);

    /// 三分搜索
    int left = pp.first, right = pp.second, m1, m2;
    do{
        m1 = left + (right - left) / 3;
        m2 = right - (right - left) / 3;
        if(sgn(p.dist(pts[m1], pts[(m1+1)%n]) - p.dist(pts[m2], pts[(m2+1)%n])) <= 0){
            right = (m2 - 1 + n) % n;
        }else{
            left = (m1+1)%n; 
        }
    }while(left <= right);
    /// left是答案
    return p.dist(pts[left], pts[left+1]);    
}

};

/** 7 半平面和半平面交排序增量法 **/
template<typename T>struct HalfPlane{

using Dian = Point<T>;
using Banpm = HalfPlane<T>;

/// ax+by+c >= 0, (a, b)就是法向量
T a, b, c; // 整点可以形成整数半平面

HalfPlane(T aa=0, T bb=0, T cc=0):a(aa),b(bb),c(cc){}
/// 两点生成一个半平面，从u到v是逆时针，即半平面在uv的左手边
HalfPlane(const Dian &u, const Dian &v){
    /// 与直线生成一模一样
    assert(!(u == v));
    this->a = u.y - v.y;
    this->b = v.x - u.x;
    this->c = u.x * v.y - v.x * u.y;    
}

T eval(const Dian &p) const {return a * p.x + b * p.y + c;}
/// 点与半平面的关系, 内, 边界, 外
int relate(const Dian &p) const {
    int r = sgn(eval(p));
    if(0 == r) return IN & EDGE;
    if(r > 0) return IN;
    return OUT;
}

/// 半平面相交求交点，保证相交
/// 只有一种情况需要特判，就是法向量相反，且交集为空的情况
/// 该特殊情况在排序增量法中直接得到半平面交为空集
/// 返回真表示交点有效，返回false表示特殊情况
/// 交点只能用实型
bool inter(const Banpm & r, Point<Real> &p) const {
    const T xishu = a * r.b - b * r.a;
    if(is0(xishu)) return false;
    Real tmp = xishu;
    p = {(b * r.c - c * r.b) / tmp, (c * r.a - a * r.c) / tmp};
    return true;
}

/// 半平面沿着法向量方向移动距离d, 为负数表示沿着法向量反方向移动
/// 只能是实型
Banpm move(T d) const {
    return Banpm(a, b, c - d * sqrt(a * a + b * b));
}

/// 半平面交的排序增量法
/// 保证结果是有限的，否则需要加包围盒，因此n肯定大于4
/// 会改变hp的内容，0-index
/// 结果保存在hp[bot..top]中
/// 返回top-bot+1，即半平面的数量，如果小于3，说明原交集为空集
static int sandi(Banpm hp[], int n, int&bot, int&top){
    /// 根据法向量幅角(-180,180]比较大小，角度相同越靠近法向量越小
    sort(hp, hp+n, [](const Banpm&u, const Banpm&v)->bool{
        /// 法向量分别位于x轴上下，可以直接得到结果
        int ly = sgn(u.b) >= 0 ? 1 : -1;
        int ry = sgn(v.b) >= 0 ? 1 : -1;
        if(ly != ry) return ly < ry;
        
        /// 如果都在x轴上，且一东一西
        if(is0(u.b) && is0(v.b) && sgn(u.a * v.a) < 0) return u.a > v.a;
        
        /// 计算叉积，如果叉积不为零
        int chaji = sgn(u.a * v.b - u.b * v.a);
        if(chaji) return chaji > 0;
        
        /// 到此处说明平行, 当a大于0
        if(sgn(u.a) > 0){
            /// 若hp1比hp2更靠近法向量，则必有a1x+b1y+c1=0而a2x+b2y+c2>0
            return u.c * v.a < u.a * v.c;
        }
        if(sgn(u.a) < 0){ // 小于0就是反过来
            return u.c * v.a > u.a * v.c;
        }
        /// a为0则b必不为0
        if(sgn(u.b) > 0){
            return u.c * v.b < u.b * v.c;
        }
        return u.c * v.b > u.b * v.c;
    });

    /// 完全平行的法向量只取一个
    n = unique(hp, hp+n, [](const Banpm&u, const Banpm&v)->bool{
        int ly = sgn(u.b) >= 0 ? 1 : -1;
        int ry = sgn(v.b) >= 0 ? 1 : -1;
        if (ly != ry) return false;
        if (is0(u.b) && is0(v.b)) return u.a * v.a > 0;
        return is0(u.a * v.b - v.a * u.b);        
    }) - hp;

    /// 主循环
    bot = 0, top = 1;
    Point<Real> p; // 交点必须是实型
    for(int i=2;i<n;++i){
        /// 最前端的两个半平面相交
        while(bot < top){
            bool b = hp[top-1].inter(hp[top], p);
            if(!b) return bot = top = -1, 0; // 直接返回空集即可

            /// 交点在当前半平面外则出队            
            if(hp[i].relate(p)){
                break;
            }else{
                --top;
            }
        }
        /// 最底端的两个半平面相交
        while(bot < top){
            bool b = hp[bot].inter(hp[bot+1], p);
            if(!b) return bot = top = -1, 0;

            if(hp[i].relate(p)){
                break;
            }else{
                ++bot;
            }
        }
        /// 赋值
        hp[++top] = hp[i];
    }

    /// 后处理
    while(bot < top){
        bool b = hp[top-1].inter(hp[top], p);
        if(!b) return bot = top = -1, 0;        
        if(hp[bot].relate(p)){
            break;
        }else{
            --top;
        }
    }
    while(bot < top){
        bool b = hp[bot].inter(hp[bot+1], p);
        if(!b) return bot = top = -1, 0;  
            
        if(hp[top].relate(p)){
            break;
        }else{
            ++bot;
        }
    }

    return top - bot + 1;
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

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  

    return 0;
}
