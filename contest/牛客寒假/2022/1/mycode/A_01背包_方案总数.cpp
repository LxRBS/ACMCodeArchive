/**
 * 对一个多位数，令各个位数字相加再相加，直到和为个位数，该结果称为原数的根
 * 给定N个数，问一共有多少种选法使得选出数之和的根为k，其中k为1~9
 * 相加再相加最后得到的就是对9取模，因此原问题变为多少种选法使得和模9为k
 * Dvi为前i个数模为v的方法的总数，则
 * Dvi = D[v][i-1] + D[v-Ai+9][i-1]
 * 即第i个数不选或者选
 * 注意初始化条件
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
int const SIZE = 11;
#else
int const SIZE = 100055;
#endif

typedef long long llt;
llt const MOD = 998244353;

int N;
llt A[SIZE];
llt D[10][SIZE];

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt();
	for(int i=1;i<=N;++i)A[i] = getInt() % 9;
	D[0][0] = 1;
    for(int i=1;i<=N;++i){
		D[1][i] = (D[1][i-1] + D[(1-A[i]+9)%9][i-1])%MOD;
		D[2][i] = (D[2][i-1] + D[(2-A[i]+9)%9][i-1])%MOD;
		D[3][i] = (D[3][i-1] + D[(3-A[i]+9)%9][i-1])%MOD;
		D[4][i] = (D[4][i-1] + D[(4-A[i]+9)%9][i-1])%MOD;
		D[5][i] = (D[5][i-1] + D[(5-A[i]+9)%9][i-1])%MOD;
		D[6][i] = (D[6][i-1] + D[(6-A[i]+9)%9][i-1])%MOD;
		D[7][i] = (D[7][i-1] + D[(7-A[i]+9)%9][i-1])%MOD;
		D[8][i] = (D[8][i-1] + D[(8-A[i]+9)%9][i-1])%MOD;
		D[0][i] = (D[0][i-1] + D[(0-A[i]+9)%9][i-1])%MOD;		
	}
	for(int i=1;i<=8;++i)printf("%lld ", D[i][N]);
	printf("%lld\n", D[0][N]-1);
    return 0;
}
