/**
 * 给一个数组，给定若干询问，每个询问: k, p
 * 即两个相邻元素差大于等于k时，可以将剩余的部分累加，问累加和是否大于等于p
 * 将差分输出排序，然后求一个前缀和，然后二分找到合法的位置，可以直接计算累加和
 * 二分搜索
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
int const SIZE = 33;
#else
int const SIZE = 1000100;
#endif

typedef long long llt;

int N, Q;
llt A[SIZE];
llt B[SIZE];
llt C[SIZE];

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt(); Q = getInt();
    for(int i=0;i<N;++i) A[i] = getInt();
    for(int i=1;i<N;++i){
        B[i] = A[i] - A[i-1];
    } 
    sort(B+1, B+N);
    for(int i=N-1;i>=1;--i){
        C[i] = C[i+1] + B[i];
    }

    llt k, p;
    llt ans;
    for(int q=1;q<=Q;++q){
        k = getInt(); p = getInt();
        int t = lower_bound(B+1, B+N, k) - B;
        ans = C[t] - k * (N - t);
        puts(ans>=p?"Yes":"No");
    }

    return 0;
}