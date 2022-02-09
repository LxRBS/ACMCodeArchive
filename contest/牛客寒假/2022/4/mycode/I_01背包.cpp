/**
 * 每张卡片有消耗ai和威力bi，一共有N张，
 * 要求选出若干张满足：
 * 1 威力最大
 * 2 消耗是K的倍数
 * 显然01背包，状态是对K取余数，令
 * Div是考虑前i张卡片，总消耗余K为v的最大威力，则
 * Div = max(D[i-1][v], D[i-1][v-ai]+bi)
 * 最后输出D[N][0]即可
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
int const SIZE = 1010;
#endif

typedef long long llt;

int N, K;
llt A[SIZE], B[SIZE];
llt D[SIZE][SIZE];

inline int sub(int a, llt b){
    return ((int)(((llt)a - b) % K) + K) % K;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); K = getInt();
    for(int i=1;i<=N;++i){
        A[i] = getInt(); B[i] = getInt();        
    }
    for(int i=1;i<K;++i) D[0][i] = -1;
    for(int i=1;i<=N;++i){
        for(int t,j=0;j<K;++j){
            t = sub(j, A[i]);
            if(D[i-1][t] != -1){
                D[i][j] = max(D[i-1][j], D[i-1][t]+B[i]);
            }else{
                D[i][j] = D[i-1][j];
            }             
        }
    }
    cout<<(D[N][0]?D[N][0]:-1)<<endl;
    return 0;
}


