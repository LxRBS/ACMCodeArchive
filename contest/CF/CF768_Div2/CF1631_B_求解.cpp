/**
 * 给定一个数组A，有一种操作，每次可以选择一个偶数长度的区间，
 * 将后一半内容复制到前一半，即改变前一半内容、后一半不变。
 * 问最少要几次操作，可以将整个数组改为一样
 * 因为只能把后面的复制到前面去，所以目标就是最后一个值。
 * 从最后一个值开始，贪心即可。
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
int const SIZE = 200010;
#endif

int N;
int A[SIZE];

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
    while(nofkase--){
		N = getInt();
		for(int i=1;i<=N;++i) A[i] = getInt();
		if(1 == N){
			puts("0"); continue;
		}
		int cnt = 0;
		int now = N - 1;
		while(1){
            while(now >= 1 && A[now] == A[N]) --now;
			if(now == 0) break;

			++cnt;
			int start = max(1, now+1-(N-now));
			fill(A+start, A+now+1, A[N]);
			now = start - 1;
		}
		printf("%d\n", cnt);
	}	
    return 0;
}