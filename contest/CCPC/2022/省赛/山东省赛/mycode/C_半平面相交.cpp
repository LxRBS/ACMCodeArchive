/**
 * 给定A和B两个凸多边形，B在A里面
 * 找一个最大的凸多边形C：满足C在A里面且C与B的不相交
 * 求这个最大的面积，最多80边形，可以弄个立方的算法
 * 首先确定只有两种情况有可能产生最大值，
 * 一种情况是B的边作为直线截取A的一部分
 * 另一种情况是A、B各取一个点形成直线截取A的一部分
 * 后一种情况还需要判断直线是否合法
 * 两种情况都需要求取直线与A的交点
 * 由于只有80，可以使用O(N^3logN)的算法
 * 对第一种情况，把B的每条边做成半平面，
 * 直接与A的半平面求半平面交的面积即可，O(N^2logN)
 * 第二种情况，各取一个点做成半平面，分别与A、B半平面相交，
 * 既能判断该直线是否合法，又能求到面积，O(N^3logN)
 * 如果N比较大，就需要采用类似双指针方法，类似2021CCPC桂林的某道题
 * 可以在O(N)解决。
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
int const SIZE = 7;
#else
int const SIZE = 88;
#endif


using Real = long double;
Real const EPS = 1E-9;
Real const PI = acos(-1.0L);
inline int sgn(Real x){return x >= EPS ? 1 : (x <= -EPS ? -1 : 0);}
inline bool is0(Real x){return 0 == sgn(x);}

struct point_t{
    Real x, y;
    point_t(Real a=0, Real b=0):x(a),y(b){}
    void input(){
        this->x = getInt();
        this->y = getInt();
    }
    Real dist(const point_t & p)const{
        Real x = this->x - p.x;
        Real y = this->y - p.y;
        return sqrt(x * x + y * y);
    }
};

struct hp_t{
    Real a, b, c; // ax + by + c >= 0
    hp_t():a(0),b(0),c(0){}
    /// ctor，从a到b，逆时针方向
    hp_t(const point_t & u, const point_t & v)
    :a(u.y - v.y)
    ,b(v.x - u.x)
    ,c(u.x * v.y - v.x * u.y){}
    /// 半平面相交，保证有且只有一个交点
    point_t inter(const hp_t & r)const{
        Real xishu = this->a * r.b - r.a * this->b;
        if(0 == sgn(xishu)){
            this->output();
            r.output();
            throw runtime_error("xx");
        }
        return point_t(
            (this->b * r.c - r.b * this->c) / xishu,
            (this->c * r.a - this->a * r.c) / xishu
        );
    }
    /// 判断点是否在半平面内
    bool isIn(const point_t & p)const{
        Real v = this->a * p.x + this->b * p.y + this->c;
        return sgn(v) >= 0;
    }
    void output()const{
        cout<<fixed<<setprecision(2)<<a<<"x+"<<b<<"y+"<<c<<">=0"<<endl;
    }
};

Real cross(const point_t &O, const point_t &A, const point_t &B){
    Real xoa = A.x - O.x;
    Real yoa = A.y - O.y;
    Real xob = B.x - O.x;
    Real yob = B.y - O.y;
    return xoa * yob - xob * yoa;
}


/// 排序增量法
/// 保证输入的半平面相交为封闭，如果不满足就需要事先加包围盒
/// hp的编号为0到n-1，结果保存在hp[bot...top]
int sandi(hp_t hp[], int n, int & bot, int & top){
    /// 排序，根据半平面的法向量极角排序
    sort(hp, hp+n, [](const hp_t&u,const hp_t&v)->bool{
        /// 法向量位于x轴上下，可以直接得到结果
        int uy = u.b >= 0 ? 1 : -1;
        int vy = v.b >= 0 ? 1 : -1;
        if(uy != vy) return uy < vy;
        /// 如果都位于x轴上，且不同向
        if(is0(u.b) && is0(v.b) && u.a * v.a < 0) return u.a > v.a;
        /// 计算叉积
        Real chaji = u.a * v.b - u.b * v.a;
        if(sgn(chaji)) return chaji > 0;
        /// 到此说明法向量平行
        if(sgn(u.a) > 0){
            /// 若hp1比hp2更靠近法向量，则必有a1x+b1y+c1=0而a2x+b2y+c2>0
            return u.c * v.a < u.a * v.c;
        }
        if(sgn(u.a) < 0){
            return u.c * v.a > u.a * v.c;
        }
        /// 如果a为0，则b必然不为0
        assert(sgn(u.b));
        if(sgn(u.b) > 0){
            return u.c * v.b < u.b * v.c;
        }
        return u.c * v.b > u.b * v.c;
    });

    /// 平行的半平面只取一个
    n = unique(hp, hp+n, [](const hp_t&u,const hp_t&v)->bool{
        int ly = u.b >= 0 ? 1 : -1;
        int ry = v.b >= 0 ? 1 : -1;
        if(ly != ry) return false;
        if(is0(u.b) && is0(v.b)) return u.a * v.a > 0;
        return is0(u.a * v.b - v.a * u.b);
    }) - hp;

    bot = 0, top = 1;
    for(int i=2;i<n;++i){
        /// 最前端的两个半平面相交
        while(bot < top){
            auto p = hp[top-1].inter(hp[top]);
            /// 当p在当前半平面外，出队
            if(hp[i].isIn(p)) break;
            else --top;
        }
        /// 最底端的两个半平面相交
        while(bot < top){
            auto p = hp[bot].inter(hp[bot+1]);
            /// p在当前半平面外，出队
            if(hp[i].isIn(p)) break;
            else ++bot;
        }
        /// 入队
        hp[++top] = hp[i];
    }
    /// 后处理
    while(bot < top){
        auto p = hp[top-1].inter(hp[top]);
        if(hp[bot].isIn(p)) break;
        else --top;
    }
    /// 再后处理
    while(bot < top){
        auto p = hp[bot].inter(hp[bot+1]);
        if(hp[top].isIn(p)) break;
        else ++bot;
    }

    return top - bot + 1;
}

/// 计算hp[s]到hpt[e]围成的面积，必然逆时针
Real area(const hp_t hp[], int s, int e){
    /// 首先求出交点
    vector<point_t> vec;
    for(int i=s;i<e;++i){
        vec.emplace_back(hp[i].inter(hp[i+1]));
    }
    vec.emplace_back(hp[e].inter(hp[s]));
    Real ans = 0;
    for(int i=1,n=vec.size()-1;i<n;++i){
        ans += cross(vec[0], vec[i], vec[i+1]);
    }
    return 0.5 * ans;
}

/// 判断hp是否交于vec的其他地方，这是一个over复杂度的方法
bool inter(const hp_t & curhp, const vector<hp_t> & vec, Real a){
    hp_t hp[SIZE];
    copy(vec.begin(), vec.end(), hp);
    hp[vec.size()] = curhp; 
    int bot, top;
    int n = sandi(hp, vec.size()+1, bot, top);
    if(n < 3) return false;
    /// 计算面积
    Real tmp = area(hp, bot, top);
    /// 半平面交的面积为0，说明curhp其实没有交到vec的其他地方
    if(is0(tmp)) return false;
    return true;
}

int N, M;
point_t A[SIZE], B[SIZE];

Real proc(){
    /// 将AB边形生成NM个半平面
    vector<hp_t> hpa, hpb;
    for(int i=0;i<N;++i) hpa.emplace_back(hp_t(A[i], A[i+1]));
    for(int i=0;i<M;++i) hpb.emplace_back(hp_t(B[i], B[i+1]));
    /// B边形的面积
    Real bArea = 0;
    for(int i=1;i<M-1;++i){
        bArea += cross(B[0], B[i], B[i+1]);
    }
    bArea *= 0.5;

    Real ans = 0;

    /// 将B的每条边做成一条直线，这条直线形成一个半平面，与A边形求一个半平面交
    for(int bot, top, i=0;i<M;++i){
        hp_t hp[SIZE];
        copy(hpa.begin(), hpa.end(), hp);
        hp[N] = hp_t(B[i+1], B[i]); // 注意是反过来的
        int n = sandi(hp, N+1, bot, top);
        if(n < 3) continue;
        /// 求面积
        ans = max(ans, area(hp, bot, top));
    }      

    /// 再将B的每个点和A的每个点形成一个半平面
    for(int bot, top, i=0;i<M;++i)for(int j=0;j<N;++j){
        hp_t curhp(B[i], A[j]);
        hp_t hp[SIZE];
        bool b1 = inter(curhp, hpb, bArea);
        if(!b1){ /// 说明curhp可以用来计算
            copy(hpa.begin(), hpa.end(), hp);
            hp[N] = curhp;
            int n = sandi(hp, N+1, bot, top);
            if(n >= 3) ans = max(ans, area(hp, bot, top));
        }
        curhp = {A[j], B[i]}; // 反过来再来一遍
        bool b2 = inter(curhp, hpb, bArea);
        if(!b2){
            copy(hpa.begin(), hpa.end(), hp);
            hp[N] = curhp;
            int n = sandi(hp, N+1, bot, top);
            if(n >= 3) ans = max(ans, area(hp, bot, top));            
        }
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); 
    for(int i=0;i<N;++i) A[i].input();
    A[N] = A[0];
    M = getInt();
    for(int i=0;i<M;++i) B[i].input();
    B[M] = B[0];
    cout << fixed << setprecision(12) << proc() << endl;
    return 0;
}

