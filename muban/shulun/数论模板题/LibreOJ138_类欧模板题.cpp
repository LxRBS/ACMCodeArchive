/**
 * 令 f(i) = floor((Pi + R) / Q)
 * 求 SIGMA{i^K1 * f(i)^K2, i=0...N}
 * 类欧模板题，注意当K1==0时，认为i=0是有意义的
 */
#include <bits/stdc++.h>
using namespace std;

namespace IO{

char *__abc147, *__xyz258, __ma369[1000000];
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

using llt = long long;

llt getLL(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;    
}

char getChar(function<bool(char)> ok){
    char ch = __hv007();
    while(!ok(ch)) ch = __hv007();
    return ch;
}

}

namespace SHULUN{

template<long long MOD = 998244353LL>
struct modint{

using T = long long;
using int128 = __int128_t;
// using int128 = T; // 如果MOD不是特大的情况下，不要用128，否则会导致耗时增加

static const T mod(){return MOD;}

T value;
explicit modint(T v = 0):value((v%MOD+MOD)%MOD){}

static const modint ZERO(){
    static modint zero(0);
    return zero;
}

static const modint ONE(){
    static modint one(1);
    return one;
}

static const modint TWO(){
    static modint two(2);
    return two;
}

static T pow(T a, T n){
    T ret = 1;
	while(n){
        if(n & 1) ret = (int128)ret * a % MOD; // MOD特大的时候需要先转128
		a = (int128)a * a % MOD; // MOD特大的时候需要先转128
		n >>= 1;
	}
	return ret;
}
/// MOD为质数才行
static T inv(T a) {return modint::pow(a, MOD - 2);}

/// this的n次方, 重载方括号为了保证优先级
const modint operator [] (T n) const {return modint(modint::pow(this->value, n));}
modint & operator ^= (T n) {this->value=modint::pow(this->value, n); return *this;}

const modint operator + (const modint & r) const {return modint(value + r.value);}
modint & operator += (const modint & r) {(value+=r.value)%=MOD; return *this;}

const modint operator - (const modint & r) const {return modint(value - r.value);}
modint & operator -= (const modint & r) {(value-=r.value)%=MOD; return *this;}

const modint operator * (const modint & r) const {
    return modint((int128)value * r.value % MOD); // MOD特大的时候需要先转128
}
modint & operator *= (const modint & r) {
    value = (int128)value * r.value % MOD; // MOD特大的时候要转128 
    return *this;
}

const modint operator / (const modint & r) const {
    return modint((int128)value * modint::inv(r.value) % MOD);
}

modint & operator /= (const modint & r) {
    value = (int128)value * modint::inv(r.value) % MOD;
    return *this;
}

bool operator ! () const {return !value;}

};

}


namespace ZUHE{


struct CSimple{ // 小规模计算组合数

using T = SHULUN::modint<1000000007LL>;

using vt = vector<T>;
using vvt = vector<vt>;

vvt c;

CSimple() = default;

// n取m的组合数
T get(int n, int m) const {return c[n][m];}

void init(int n){
    this->c.assign(n + 1, vt());
    for(int i=0;i<=n;++i){
        auto & vec = c[i];
        vec.reserve(i + 1);
        vec.emplace_back(T(1));
    }
    for(int i=1;i<=n;++i){
        const auto & prv = c[i - 1];
        auto & vec = c[i];
        for(int j=1;j<i;++j){
            vec.emplace_back(prv[j - 1] + prv[j]);
        }
        vec.emplace_back(T(1));
    }
    return;
}

};

}

