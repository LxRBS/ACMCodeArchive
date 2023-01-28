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
// using int128 = __int128_t;
using int128 = T;

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


struct px_plus_r_divide_by_q{

/// floor((pi + r) / q)
/// 与uniEuclid配合使用，即可求出 SUM{floor(i), i=1...n}

using INT = llt; // 不取模就直接用longlong
// using INT = SHULUN::mint;

/// 分别表示x的整点数量，y的整点数量，s即表示结果的和
INT x, y, s;

px_plus_r_divide_by_q() = default;
px_plus_r_divide_by_q(llt xx, llt yy, llt ss):x(xx),y(yy),s(ss){}

static px_plus_r_divide_by_q sr(){return px_plus_r_divide_by_q(1, 0, 0);}
static px_plus_r_divide_by_q su(){return px_plus_r_divide_by_q(0, 1, 0);}

px_plus_r_divide_by_q & operator += (const px_plus_r_divide_by_q & r){
	/// this->y表示左边段的y整点数量, r.x表示右边x的整点数量
	/// 相乘恰好表明右边段下方矩形的整点数量
	this->s += r.s + this->y * r.x;	
	this->x += r.x; // 两段的整点数量相加
	this->y += r.y;
	return *this;
}

const px_plus_r_divide_by_q operator + (const px_plus_r_divide_by_q & r) const {
    auto tmp(*this);
	return tmp += r;
}

px_plus_r_divide_by_q & operator *= (llt n){
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

const px_plus_r_divide_by_q operator * (llt n) const {
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

}

using llt = long long;
using mint = SHULUN::mint;

llt N, P, R, Q;

void proc(){
	if(0 == N){
		return (void)printf("%lld %lld 0\n", R/Q, (R/Q)*(R/Q)%mint::mod());
	}
	if(0 == P){
		auto tmp = mint(R/Q);
		return (void)printf("%lld %lld %lld\n", (tmp*mint(N+1)).value, (tmp*tmp*mint(N+1)).value, (tmp*mint(N)*mint(N+1)/mint::TWO()).value);
	}
	auto ans = SHULUN::uniEuclid<SHULUN::pqr_suit>(P, Q, R, N);
	auto b_c = mint(R/Q);
	auto sf = ans.sf + b_c;
	auto sg = ans.sg + b_c * b_c;
	printf("%lld %lld %lld\n", sf.value, sg.value, ans.sh.value);
	return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); 
    // cin.tie(0); cout.tie(0);
    using namespace IO;
    int nofkase = getInt();
	while(nofkase--){
		N = getInt(); P = getInt(); R = getInt(); Q = getInt();
		proc();
	}
	return 0;
}