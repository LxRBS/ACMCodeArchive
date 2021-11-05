/*
    ��n^k�ĸ���λ�͵���λ
    ����λ���ǿ�����ȡģ1000
    ����λ��Ҫ�õ�����
    ��n^k = a.bEm
    ��log(n^k) = m + log(a.b)
    �������log(n^k)����ȡ��С������
    ����10���ݣ����ɵõ�a.b
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

        //����λ
        llt ans2 = powerMod(n,k,1000LL);

        //����λ
        double x = k*log10(n);
        x -= (int)x;
        x = pow(10,x);
        x *= 100;

        printf("Case %d: %d %03d\n",kase,(int)x,(int)ans2);
    }
    return 0;
}
