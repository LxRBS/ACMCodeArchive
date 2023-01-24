/**
 * 会T两个点，常数时间超了。封装太过，大概是两倍时间。开O2也过不了。
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

struct dymint{

using T = long long;
// using int128 = __int128_t;
using int128 = T;

static T MOD;

static const T mod(){return MOD;}

T value;
explicit dymint(T v = 0):value((v%MOD+MOD)%MOD){}

static const dymint ZERO(){
    static dymint zero(0);
    return zero;
}

static const dymint ONE(){
    static dymint one(1);
    return one;
}

static const dymint TWO(){
    static dymint two(2);
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
static T inv(T a) {return dymint::pow(a, MOD - 2);}

/// this的n次方, 重载方括号为了保证优先级
const dymint operator [] (T n) const {return dymint(dymint::pow(this->value, n));}
dymint & operator ^= (T n) {this->value=dymint::pow(this->value, n); return *this;}

const dymint operator + (const dymint & r) const {return dymint(value + r.value);}
dymint & operator += (const dymint & r) {(value+=r.value)%=MOD; return *this;}

const dymint operator - (const dymint & r) const {return dymint(value - r.value);}
dymint & operator -= (const dymint & r) {(value-=r.value)%=MOD; return *this;}

const dymint operator * (const dymint & r) const {
    return dymint((int128)value * r.value % MOD); // MOD特大的时候需要先转128
}
dymint & operator *= (const dymint & r) {
    value = (int128)value * r.value % MOD; // MOD特大的时候要转128 
    return *this;
}

const dymint operator / (const dymint & r) const {
    return dymint((int128)value * dymint::inv(r.value) % MOD);
}

dymint & operator /= (const dymint & r) {
    value = (int128)value * dymint::inv(r.value) % MOD;
    return *this;
}

bool operator ! () const {return !value;}


};

dymint::T dymint::MOD;

}

namespace SHULUN{

/// T是模数类型，需要提供mod()函数
template<typename T>struct AllNi{

using llt = long long;
using vt = vector<T>;


llt const MOD;
/// 求1到n的逆,O(n)
/// 答案保存在data中, data[i] = i的逆，
/// 令 p = kx + r, 两边同时乘以x^(-1)，并且对p取模有
/// 0 = k + x^(-1) * r，所以x^(-1) = - k * r^(-1)
AllNi(int n):MOD(T::mod()){
    data.assign(n + 1, T());
    data[1] = T::ONE();
    for(int i=2;i<=n;++i) data[i] = T(MOD - MOD / i) * data[MOD % i];
    return;
}

/// 给定数组，求数组的逆, begin为首元素地址，n为元素数量
/// data[i]表示a[i]的逆，从0开始
template<typename IT = vector<llt>::const_iterator>
AllNi(IT begin, int n):MOD(T::mod()){
	assert(n > 0);
    vt tmp(n, T());
	auto it = begin;
    tmp[0] = T(*it++);
	for(int i=1;i<n;++i) tmp[i] = tmp[i-1] * T(*it++);

	T ni = T(T::inv(tmp[n-1].value));

	data.assign(n, T());
	for(int i=n-1;i;--i) data[i] = tmp[i - 1] * ni, ni *= T(*--it);
	data[0] = ni;
	return;
}

const vt & get()const{return data;}

private:
vt data;

};

}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); 
    // cin.tie(0); cout.tie(0);
    int n = IO::getInt();
	int p = IO::getInt();
	int k = IO::getInt();
	vector<long long> a(n);
	for(auto & i : a) i = IO::getInt();

	SHULUN::dymint::MOD = p;
	SHULUN::AllNi<SHULUN::dymint> solver(a.begin(), n);
    const auto & d = solver.get();
	
	SHULUN::dymint ans = SHULUN::dymint::ZERO();
	SHULUN::dymint t(k);
	SHULUN::dymint tt = SHULUN::dymint::ONE();
	for(int i=0;i<n;++i) ans += d[i] * (tt *= t);
	cout << ans.value << endl;
	return 0;
}