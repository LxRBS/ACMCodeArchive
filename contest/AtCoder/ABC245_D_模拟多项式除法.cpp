/**
 * 多项式的除法，阶数在100
 * 按照定义进行计算即可
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
int const SIZE = 10;
#else
int const SIZE = 1005;
#endif

typedef long long llt;
typedef pair<int, int> pii;

int A[SIZE];
int B[SIZE];
int C[SIZE];
int N, M;

void proc(){
	int high = N + M;
	int b = M, t;
	while(1){
        B[b] = t = C[high] / A[N];
		C[high] = 0;
		for(int i=1;i<=N;++i){
			C[high-i] -= t * A[N-i];
		}
		--b; --high;
		if(-1 == b) break;
	}
}

int main() {    
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt(); M = getInt();
	for(int i=0;i<=N;++i) A[i] = getInt();
	for(int i=0;i<=N+M;++i) C[i] = getInt();
	proc();
	printf("%d", B[0]);
	for(int i=1;i<=M;++i) printf(" %d", B[i]);
	printf("\n");
    return 0;
}

