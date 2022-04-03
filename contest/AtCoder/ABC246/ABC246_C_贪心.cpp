/**
 * 给定数组A与X，K次操作
 * 每次操作可以选择Ai将其减去X，最小减到0
 * 问K次操作后，数组A的总和最小是多少
 * 贪心即可
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
int const SIZE = 100;
#else
int const SIZE = 2E5+5;
#endif

typedef long long llt;
typedef pair<int, int> pii;

int N;
llt A[SIZE];
llt K, X;

llt proc(){
	for(int i=1;i<=N;++i){
        llt a = A[i] / X;
		int k = min(a, K);
		A[i] -= k * X;
		if(0 == (K -= k)) goto L;
	}
	sort(A+1, A+N+1, greater<llt>());
	for(int i=1;i<=N;++i){
		if(0 == A[i]) continue;
		A[i] = 0;
		if(0 == --K) goto L;
	}

L:
    return accumulate(A+1, A+N+1, 0LL);
}

int main() {    
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt();
	K = getInt();
	X = getInt();	
	for(int i=1;i<=N;++i)A[i] = getInt();
	cout<<proc()<<endl;
    return 0;
}

