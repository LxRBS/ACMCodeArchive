/**
 * @brief 二维平面几何
 * @version 20221225, 所有函数作为成员函数，默认为整型坐标
 * 注意： 如果多边形退化成一个点或者一个线段，或者多边形存在三点共线，都需要慎重考虑
 * 1. typedef和常数
 * 2. 处理边界的数学库函数
 * 3. 点与向量的结构体以及基本运算，算术运算, 关系运算, 点积和叉积
 * 4. 直线的结构体
 * 5. 线段的结构体，线段有时也用两点表示
 * 6. 简单多边形
 * 7. 凸包与凸多边形
 * 8. 半平面交排序增量法
 * 9. 德劳奈三角剖分和Voronoi图
 * 持续更新...
 * 题目列表:
 * 
 * 基础运算
 * LuoguP1355: 点在三角形内，用的是logN的算法
 * 牛客207032: 直线的位置关系, 2个方法
 * 牛客220476: 线段相交, 2个方法
 * 
 * 半平面
 * 牛客19905: 半平面交，求面积
 * 牛客233170UVA1396UVALive3890: 半平面移动, 半平面交, 二分，实型坐标
 * 牛客234015: 半平面交二分
 * 
 * 凸包
 * 牛客233135: 凸包求周长
 * ZOJ1464: 凸包求周长
 * 
 * 凸多边形的log算法
 * 牛客233165: 点关于凸多边形的切点，动态凸包，面积
 * 牛客233737: 点在凸多边形内，log算法 
 * 牛客233738: 直线关于凸多边形的切点
 * 
 * 闵可夫斯基和
 * 牛客233186: 凸多边形的距离，闵可夫斯基和，GJK算法，实型坐标
 * 
 * 旋转卡壳
 * 牛客20057: 凸包最小矩形覆盖求矩形
 * 牛客233136: 凸包旋转卡壳求直径
 * 牛客232791: 凸包最小矩形覆盖求面积
 * hdu7052: 外凸包到内凸包的距离
 *
 * contest
 * 牛客20057: 凸包最小矩形覆盖求矩形
 * 牛客19905: 半平面交求面积
 * 牛客233171: 半平面交求周长
 * 牛客2022暑假3G: 凸多边形碰撞检测, 闵可夫斯基何, GJK算法
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

/** 1. typdef和常数 **/
using Real = long double;
using llt = long long;

Real const EPS = 1E-9; // 根据需要调整
Real const PI = acos(-1);
Real const INF = 1E100;  // 根据需要调整

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

/** 3. 点与向量的结构，只实现整型的 **/
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

/** 4. 直线的结构体 **/
struct Line{

T a, b, c; // ax + by + c = 0

Line() = default;

/**
 * @brief 直线AB
 * @param needNorm 是否需要归一化
 */
Line(const Point & A, const Point & B, bool needNorm=false){
    assert(!(A == B));
    this->a = A.y - B.y;
    this->b = B.x - A.x;
    this->c = A.x * B.y - B.x * A.y;     
    if(needNorm) normSelf();    
}

/**
 * @brief 归一化，即a/b/c互质，
 * 且a不为零则a保证大于零，a为零则保证b大于零
 */
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

T eval(const Point & p) const {return p.x * a + p.y * b + c;}

/**
 * @brief this与r的位置关系，两条直线的位置关系
 * @param pk 相交情况下，且不为空，则会带出交点坐标，注意交点不能保证是整型
 * @return CHONGHE, PINGXING或者JIAO 
 */
int relate(const Line & r, pair<Real, Real> * pk=nullptr) const {
    T x = b * r.c - c * r.b; // 整型有可能溢出
    T y = r.a * c - r.c * a;
    T t = a * r.b - b * r.a;
    if(is0(t)){
        if(is0(x) && is0(y)) return CHONGHE;
        return PINGXING;
    }
    if(pk) pk->first = (Real)x / t, pk->second = (Real)y / t;
    return JIAO;
}

};

/** 5. 线段的结构体，线段有时也用两点表示 **/
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

