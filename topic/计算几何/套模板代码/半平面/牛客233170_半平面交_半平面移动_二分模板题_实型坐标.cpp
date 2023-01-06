/**
 * 给定一个凸多边形，看作小岛。问小岛上距离海边最远的点，求这个最远距离
 * 将小岛的边均向内推进距离d，恰好交于一点，则该点是最远点，且d是最远距离
 * 二分距离d，半平面相交即可。
 * 因为要二分，所以直接采用实型坐标
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
 
#ifndef ONLINE_JUDGE
int const SIZE = 23;
#else
int const SIZE = 2E5+10;
#endif


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

using T = Real;

struct Point{

T x, y;
Point() = default;
Point(T a, T b):x(a),y(b){}

void input(){
    // this->x = getInt();
    // this->y = getInt();
    scanf("%Lf%Lf", &x, &y);
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


int relate(const Point & A, const Point & B) const {
    assert(!(A == B));
    if(A == *this || B == *this) return IN | VERTEX;
    if(sgn(this->dot(A, B)) <= 0 && 0 == sgn(this->cross(A, B))){
        return IN | EDGE;
    }
    return OUT;    
}


Real dist(const Point & A, const Point & B) const {
    if(IN & this->relate(A, B)) return 0;
    if(sgn(A.dot(*this, B)) <= 0) return this->dist(A);
    if(sgn(B.dot(*this, A)) <= 0) return this->dist(B);
    /// 距离为高
    return fabs(this->cross(A, B)) / (A - B).length();
}

};

struct HalfPlane{

/// ax+by+c >= 0, (a, b)就是法向量
T a, b, c; 

HalfPlane() = default;

HalfPlane(T aa, T bb, T cc):a(aa),b(bb),c(cc){}

HalfPlane(const Point &u, const Point &v){
    /// 与直线生成一模一样
    assert(!(u == v));
    this->a = u.y - v.y;
    this->b = v.x - u.x;
    this->c = u.x * v.y - v.x * u.y;    
}

Real eval(Real x, Real y) const {return a * x + b * y + c;}


int relate(Real x, Real y) const {
    int r = sgn(eval(x, y));
    if(0 == r) return IN | EDGE;
    if(r > 0) return IN;
    return OUT;
}


bool inter(const HalfPlane & r, Real & x, Real & y) const {
    const T xishu = a * r.b - b * r.a;
    if(is0(xishu)) return false;
    Real tmp = xishu;
    x = (b * r.c - c * r.b) / tmp;
    y = (c * r.a - a * r.c) / tmp;
    return true;
}


HalfPlane move(T d) const {
    return HalfPlane(a, b, c - d * sqrt(a * a + b * b));
}

static int bound(HalfPlane hp[], int n, T inf){
    hp[n++] = {Point(-inf, 1), Point(-inf, 0)}; // 左
    hp[n++] = {Point(+inf, 0), Point(+inf, 1)}; // 右
    hp[n++] = {Point(1, +inf), Point(0, +inf)}; // 上
    hp[n++] = {Point(0, -inf), Point(1, -inf)}; // 下
    return n;
}

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

int N;
HalfPlane Hp[SIZE], Oh[SIZE];
Point P[SIZE];

/// 将所有半平面移动d，看交集是否为空，为空返回true
bool check(Real d){
    for(int i=0;i<N;++i){
        Hp[i] = Oh[i].move(d);
    }
    /// 加包围盒
    int k = HalfPlane::bound(Hp, N, 1E10);

    int bot, top;
    int n = HalfPlane::sandi(Hp, k, bot, top);
    return n <= 2;
}

Real proc(){
    P[N] = P[0];
    for(int i=0;i<N;++i) Oh[i] = {P[i], P[i+1]};

    Real left = 0, right = 1E6, mid;
    do{
        mid = (left + right) * 0.5;
        if(check(mid)) right = mid - EPS;
        else left = mid + EPS;
    }while(sgn(left - right) <= 0);
    return right;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    while(1){
        scanf("%d", &N);
        if(0 == N) return 0;

        for(int i=0;i<N;++i) P[i].input();
        printf("%.12Lf\n", proc());
    }
    return 0;
}


