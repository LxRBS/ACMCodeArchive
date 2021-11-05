//给定x，求能够满足b^p=x的最大的p，x有可能是负数
//算术基本定理，将质因子分解以后，求所有幂次的最大公约数
#include <stdio.h>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long llt;

//线性筛法
int const SIZE = sqrt(2.2E9)+2;//一般只筛到30000+即可
bool isComp[SIZE] = {false};//isComp[i]为真说明i是合数
llt P[SIZE];//P[i]为第i个素数，i从0开始
int PCnt = 0;//PCnt记录1~SIZE之间的素数的个数
void sieve(){
    for(int i=2;i<SIZE;++i){
        if ( !isComp[i] ) P[PCnt++] = i;

        for(llt j=0;j<PCnt&&i*P[j]<SIZE;++j){
            isComp[i*P[j]] = true;
            if ( 0 == i % P[j] ) break;
        }
    }
}

typedef long long int_t;

//iteration implementation
int_t gcd(int_t a,int_t b){
    while( b ){
        int_t r = b;
        b = a % b;
        a = r;
    }
    return a;
}

int proc(llt n){
    bool flag = n < 0;
    if ( flag ) n = -n;

    int ret = 0;
    for(int i=0;i<PCnt&&P[i]*P[i]<=n&&n!=1LL;++i){
        if ( n % P[i] ) continue;

        int k = 0;
        while( 0 == n % P[i] ) n /= P[i], ++k;
        ret = gcd(ret,k);
        if ( 1 == ret ) return 1;
    }
    if ( 1LL != n ) return 1;

    if ( flag ) while( 0 == (ret&1) ) ret >>= 1;
    return ret;
}

int main(){
    sieve();

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        llt n;
        scanf("%lld",&n);
        printf("Case %d: %d\n",kase,proc(n));
    }
    return 0;
}