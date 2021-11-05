//正整数分解成2的幂的和的不同方法的数量
#include <iostream>
using namespace std;

typedef long long llt;
llt const MOD = 1000000000LL;

llt D[1000010];
llt dp(int n){
    D[1] = 1LL;
    D[2] = 2LL;
    for(int i=3;i<=n;++i){
        if ( i & 1 ) D[i] = D[i-1];
        else D[i] = ( D[i-2] + D[i>>1] ) % MOD;    
    }
    return D[n];
}

int main(){
    int n;
    cin>>n;
    cout<<dp(n)<<endl;
    return 0;
}