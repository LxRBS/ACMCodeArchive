/**
 * 给定一个排列，只有一次机会选中一个区间进行reverse操作，要求操作后字典序最小
 * 字典序最小，显然就是要按12345...的顺序
 * 如果中间有一个数不在位置，将其换过来即可
 * 因此假设k不在第k个位置，而在第y个位置，reverse区间[k, y]即可
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
int const SIZE = 7;
#else
int const SIZE = 1010;
#endif

int N, A[SIZE];

void proc(){
	if(1 == N){
		return (void)printf("%d\n", A[1]);
	}

	int k = 1;
	while(k <= N && k == A[k]) ++k;
	if(k == N + 1){
		for(int i=1;i<=N-2;++i)printf("%d ", i);
		printf("%d %d\n", N-1, N);
		return;
	}

    int i, pos = k;
	for(i=k;A[i]!=k;++i){
        if(A[i] > A[pos]) pos = i;
	}

	reverse(A+k, A+i+1);
	printf("%d", A[1]);
	for(int i=2;i<=N;++i)printf(" %d", A[i]);
	printf("\n");
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
		for(int i=1;i<=N;++i) A[i] = getInt();
		proc();
    }
    return 0;
}
