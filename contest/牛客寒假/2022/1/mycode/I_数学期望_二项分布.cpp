/**
 * N个人M段，每个人独立的选或者不选，
 * 每一段当全选或者全不选，看做失败，否则为成功
 * 问成功段数的期望是多少
 * 每一段失败的概率为2/2^N, 令成功的概率P=1-2/2^N
 * 则成功的期望是
 * C(M, 1)*P*(1-P)^(M-1) + C(M, 2)*P^2*(1-P)^(M-2) + ...
 * 就是一个二项分布，因此成功数量的期望就是 MP 
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

typedef long long llt;

#ifndef ONLINE_JUDGE
int const SIZE = 11;
#else
int const SIZE = 1000055;
#endif

typedef long long llt;
llt const MOD = 1000000000+7;

llt N, M;

llt powerMod(llt a,llt n){
    llt ret = 1;
    a %= MOD;

    while( n ){
        if ( n & 1 ) ret = ret * a % MOD;
        n >>= 1;
        a = a * a % MOD;
    }
    return ret;
}

inline llt inv(llt n){
	return powerMod(n, MOD-2); 
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
	while(nofkase--){
		N = getInt();
		M = getInt();
		llt tmp = powerMod(2, N-1);
		printf("%lld\n", M * (1 - inv(tmp) + MOD) % MOD);
	}
    return 0;
}
