/**
 * Taka从坐标0处开始跳，第i步可以跳ai或者bi
 * 问N跳以后是否能够到到X。
 * 就是问A或B中依次挑一个，和是否为X，显然是背包，每次选A或者选B
 * 到第N个，D[x]是否恰好为x
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000-1,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

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
int const SIZE = 17;
#else
int const SIZE = 110;
#endif

int A[SIZE], B[SIZE];
int N, X;
int D[101][10001];

bool proc(){
	for(int i=1;i<=N;++i)fill(D[i], D[i]+X+1, -1);
	D[1][A[1]] = A[1]; D[1][B[1]] = B[1];
	
	for(int i=2;i<=N;++i){
		for(int v=X;v>=min(A[i], B[i]);--v){
			if(-1 != D[i-1][v-A[i]] && v >= A[i]) D[i][v] = D[i-1][v-A[i]] + A[i];
			if(-1 != D[i-1][v-B[i]] && v >= B[i]) D[i][v] = D[i-1][v-B[i]] + B[i];
		}
	}
	return D[N][X] != -1;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt(); X = getInt();
	for(int i=1;i<=N;++i)A[i]=getInt(), B[i]=getInt();
	puts(proc()?"Yes":"No");
    return 0;
}
