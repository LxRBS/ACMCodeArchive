/**
 * 给一个圆括号和方括号的串。有两种操作：
 * 1 改变括号的方向，花费为0
 * 2 方变圆花费为1，注意，不允许圆变方
 * 给定q个独立的询问，每次问：
 * 将[s, e]的序列改为合法括号序列，最小花费是多少
 * 显然方变圆越少越好
 * 考虑一对方括号，如果其内有偶数个括号，则通过操作1一定可以变为合法，从而这一对方括号只需零花费就能匹配
 * 而这对方括号的位置是奇偶相异的
 * 因此只需统计奇数位置和偶数位置方括号的数量即可
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
int const SIZE = 1000010;
#endif

char A[SIZE];
int Q, N, L, R;
int Cnt[2][SIZE];
int T[SIZE];

void preproc(){
    N = strlen(A+1);
	for(int i=0;i<4;++i){
		fill(Cnt[0], Cnt[0]+N, 0);
		fill(Cnt[1], Cnt[1]+N, 0);
	}

	for(int i=1;i<=N;i+=2){
		Cnt[0][i+1] = Cnt[0][i] = Cnt[0][i-1]; 
		Cnt[1][i+1] = Cnt[1][i] = Cnt[1][i-1]; 
		if('[' == A[i] || ']' == A[i]){
			++Cnt[0][i]; ++Cnt[0][i+1];
		}
		if('[' == A[i+1] || ']' == A[i+1]){
			++Cnt[1][i+1];
		}
		T[i] = Cnt[0][i] - Cnt[1][i];
		T[i+1] = Cnt[0][i+1] - Cnt[1][i+1];
	}
}

inline int ABS(int x){return x >= 0 ? x : -x;}

inline int proc(){
    return ABS(T[R] - T[L-1]);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    int nofkase;
	scanf("%d", &nofkase);
	while(nofkase--){
        scanf("%s%d", A+1, &Q);
		preproc();
		while(Q--){
			scanf("%d%d", &L, &R);
			printf("%d\n", proc());
		}
	}
    return 0;
}

