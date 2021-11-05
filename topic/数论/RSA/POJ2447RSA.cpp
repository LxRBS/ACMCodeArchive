/*
    RSA破解
    给定n，分解出p、q
    再计算出r=(p-1)(q-1)
    再利用e，计算出e模r的逆d
    令c是明文，则源信息m=c^d%n
*/
#include <stdio.h>
#include <stdlib.h>
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

llt gcd(llt a,llt b){
    while( b ){
        llt t = a % b;
        a = b;
        b = t;
    }
    return a;
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

//returns one of factors of n, c is a random number
llt Pollard_Rho(llt n,llt c){
    llt k = 2;
    llt x = rand() % n;
    llt y = x;
    for(int i=1;;++i){
        x = ( multiMod(x,x,n) - c ) % n;
        if ( x < 0 ) x += n;

        if ( y == x ) return n;

        llt d = gcd(y-x>0?y-x:x-y,n);
        if ( d != 1 && d != n ) return d;

        if ( i == k ) y = x, k <<= 1;
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    llt c,e,n,p,q,r,d,m;
    while( EOF != scanf("%lld%lld%lld",&c,&e,&n) ){
        p = Pollard_Rho(n,rand()%(n-3)+3);
        q = n / p;
        r = ( p - 1 ) * ( q - 1 );
        d = inv(e,r);
        m = powerMod(c,d,n);
        printf("%lld\n",m);
    }
    return 0;
}
