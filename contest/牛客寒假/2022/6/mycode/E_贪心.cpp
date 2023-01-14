/**
 * 给定三个数组A、B、H，对于任意i、j，如果Ai >= Bj + Hj，则i能够秒j
 * 问最少一共要加多少h，才能使得没有人被秒
 * 对于普通人，只需将h加到不会被最大的Ai秒即可
 * 但是对于最大的Ai那个人，他需要加到不能被第二大A秒即可。
 * 注意第二大Ai可能也等于最大A
 */
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 33;
#else
int const SIZE = 200100;
#endif

typedef long long llt;

int N;
llt A[SIZE], B[SIZE], H[SIZE];


llt proc(){
    if(1 == N) return 0;
    llt m1 = -1, m2 = -1;
    for(int i=0;i<N;++i){
        if(m1 < A[i]){
            m2 = m1;
            m1 = A[i];
        }else if(m2 < A[i]){
            m2 = A[i];
        }
    }
    llt ans = 0;
    for(int i=0;i<N;++i){
        llt tmp = m1 != A[i] ? m1 : m2;
        if(tmp - B[i] >= H[i]){
            ans += tmp- B[i] - H[i] + 1;
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
        for(int i=0;i<N;++i){
            scanf("%lld%lld%lld", A+i, B+i, H+i);
        }
        printf("%lld\n", proc());
    }
    return 0;
}