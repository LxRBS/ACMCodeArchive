/*
    RSA解密
    利用p、q计算出n=pq，r=(p-1)(q-1)
    再利用e，计算出e模r的逆d
    令c是明文，则源信息m=c^d%n
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

typedef long long llt;

//returns a * b % mod
llt multiMod(llt a,llt b,llt mod){
    llt ret = 0;
    a %= mod, b %= mod;

    while( b ){
        if ( b & 1 ) ret = ( ret + a ) % mod;
        b >>= 1;
        a = ( a + a ) % mod;
    }
    return ret;
}

//another a^n%mod using multiMod()
llt powerMod(llt a,llt n,llt mod){
    llt ret = 1;
    a %= mod;

    while( n ){
        if ( n & 1 ) ret = multiMod(ret,a,mod);
        n >>= 1;
        a = multiMod(a,a,mod);
    }
    return ret;
}

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

int main(){
    //freopen("1.txt","r",stdin);
    llt p,q,e,len,t;
    while( EOF != scanf("%lld%lld%lld%lld",&p,&q,&e,&len) ){
        llt n = p * q;
        llt r = (p-1)*(q-1);
        llt d = inv(e,r);

        for(int i=0;i<len;++i){
            scanf("%lld",&t);
            llt m = powerMod(t,d,n);
            printf("%c",m);
        }
        printf("\n");
    }
    return 0;
}
