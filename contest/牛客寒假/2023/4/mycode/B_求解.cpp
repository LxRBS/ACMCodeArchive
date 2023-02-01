/**
 * 给定N长度的数组C，且已知
 * Ci = Ai + Bi
 * Ai = A[N-1-i]
 * Bi = -B[N-1-i]
 * 下标从0开始，以上等式在模M意义下成立。构造符合条件的数组A和B
 * 简单运算就能发现 2 * Ai = Ci + C[N-1-i]
 * 所以在2的逆元存在的情况下， A[N-1-i] = A[i] = (Ci + C[N-1-i]) * 2^(-1)
 * B[i] = C[i] - A[i], B[N-1-i] = M - B[i];
 * 注意M为2时，2的逆不存在，需要特判。
 */
#include <bits/stdc++.h>
using namespace std;

using llt = long long;
using vll = vector<long long>;

int N;
llt MOD;

llt qpow(llt a, llt n){
	a %= MOD;
	llt ret = 1;
	while(n){
		if(n & 1) ret = ret * a % MOD;
		a = a * a % MOD;
		n >>= 1;
	}
	return ret;
}

inline llt inv(llt a){return qpow(a, MOD-2LL);}

vll A, B, C;

bool proc2(){
	for(int i=0;i<N/2;++i){
        if(C[i] != C[N-1-i]) return false;
		B[i] = C[i];
		B[N-1-i] = C[N-1-i];
	}
	if(N & 1)B[N/2] = C[N/2];
	return true;
}

bool proc(){
	if(2 == MOD) return proc2();

    const auto inv2 = inv(2LL);
    for(int i=0;i<N/2;++i){
        A[N-1-i] = A[i] = inv2 * (C[i] + C[N-1-i]) % MOD;
        B[i] = (C[i] - A[i]) % MOD;
		B[N-1-i] = (MOD - B[i]) % MOD;
	}
	if(N & 1) A[N/2] = C[N/2];
	return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> MOD;
	C.assign(N, 0LL);
	for(auto & i : C) cin >> i;
	A.assign(N, 0LL);
	B.assign(N, 0LL);
	bool b = proc();
	if(!b) return puts("No"), 0;
	printf("Yes\n");
	for(auto i : A) printf("%lld ", i);printf("\n");
	for(auto i : B) printf("%lld ", i);printf("\n");
    return 0;
}