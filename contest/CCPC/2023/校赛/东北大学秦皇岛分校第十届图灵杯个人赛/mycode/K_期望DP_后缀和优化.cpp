/**
 * 给定N个格子，每个格子有一个金币数，有一个[L, R]，表示在当前格子，等概率从[L, R]选一个步数我，往前跳
 * 问从1跳过N，金币期望是多少。典型的期望DP，令Di为从i跳过N的期望，则
 * Di = SIGMA{D[i+L,...,i+R]} / (R - L + 1) + Ai
 * 直接计算显然与区间长度有关，最差能到平方。但是求和部分显然是求一段连续区间的和，且必然是已知的。
 * 因此可以使用一个后缀和记录。得到
 * Di = (U[i+L] - U[i+R+1]) / (R - L + 1) + Ai
 * Ui = Di + U[i+1]
 */
#include <bits/stdc++.h>
using namespace std;

using llt = long long;
llt const MOD = 998244353LL;

llt qpow(llt a, llt n){
    llt ret = 1;
    while(n){
        if(n & 1) ret = ret * a % MOD;
        a = a * a % MOD;
        n = n >> 1;
    }
    return ret;
}

inline llt inv(llt a){return qpow(a, MOD - 2LL);}

using t3t = tuple<llt, llt, llt>;
using vt3t = vector<t3t>;
using vll = vector<llt>;


int N;
vt3t A;
vll D, U;

llt proc(){
    D.assign(N + 2, 0LL);
    U.assign(N + 3, 0LL);
    for(int i=N;i>=1;--i){
		const auto & a = A[i - 1];
        auto s = i + get<1>(a);
        if(s > N + 1) s = N + 1;
        auto e = i + get<2>(a);
        if(e > N + 1) e = N + 1;
        D[i] = (inv(get<2>(a) - get<1>(a) + 1) * (U[s] - U[e + 1] + MOD) %  MOD + get<0>(a)) % MOD;
        U[i] = (D[i] + U[i + 1]) % MOD;
    }
    return D[1];
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    A.assign(N, {});
    for(auto & p : A)cin >> get<0>(p); 
    for(auto & p : A)cin >> get<1>(p); 
    for(auto & p : A)cin >> get<2>(p);
    cout << proc() << endl; 
    return 0;
}