/*
    求n^k的高三位和低三位
    低三位就是快速幂取模1000
    高三位需要用到对数
    令n^k = a.bEm
    则log(n^k) = m + log(a.b)
    所以求出log(n^k)，再取其小数部分
    再做10的幂，即可得到a.b
*/
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

typedef long long llt;
typedef llt int_t;

//returns a^n%mod
int_t powerMod(int_t a,int_t n,int_t mod){
    int_t ret = 1;
    a %= mod;

    while( n ){
        if ( n & 1 ) ret = ret * a % mod;
        n >>= 1;
        a = a * a % mod;
    }
    return ret;
}

int main(){
    //freopen("1.txt","r",stdin);

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        llt n,k;
        scanf("%lld%lld",&n,&k);

        //低三位
        llt ans2 = powerMod(n,k,1000LL);

        //高三位
        double x = k*log10(n);
        x -= (int)x;
        x = pow(10,x);
        x *= 100;

        printf("Case %d: %d %03d\n",kase,(int)x,(int)ans2);
    }
    return 0;
}
