/**
 * 给定一个数组，允许一种操作：选定1<=x<y<z<=N
 * 将A[x]替换为A[y]-A[z]
 * 问能否经过不超过N次操作将数组改为不严格升序，要求方案
 * 首先特判，数组是否有序；然后特判A[N-1]和A[N]的关系
 * 然后考虑，假设A[N-2] > A[N-1]，那么唯一的机会就是令A[N-2]=A[N-1]-A[N]，此时要求A[N]是非负数。
 * 反之，如果A[N]是负数且要求数组可行，则只能A[N-2]自身就是有序的，这种情况已经特判过了
 * 所以，A[N]是正数才有可行解。此时可以构造一个解，令Ai=A[i+1]-A[N]即可
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
int const SIZE = 200110;
#endif

typedef long long llt;

int N;
llt A[SIZE];

void proc(){
	if(A[N-2] > A[N-1]){
		return (void)puts("-1");
	}
	if(is_sorted(A, A+N)){
		return (void)puts("0");
	}

    if(A[N-1] < 0){
		return (void)puts("-1");
	}

	printf("%d\n", N-2);
	for(int i=N-3;i>=0;--i){
		printf("%d %d %d\n", i+1, i+1+1, N);
	}
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
	while(nofkase--){
        N = getInt();
		for(int i=0;i<N;++i)A[i]=getInt();
        proc();
	}
	
    return 0;
}
