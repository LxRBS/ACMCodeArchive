/*
    给定n，问有多少组(a,b)满足
    lcm(a,b)=n

    利用算术基本定理
    n = PI(pi^ki)

    对每一个质因子pi，
    a和b包含pi的不同情况一共有2ki+1种
    因为a或者b之中必须有一个包含pi^ki
    然后另一个关于pi的指数可以取遍0~ki

    最后去一下重
*/
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

//线性筛法
int const SIZE = 1E7+5;//一般只筛到30000+即可
bool isComp[SIZE] = {false};//isComp[i]为真说明i是合数
int P[665000];//1E7以内的质数为664000+
int PCnt = 0;//PCnt记录1~SIZE之间的素数的个数
void sieve(){
    for(int i=2;i<SIZE;++i){
        if ( !isComp[i] ) P[PCnt++] = i;

        for(int j=0;j<PCnt&&i*P[j]<SIZE;++j){
            isComp[i*P[j]] = true;
            if ( 0 == i % P[j] ) break;
        }
    }
}

typedef long long llt;

int main(){
    //freopen("1.txt","r",stdin);
    sieve();

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        llt n;
        scanf("%lld",&n);

        llt ans = 1LL;
        for(int i=0;(llt)P[i]*(llt)P[i]<=n&&i<PCnt;++i){
            if ( 0 == n % P[i] ){
                int k = 0;
                while( 0 == n % P[i] ) n /= P[i], ++k;
                ans *= 2 * k + 1;
            }
        }
        if ( n != 1 ) ans *= 3;
        printf("Case %d: %lld\n",kase,(ans+1)>>1);
    }
    return 0;
}