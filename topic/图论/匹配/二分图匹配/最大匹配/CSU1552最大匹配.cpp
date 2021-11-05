#include <time.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
typedef long long llt;
int const K = 8;
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
	if ( 2LL == n ) return true;
	if ( !( n & 1LL ) ) return false;

	//将n分解为2^s*d
	llt d = n - 1;
	int s = 0;
	while( !( d & 1LL ) ) ++s, d>>=1LL;

	srand((unsigned)time(0));
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

int N;
llt A[105];
bool G[105][105];//二分图矩阵
int OddCnt,EvenCnt;
int OIdx[105],EIdx[105];
int Idx[105];
bool read(){
	if ( EOF == scanf("%d",&N) ) return false;
	memset(G,0,sizeof(G));
	OddCnt = EvenCnt = 0;
	for(int i=0;i<N;++i){
		scanf("%lld",A+i);//lld is used on CSU OJ
		Idx[i] = ( A[i] & 1LL ) ? ++OddCnt : ++EvenCnt;
		for(int j=0;j<i;++j){
			if( !Miller_Rabin(A[i]+A[j],K) ) continue;
			if ( A[i] & 1LL ) G[Idx[i]][Idx[j]] = true;
			else G[Idx[j]][Idx[i]] = true;
		}
	}
	return true;
}

bool F[105];
int L[105];
int dfs(int node){
	for(int i=1;i<=EvenCnt;++i){
		if ( !G[node][i] || F[i] ) continue;
		F[i] = true;
		if ( 0 == L[i] || dfs(L[i]) ){
			L[i] = node;
			return 1;
		}
	}
	return 0;
}
int Hungary(){
	memset(L,0,sizeof(L));
	int ret = 0;
	for(int i=1;i<=OddCnt;++i){
        memset(F,0,sizeof(F));
        ret += dfs(i);
	}
	return ret;
}
int main() {
	while( read() )printf("%d\n",Hungary());
	return 0;
}
