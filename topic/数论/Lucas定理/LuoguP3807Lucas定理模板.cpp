/**
    Lucas定理模板题
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;
//The extended Euclidean algorithm implemented by iteration
//returns gcd(a,b), and x, y are satisfied with ax + by = gcd
llt exEuclid(llt a,llt b,llt&x,llt&y){
    llt x0 = 1, y0 = 0;
    llt x1 = 0, y1 = 1;
    x = 0; y = 1;
    llt r = a % b;
    llt q = ( a - r ) / b;
    while( r ){
        x = x0 - q * x1;
        y = y0 - q * y1;
        x0 = x1; y0 = y1;
        x1 = x; y1 = y;
        a = b; b = r; r = a % b;
        q = ( a - r ) / b;
    }
    return b;
}

//returns the inverse of a mod p satisfied with 1 == ax%p
//it will be success only when a and p are co-prime
inline llt inv(llt a,llt p){
    llt x,y;
    llt r = exEuclid(a,p,x,y);
    if ( r != 1 ) return 0;
    x = x % p;
    if ( x < 0 ) x += p;
    return x;
}

//to find out C(n,k)%mod = ? to satisfied with n<mod and k<mod and mod>1E5
llt Cmod(llt n,llt k,llt mod){
    if(k>n) return 0;
    llt fenzi = 1, fenmu = 1;
    for(int i=n-k+1;i<=n;++i)fenzi=fenzi*i%mod;
    for(int i=1;i<=k;++i)fenmu=fenmu*i%mod;
    return fenzi*inv(fenmu,mod)%mod;
}

//to find out C(n,k)%mod = ?
llt Lucas(llt n,llt k,llt mod){
    if(0==k) return 1;
    return Lucas(n/mod,k/mod,mod) * Cmod(n%mod,k%mod,mod) % mod;
}

int main(){
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        int n,k,mod;
        scanf("%d%d%d",&n,&k,&mod);
        printf("%lld\n",Lucas(n+k,k,mod));
    }
    return 0;
}
