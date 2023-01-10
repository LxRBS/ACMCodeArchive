/**
 * N*N的矩阵，从(1,1)到(N,N)，只能向下或者向右
 * 经过一个就能得到i*j的分数，问最大可能得到的分数
 * 答案为最大分数乘以2022在对1E9+7取模
 * 简单验证一下发现是Hexagonal pyramidal numbers, or greengrocer's numbers
 * 公式为 n(n+1)(4n-1)/6
 */
#include <bits/stdc++.h>
using namespace std;
 
char *__abc147, *__xyz258, __ma369[1000000];
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
int const SIZE = 23;
#else
int const SIZE = 2E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;

llt const MOD = 1000000000LL + 7;

llt power(llt a, llt n){
    llt ret = 1;
    while(n){
        if(n & 1) ret = ret * a % MOD;
        a = a * a % MOD;
        n >>= 1;
    }
    return ret;
}
inline llt inv(llt a){return power(a, MOD-2LL);}

llt const INV6 = inv(6LL);

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        llt n = getInt();
        llt ans = n * (n + 1LL) % MOD * ((4 * n - 1) % MOD) % MOD * INV6 % MOD * 2022LL % MOD;
        printf("%lld\n", ans);     
    }
    return 0;
}


