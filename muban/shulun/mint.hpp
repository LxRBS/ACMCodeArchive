#include <bits/stdc++.h>
using namespace std;

namespace SHULUN{

const long long MOD998244353 = 998244353LL;
const long long MOD1000000007 = 1000000007LL;
const long long MOD = 0;

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



