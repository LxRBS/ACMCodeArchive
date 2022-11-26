/**
 * 给定一个01方阵，要将其改成任意90度旋转不变，最少要修改多少个元素
 * 4个元素为一组，挨个检查即可。
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
int const SIZE = 114;
#endif

int N;
char A[SIZE][SIZE];

int proc(){
    int in = (N + 1) / 2;
    int jn = N / 2;
    int ans = 0;
    for(int i=0;i<in;++i)for(int j=0;j<jn;++j){
        int c[2] = {0};
        ++c[A[i][j] - '0'];
        ++c[A[j][N-1-i] - '0'];
        ++c[A[N-1-i][N-1-j] - '0'];
        ++c[A[N-1-j][i] - '0'];
        ans += min(c[0], c[1]);
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    cin.sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int nofkase; cin >> nofkase;
    for(int kase=1;kase<=nofkase;++kase){
        cin >> N;
        for(int i=0;i<N;++i) cin >> A[i];
        printf("%d\n", proc());
    }
    return 0;
}

