#include <bits/stdc++.h>
using namespace std;

#include "modint.hpp"



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




