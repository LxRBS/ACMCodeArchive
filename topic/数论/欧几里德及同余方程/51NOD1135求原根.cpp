#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

typedef long long int llt;

//线性筛法
int const SIZE = sqrt(1E9) + 2;//一般只筛到30000+即可
bool isComp[SIZE] = {false};//isComp[i]为真说明i是合数
int P[SIZE];//P[i]为第i个素数，i从0开始
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

//质因子分解，n是待分解的数,p保存质因子，cnt是不同质因子的数量
void primeFactor(int n,int p[],int&cnt){
    cnt = 0;
    for(int i=0;i<PCnt&&P[i]*P[i]<=n;++i){
        if ( 0 == n % P[i] ){
            p[cnt++] = P[i];
            while( 0 == n % P[i] ) n /= P[i];
        }
    }
    if ( n != 1 ) p[cnt++] = n;
}

//returns a^n%mod
llt powerMod(llt a,llt n,llt mod){
    llt ret = 1;
    a %= mod;

    while( n ){
        if ( n & 1 ) ret = ret * a % mod;
        n >>= 1;
        a = a * a % mod;
    }
    return ret;
}

//求prime的最小原根，prime是质数,p用来保存prime-1的质因子
llt minPrimitiveRoot(llt prime,int p[]){
    //分解质因子
    llt n = prime - 1;
    int cnt;
    primeFactor(n,p,cnt);
    for(llt g=2;g<prime;++g){
        bool flag = true;
        for(int i=0;i<cnt;++i){
            if ( 1 == powerMod(g,n/p[i],prime) ){
                flag = false;
                break;
            }
        }
        if (flag) return g;
    }
}

int A[SIZE];
int main(){
    sieve();
    llt prime;
    scanf("%lld",&prime);
    printf("%lld\n",minPrimitiveRoot(prime,A));
    return 0;
}
