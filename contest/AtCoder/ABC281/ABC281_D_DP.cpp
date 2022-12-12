/**
 * 给定N长度的数组A，再给定K和M
 * 在A中选K个数，使得其和是M的倍数且最大
 * N、K、M均在100
 * 令Dijk为前i个数选j个余数为k的最大
 * 则 Dijk = max(D[i-1][j][k], D[i-1][j-1][k-Ai%M]+Ai)
 * 类似背包DP
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
int const SIZE = 13;
#else
int const SIZE = 2E5+5;
#endif

using llt = long long;
using vll = vector<llt>;
using v3ll = vector<vector<vll>>;

int N, M, K;
vll A;
v3ll D; // Dijk表示前i个数选择k个余数是k的最大值

llt proc(){
    D.assign(N+1, vector<vll>(K+1, vll(M, -1LL)));

    D[0][0][0] = 0;
    
	for(int i=1;i<=N;++i){
		D[i][0][0] = 0;
		llt left = A[i] % M;
		for(int j=1;j<=min(i,K);++j){
			for(int k=0;k<M;++k){
				D[i][j][k] = D[i-1][j][k];
				int pos = ((k - left) % M + M) % M;
				if(D[i-1][j-1][pos] != -1){
					D[i][j][k] = max(D[i][j][k], D[i-1][j-1][pos] + A[i]);
				}
			} 
		}
	}

	return D[N][K][0];
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    A.assign((N = getInt())+1, 0LL);
	K = getInt();
	M = getInt();
	for(int i=1;i<=N;++i) A[i] = getInt();
	cout << proc() << endl;
    return 0;
}