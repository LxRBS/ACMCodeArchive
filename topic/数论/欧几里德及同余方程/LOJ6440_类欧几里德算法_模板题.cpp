#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147 == __xyz258) && (__xyz258 = (__abc147 = __ma369) + fread(__ma369, 1, 100000, stdin), __abc147 == __xyz258) ? EOF : *__abc147++)

int getInt()
{
	int sgn = 1;
	char ch = __hv007();
	while (ch != '-' && (ch < '0' || ch > '9'))
		ch = __hv007();
	if ('-' == ch)
	{
		sgn = 0;
		ch = __hv007();
	}

	int ret = (int)(ch - '0');
	while ('0' <= (ch = __hv007()) && ch <= '9')
		ret = ret * 10 + (int)(ch - '0');
	return sgn ? ret : -ret;
}

using llt = long long;
using vll = vector<llt>;
using vvll = vector<vll>;
using v3ll = vector<vvll>;
using si = set<int>;

template<long long MOD = 998244353LL>
struct modint{

using llt = long long;

llt value;
explicit modint(llt v = 0):value((v%MOD+MOD)%MOD){}

// static const modint ZERO = modint(0);
// static const modint ONE = modint(1);
// static const modint TWO = modint(2);
// static const modint THREE = modint(3);

static llt pow(llt a, llt n){
    llt ret = 1;
	while(n){
        if(n & 1) ret = ret * a % MOD; // MOD特大的时候需要先转128
		a = a * a % MOD;
		n >>= 1;
	}
	return ret;
}
/// MOD为质数才行
static llt inv(llt a) {return modint::pow(a, MOD - 2);}

/// this的n次方, 重载方括号为了保证优先级
const modint operator [] (llt n) const {return modint(modint::pow(this->value, n));}
modint & operator ^= (llt n) {this->value=modint::pow(this->value, n); return *this;}

const modint operator + (const modint & r) const {return modint(value + r.value);}
modint & operator += (const modint & r) {(value+=r.value)%=MOD; return *this;}

const modint operator - (const modint & r) const {return modint(value - r.value);}
modint & operator -= (const modint & r) {(value-=r.value)%=MOD; return *this;}

const modint operator * (const modint & r) const {return modint(value * r.value);}
modint & operator *= (const modint & r) {(value*=r.value)%=MOD; return *this;}

const modint operator / (const modint & r) const {return modint(value*modint::inv(r.value));}
modint & operator /= (const modint & r) {(value*=modint::inv(r.value))%=MOD; return *this;}

};

template<long long MOD>
ostream & operator << (ostream & os, const modint<MOD> & r) {return os << r.value;}
template<long long MOD>
istream & operator >> (istream & is, modint<MOD> & r) {return is >> r.value;}
using mint = modint<>;

struct SquareMatrix{ // 方阵

int SZ;
using T = modint<>;
/// SZ*SZ的数组
vector<vector<T>> data;

SquareMatrix() = default;

SquareMatrix(int sz):SZ(sz){
	assert(sz > 0);
	data.assign(SZ, vector<T>(SZ, T()));
}

static SquareMatrix I(int sz){
	SquareMatrix m(sz);
	for(int i=0;i<sz;++i)m.data[i][i] = T(1);
	return m;
}

SquareMatrix & operator = (const SquareMatrix & r){
	if(this != &r){
		this->SZ = r.SZ;
        this->data.assign(r.data.begin(), r.data.end());
	}
	return *this;
}

SquareMatrix & operator += (const SquareMatrix & r){
	assert(this->SZ == r.SZ);
	for(int i=0;i<SZ;++i)for(int j=0;j<SZ;++j){
		data[i][j] += r.data[i][j];
	}
	return *this;
}

const SquareMatrix operator + (const SquareMatrix & r) const {
    SquareMatrix ret(*this);
	return ret += r;
}

const SquareMatrix operator * (const SquareMatrix & r) const {
	assert(this->SZ == r.SZ);
    SquareMatrix ret(SZ);
	for(int i=0;i<SZ;++i)for(int j=0;j<SZ;++j){
		auto & d = ret.data[i][j];
		for(int k=0;k<SZ;++k) d += data[i][k] * r.data[k][j];
	}
	return ret;
}

SquareMatrix & operator *= (const SquareMatrix & r) {
    return *this = std::move(*this * r);
}

void output(ostream & os = std::cout) const {
	for(const auto & vec : data){
		for(const auto & i : vec){
			os << i << " ";
		}
		os << endl;
	}
    return;
}

};

