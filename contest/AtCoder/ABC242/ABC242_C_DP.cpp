/**
 * 求N位长的满足条件的数字串的数量，条件是：相邻位差不超过1
 * DP， N在1E6，就不用矩阵快速幂了，O(9N)可以完成
 * Dij是长度为i以j结尾的方案总数
 * Dij = D[i-1][j-1] + D[i-1][j] + D[i-1][j+1]
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
int const SIZE = 1000001;
#endif

typedef long long llt;
llt const MOD = 998244353LL;

int D[SIZE][10];

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int n = getInt();
    for(int i=1;i<=9;++i) D[1][i] = 1;
	for(int i=2;i<=n;++i)for(int j=1;j<=9;++j){
		D[i][j] = D[i-1][j];
		if(j > 1) (D[i][j] += D[i-1][j-1]) %= MOD;
		if(j < 9) (D[i][j] += D[i-1][j+1]) %= MOD;
	}
    cout<<accumulate(D[n]+1,D[n]+10,0LL)%MOD<<endl;
    return 0;
}