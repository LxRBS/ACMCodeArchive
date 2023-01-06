/**
 * 给定两个凸包A和B，求最近距离
 * 求出A和B的闵可夫斯基差，则最近距离就是原点到A-B的距离
 * 原题转为了点到凸包的距离。
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


struct Convex{

vector<Point> pts; // 编号从0开始，逆时针

void input(int n){
    this->pts.assign(n, Point());
    for(auto & p : this->pts) p.input();
}

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
//     for(auto & p : pc){
//         cout << "(" << p.x << ", " << p.y << ")" << endl;
//     }
    /// 再将pc依次连接起来即可，pc中可能存在共线的点
    pc[0].x += pa[ka].x + pb[kb].x;
    pc[0].y += pa[ka].y + pb[kb].y;
    for(int i=1;i<nc;++i){
        pc[i].x += pc[i-1].x;
        pc[i].y += pc[i-1].y;
    }
    return;        
}

};

int N, M;
Convex A, B, C;
const Point Origin(0, 0);

Real proc(){
    int na = A.Graham();
    // B要负一下
    for(auto & p : B.pts) p.x = -p.x, p.y = -p.y; 
    int nb = B.Graham();
    
    A.Minkowski(B, C);

    if(IN & C.relate(Origin)) return 0;

    Real ans = 1E100;
    auto & p = C.pts;
    int n = p.size();
    for(int i=0;i<n;++i){
        ans = min(ans, Origin.dist(p[i], p[(i+1)%n]));
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    while(scanf("%d%d", &N, &M)){
        if(0 == N && 0 == M) break;
        A.input(N);
        B.input(M); 
        printf("%.12Lf\n", proc());       
    }

    return 0;
}