/// 万能欧几里德，又称作类欧几里德，FloorSum
/// 给定ABPQRL，计算 SIGMA{(A^x)B^floor((ax+b)/c),x=1...limit}
/// 其中A和B是n×n的方阵
struct UniversalEuclid{

using mat = SquareMatrix;
using llt = mat::T::llt;

struct node_t{

mat x, y, s;

node_t(int sz):s(sz){x = y = mat::I(sz);}

void mulright(const node_t & m){
	SquareMatrix r = m.s;
    r = x * r;
	r *= y;
	s += r;
	x *= m.x;
	y *= m.y;
	return;
}

void mulleft(const node_t & m){
	x *= m.x;
	y *= m.y;
	s = m.x * s;
    s *= m.y;
	s += m.s;
	return;
}

void mulleft(node_t m, llt n){
	for(llt i=n;i;i>>=1){
        if(i & 1) this->mulleft(m);
		m.mulright(m);
	}
	return;
}

void mulright(node_t m, llt n){
	for(llt i=n;i;i>>=1){
		if(i & 1) this->mulright(m);
		m.mulright(m);
	}
	return;
}

void output(ostream & os = std::cout) const {
	x.output(os); y.output(os); s.output(os);
}

};

int const SZ;
node_t left, right;
node_t U, R;
llt a, b, c, limit;


UniversalEuclid() = delete;

/// 计算SIGMA{(A^x)B^floor((ax+b)/c),x=1...limit}
/// A和B均是sz*sz的方阵
UniversalEuclid(const mat & A, const mat & B, llt a, llt b, llt c, llt limit, int sz)
:SZ(sz), left(sz), right(sz), U(sz), R(sz){
    this->U.y = B;
	this->R.x = this->R.s = A;
	this->a = a, this->b = b, this->c = c, this->limit = limit;

	while(limit){
        const auto da = a / c, db = b / c, lc = c;
		const auto m = static_cast<const llt>((1.L * a * limit + b) / c) - da * limit - db;
		R.mulleft(U, da);

		if(!m){
			left.mulright(R, limit);
			break;
		}

		b = db * c + c - b- 1;
		c = a - da * c;
		a = lc;
		left.mulright(R, b / c);
		left.mulright(U);
		right.mulleft(R, limit - static_cast<llt>((1.L*a*(m-1)+b)/c));
		std::swap(U, R);
		limit = m - 1;
	}
	left.mulright(right);
	return;
}

const mat & get()const{return left.s;}

void output(ostream & os = std::cout)const{
    for(const auto & a : this->get().data){
	    os << a[0];
		for(int i=1;i<SZ;++i) os << " " << a[i];
		os << endl;
	}
}

};


int main(){
#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
#endif
    // llt a = getInt();
	// llt c = getInt();
	// llt b = getInt();
	// llt limit = getInt();
	// llt n = getInt();
	llt a, c, b, limit, n;
	cin >> a >> c >> b >> limit >> n;
    SquareMatrix A(n), B(n);
	for(auto & arr : A.data)for(auto & i : arr) cin >> i;
	for(auto & arr : B.data)for(auto & i : arr) cin >> i;
	UniversalEuclid e(A, B, a, b, c, limit, n);
	e.output();
	return 0;
}