#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long llt;

int const Repeat = 10;

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

long long Fac[100];//质因数分解结果（刚返回时是无序的）
int FCnt;//质因数的个数

llt gcd(llt a,llt b){
    if (0L == a || 0L == b) return 1;
    if ( a < 0 ) a = -a;
    if ( b < 0 ) b = -b;
    while(b){
        llt t = a % b;
        a = b;
        b = t;
    }
    return a;
}
llt Pollard_Rho(llt n,llt c){
	llt i = 1, k = 2;
    //llt k = 2;
    llt x = rand() % n;
    llt y = x;
    while(1){
    	++i;
        x = ( multiMod(x,x,n) + c ) % n;
        llt d = gcd(y-x,n);
        if (d!=1LL && d!=n) return d;
        if (y == x) return n;
        if ( i == k ) y = x, k <<= 1;
    }
}

void find(llt n){
	if ( 4LL == n ){
		Fac[0] = Fac[1] = 2LL;
		FCnt = 2;
		return;
	}
    if ( Miller_Rabin(n,Repeat) ){
        Fac[FCnt++] = n;
        return;
    }

    llt p;
    while( ( p = Pollard_Rho(n,rand()%(n-3)+3) ) == n );

    find(p);
    find(n/p);
}

int main(){
    int kase;
    scanf("%d",&kase);
    while(kase--){
    	llt n;
        scanf("%I64d",&n);

        FCnt=0;
        find(n);
        
        
        if(Fac[0] == n) printf("Prime\n");
        else printf("%I64d\n",*min_element(Fac,Fac+FCnt));
    }
    return 0;
}
