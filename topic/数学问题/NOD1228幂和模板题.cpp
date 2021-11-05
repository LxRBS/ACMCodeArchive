#include <stdio.h>

typedef long long llt;
int const SIZE = 2100;
llt const MOD = 1000000007LL;

llt C[SIZE][SIZE];//组合数
llt Inv[SIZE];//逆元
llt B[SIZE];//伯努利数

//初始化从1到n的组合数，包括n
void initC(int n){
    C[0][0] = 1;
	for(int i=1;i<=n;++i){
        C[i][0] = C[i][i] = 1;
        for(int j=1;j<i;++j) C[i][j] = ( C[i-1][j] + C[i-1][j-1] ) % MOD;
	}
}

//初始化从1到n的逆元，包括n
void initInv(int n,llt const mod){
    Inv[1] = 1;
    for(int i=2;i<=n;++i) Inv[i] = ( mod - mod / i ) * Inv[mod%i] % mod;
}

//初始化伯努利数，B[n] = 0
void initBernoulli(int n){
    B[0] = 1;
    for(int i=1;i<n;++i){
        for(int j=0;j<i;++j){
            B[i] = ( B[i] + C[i+1][j] * B[j] % MOD ) % MOD;
        }
        B[i] = ( B[i] * -Inv[i+1] ) % MOD;
        B[i] += MOD;
    }
}

llt proc(llt n,llt k){
    llt ans = 0LL;
    n = ( n + 1 ) % MOD;
    llt m = n;
    for(int i=1,t=k+1;i<=t;++i){
        ans = ( ans + C[t][i] * B[t-i] % MOD * m % MOD ) % MOD;
        m = m * n % MOD;
    }
    return ans * Inv[k+1] % MOD;
}

int main(){
    initC(2010);initInv(2010,MOD);initBernoulli(2010);
    int t;
    scanf("%d",&t);
    while(t--){
        llt n,k;
        scanf("%lld%lld",&n,&k);
        printf("%lld\n",proc(n,k));
    }
    return 0;
}
