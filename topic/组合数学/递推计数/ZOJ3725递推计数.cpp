/*
N个仓库，用红蓝两色染色。要求至少M个连续的仓库染成红色。问方法总数
令Di为符合条件的数量，Ui为不符合条件的数量，Fi为总数量
易得：Fi = 2^i;
且：
Di = 2 * Di-1 + Ui-M-1
Ui = Fi - Di
*/

#include <iostream>
using namespace std;
typedef long long llt;
llt const MOD =  1000000007LL;
int const SIZE = 100001;
llt D[SIZE],F[SIZE],U[SIZE];

llt dp(int n,int m){
    if ( n < m ) return 0LL;
    if ( n == m ) return 1LL;

    F[0] = U[0] = 1LL;
    for(int i=1;i<=m;++i){
        D[i] = 0LL;
        F[i] = U[i] = (F[i-1]<<1) % MOD;
    }
    D[m] = 1LL;
    U[m] = F[m] - 1LL;
    if ( U[m] < 0 ) U[m] += MOD;

    for(int i=m+1;i<=n;++i){
        F[i] = ( F[i-1] << 1 ) % MOD;
        D[i] = ( ( D[i-1] << 1 ) % MOD + U[i-m-1] ) % MOD;
        U[i] = F[i] - D[i];
        if ( U[i] < 0 ) U[i] += MOD;
    }

    return D[n];
}

int main(){
    int n,m;
    while( cin>>n>>m ) cout<<dp(n,m)<<endl;
    return 0;
}
