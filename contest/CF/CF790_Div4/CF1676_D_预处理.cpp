/**
 * 给定一个二维数组，问放置一个国际象棋的象，能够攻击到的格子的最大和是多少。
 * 也就是问所在格子的正对角线和反对角线之和最大是多少
 * 预处理出所有对角线各自的和，然后循环找最大值即可
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
int const SIZE = 14;
#else
int const SIZE = 220;
#endif

using llt = long long;
llt A[SIZE][SIZE];
int N, M;

llt Z[SIZE+SIZE+13];
llt F[SIZE+SIZE+13];

llt proc(){
    memset(Z, 0, sizeof(Z));
    memset(F, 0, sizeof(F));

    for(int i=0;i<N;++i)for(int j=0;j<M;++j){
        Z[j-i+N] += A[i][j];
        F[i+j] += A[i][j];
    }

    llt ans = 0;
    for(int i=0;i<N;++i)for(int j=0;j<M;++j){
        ans = max(ans, Z[j-i+N] + F[i+j] - A[i][j]);
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
        M = getInt();
        for(int i=0;i<N;++i)for(int j=0;j<M;++j)A[i][j] = getInt();
        printf("%lld\n", proc());
    }
    return 0;
}

