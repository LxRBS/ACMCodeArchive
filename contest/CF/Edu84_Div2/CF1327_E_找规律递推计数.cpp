/**
   给定n，写出一个数字串，例如当n=3时，该串是
   000001002003...010011012...099100101102...998999
   问，该串中连续k个数字相同的片段有多少个，其中k从1取到n。
   找规律，先打出若干答案，观察规律。
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;
llt const MOD = 998244353;

llt Power10[200100]={1};
llt NPower[200100];
llt A[200100];
llt Sum[200100];
int main(){
    llt n;
    scanf("%lld",&n);
    for(int i=1;i<=n;++i){
        Power10[i] = 10 * Power10[i-1] % MOD;
        NPower[i] = ( NPower[i-1] * 10 % MOD + Power10[i] ) % MOD;
        A[i] = ( NPower[i] - NPower[i-1] - Sum[i-1] ) % MOD;
        if (A[i]<0) A[i] += MOD;
        Sum[i] = ( Sum[i-1] + A[i] ) % MOD;
    }
    printf("%lld",A[n]);
    for(int i=n-1;i;--i)printf(" %lld",A[i]);
    printf("\n");
    return 0;
}