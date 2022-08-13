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
int const SIZE = 23;
#else
int const SIZE = 1010;
#endif

HalfPlane<Real> Hp[SIZE];
Point64F P[SIZE];
int N;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int k = 0;
    /// 包围盒
    Hp[k++] = {Point64F(-INF, 1), Point64F(-INF, 0)}; // 左
    Hp[k++] = {Point64F(+INF, 0), Point64F(+INF, 1)}; // 右
    Hp[k++] = {Point64F(1, +INF), Point64F(0, +INF)}; // 上
    Hp[k++] = {Point64F(0, -INF), Point64F(1, -INF)}; // 下
    N = getInt();
    for(int m,i=0;i<N;++i){
        m = getInt();
        for(int j=0;j<m;++j) P[j].x=getInt(), P[j].y=getInt();
        P[m] = P[0];
        for(int j=0;j<m;++j) Hp[k++] = {P[j], P[j+1]};
    }
    
    int bot, top;
    int n = HalfPlane<Real>::sandi(Hp, k, bot, top);
    if(n <= 2) {
        puts("0.000"); return 0;
    }
    /// 求交点
    Point64F p;
    bool b = Hp[top].inter(Hp[bot], p);
    assert(b);
    vector<Point64F> vec(1, p);
    for(int i=bot; i<top;++i){
        bool b = Hp[i].inter(Hp[i+1], p);
        assert(b);        
        vec.emplace_back(p);
    }
    Real ans = 0;
    for(int i=0,n=vec.size();i<n-1;++i){
        ans += vec[0].cross(vec[i], vec[i+1]);
    }
    cout << fixed << setprecision(3) << 0.5 * ans << endl;
    return 0;
}
