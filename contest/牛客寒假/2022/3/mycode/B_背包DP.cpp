/**
 * 给定数组A，对每个Ai，可以全选、选一半，或者不选
 * 问所选之和从1到M的方案总数
 * 背包DP
*/
#include<bits/stdc++.h>
using namespace std;
 
char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)
 
int getUnsigned(){
    char ch = __hv007();
    while( ch < '0' || ch > '9' ) ch = __hv007();
 
    int ret = (int)(ch-'0');
    while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
    return ret;
}
 
#ifndef ONLINE_JUDGE
int const SIZE = 18;
#else
int const SIZE = 1010;
#endif
 
typedef long long llt;
llt const MOD = 1000000000+7;
 
int N, M;
int W[SIZE];
 
llt D[SIZE][SIZE];
 
void proc(){
    if(0 == N){
        printf("0");
        for(int i=1;i<M;++i)printf(" 0");
        printf("\n");
        return;
    }
 
    D[0][0] = 1;
    for(int w,i=1;i<=N;++i){
        w = W[i];
        for(int j=0;j<=M;++j){          
            D[i][j] = (D[i-1][j] + (j>=w?D[i-1][j-w]:0) + (j>=w/2?D[i-1][j-w/2]:0)) % MOD;
        }
        int t = 5;
    }
    printf("%lld", D[N][1]);
    for(int i=2;i<=M;++i)printf(" %lld", D[N][i]);
    printf("\n");
}
 
int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getUnsigned();
    M = getUnsigned();
    for(int i=1;i<=N;++i) W[i] = getUnsigned();
    proc();
    return 0;
}