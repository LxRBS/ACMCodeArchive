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

const long long MOD998244353 = 998244353LL;
const long long MOD1000000007 = 1000000007LL;
const long long MOD = MOD998244353;

struct mint{

using T = long long;
// using int128 = __int128_t;
using int128 = T; // 如果MOD不是特大的情况下，不要用128，否则会导致耗时增加

T value;
explicit mint(T v = 0):value((v%MOD+MOD)%MOD){}

static const mint zero(){return mint(0);}
static const mint one(){return mint(1);}
static const mint two(){return mint(2);}

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
static T inv(T a) {return mint::pow(a, MOD - 2);}

/// this的n次方, 重载方括号为了保证优先级
const mint operator [] (T n) const {return mint(mint::pow(this->value, n));}
mint & operator ^= (T n) {this->value=mint::pow(this->value, n); return *this;}

const mint operator + (const mint & r) const {return mint(value + r.value);}
mint & operator += (const mint & r) {(value+=r.value)%=MOD; return *this;}

const mint operator - (const mint & r) const {return mint(value - r.value);}
mint & operator -= (const mint & r) {(value-=r.value)%=MOD; return *this;}

const mint operator * (const mint & r) const {
    return mint((int128)value * r.value % MOD); // MOD特大的时候需要先转128
}
mint & operator *= (const mint & r) {
    value = (int128)value * r.value % MOD; // MOD特大的时候要转128 
    return *this;
}

const mint operator / (const mint & r) const {
    return mint((int128)value * mint::inv(r.value) % MOD);
}

mint & operator /= (const mint & r) {
    value = (int128)value * mint::inv(r.value) % MOD;
    return *this;
}

bool operator ! () const {return !value;}

};

}


namespace DAISHU{


struct SquareMatrix{

// using T = int;
using T = SHULUN::mint;
using vt = vector<T>;
using vvt = vector<vt>;

vvt data;

static SquareMatrix zero(int n){return SquareMatrix(n);}
static SquareMatrix eye(int n){SquareMatrix a(n);for(int i=0;i<n;++i)a.data[i][i] = T(1);return a;}

SquareMatrix() = default;
SquareMatrix(int n):data(n, vt(n, T(0))){}

void init(int n){data.assign(n, vt(n, T(0)));}

SquareMatrix & operator += (const SquareMatrix & r) {
	assert(data.size() == r.data.size());
	auto n = data.size();
	for(int i=0;i<n;++i)for(int j=0;j<n;++j)data[i][j] += r.data[i][j];
	return *this;
}

SquareMatrix const operator + (const SquareMatrix & r) const {SquareMatrix tmp(*this); return tmp += r;}

SquareMatrix const operator * (const SquareMatrix & r) const {
    auto n = data.size();
	SquareMatrix ret(n);
	for(int i=0;i<n;++i)for(int j=0;j<n;++j){
		auto & d = ret.data[i][j];
		for(int k=0;k<n;++k) d += this->data[i][k] * r.data[k][j];
	}    
	return ret;
}

SquareMatrix & operator *= (const SquareMatrix & r){
    auto n = data.size();
	vvt ret(n, vt(n, T(0)));
	for(int i=0;i<n;++i)for(int j=0;j<n;++j){
		auto & d = ret[i][j];
		for(int k=0;k<n;++k) d += this->data[i][k] * r.data[k][j];
	}  
	for(int i=0;i<n;++i)for(int j=0;j<n;++j)data[i][j] = ret[i][j];  
	return *this;	
}

static SquareMatrix pow(SquareMatrix a, int n){
	SquareMatrix ret = eye(a.data.size());
    while(n){
		if(n & 1) ret *= a;
		a *= a;
		n >>= 1;
	}
	return ret;
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


struct matrix_ab{
/// f = floor((Pi+R)/Q)
/// 求 SIGMA{A^i * B^f(i), A,B是方阵, i=1...N}

using T = DAISHU::SquareMatrix;

static T A, B;

T x; // 表示A^x
T y; // 表示B^y
T s; // 表示结果

matrix_ab(const T & xx, const T & yy, const T & ss):x(xx),y(yy),s(ss){}

static matrix_ab su(){return matrix_ab(T::eye(A.data.size()), B, T::zero(A.data.size()));}
static matrix_ab sr(){return matrix_ab(A, T::eye(A.data.size()), A);}

matrix_ab & operator += (const matrix_ab & r){
    this->s += this->x * r.s * this->y;
	this->x *= r.x;
	this->y *= r.y;
    return *this;
}

const matrix_ab operator + (const matrix_ab & r)const{matrix_ab tmp(*this); return tmp += r;}

matrix_ab & operator *= (long long n){
	// assert(n > 0);
	if(0 == n) {x = y = T::eye(x.data.size()); s = T::zero(A.data.size()); return *this;}
	if(1 == n) {return *this;}
	n -= 1;
	matrix_ab tmp(*this);
    while(n){
		if(n & 1) *this += tmp;
		tmp += tmp;
		n >>= 1; 
	}
	return *this;
}

matrix_ab const operator * (long long n)const{matrix_ab tmp(*this); return tmp *= n;}

};

matrix_ab::T matrix_ab::A;
matrix_ab::T matrix_ab::B;

}


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); 
    // cin.tie(0); cout.tie(0);	

	using namespace IO;
    using llt = long long;
	llt P = getLL();
	llt Q = getLL();
	llt R = getLL();
	llt N = getLL();
	llt M = getLL();
	auto & A = SHULUN::matrix_ab::A;
	auto & B = SHULUN::matrix_ab::B;
    A.init(M); B.init(M);
	for(auto & vec : A.data)for(auto & i : vec)i.value = getLL();
	for(auto & vec : B.data)for(auto & i : vec)i.value = getLL();
	auto ans = SHULUN::uniEuclid<SHULUN::matrix_ab>(P, Q, R, N);
	for(const auto & vec : ans.s.data){
		for(const auto & i : vec)printf("%lld ", i.value);
		printf("\n");
	}
	return 0;
}