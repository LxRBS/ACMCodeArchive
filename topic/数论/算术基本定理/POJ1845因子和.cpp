#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

typedef long long int llt;
typedef llt int_t;

llt const MOD = 9901LL;

//非递归的扩展欧几里德算法
//返回a、b的gcd，同时x、y满足ax+by=gcd
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

//求a相对于p的逆元，a、p互质才存在逆元
int_t inv(int_t a,int_t p){
    int_t x,y;
    int_t r = exEuclid(a,p,x,y);
    if ( r != 1 ) return 0;
    x = x % p;
    if ( x < 0 ) x += p;
    return x;
}

//利用二进制计算a*b%MOD
llt multiMod(llt a,llt b,llt MOD){
	llt ret = 0LL;
	a %= MOD;
	while( b ){
		if ( b & 1LL ) ret = ( ret + a ) % MOD, --b;
		b >>= 1LL;
		a = ( a + a ) % MOD;
	}
	return ret;
}

//计算a^b%MOD
llt powerMod(llt a,llt b,llt MOD){
    llt ret = 1LL;
    a %= MOD;
    while( b ){
    	if ( b & 1LL ) ret = multiMod(ret,a,MOD),--b;
    	b >>= 1LL;
    	a = multiMod(a,a,MOD);
    }
    return ret;
}

//质因子p，个数k
llt sum(llt p,llt k){
    if ( 1LL == p % MOD ) return ( k + 1LL ) % MOD;

    llt ret = ( powerMod(p,k+1LL,MOD) - 1LL ) % MOD;
    if ( ret < 0 ) ret += MOD;

    llt i = inv(p-1LL,MOD);
    return multiMod(ret,i,MOD);
}

llt proc(llt a,llt b){
    llt ret = 1LL;

    for(llt i=2LL;i*i<=a;i+=1LL){
        if ( a % i ) continue;

        llt k = 0;
        while( 0LL == a % i ) a /= i, ++k;
        k *= b;
        ret = ( ret * sum(i,k) ) % MOD;
    }

    if ( a != 1LL ) ret = ( ret * sum(a,b) ) % MOD;
    return ret;
}

int main(){
    llt a,b;
    while(cin>>a>>b) cout<<proc(a,b)<<endl;
    return 0;
}
