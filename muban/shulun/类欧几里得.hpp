#include <bits/stdc++.h>
using namespace std;

#include "modint.hpp"
#include "zuhe.hpp"


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
// using INT = SHULUN::modint<>;

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

using INT = modint<>;

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
using INT = modint<>;
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



