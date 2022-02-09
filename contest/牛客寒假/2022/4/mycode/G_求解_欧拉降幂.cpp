/**
 * 给定一个长度为N的序列，N在2E5
 * 对所有子序列，计算其最大值乘以最小值的累乘积
 * 显然不可能枚举子序列。考虑每个Ai，作为最大值出现了多少次，最小值出现了多少次
 * 显然以Ai为最小值的序列一共有2^right个，其中right是大于等于Ai的数
 * 最大值的数量是2^left，至于left和right，排序以后即可得到
 * 所以ans = SIGMA{Ai^2^(i-1) * Ai^2^(N-i)}
 * 但是2^x是一个很大的数，需要用到欧拉降幂，即当a、p互质时，a^n%p = a^(n%phi(p))%p
 * 即需要计算2^x%(p-1)，快速幂即可
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

#ifndef ONLINE_JUDGE
int const SIZE = 22;
#else
int const SIZE = 201010;
#endif

typedef long long llt;
llt const MOD = 1000000007LL;

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


int N;
llt A[SIZE];

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt();
	for(int i=1;i<=N;++i) A[i] = getInt();
	sort(A+1, A+N+1);
	llt ans = 1LL;
	for(int v=N-1,u=0,i=1;i<=N;++i,++u,--v){
        ans = ans * powerMod(A[i], powerMod(2LL, u, MOD-1), MOD) % MOD
		     * powerMod(A[i], powerMod(2LL, v, MOD-1), MOD) % MOD;
	}
	cout<<ans<<endl;
    return 0;
}


