/**
 * ����A��B����͹����Σ�B��A����
 * ��һ������͹�����C������C��A������C��B�Ĳ��ཻ
 * �����������������80���Σ�����Ū���������㷨
 * ����ȷ��ֻ����������п��ܲ������ֵ��
 * һ�������B�ı���Ϊֱ�߽�ȡA��һ����
 * ��һ�������A��B��ȡһ�����γ�ֱ�߽�ȡA��һ����
 * ��һ���������Ҫ�ж�ֱ���Ƿ�Ϸ�
 * �����������Ҫ��ȡֱ����A�Ľ���
 * ����ֻ��80������ʹ��O(N^3logN)���㷨
 * �Ե�һ���������B��ÿ�������ɰ�ƽ�棬
 * ֱ����A�İ�ƽ�����ƽ�潻��������ɣ�O(N^2logN)
 * �ڶ����������ȡһ�������ɰ�ƽ�棬�ֱ���A��B��ƽ���ཻ��
 * �����жϸ�ֱ���Ƿ�Ϸ��������������O(N^3logN)
 * ���N�Ƚϴ󣬾���Ҫ��������˫ָ�뷽��������2021CCPC���ֵ�ĳ����
 * ������O(N)�����
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
    /// ctor����a��b����ʱ�뷽��
    hp_t(const point_t & u, const point_t & v)
    :a(u.y - v.y)
    ,b(v.x - u.x)
    ,c(u.x * v.y - v.x * u.y){}
    /// ��ƽ���ཻ����֤����ֻ��һ������
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
    /// �жϵ��Ƿ��ڰ�ƽ����
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


/// ����������
/// ��֤����İ�ƽ���ཻΪ��գ�������������Ҫ���ȼӰ�Χ��
/// hp�ı��Ϊ0��n-1�����������hp[bot...top]
int sandi(hp_t hp[], int n, int & bot, int & top){
    /// ���򣬸��ݰ�ƽ��ķ�������������
    sort(hp, hp+n, [](const hp_t&u,const hp_t&v)->bool{
        /// ������λ��x�����£�����ֱ�ӵõ����
        int uy = u.b >= 0 ? 1 : -1;
        int vy = v.b >= 0 ? 1 : -1;
        if(uy != vy) return uy < vy;
        /// �����λ��x���ϣ��Ҳ�ͬ��
        if(is0(u.b) && is0(v.b) && u.a * v.a < 0) return u.a > v.a;
        /// ������
        Real chaji = u.a * v.b - u.b * v.a;
        if(sgn(chaji)) return chaji > 0;
        /// ����˵��������ƽ��
        if(sgn(u.a) > 0){
            /// ��hp1��hp2�������������������a1x+b1y+c1=0��a2x+b2y+c2>0
            return u.c * v.a < u.a * v.c;
        }
        if(sgn(u.a) < 0){
            return u.c * v.a > u.a * v.c;
        }
        /// ���aΪ0����b��Ȼ��Ϊ0
        assert(sgn(u.b));
        if(sgn(u.b) > 0){
            return u.c * v.b < u.b * v.c;
        }
        return u.c * v.b > u.b * v.c;
    });

    /// ƽ�еİ�ƽ��ֻȡһ��
    n = unique(hp, hp+n, [](const hp_t&u,const hp_t&v)->bool{
        int ly = u.b >= 0 ? 1 : -1;
        int ry = v.b >= 0 ? 1 : -1;
        if(ly != ry) return false;
        if(is0(u.b) && is0(v.b)) return u.a * v.a > 0;
        return is0(u.a * v.b - v.a * u.b);
    }) - hp;

    bot = 0, top = 1;
    for(int i=2;i<n;++i){
        /// ��ǰ�˵�������ƽ���ཻ
        while(bot < top){
            auto p = hp[top-1].inter(hp[top]);
            /// ��p�ڵ�ǰ��ƽ���⣬����
            if(hp[i].isIn(p)) break;
            else --top;
        }
        /// ��׶˵�������ƽ���ཻ
        while(bot < top){
            auto p = hp[bot].inter(hp[bot+1]);
            /// p�ڵ�ǰ��ƽ���⣬����
            if(hp[i].isIn(p)) break;
            else ++bot;
        }
        /// ���
        hp[++top] = hp[i];
    }
    /// ����
    while(bot < top){
        auto p = hp[top-1].inter(hp[top]);
        if(hp[bot].isIn(p)) break;
        else --top;
    }
    /// �ٺ���
    while(bot < top){
        auto p = hp[bot].inter(hp[bot+1]);
        if(hp[top].isIn(p)) break;
        else ++bot;
    }

    return top - bot + 1;
}

/// ����hp[s]��hpt[e]Χ�ɵ��������Ȼ��ʱ��
Real area(const hp_t hp[], int s, int e){
    /// �����������
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

/// �ж�hp�Ƿ���vec�������ط�������һ��over���Ӷȵķ���
bool inter(const hp_t & curhp, const vector<hp_t> & vec, Real a){
    hp_t hp[SIZE];
    copy(vec.begin(), vec.end(), hp);
    hp[vec.size()] = curhp; 
    int bot, top;
    int n = sandi(hp, vec.size()+1, bot, top);
    if(n < 3) return false;
    /// �������
    Real tmp = area(hp, bot, top);
    /// ��ƽ�潻�����Ϊ0��˵��curhp��ʵû�н���vec�������ط�
    if(is0(tmp)) return false;
    return true;
}

int N, M;
point_t A[SIZE], B[SIZE];

Real proc(){
    /// ��AB��������NM����ƽ��
    vector<hp_t> hpa, hpb;
    for(int i=0;i<N;++i) hpa.emplace_back(hp_t(A[i], A[i+1]));
    for(int i=0;i<M;++i) hpb.emplace_back(hp_t(B[i], B[i+1]));
    /// B���ε����
    Real bArea = 0;
    for(int i=1;i<M-1;++i){
        bArea += cross(B[0], B[i], B[i+1]);
    }
    bArea *= 0.5;

    Real ans = 0;

    /// ��B��ÿ��������һ��ֱ�ߣ�����ֱ���γ�һ����ƽ�棬��A������һ����ƽ�潻
    for(int bot, top, i=0;i<M;++i){
        hp_t hp[SIZE];
        copy(hpa.begin(), hpa.end(), hp);
        hp[N] = hp_t(B[i+1], B[i]); // ע���Ƿ�������
        int n = sandi(hp, N+1, bot, top);
        if(n < 3) continue;
        /// �����
        ans = max(ans, area(hp, bot, top));
    }      

    /// �ٽ�B��ÿ�����A��ÿ�����γ�һ����ƽ��
    for(int bot, top, i=0;i<M;++i)for(int j=0;j<N;++j){
        hp_t curhp(B[i], A[j]);
        hp_t hp[SIZE];
        bool b1 = inter(curhp, hpb, bArea);
        if(!b1){ /// ˵��curhp������������
            copy(hpa.begin(), hpa.end(), hp);
            hp[N] = curhp;
            int n = sandi(hp, N+1, bot, top);
            if(n >= 3) ans = max(ans, area(hp, bot, top));
        }
        curhp = {A[j], B[i]}; // ����������һ��
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

