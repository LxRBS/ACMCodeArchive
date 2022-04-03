/**
 * 给定数组A和B，要求挑出一个新的数组X，满足：
 * Xi=Ai或者Bi
 * 两个连续的Xi之差的绝对值不超过K
 * DP，令Ui为是否可以以Ai结尾，Vi是否可以以Bi结尾
 * 依次计算即可。
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
int const SIZE = 2E5+5;
#endif

typedef long long llt;
typedef pair<int, int> pii;

int N;
llt K, A[SIZE], B[SIZE];

inline llt ABS(llt n){return n>=0?n:-n;}

int U[SIZE], V[SIZE];
bool proc(){
	U[0] = V[0] = 1;
	for(int i=1;i<N;++i){
        if(U[i-1] != 0){
			if(ABS(A[i-1] - A[i]) <= K){
				U[i] = 1;
			}
			if(ABS(A[i-1] - B[i]) <= K){
				V[i] = 1;
			}
		}
		if(V[i-1] != 0){
			if(ABS(B[i-1] - A[i]) <= K){
				U[i] = 1;
			}
			if(ABS(B[i-1] - B[i]) <= K){
				V[i] = 1;
			}
		}
	}
	return U[N-1] || V[N-1];
}

int main() {    
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt(); K = getInt();
	for(int i=0;i<N;++i) A[i] = getInt();
	for(int i=0;i<N;++i) B[i] = getInt();
	puts(proc()?"Yes":"No");
    return 0;
}

