/**
 * 给定一个数组，再给Q个询问，每次问：
 * 给一个X，问最少选几个数可以使得其和大于等于X
 * 对原数组做一个排序，并求出前缀和，二分搜索即可
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
int const SIZE = 2E5+13;
#endif

using llt = long long;

int N, Q;
llt A[SIZE];
llt B[SIZE];

void proc(){
    llt x = getInt();
    int ans = lower_bound(B, B+N+1, x) - B;
	if(ans == N + 1) printf("-1\n");
	else printf("%d\n", ans);
	return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif    
    int nofkase = getInt();
	while(nofkase--){
		N = getInt(); Q = getInt();
		for(int i=1;i<=N;++i) A[i] = getInt();
		sort(A+1, A+N+1, [](int a, int b){return a>b;});
		for(int i=1;i<=N;++i) B[i] = B[i-1] + A[i];
		for(int q=1;q<=Q;++q){
			proc();
		}
	}

    return 0;
}