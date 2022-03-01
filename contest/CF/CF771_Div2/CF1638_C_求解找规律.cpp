/**
 * 给定一个排列，令每个Ai表示图上的一个点，如果Ai和Aj是逆序对就连边，
 * 问，该图有几个连通块
 * 设A1=k，则可以肯定A1所在的连通块延伸至第k个位置之后
 * 还可以肯定2~k范围内数都和A1在同一个连通块内
 * 所以只需要对每一个Ai记录其所在连通块能够到达的最右边界即可
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
int const SIZE = 100110;
#endif

int N, A[SIZE];

int proc(){
	int anchor = 0, ans = 0;
	for(int i=1;i<=N;++i){
		if(i > anchor){
			++ans; anchor = i;
		}
		if(A[i] >= anchor) anchor = A[i];
	}
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
	while(nofkase--){
		N = getInt();
		for(int i=1;i<=N;++i)A[i]=getInt();
		printf("%d\n", proc());
	}
    return 0;
}
