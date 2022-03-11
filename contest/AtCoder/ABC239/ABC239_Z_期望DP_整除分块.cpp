/**
 * 给定N和M，每次随机得到1~N中的数y
 * 令x初始为1，每次令x*=y
 * 问x不超过M的情况下的期望次数是多少
 * 令f(x)为不超过x的期望次数，可以发现
 * f(x) = 1/N * (1 + SIGMA{f(x/i),i从1到N}
 * 但由于N和M都在1E9，需要优化
 * 很容易观察到f(x),f(x-1),f(x-2),...,f(x/2+1)的值都是一样的
 * 因此可以使用整除分块，在根号时间内计算出答案
 * 另外由于x很大，所以需要使用map来保存答案
 * 写一个记忆化搜索DP即可
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;
llt const MOD = 1E9+7;

llt power(llt a, llt n){
    llt ret = 1; a %= MOD;
    while(n){
        if(n&1) ret = ret * a % MOD;
        a = a * a % MOD;
        n >>= 1;
    }
    return ret;
}
inline llt inv(llt a){return power(a, MOD-2);}

llt N, M;
unordered_map<llt, llt> D;
llt InvN;

llt dfs(llt m){
    auto it = D.find(m);
    if(it != D.end()) return it->second;
    llt ans = 0;
    for(llt r,i=2;i<=min(N,m);i=r+1){
        r = min(N, m / (m / i));
        (ans += dfs(m/i) * (r - i + 1)) %= MOD;
        if(r-i+1<0){
            cout<<r<<" - "<<i<<" + 1"<<endl;
        }
    }
    ans = (ans * InvN % MOD + 1) % MOD;
    ans = ans * D[1] % MOD;
    it = D.insert(it, {m, ans});
    return it->second;
}

llt proc(){
    InvN = inv(N);
    D[0] = 0;
    D[1] = N * inv(N-1) % MOD;
    return dfs(M);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    cin>>N>>M;
    cout<<proc()<<endl;
    return 0;
}
