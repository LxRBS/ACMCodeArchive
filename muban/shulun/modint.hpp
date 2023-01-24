#include <bits/stdc++.h>
using namespace std;

namespace SHULUN{

template<long long MOD = 998244353LL>
struct modint{

using T = long long;
// using int128 = __int128_t;
using int128 = T; // 如果MOD不是特大的情况下，不要用128，否则会导致耗时增加

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

struct dymint{

using T = long long;
// using int128 = __int128_t;
using int128 = T; // 如果MOD不是特大的情况下，不要用128，否则会导致耗时增加

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

