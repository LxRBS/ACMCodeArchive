#include <bits/stdc++.h>
using namespace std;

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



