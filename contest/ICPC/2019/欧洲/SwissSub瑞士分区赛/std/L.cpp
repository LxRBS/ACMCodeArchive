#include <vector>
#include <iostream>
using namespace std;

#define x first
#define y second
typedef std::pair<int,int> pii; typedef long long ll; typedef unsigned long long ull; typedef unsigned int ui; typedef pair<ui,ui> puu;

template<typename T>class vector2:public vector<vector<T>>{public:vector2(){} vector2(size_t a,size_t b,T t=T()):vector<vector<T>>(a,vector<T>(b,t)){}};


template <unsigned int N> class Field {
    typedef unsigned int ui;
    typedef unsigned long long ull;
	inline ui pow(ui a, ui p){ui r=1,e=a;while(p){if(p&1){r=((ull)r*e)%N;}e=((ull)e*e)%N;p>>=1;}return r;}
	inline ui inv(ui a){return pow(a,N-2);}
public:
    inline Field(int x = 0) : v(x) {}
	inline Field<N> pow(int p){return (*this)^p; }
	inline Field<N> operator^(int p){return {(int)pow(v,(ui)p)};}
    inline Field<N>&operator+=(const Field<N>&o) {if (v+o.v >= N) v += o.v - N; else v += o.v; return *this; }
    inline Field<N>&operator-=(const Field<N>&o) {if (v<o.v) v -= o.v-N; else v-=o.v; return *this; }
    inline Field<N>&operator*=(const Field<N>&o) {v=(ull)v*o.v % N; return *this; }
    inline Field<N>&operator/=(const Field<N>&o) { return *this*=inv(o.v); }
    inline Field<N> operator+(const Field<N>&o) const {Field<N>r{*this};return r+=o;}
    inline Field<N> operator-(const Field<N>&o) const {Field<N>r{*this};return r-=o;}
    inline Field<N> operator*(const Field<N>&o) const {Field<N>r{*this};return r*=o;}
    inline Field<N> operator/(const Field<N>&o) const {Field<N>r{*this};return r/=o;}
    inline Field<N> operator-() {if(v) return {(int)(N-v)}; else return {0};};
    inline Field<N>& operator++() { ++v; if (v==N) v=0; return *this; }
    inline Field<N> operator++(int) { Field<N>r{*this}; ++*this; return r; }
    inline Field<N>& operator--() { --v; if (v==-1) v=N-1; return *this; }
    inline Field<N> operator--(int) { Field<N>r{*this}; --*this; return r; }
    inline bool operator==(const Field<N>&o) const { return o.v==v; }
	inline bool operator!=(const Field<N>&o) const { return o.v!=v; }
	inline explicit operator ui() const { return v; }
	inline static vector<Field<N>>fact(int t){vector<Field<N>>F(t+1,1);for(int i=2;i<=t;++i){F[i]=F[i-1]*i;}return F;}
	inline static vector<Field<N>>invfact(int t){vector<Field<N>>F(t+1,1);Field<N> X{1};for(int i=2;i<=t;++i){X=X*i;}F[t]=1/X;for(int i=t-1;i>=2;--i){F[i]=F[i+1]*(i+1);}return F;}
private: ui v;
};
template<unsigned int N>istream &operator>>(std::istream&is,Field<N>&f){unsigned int v;is>>v;f=v;return is;}
template<unsigned int N>ostream &operator<<(std::ostream&os,const Field<N>&f){return os<<(unsigned int)f;}
template<unsigned int N>Field<N> operator+(int i,const Field<N>&f){return Field<N>(i)+f;}
template<unsigned int N>Field<N> operator-(int i,const Field<N>&f){return Field<N>(i)-f;}
template<unsigned int N>Field<N> operator*(int i,const Field<N>&f){return Field<N>(i)*f;}
template<unsigned int N>Field<N> operator/(int i,const Field<N>&f){return Field<N>(i)/f;}

typedef Field<1000000007> FieldMod;

class treequeries {
public:
    void solve(istream& cin, ostream& cout) {
        int Q; cin >> Q;
        vector<FieldMod> B(31, 0);
        vector2<int> C(31, 31, 0);
        for (int i = 0; i <= 30; ++i) {
            C[i][0] = C[i][i] = 1;
            for (int j = 1; j < i; ++j) C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
        auto add = [&](int x, FieldMod s) {
            int pref = 0, cnt = 0;
            for (int i = 30; i >= 0; --i) {
                if (x&1<<i) {
                    for (int j = 0; j <= i; ++j) B[cnt+j] += s * C[i][j];

                    pref |= 1<<i;
                    cnt++;
                }
            }
        };

        for (int q = 0; q < Q; ++q) {
            int t, l, r; cin >> t >> l >> r;
            if (t == 0) {
                FieldMod X; cin >> X;
                add(r, X);
                add(l, -X);
            } else {
                FieldMod ans = 0;
                for (int i = 31-r; i < 31-l; ++i) ans += B[i];
                cout << ans << '\n';
            }
        }
    }
};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	treequeries solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
    return 0;
}