namespace SHULUN{

using llt = long long;
using int128 = __int128_t;

/// T需要支持加法和乘法运算,注意不满足交换律, p是乘数，q是分母，r是加数
/// n是累加上限，即累加从1到n，su是U事件的信息，sr是r事件的信息
template<typename T>
T __dfs_uniEuclid(llt p, llt q, llt r, llt n, T su, T sr){
    if(r >= q) {
		return su * (r / q) + __dfs_uniEuclid(p, q, r % q, n, su, sr);
	}
	if(p >= q){
		return __dfs_uniEuclid(p % q, q, r, n, su, su * (p / q) + sr);
	}
	llt k = (static_cast<int128>(p) * n + r) / q; // 乘法可能超
	if(0 == k){
		return sr * n;
	}

	auto ans = sr * ((q - r - 1) / p);
	ans += su;
	ans += __dfs_uniEuclid(q, p, (q - r - 1) % p, k - 1, sr, su);
    ans += sr * (n - (static_cast<int128>(k) * q - r - 1) / p);
	return ans;
}

/// T需要支持加法和乘法运算,注意不满足交换律, 
/// T需要提供sr和su的构造方法
/// p是乘数，q是分母，r是加数
/// n是累加上限，即累加从1到n
/// q必须不为0，如果n为0或者p为0，要在外面单独计算
/// 构造不同的T，就可以支持不同的求和式
template<typename T>
T uniEuclid(llt p, llt q, llt r, llt n){
	assert(p && q && n);
	// T sr(1, 0, 0); // 表示x=0与f相交的情况
	// T su(0, 1, 0); // 表示y=1与f相交的情况
    // auto ans = __dfs_uniEuclid(p, q, r, n, su, sr);
	// return ans;
	// return __dfs_uniEuclid(p, q, r, n, T(0, 1, 0), T(1, 0, 0));
    return __dfs_uniEuclid(p, q, r, n, T::su(), T::sr());
}


struct pqr01{

/// floor((pi + r) / q)
/// 与uniEuclid配合使用，即可求出 SUM{floor(i), i=1...n}

using INT = llt; // 不取模就直接用longlong
// using INT = SHULUN::mint;

/// 分别表示x的整点数量，y的整点数量，s即表示结果的和
INT x, y, s;

pqr01() = default;
pqr01(llt xx, llt yy, llt ss):x(xx),y(yy),s(ss){}

static pqr01 sr(){return pqr01(1, 0, 0);}
static pqr01 su(){return pqr01(0, 1, 0);}

pqr01 & operator += (const pqr01 & r){
	/// this->y表示左边段的y整点数量, r.x表示右边x的整点数量
	/// 相乘恰好表明右边段下方矩形的整点数量
	this->s += r.s + this->y * r.x;	
	this->x += r.x; // 两段的整点数量相加
	this->y += r.y;
	return *this;
}

const pqr01 operator + (const pqr01 & r) const {
    auto tmp(*this);
	return tmp += r;
}

pqr01 & operator *= (llt n){
	if(0 == n) {x = y = s = INT(0); return *this;}
	if(1 == n) return *this;
	n -= 1;
	auto tmp(*this);
	while(n){
		if(n & 1) *this += tmp;
		tmp += tmp;
		n >>= 1; 
	}
	return *this;
}

const pqr01 operator * (llt n) const {
	auto tmp(*this); return tmp *= n;
}


};


struct pqr_suit{

/// f(i) = floor((pi+r)/q)
/// g(i) = f * f
/// h(i) = i * f
/// 分别计算 SUM{f}, SUM{g}, SUM{h}

using INT = mint;

INT x, y; // x和y的整点数
INT sigmax; // x的累加和，即从1加到x
INT sf; // SUM{f}
INT sg; // SUM{g}
INT sh; // SUM{h}

pqr_suit() = default;
pqr_suit(llt xx, llt yy, llt sigmaxx, llt sff, llt sgg, llt shh):x(xx),y(yy),sigmax(sigmaxx),sf(sff),sg(sgg),sh(shh){}

static pqr_suit su(){return pqr_suit(0,1,0,0,0,0);}
static pqr_suit sr(){return pqr_suit(1,0,1,0,0,0);}

pqr_suit & operator += (const pqr_suit & r){
	/// 对sh，r的贡献为 SIGMA{(yi+y)*(xi+x), (xi,yi)为r中的整点}，其中x和y是this两个方向的整点维度
	/// xi*yi + xi*y + x*yi + x*y，一共有r.x项，求和以后，这四项分别是
	/// r.sh + r.sigmax*y + x*r.sf + x*y*r.x
    this->sh += r.sh + r.sigmax * this->y + this->x * r.sf + this->x * this->y * r.x;
    /// 对sg，r的贡献为 SIGMA{(yi+y)*(yi+y)}，即 yi*yi + 2*y*yi + y*y
	this->sg += r.sg + INT(2) * this->y * r.sf + this->y * this->y * r.x;
	/// sf比较简单
	this->sf += r.sf + this->y * r.x;
	/// 还要维护sigmax
	this->sigmax += r.sigmax + this->x * r.x;
	this->x += r.x;
	this->y += r.y; 	
	return *this;
}

const pqr_suit operator + (const pqr_suit & r) const {pqr_suit tmp(*this); return tmp += r;}

pqr_suit & operator *= (llt n){
	if(0 == n) {x = y = sigmax = sf = sg = sh = INT(0); return *this;}
	if(1 == n) return *this;
	n -= 1;
	auto tmp(*this);
	while(n){
		if(n & 1) *this += tmp;
		tmp += tmp;
		n >>= 1; 
	}
	return *this;
}

const pqr_suit operator * (llt n) const {pqr_suit tmp(*this); return tmp *= n;}

};


struct pqr{

static int K1;
static int K2;	
static ZUHE::CSimple C;

using llt = long long;
using INT = modint<1000000007LL>;
using vt = vector<INT>;
using vvt = vector<vt>;

vvt data; // data[a][b] 表示 i^(a)*f^(b)
INT x;    // x方向的尺度，其实就是data[0][0]
INT y;    // y方向的尺度

pqr() = default;
pqr(llt xx, llt yy):data(K1+1, vt(K2+1, INT(0))), x(xx), y(yy){}

static pqr su(){return pqr(0LL, 1LL);}
static pqr sr(){pqr tmp(1LL, 0LL);for(auto&a:tmp.data)a[0]=INT(1);return tmp;}

pqr& operator += (const pqr & r){
	vvt tmp(K1+1, vt(K2+1, INT(0)));
	for(int u=0;u<=K1;++u)for(int v=0;v<=K2;++v){
		auto & d = tmp[u][v];
		d = this->data[u][v];
        for(int a=0;a<=u;++a)for(int b=0;b<=v;++b){
			d += C.get(u, a) * C.get(v, b) * this->x[u - a] * this->y[v - b] * r.data[a][b]; 
		}
	}
	// copy(tmp.begin(), tmp.end(), this->data.begin());
	for(int i=0;i<=K1;++i)for(int j=0;j<=K2;++j)this->data[i][j] = tmp[i][j];
	this->x += r.x;
	this->y += r.y;
	return *this;
}

pqr const operator + (const pqr & r) const {pqr tmp(*this); return tmp += r;}

pqr & operator *= (llt n){
	if(0 == n){for(auto&vec:data)for(auto&i:vec)i=INT(0);x=y=INT(0);return *this;}
	if(1 == n){return *this;}
	n -= 1;
	pqr tmp(*this);
	while(n){
		if(n & 1) *this += tmp;
		tmp += tmp;
		n >>= 1;
	}
	return *this;
}

pqr const operator * (llt n)const{pqr tmp(*this);return tmp *= n;}

};

int pqr::K1;
int pqr::K2;
ZUHE::CSimple pqr::C;


}


using llt = long long;
using mint = SHULUN::modint<1000000007LL>;

llt N, P, R, Q;
auto & K1 = SHULUN::pqr::K1;
auto & K2 = SHULUN::pqr::K2;

llt proc(){
	if(0 == N) return ((mint(R/Q))[K2]).value;
	if(0 == P) return ((mint(R/Q)[K2]) * mint(N + 1)).value;
	auto ans = SHULUN::uniEuclid<SHULUN::pqr>(P, Q, R, N);
	if(0 == K1) return (ans.data[K1][K2] + (mint(R/Q))[K2]).value;
	return (ans.data[K1][K2]).value;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); 
    // cin.tie(0); cout.tie(0);	
	SHULUN::pqr::C.init(10);
    using namespace IO;
    int nofkase = getInt();
	while(nofkase--){
		N = getInt(); P = getInt(); R = getInt(); Q = getInt(); K1 = getInt(); K2 = getInt();
		printf("%lld\n", proc());
	}
	return 0;
}