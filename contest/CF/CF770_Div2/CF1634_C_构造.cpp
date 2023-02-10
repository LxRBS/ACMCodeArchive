/**
 * 给定N行K列，要求把1到NK填入表格，并且保证任意行的任意区间的数，
 * 其均值是一个整数，即任意连续m个数的和要是m的倍数
 * 首先必然是奇数一行，偶数一行，才能满足2的
 * 接着往下考虑，发现任意连续m个奇数和必然是m的倍数，任意连续m个偶数和也必然是m的倍数
 * 因此连续的奇数排一行、偶数排一行即可。
 * 例如：N=4,K=3
 * 1 3 5
 * 2 4 6
 * 7 9 11
 * 8 10 12
 * 还有另外一种解法，排出的效果如下：
 * 1 5 9
 * 2 6 10
 * 3 7 11
 * 4 8 12
 * 显然N要是偶数才行。N是奇数不能排，不证明。
 * 注意K==1是特殊情况
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

typedef long long llt;

#ifndef ONLINE_JUDGE
int const SIZE = 11;
#else
int const SIZE = 510;
#endif

int N, K;
int A[SIZE][SIZE];

void proc(){
	if(1 == K){
		puts("YES");
		for(int i=1;i<=N;++i)printf("%d\n", i);
		return;
	}
	if(N&1) return (void)puts("NO");

	puts("YES");
	int t = N / 2;
	int a1 = 1, a2 = 2;
	for(int i=0;i<t;++i){
        for(int i=0;i<K;++i){
			printf("%d ", a1); a1 += 2;
		}
		printf("\n");
		for(int i=0;i<K;++i){
			printf("%d ", a2); a2 += 2;
		}
		printf("\n");
	}
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
		K = getInt();
		proc();
    }
    return 0;
}