/**
    扩展的卢卡斯定理模板题
*/
#include<bits/stdc++.h>
using namespace std;

typedef long long llt;

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

//计算n!%p^k，参数pk=p^k
llt facMod(llt n,llt p,llt pk){
    if(0==n||1==n) return 1;
    llt ans = 1;
    //把[1,pk]中所有不是p的倍数乘起来
    for(int i=2;i<pk;++i)if(i%p)ans=ans*i%pk;
    //在模pk意义下，一共有n/pk个
    ans = powerMod(ans,n/pk,pk);
    //把剩下的部分也乘上
    for(int i=2;i<=n%pk;++i)if(i%p)ans=ans*i%pk;
    //递归计算n/p的阶乘
    return ans * facMod(n/p,p,pk) % pk;
}

//计算C(n,m)%p^k，其中参数pk=p^k
llt Cmod(llt n,llt m,llt p,llt pk){
    if(m>n) return 0;
    llt fenzi = facMod(n,p,pk);
    llt fenmu1 = facMod(m,p,pk);
    llt fenmu2 = facMod(n-m,p,pk);
    llt tmp = 0;
    for(llt i=n;i;i/=p) tmp += i/p;
    for(llt i=m;i;i/=p) tmp -= i/p;
    for(llt i=n-m;i;i/=p)tmp -= i/p;
    llt ptmp = powerMod(p,tmp,pk);
    if(0==ptmp) return 0;
    return ptmp * fenzi % pk * inv(fenmu1,pk) % pk * inv(fenmu2,pk) % pk;
}
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
//扩展的Lucas定理，求C(n,k)%m,m不一定是质数
llt exLucas(llt n,llt k,llt m){
    llt mm=m,ans=0;
    //分解m
    for (int i=0;P[i]*P[i]<=mm;++i){
        llt pk = 1, tmp=P[i];
        while(0==mm%tmp) mm/=tmp,pk*=tmp;
        if(1==pk) continue;
        ans = ( ans + Cmod(n,k,tmp,pk) * m/pk % m * inv(m/pk,pk) % m ) % m;
    }
    if (mm!=1)ans = ( ans + Cmod(n,k,mm,mm) * m/mm % m * inv(m/mm,mm) % m ) % m;
    return ans;
}

int main(){
    //freopen("1.txt","r",stdin);
    sieve();
    llt n,m,p;
    scanf("%lld%lld%lld",&n,&m,&p);
    printf("%lld\n",exLucas(n,m,p));
    return 0;
}
