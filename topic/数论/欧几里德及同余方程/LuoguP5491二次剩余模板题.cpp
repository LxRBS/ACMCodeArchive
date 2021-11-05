/**
    二次剩余模板题
    首先判断是否为二次剩余，即判断方程是否有解
    然后解方程
*/
#include<bits/stdc++.h>
using namespace std;

typedef long long llt;
typedef long long ll;

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

//勒让德符号，判断a是否p的二次剩余
//是返回1，否返回-1
//p是正奇数
int Legendre(llt a, llt p){
    //取余数
    a %= p;

    if(0==a||1==a) return 1;
    if(-1==a){
        switch(p%4){case 1:return 1;case 3:return -1;default:return 0;}
    }
    if(2==a){
        switch(p%8){case 1:case 7:return 1;case 3:case 5:return -1;default:return 0;}
    }
    //分解出-1
    if(a<0) return Legendre(-a, p) * Legendre(-1, p);
    //分解出2
    int k = 0;
    while(!(a&1)) a>>=1, ++k;
    if(k){
        int t = Legendre(2, p);
        return -1==t&&(k&1)?-Legendre(a, p):Legendre(a, p);
    }
    //上下颠倒
    return 1==a%4||1==p%4?Legendre(p, a):-Legendre(p, a);
}

typedef pair<llt,llt> complex_t;
//i2是虚数单位的平方，p是模数
complex_t multi(complex_t const&lhs,complex_t const&rhs,llt const i2,llt p){
    return make_pair(
            (lhs.first*rhs.first%p+i2*lhs.second%p*rhs.second%p)%p,
            (lhs.first*rhs.second%p+lhs.second*rhs.first%p)%p
        );
}
//a^n%p，i2是虚数单位的平方
complex_t powerMod(complex_t a,llt n,llt const i2,llt p){
    complex_t ans = make_pair(1,0);
    while(n){
        if(n&1) ans = multi(ans,a,i2,p);
        a = multi(a,a,i2,p);
        n>>=1;
    }
    return ans;
}

//解二次同余方程x^2=n(mod p)
//返回解的数量
int Cipolla(llt n,llt p,llt& x0,llt& x1){
    if(0==n)return x0=x1=0,1;// 特殊解
    if(1==n)return x0=1,x1=p-1,2;//特殊解
    if(-1==Legendre(n, p)) return 0;//无解，n不是二次剩余

    n %= p;
    if(n<0)n+=p;

    if(3==p%4){//n^((p+1)/2)必然是一个解
        x0 = powerMod(n,(p+1)>>2,p);
    }else if(5==p%8){//n^((p+3)/8)与2n*(4n)^((p-5)/8)其中必然有一个是解
        x0 = powerMod(n,(p+3)>>3,p);
        if((x0*x0-n)%p) x0 = (n+n)%p*powerMod(4*n%p,(p-5)>>3,p);
    }else{//Cipolla算法
        llt a = rand() % p;
        while(0==a||1==Legendre(a*a-n,p)) a = rand()%p;
        x0 = powerMod(make_pair(a,1),(p+1)>>1,(a*a-n+p)%p,p).first;
    }

    x1 = p - x0;
    if(x0==x1) return 1;
    if(x0>x1)swap(x0,x1);
    return 2;
}

int main(){
    //freopen("1.txt","r",stdin);
    //srand(time(0));
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--)    {
        ll n,p;
        scanf("%lld%lld",&n,&p);

        llt x0,x1;
        int cnt = Cipolla(n,p,x0,x1);
        switch(cnt){
            case 0:printf("Hola!\n");break;
            case 1:printf("%lld\n",x0);break;
            case 2:printf("%lld %lld\n",x0,x1);break;
        }
    }
}
