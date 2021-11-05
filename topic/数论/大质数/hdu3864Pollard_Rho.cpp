#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long llt;

llt gcd(llt a,llt b){
    if (0L == a || 0L == b) return 1;
    if (a < 0) a = -a;
    if (b <0 ) b = -b;
    while(b){
        llt t = a % b;
        a = b;
        b = t;
    }
    return a;
}
//利用二进制计算a*b%mod
llt multiMod(llt a,llt b,llt mod){
	llt ret = 0LL;
	a %= mod;
	while( b ){
		if ( b & 1LL ) ret = ( ret + a ) % mod, --b;
		b >>= 1LL;
		a = ( a + a ) % mod;
	}
	return ret;
}

//计算a^b%mod
llt powerMod(llt a,llt b,llt mod){
    llt ret = 1LL;
    a %= mod;
    while( b ){
    	if ( b & 1LL ) ret = multiMod(ret,a,mod),--b;
    	b >>= 1LL;
    	a = multiMod(a,a,mod);
    }
    return ret;
}

//Miller-Rabin测试,测试n是否为素数
bool Miller_Rabin(llt n,int repeat){
	if ( 2LL == n || 3LL == n ) return true;
	if ( !( n & 1LL ) ) return false;

	//将n分解为2^s*d
	llt d = n - 1LL;
	int s = 0;
	while( !( d & 1LL ) ) ++s, d>>=1LL;

	//srand((unsigned)time(0));
    for(int i=0;i<repeat;++i){//重复repeat次
        llt a = rand() % ( n - 3 ) + 2;//取一个随机数,[2,n-1)
        llt x = powerMod(a,d,n);
        llt y = 0LL;
        for(int j=0;j<s;++j){
        	y = multiMod(x,x,n);
        	if ( 1LL == y && 1LL != x && n-1LL != x ) return false;
        	x = y;
        }
        if ( 1LL != y ) return false;
    }
    return true;
}

llt Fac[100];
int FCnt = 0;

llt Pollard_Rho(llt n,llt c){
    llt k = 2;
    llt x = rand() % n;
    llt y = x;
    for(int i=1;;++i){
        x = ( multiMod(x,x,n) - c ) % n;
        if ( x < 0 ) x += n;

        llt d = gcd(y-x,n);
        if (d!=1L && d!=n) return d;
        if (y == x) return n;
        if ( i == k ) y = x, k <<= 1;
    }
}

void find(llt n){
    if ( Miller_Rabin(n,1) ){
        Fac[FCnt++] = n;
        return;
    }

    llt p;
    while( ( p = Pollard_Rho(n,rand()%(n-3)+3) ) == n );

    find(p);
    find(n/p);
}

char const Out[] = "is not a D_num";
int main(){
    llt n;
    while( EOF != scanf("%I64d",&n) ){
        if ( 1L == n ){
            printf("%s\n",Out);
            continue;
        }

        FCnt = 0;
        find(n);

        if ( 3 == FCnt && Fac[0] == Fac[1] && Fac[1] == Fac[2] ){
            llt& p = Fac[0];
            printf("%I64d %I64d %I64d\n",p,p*p,n);
        }else if ( 2 == FCnt && Fac[0] != Fac[1] ){
            printf("%I64d %I64d %I64d\n",Fac[0],Fac[1],n);
        }else{
            printf("%s\n",Out);
        }
    }
    return 0;
}

