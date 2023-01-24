#include <bits/stdc++.h>
using namespace std;

namespace SHULUN{

struct dymint{

using T = long long;
using int128 = __int128_t;

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
    int n, p; cin >> n >> p;
	SHULUN::dymint::MOD = p;
	SHULUN::AllNi<SHULUN::dymint> solver(n);
    auto & a = solver.get();
	for(int i=1;i<=n;++i) printf("%lld\n", a[i].value);
	return 0;
}