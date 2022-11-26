/**
 * 给一个01数组，再给定一个S，可以在数组的头尾每次删除一个数
 * 问最少需要多少次操作，数组中剩下的数之和恰好等于S
 * 做一个前缀和做一个后缀和，然后二分即可 
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
int const SIZE = 18;
#else
int const SIZE = 2E5+13;
#endif

int N, S;
int A[SIZE];
int B[SIZE];
int C[SIZE];

int proc(){
    for(int i=1;i<=N;++i) B[i] = B[i-1] + A[i];
    if(B[N] < S) return -1;
    if(B[N] == S) return 0;

    C[N+1] = 0;
    for(int i=N;i>=1;--i) C[i] = C[i+1] + A[i];

    int ans = N;
    int t = B[N] - S;
    for(int i=N+1;i>=1;--i){
        int tmp = t - C[i];
        int pos = lower_bound(B, B+N+1, tmp) - B;
        ans = min(ans, N-i+1+pos);
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
        S = getInt();
        for(int i=1;i<=N;++i) A[i] = getInt();
        printf("%d\n", proc());
    }
    return 0;
}
