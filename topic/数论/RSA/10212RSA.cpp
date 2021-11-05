#include <cstdio>
#include <cstdlib>
#include <ctime>

typedef long long int int_t;

int_t gcd(int_t a,int_t b){
    while( b ){
        int_t t = a % b;
        a = b;
        b = t;
    }
    return a;
}

//returns a * b % mod
int_t multiMod(int_t a,int_t b,int_t mod){
    int_t ret = 0;
    a %= mod, b %= mod;

    while( b ){
        if ( b & 1 ) ret = ( ret + a ) % mod;
        b >>= 1;
        a = ( a + a ) % mod;
    }
    return ret;
}
//returns a ^ n % mod
int_t powerMod(int_t a,int_t n,int_t mod){
    int_t ret = 1;
    a %= mod;

    while( n ){
        if ( n & 1 ) ret = multiMod(ret,a,mod);
        n >>= 1;
        a = multiMod(a,a,mod);
    }
    return ret;
}

//Miller_Rabin algorithm
//returns true if n is possible a prime
bool Miller_Rabin(int_t n,int repeat){
    if ( 2 == n ) return true;
    if ( !( n & 1 ) ) return false;

    //n = 2^s*d
    int_t d = n - 1;
    int s = 0;
    while( ! ( d & 1 ) ) ++s, d>>=1;

    srand((unsigned)time(0));
    for(int i=0;i<repeat;++i){
        int_t a = rand() % ( n - 3 ) + 2;//a random number from the range of [2,n-1)
        int_t x = powerMod(a,d,n);
        int_t y = 0LL;
        for(int j=0;j<s;++j){
        	y = multiMod(x,x,n);
        	if ( 1LL == y && 1LL != x && n-1LL != x ) return false;
        	x = y;
        }
        if ( 1LL != y ) return false;
    }
    return true;
}

//returns one of factors of n, c is a random number
int_t Pollard_Rho(int_t n,int_t c){
    int_t k = 2;
    int_t x = rand() % n;
    int_t y = x;
    for(int i=1;;++i){
        x = ( multiMod(x,x,n) - c ) % n;
        if ( x < 0 ) x += n;

        if ( y == x ) return n;

        int_t d = gcd(y-x>0?y-x:x-y,n);
        if ( d != 1 && d != n ) return d;

        if ( i == k ) y = x, k <<= 1;
    }
}

//The extended Euclidean algorithm implemented by iteration
//returns gcd(a,b), and x, y are satisfied with ax + by = gcd
int_t exEuclid(int_t a,int_t b,int_t&x,int_t&y){
    int_t x0 = 1, y0 = 0;
    int_t x1 = 0, y1 = 1;
    x = 0; y = 1;
    int_t r = a % b;
    int_t q = ( a - r ) / b;
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

//returns the inverse of a mod p satisfined with 1 == ax%p
//it will be seccess only when a and p are co-prime
int_t inv(int_t a,int_t p){
    int_t x,y;
    int_t r = exEuclid(a,p,x,y);
    if ( r != 1 ) return 0;
    x = x % p;
    if ( x < 0 ) x += p;
    return x;
}

typedef long long int llt;
int main(){
    int nofkase;
    scanf("%d",&nofkase);

    while(nofkase--){
        llt n,e,m;
        scanf("%I64d%I64d%I64d",&n,&e,&m);

        llt p = Pollard_Rho(n,rand()%(n-3)+3);
        llt q = n / p;
        llt phi = ( p - 1LL ) * ( q - 1LL );
        llt d = inv(e,phi);

        printf("%I64d\n",powerMod(m,d,n));
    }
}

