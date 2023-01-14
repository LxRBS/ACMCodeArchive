/**
 * 定义一个数列的价值为相邻元素的差的绝对值，给定一个数组
 * 问数组中有多少个子序列满足子序列的价值等于整个数组的价值
 * 简单分析可知，如果a1,a2,a3,a4,a5是单调的，则a234存在与否不影响子序列的价值，只需a1和a5即可
 * 所以需要找到原数组的极值，中间非极值的元素可以选也可以不选，求一个2的幂即可 
 */
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 133;
#else
int const SIZE = 100100;
#endif

typedef long long llt;
llt const MOD = 998244353LL;

llt powerMod(llt a,llt n){
    llt ret = 1;
    a %= MOD;

    while( n ){
        if ( n & 1 ) ret = ret * a % MOD;
        n >>= 1;
        a = a * a % MOD;
    }
    return ret;
}

int N;
int A[SIZE];
typedef pair<int, int> pii;
pii B[SIZE];

llt proc(){
    if(1 == N) return 1;
    if(2 == N){
        return A[0] == A[1] ? 3 : 0;
    }
    
    int bn = 0;
    int k = 0;
    while(1){
        int t = 0;
        while(k+t<N&&A[k]==A[k+t]) ++t;

        B[bn++] = {A[k], t};
        if((k += t) == N) break;
        
    }
    if(1 == bn){
        return (powerMod(2, B[0].second) - 1 + MOD) % MOD;
    }
    if(2 == bn){
        return (powerMod(2, B[0].second) - 1 + MOD) * ((powerMod(2, B[1].second) - 1) + MOD) % MOD;
    }
    llt ans = (powerMod(2, B[0].second) - 1 + MOD)
     * (powerMod(2, B[bn-1].second) - 1 + MOD) % MOD;
    for(int i=1;i<bn-1;++i){
        if((B[i-1].first > B[i].first && B[i+1].first > B[i].first) 
        || (B[i-1].first < B[i].first && B[i+1].first < B[i].first)){
            ans = ans * (powerMod(2, B[i].second) - 1 + MOD) % MOD;
        }else{
            ans = ans * (powerMod(2, B[i].second)) % MOD;
        }
        
    }
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase; scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%d", &N);
        for(int i=0;i<N;++i)scanf("%d", A+i);
        printf("%lld\n", proc());
    }
    return 0;
}