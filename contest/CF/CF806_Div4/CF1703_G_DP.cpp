/**
 * 给定一个数组，依次对每个Ai，有两种操作：
 * 1 付出代价K，收获Ai
 * 2 使得i位置及其以后的数均减半，然后收获此时的Ai
 * 经过N次操作后，问最大的收获是多少。
 * 不能贪心。
 * 令Dij是到i为止减半j次拿到的最大收获，则
 * Dij = max(D[i-1][j] + Aij - K, D[i-1][j-1]+Aij)
 * 注意相应的状态需要存在。
 * 不能用-1来表示状态是否存在，因为计算结果可能存在-1
 * 所以又开了一个Flag数组
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

char getChar(){
    char ch = __hv007();
    while(!isalpha(ch)) ch = __hv007();
    return ch;
}

#ifndef ONLINE_JUDGE
int const SIZE = 18;
#else
int const SIZE = 1E5+13;
#endif

using llt = long long;

int N, K;
int A[SIZE][32];
llt D[SIZE][32];
bool Flag[SIZE][32];
int M;

llt proc(){
    for(int i=1;i<=N;++i) memset(Flag[i], 0, sizeof(Flag[i]));

    llt ans = 0;
    ans = max(ans, D[1][0] = A[1][0] - K);
    ans = max(ans, D[1][1] = A[1][1]);
    Flag[1][0] = Flag[1][1] = true;
    for(int i=2;i<=N;++i){
        ans = max(ans, D[i][0] = D[i-1][0] + A[i][0] - K);
        Flag[i][0] = true;
        for(int j=1;j<M;++j){
            if(!Flag[i-1][j-1]) break;

            D[i][j] = D[i-1][j-1] + A[i][j];
            Flag[i][j] = true;
            if(Flag[i-1][j]){
                D[i][j] = max(D[i][j], D[i-1][j] + A[i][j] - K);
            }
            ans = max(ans, D[i][j]);
        }
    } 
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
    for(int kase=1;kase<=nofkase;++kase){
        N = getInt(); K = getInt();
        M = 0;
        for(int i=1;i<=N;++i){
            memset(A[i], 0, sizeof(A[i]));
            A[i][0] = getInt();
            for(int j=1;;++j){
                M = max(M, j);
                if(0 == (A[i][j] = A[i][j-1] >> 1)) break;
            }
        }
        printf("%lld\n", proc());
    }
    return 0;
}

