/**
 * 给一个N长度数字串，求所有可能划分的乘积之和。例如：234
 * 可以划分的位置一共有2个，因此用有4种可能，分别是
 * 234,23|4,2|34,2|3|4，乘积分别是234,92,68,24
 * 所以答案是418
 * 基本上比较显然的DP，令Di是到i位置的答案，则
 * Di = SIGMA{Dj * A[j+1:i], j=0,...,i-1}
 * 这个方程显然是N^2的，考虑优化一下。对比一下就发现
 * Di = D[i-1] * 10 + A[i] * SIGMA{Dj, j=0,...,i-1}
 * 注意D[0]和D[1]的值需要初始化。
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
int const SIZE = 33;
#else
int const SIZE = 2E5+10;
#endif

using llt = long long;
using vll = vector<llt>;
using vi = vector<int>;
using vvi = vector<vi>;

llt const MOD = 998244353LL;

int N;
char A[SIZE];
vector<llt> D;


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    scanf("%d%s", &N, A + 1);
    D.assign(N + 1, 0LL);    
    D[0] = 1;
    D[1] = A[1] - '0';
    llt s = D[0] + D[1];
    for(int i=2;i<=N;++i){
        D[i] = D[i - 1] * 10 % MOD + (A[i] - '0') * s % MOD;
        D[i] %= MOD;
        s = (s + D[i]) % MOD;
    }
    cout << D[N] << endl;
    return 0;
}