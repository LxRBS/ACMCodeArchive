/**
 * 给定一个凸多边形，我方首先放置一个指挥塔
 * 敌人删除若干个顶点使得指挥塔落在剩余多边形的外面
 * 问: 如果我方用最优放置策略, 敌人至少要删除多少个点以确保指挥塔落在外面
 * 显然如果敌人把点全删了, 必然能够落在外面
 * 简单推理就知道敌人没有必要分开删点，即如果要删除n个点，则这n个点必然是连在一起的
 * 则在删除n个点的前提下，剩下的图形是一个半平面交
 * 如果这个半平面交是空集或者面积为0(面积为0很重要, 估计有1个测试点就是这样的数据)
 * 则我方无论如何不能存活
 * 这个n显然是单调的，二分搜索即可
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
using coor = Real;  // 默认是整数坐标
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

/** 8 半平面交排序增量法 **/
/// 半平面交需要求交点或者移动，直接使用实数类型作为坐标
struct HalfPlane{
    Real a, b, c; // ax+by+c >= 0, 法向量为(a, b), 
    HalfPlane(Real aa=0, Real bb=0, Real cc=0):a(aa),b(bb),c(cc){}
    /// 两点生成一个半平面，从u到v是逆时针，即半平面在uv的左手边
    HalfPlane(const Point &u, const Point &v){
        /// 与直线生成一模一样
        assert(!(u == v));
        this->a = u.y - v.y;
        this->b = v.x - u.x;
        this->c = u.x * v.y - v.x * u.y;
    }
    /// 点p是否在半平面上
    bool contains(const Point &p) const {
        return sgn(a * p.x + b * p.y + c) >= 0;
    }
    /// 半平面相交求交点，保证相交
    /// 只有一种情况需要特判，就是法向量相反，且交集为空的情况
    /// 该特殊情况在排序增量法中直接得到半平面交为空集
    /// 返回真表示交点有效，返回false表示特殊情况
    bool inter(const HalfPlane &r, Point &p) const {
        const auto xishu = a * r.b - r.a * b;
        if(is0(xishu)) return false;
        p = {(b * r.c - r.b * c) / xishu, (c * r.a - r.c * a) / xishu};
        return true;
    }
    /// 半平面沿着法向量方向移动距离d, 为负数表示沿着法向量反方向移动
    HalfPlane move(Real d) const {
        return HalfPlane(a, b, c - d * sqrt(a*a+b*b));
    }
};

/// 半平面交的排序增量法
/// 保证结果是有限的，否则需要加包围盒，因此n肯定大于4
/// 会改变hp的内容，0-index
/// 结果保存在hp[bot..top]中
/// 返回top-bot+1，即半平面的数量，如果小于3，说明原交集为空集
int sandi(HalfPlane hp[], int n, int&bot, int &top){
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
        
        /// 到此处说明平行 
        /// 当a大于0
        if(sgn(u.a) > 0){
            /// 若hp1比hp2更靠近法向量，则必有a1x+b1y+c1=0而a2x+b2y+c2>0
            return u.c * v.a < u.a * v.c;
        }
        if(sgn(u.a) < 0){ // 小于0就是反过来
            return u.c * v.a > u.a * v.c;
        }
        /// a为0则b必不为0
        if(sgn(u.b > 0)){
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
    Point p;
    for(int i=2;i<n;++i){
        /// 最前端的两个半平面相交
        while(bot < top){
            bool b = hp[top-1].inter(hp[top], p);
            if(!b) return bot = top = -1, 0; // 直接返回空集即可

            /// 交点在当前半平面外则出队            
            if(hp[i].contains(p)){
                break;
            }else{
                --top;
            }
        }
        /// 最底端的两个半平面相交
        while(bot < top){
            bool b = hp[bot].inter(hp[bot+1], p);
            if(!b) return bot = top = -1, 0;

            if(hp[i].contains(p)){
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
        if(hp[bot].contains(p)){
            break;
        }else{
            --top;
        }
    }
    while(bot < top){
        bool b = hp[bot].inter(hp[bot+1], p);
        if(!b) return bot = top = -1, 0;  
            
        if(hp[top].contains(p)){
            break;
        }else{
            ++bot;
        }
    }

    return top - bot + 1;
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

int N;
Point P[SIZE];
HalfPlane Hp[SIZE];

/// 炸n个点，是否能够存活
bool check(int n){
    if(n + 2 >= N) return false;
    int k = 0;
    /// 包围盒    
    Hp[k++] = {Point(-INF, 1), Point(-INF, 0)}; // 左
    Hp[k++] = {Point(+INF, 0), Point(+INF, 1)}; // 右
    Hp[k++] = {Point(1, +INF), Point(0, +INF)}; // 上
    Hp[k++] = {Point(0, -INF), Point(1, -INF)}; // 下
    for(int i=0;i<N;++i){
        Hp[k++] = {P[(i+n)%N], P[(i-1+N)%N]};
    }
    /// 交
    int bot, top;
    k = sandi(Hp, k, bot, top);
    if(k <= 2) return false;
    /// 计算面积
    Point p;
    vector<Point> vec;
    Hp[top+1] = Hp[bot];
    for(int i=bot;i<=top;++i){
        bool b = Hp[i].inter(Hp[i+1], p);
        assert(b);
        vec.emplace_back(p);
    }
    Real ans = 0;
    for(int i=0,n=vec.size();i<n-1;++i){
        ans += cross(vec[0], vec[i], vec[i+1]);
    }
    if(is0(ans)) return false;
    return true;
}

int proc(){
    /// 特判
    if(3 == N) return 1;
    // if(4 == N) return 2;

    int left = 1, right = N, mid;
    do{
        mid = (left + right) >> 1;
        if(check(mid)) left = mid + 1;
        else right = mid - 1;
    }while(left <= right);
    return left;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    N = getInt();
    for(int i=0;i<N;++i) P[i].x = getInt(), P[i].y = getInt();
    printf("%d\n", proc());
    return 0;
}