/*** 6. 简单多边形 ***/
struct Polygon{

vector<Point> pts; // 编号从0开始

Polygon() = default;

void input(int n){
    this->pts.assign(n, Point());
    for(auto & p : this->pts){
        p.x = getInt();
        p.y = getInt();
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

/*** 7. 凸多边形与凸包 ***/
struct Convex{

vector<Point> pts; // 编号从0开始，逆时针

void input(int n){
    this->pts.assign(n, Point());
    for(auto & p : this->pts) p.input();
}

/**
 * @brief 凸多边形this与点p的位置关系，this必须是凸的，逆时针，O(logN)
 * this不能退化，0点所在的边不能存在三点共线?
 * @return 如果在端点上返回IN|VERTEX，在边上返回IN|EDGE，在里返回IN，否则返回OUT
 */
int relate(const Point & p)const{
    const vector<Point> & pts = this->pts;
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
        int t1 = sgn(pts[0].cross(pts[mid], p));
        int t2 = sgn(pts[0].cross(pts[mid+1], p));
        /// p 必然在(mid, mid+1)之间
        if(t1 >= 0 && t2 <= 0){
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
            int r = sgn(p.cross(pts[mid], pts[mid+1]));
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

/**
 * @brief Graham凸包算法，NlogN
 *  需要事先把点集放入pts中，最后会改变pts的内容，
 *  最后结果保证没有任意三点共线，这一点其实一般没用
 * @return 凸包点的数量 
 */
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
    if(n >= 3)for(int i=0;i<n;++i){
        int prv = (i-1+n)%n;
        int nxt = (i+1)%n;
        if(is0(pts[i].cross(pts[prv], pts[nxt]))){
            throw runtime_error(to_string(i));
        }
    }

    return top;   
}

/**
 * @brief 求this与r的闵可夫斯基和，O(N)
 *   this与r均是凸多边形，逆时针
 * @param ans 输出参数，可能存在共线的边
 */
void Minkowski(const Convex & r, Convex & ans)const{
    using vt = vector<Point>;

    auto lowleft = [](const Point & a, const Point & b){
        int t = sgn(a.y - b.y);
        if(t) return t < 0;
        return a.x < b.x;
    };
    /// 向量排序，从0-360，极角相同，长度小的排在前面
    auto cmp = [](const Point & a, const Point & b){
        auto calLoc = [](const Point & p)->int{
            if(sgn(p.y) > 0) return 2; // (0, 180)
            if(sgn(p.y) < 0) return 4; // (180,360)
            if(sgn(p.x) > 0) return 1; // 0
            if(sgn(p.x) < 0) return 2; // 180
            return 0;
        };
        int aloc = calLoc(a), bloc = calLoc(b);
        if(aloc != bloc) return aloc < bloc;

        int chaji = sgn(a.cross(b));
        if(chaji) return chaji > 0;
        return sgn(a.square() - b.square()) < 0;
    };

    /// 主计算过程，将输入的多边形p拆分成向量,放入ret
    /// ans中的向量最终按照极角0-360排序, 返回最下最左的编号
    auto calc = [cmp, lowleft](const vt &p, int n, Point ret[])->int{
        int kll = 0; // 最下最左
        int jll = 0; // 最小角
        for(int i=0;i<n;++i){
            ret[i] = p[(i+1)%n] - p[i];
            if(lowleft(p[i], p[kll])) kll = i;
            if(cmp(ret[i], ret[jll])) jll = i;
        }
        rotate(ret, ret+jll, ret+n);
        return kll;
    };  

    /// 参数
    const auto & pa = this->pts;
    const auto & pb = r.pts;
    int na = pa.size(), nb = pb.size();

    /// 返回值
    auto & pc = ans.pts;
    pc.assign(na + nb, Point());
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
    return;        
}

/**
 * @brief 返回凸多边形关于某一个方向的极值点, O(logN)
 *   假设极值点是p，方向是dir，则过p以dir做向量，则多边形上所有点都在该向量的右边
 *   https://codeforces.com/blog/entry/48868
 *   保证this是凸的，逆时针
 *   如果存在多点共线的情况，简单测试之下也是可以工作的，但是一般会先跑一个凸包，因此这种情况可以避免
 *   如果退化成一条线段，也能work。如果线段上有多个点，只要排布有序，简单测试之下也没有发现问题
 *   该函数主要是被tangent函数调用
 * @param dir 生成方向的函数, dir(p)可以得到真正的方向向量
 *   dir的具体构造可以参照后续的函数
 * @return 极值点在多边形内的编号，如果有多个极值点，返回逆时针序的第一个
 *   但是注意如果0点是答案，则会直接返回0，
 *   但一般均会先跑一个凸包算法，这样的话0点是最小最左点，则仍然符合上述规律
 */
int extreme(function<Point(const Point &)> dir)const{
    auto & pts = this->pts;
    int n = pts.size();

    /// dir(j)与向量ij的叉积的符号，为0说明共线，为1说明向量ij在左，否则在右 
    auto vertexCmp = [dir, &pts](int i, int j)->int{
        int t = sgn(dir(pts[j]).cross(pts[j] - pts[i]));
        return t;
    };
    
    /**
     * @brief 点i是否为极值点
     *  对某个点i而言，如果i-1在它的右边，i+1在它的左边或者共线，则i是极值点
     *  iSgn保存当前i的计算值，以节约运算
     */
    auto isExtreme = [n, vertexCmp](int i, int & iSgn){
        iSgn = vertexCmp((i+1)%n, i);
        int t = vertexCmp(i, (i-1+n)%n);
        return iSgn >= 0 && t < 0;
    };

    int leftSign;
    if(isExtreme(0, leftSign)) return 0;

    int left = 0, right = n, mid, midSign;
    do{
        mid = (left + right) >> 1;
        if(isExtreme(mid, midSign)) return mid;
        if(leftSign != midSign ? leftSign < midSign : leftSign == vertexCmp(left, mid)){
            right = mid;
        }else{
            left = mid, leftSign = midSign;
        }
    }while(left + 1 < right);
    return left;
}

/**
 * @brief 求p点关于凸多边形的两个切点，p要保证在多边形外
 * @return 返回两个切点在凸多边形的编号, [first, second]之间即为p的"可见"区域
 *  注意返回是有序的，不能颠倒。first有可能大于second
 *  如果恰好共线，first可能是不可见的,first+1才是可见的
 */
pair<int, int> tangent(const Point & p) const {
    int a = this->extreme([&p](const Point & q){return q - p;});
    int b = this->extreme([&p](const Point & q){return p - q;});
    return {a, b};
}

/**
 * @brief 返回凸多边形关于直线AB双向的切点，即假设p和q是答案
 *   则用平行于AB的直线族去卡多边形，恰好两边交于p和q
 * @return 切点在多边形的编号
 */
pair<int, int> tangent(const Point & A, const Point &B)const{
    /// 沿AB方向的直线，交于a点，此时多边形都在该直线右侧，即a点是直线AB的对踵点
    int a = this->extreme([&A, &B](...){return B - A;});
    int b = this->extreme([&A, &B](...){return A - B;});
    return {a, b};
}

// area[i]记录从0到i的扇形面积，注意是2倍
vector<T> sector_area;

/**
 * @brief 计算sector_area
 *  area[i]记录了从0到i的扇形面积的两倍
 */
void initSectorArea(){
    int n = pts.size();
    sector_area.assign(n + 1, 0LL);
    for(int i=1;i<=n;++i){
        sector_area[i] = pts[i-1].cross(pts[i%n]);
    }
    for(int i=1;i<=n;++i){
        sector_area[i] += sector_area[i-1];
    }
}

/**
 * @brief 计算凸多边形从idx到jdx的弓形面积的两倍, O(1)
 *   idx和jdx是有序的，但是idx有可能大于jdx
 */
llt calcArcArea(int idx, int jdx)const{
    assert(this->sector_area.size() == this->pts.size() + 1);
    int n = pts.size();
    if(idx <= jdx){
        return sector_area[jdx] - sector_area[idx] - pts[idx].cross(pts[jdx]);
    }
    return sector_area[n] - sector_area[idx] + sector_area[jdx] - pts[idx].cross(pts[jdx]);
}


/**
 * @brief 旋转卡壳法求凸包的直径, O(N)
 *   返回直径的平方, pans保存直径的端点
 * @param pans 输出参数，保存直径的两个端点的编号，可能有多条直径，只保存一条
 * @return 直径的平方
 */
T rcDiameter2(int pans[] = nullptr) const {
     
    auto f = [](const Point &u, const Point &v)->T{
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

/**
 * @brief 旋转卡壳法求凸包的最大三角形，O(N^2)
 *  即在凸包上找三个点，使得这个三点构成的三角形面积最大
 *  返回最大面积的两倍，pans保存三角形的端点
 * @param pans 输出参数，三角形端点的编号
 * @return 最大面积的两倍
 */
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
            auto chaji = p[i].cross(p[j], p[k]);
            // if(chaji < 0) chaji = -chaji;
            assert(chaji >= 0);
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
    assert(is0(p[pans[0]].cross(p[pans[1]], p[pans[2]]) - ans));
    sort(pans, pans+3);
    return ans;
}

/**
 * @brief 旋转卡壳法求凸包的最小覆盖矩形, O(N)
 *  即找到一个矩形完全覆盖住凸包，且矩形面积最小
 *  返回矩形的面积，矩形的点放在pans中返回
 * @param pans 矩形的4个端点，逆时针，矩形不能保证是整点
 *   注意return 0的时候pans里没有内容
 * @return 矩形的最小面积 
 */
Real rcRectangle(pair<Real, Real> pans[] = nullptr) const {
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
    Real ans = INF;
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
            if(pans){
                /// 底部的方向向量, 和左右的方向向量
                Point diDirection(p[(i+1)%n] - p[i]);
                Point zuoDirection(-diDirection.y, diDirection.x);
                /// 底部的直线, 注意这里不能用构造函数
                Line bLine(p[i], p[(i+1)%n]);
                /// 右侧的直线
                Line rLine(p[r], p[r] + zuoDirection);
                /// 上部直线
                Line tLine(p[t], p[t] + diDirection);
                /// 左侧直线
                Line lLine(p[l], p[l] + zuoDirection);
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

/**
 * @brief 点p到this的距离，log(N)
 *   首先判断p是否在多边形内，然后求出切点，然后再三分搜索
 */
Real dist(const Point & p) const {
    const auto & pts = this->pts;
    int const n = pts.size();

    /// 特判
    if(1 == n) return p.dist(pts[0]);
    if(2 == n) return p.dist(pts[0], pts[1]);
    /// 先判内, 这也是log算法
    int r = this->relate(p);
    if(r & IN) return 0;

    /// 求可见点范围
    auto pp = this->tangent(p);

    /// 三分搜索
    int left = pp.first, right = pp.second, m1, m2;
    if(right < left) right += n;
    do{
        m1 = left + (right - left) / 3;
        m2 = right - (right - left) / 3;
        if(sgn(p.dist(pts[m1%n], pts[(m1+1)%n]) - p.dist(pts[m2%n], pts[(m2+1)%n])) <= 0){
            right = m2 - 1;
        }else{
            left = m1 + 1;
        }
    }while(left <= right);
    /// left是答案
    return p.dist(pts[left%n], pts[(left+1)%n]);    
}



};

/** 8 半平面和半平面交排序增量法 **/
struct HalfPlane{

/// ax+by+c >= 0, (a, b)就是法向量
T a, b, c; 

HalfPlane() = default;

HalfPlane(T aa, T bb, T cc):a(aa),b(bb),c(cc){}

/**
 * @brief 两点构成一个半平面，u到v是逆时针，半平面在uv的左手边
 */
HalfPlane(const Point &u, const Point &v){
    /// 与直线生成一模一样
    assert(!(u == v));
    this->a = u.y - v.y;
    this->b = v.x - u.x;
    this->c = u.x * v.y - v.x * u.y;    
}

Real eval(Real x, Real y) const {return a * x + b * y + c;}

/**
 * @brief 点(x, y)与半平面的关系
 * @return 在边界上返回IN|EDGE，在内返回IN，否则返回OUT
 */
int relate(Real x, Real y) const {
    int r = sgn(eval(x, y));
    if(0 == r) return IN | EDGE;
    if(r > 0) return IN;
    return OUT;
}

/**
 * @brief 这个函数用于排序增量法中求this与r相交，保证相交，
 *  除了一种特殊情况，即法向量相反且交集为空，此情况下排序增量法的结果为空集
 *  返回true表示普通情况，交点坐标由x和y带回
 *  返回false，表示出现上述特殊情况
 */
bool inter(const HalfPlane & r, Real & x, Real & y) const {
    const T xishu = a * r.b - b * r.a;
    if(is0(xishu)) return false;
    Real tmp = xishu;
    x = (b * r.c - c * r.b) / tmp;
    y = (c * r.a - a * r.c) / tmp;
    return true;
}

/**
 * @brief 半平面沿法向移动d形成的新半平面，必须是实型
 */
HalfPlane move(T d) const {
    return HalfPlane(a, b, c - d * sqrt(a * a + b * b));
}

/**
 * @brief 给hp数组加上包围盒，hp的内容是hp[0...n)
 *  加完以后变为hp[0...n+4)
 * @return 返回n+4
 */
static int bound(HalfPlane hp[], int n, T inf){
    hp[n++] = {Point(-inf, 1), Point(-inf, 0)}; // 左
    hp[n++] = {Point(+inf, 0), Point(+inf, 1)}; // 右
    hp[n++] = {Point(1, +inf), Point(0, +inf)}; // 上
    hp[n++] = {Point(0, -inf), Point(1, -inf)}; // 下
    return n;
}

/**
 * @brief 半平面相交的排序增量法，必须确保结果是有限的
 *   对于可能无限的结果，需要事先加上包围盒
 * @param hp 输入输出参数，从0开始编号，输入是为hp[0...n)，输出时为hp[bot...top]
 * @return 最后结果的半平面数量，注意小于3，说明交集为空集
 */
static int sandi(HalfPlane hp[], int n, int&bot, int&top){
    /// 根据法向量幅角(-180,180]比较大小，角度相同越靠近法向量越小
    sort(hp, hp+n, [](const HalfPlane&u, const HalfPlane&v)->bool{
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
    n = unique(hp, hp+n, [](const HalfPlane&u, const HalfPlane&v)->bool{
        int ly = sgn(u.b) >= 0 ? 1 : -1;
        int ry = sgn(v.b) >= 0 ? 1 : -1;
        if (ly != ry) return false;
        if (is0(u.b) && is0(v.b)) return u.a * v.a > 0;
        return is0(u.a * v.b - v.a * u.b);        
    }) - hp;

    /// 主循环
    bot = 0, top = 1;
    Real x, y;
    for(int i=2;i<n;++i){
        /// 最前端的两个半平面相交
        while(bot < top){
            bool b = hp[top-1].inter(hp[top], x, y);
            if(!b) return bot = top = -1, 0; // 直接返回空集即可

            /// 交点在当前半平面外则出队            
            if(hp[i].relate(x, y)){
                break;
            }else{
                --top;
            }
        }
        /// 最底端的两个半平面相交
        while(bot < top){
            bool b = hp[bot].inter(hp[bot+1], x, y);
            if(!b) return bot = top = -1, 0;

            if(hp[i].relate(x, y)){
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
        bool b = hp[top-1].inter(hp[top], x, y);
        if(!b) return bot = top = -1, 0;        
        if(hp[bot].relate(x, y)){
            break;
        }else{
            --top;
        }
    }
    while(bot < top){
        bool b = hp[bot].inter(hp[bot+1], x, y);
        if(!b) return bot = top = -1, 0;  
            
        if(hp[top].relate(x, y)){
            break;
        }else{
            ++bot;
        }
    }

    return top - bot + 1;
}


};


/*** 9 Delaunay三角剖分和Voronoi图 ***/
struct Delaunay{ // 分治算法, NlogN

struct point_t{

Real x, y;
int id;
point_t(Real a=0,Real b=0,int c=-1):x(a),y(b),id(c){}

void input(){
    scanf("%Lf%Lf", &x, &y);
}

bool operator < (const point_t & r) const {
    int tmp = sgn(this->x - r.x);
    if(tmp) return tmp < 0;
    return this->y < r.y;
}

/**
 * 叉积，this作为点O，OA×OB
 */
Real cross(const point_t & a, const point_t & b) const {
    auto ax = a.x - this->x;
    auto ay = a.y - this->y;
    auto bx = b.x - this->x;
    auto by = b.y - this->y;
    return ax * by - bx * ay;
}

Real dist2(const point_t & r) const {
    auto x = this->x - r.x;
    auto y = this->y - r.y;
    return x * x + y * y;
}

};

struct t3t{

Real x, y, z;
t3t() = default;
t3t(Real a, Real b, Real c):x(a),y(b),z(c){}
t3t(const point_t & p):x(p.x),y(p.y){
    z = x * x + y * y;
}

Real dot(const t3t & p) const {
    return x * p.x + y * p.y + z * p.z;
}

t3t& operator -= (const t3t & r) {
    this->x -= r.x;
    this->y -= r.y;
    this->z -= r.z;
    return *this;
}

t3t cross(const t3t & r) const {
    return t3t(
        y * r.z - z * r.y,
        z * r.x - x * r.z,
        x * r.y - y * r.x
    );
}

};

struct edge_t{

int id;
list<edge_t>::iterator it;
edge_t(int i=0):id(i){}

};

vector<list<edge_t>> head;
vector<point_t> pts;
vector<int> rename;

/**
 * @brief 输入原始点集，一共n个点，编号[0, n-1]
 *   id也从[0, n-1]
 */
void input(int n){
    pts.assign(n, point_t());
    for(int i=0;i<n;++i){
        pts[pts[i].id = i].input();
    }
}

/**
 * @brief 拷贝原始点集，编号从[0, n-1]
 *  id也从[0, n-1]
 */
void input(const vector<Point> & origin_points){
    int n = origin_points.size();
    pts.assign(n, point_t());
    for(int i=0;i<n;++i){
        pts[pts[i].id = i].x = origin_points[i].x;
        pts[i].y = origin_points[i].y;
    }
}

/**
 * @brief Delaunay三角剖分的分治算法
 *  点集要事先保存在this->pts中
 *  会改变pts中的内容
 */
void run(){
    auto & rename = this->rename;
    auto & pts = this->pts;
    int n = pts.size();
    /// 初始化
    this->head.assign(n, list<edge_t>());
    rename.assign(n, 0);
    /// 排序
    sort(pts.begin(), pts.end());
    for(int i=0;i<n;++i) rename[pts[i].id] = i;
    /// 分治
    this->divide(0, n - 1);
}

/**
 * @brief 分治，处理[left, right]之间的点
 */
void divide(int left, int right){
    if(right <= left + 2){ // 说明少于等于3个点
        for(int i=left;i<=right;++i){
            for(int j=i+1;j<=right;++j){
                this->addEdge(i, j);
            }
        }
        return;
    }

    int mid = (left + right) >> 1;
    this->divide(left, mid);
    this->divide(mid + 1, right);

    auto & pts = this->pts;
    auto & head = this->head;

    int nowl = left, nowr = right;
    for(int update=1;update;){
        update = 0;
        auto ptL = pts[nowl], ptR = pts[nowr];
        for(auto it=head[nowl].begin(),et=head[nowl].end();it!=et;++it){
            auto t = pts[it->id];
            int tmp = sgn(ptR.cross(ptL, t));
            if(tmp > 0 || (0 == tmp && sgn(ptR.dist2(t) - ptR.dist2(ptL)) < 0)){
                nowl = it->id;
                update = 1;
                break;
            }
        }
        if(update) continue;
        for(auto it=head[nowr].begin(),et=head[nowr].end();it!=et;++it){
            auto t = pts[it->id];
            int tmp = sgn(ptL.cross(ptR, t));
            if(tmp < 0 || (0 == tmp && sgn(ptL.dist2(t) - ptL.dist2(ptR)) < 0)){
                nowr = it->id;
                update = 1;
                break;
            }
        }
    }

    this->addEdge(nowl, nowr);

    for(int update=1;;){
        update = 0;
        auto ptL = pts[nowl], ptR = pts[nowr];
        int ch = -1, side = 0;
        for(auto it=head[nowl].begin(),et=head[nowl].end();it!=et;++it){
            int tmp = sgn(ptL.cross(ptR, pts[it->id]));
            if(tmp > 0 && (-1 == ch || this->isInCircle(ptL, ptR, pts[ch], pts[it->id]) < 0)){
                ch = it->id, side = -1;
            }
        }
        for(auto it=head[nowr].begin(),et=head[nowr].end();it!=et;++it){
            int tmp = sgn(ptR.cross(pts[it->id], ptL));
            if(tmp > 0 && (-1 == ch || this->isInCircle(ptL, ptR, pts[ch], pts[it->id]) < 0)){
                ch = it->id; side = 1;
            }
        }
        if(-1 == ch) break;
        if(-1 == side){
            for(auto it=head[nowl].begin(),et=head[nowl].end();it!=et;){
                if(this->inter(ptL, pts[it->id], ptR, pts[ch])){
                    head[it->id].erase(it->it);
                    head[nowl].erase(it++);
                }else{
                    ++it;
                }
            } 
            nowl = ch;
            this->addEdge(nowl, nowr);
        }else{
            for(auto it=head[nowr].begin(),et=head[nowr].end();it!=et;){
                if(this->inter(ptR, pts[it->id], ptL, pts[ch])){
                    head[it->id].erase(it->it);
                    head[nowr].erase(it++);
                }else{
                    ++it;
                }
            }
            nowr = ch;
            this->addEdge(nowl, nowr);
        }
    }
    return;
}

/**
 * u到v之间加一条边
 */
void addEdge(int u, int v){
    this->head[u].push_front(edge_t(v));
    this->head[v].push_front(edge_t(u));
    this->head[u].begin()->it = this->head[v].begin();
    this->head[v].begin()->it = this->head[u].begin();
    return;
}

int isInCircle(const point_t & a, point_t b, point_t c, const point_t & p) const {
    if(sgn(a.cross(b, c)) < 0) swap(b, c);
    t3t a3(a), b3(b), c3(c), p3(p);
    b3 -= a3;
    c3 -= a3;
    p3 -= a3;
    t3t f = b3.cross(c3);
    int tmp = sgn(p3.dot(f));
    return tmp;
}

int inter(const point_t & a, const point_t & b, const point_t & c, const point_t & d) const {
    return sgn(a.cross(c, b)) * sgn(a.cross(b, d)) > 0
        && sgn(c.cross(a, d)) * sgn(c.cross(d, b)) > 0;
}

/**
 * @brief 获取剖分的结果, 返回三角形的边的数组
 *  ret[i]表示某条边，即从first到second有一条边
 *  注意编号指的是原点集中的编号。
 */
vector<pair<int, int>> getEdge(){
    vector<pair<int, int>> ret;
    auto & head = this->head;
    auto & pts = this->pts;
    int n = pts.size();
    
    ret.reserve(n);
    for(int i=0;i<n;++i){
        for(auto it=head[i].begin(),et=head[i].end();it!=et;++it){
            if(it->id < i) continue;
            ret.emplace_back(pts[i].id, pts[it->id].id);
        }
    }
    return ret;
}

};

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  

    return 0;
}


