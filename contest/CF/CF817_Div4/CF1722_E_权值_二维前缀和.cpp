/**
 * 给定一系列的矩形，再给定Q个询问，每次问：
 * 宽高落在[hs, hb][ws, wb]范围内的矩形一共有多少个
 * 注意到h和w的取值在1000以内，因此可以求一个前缀和
 * 
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
int const SIZE = 1E3+13;
#else
int const SIZE = 1E3+13;
#endif

using llt = long long;
using pii = pair<int, int>;

int N, Q;
int A[SIZE][SIZE];
llt B[SIZE][SIZE];
int H, W;

void proc(){
    int hs = getInt() + 1;
	int ws = getInt() + 1;
	int hb = getInt() - 1;
	int wb = getInt() - 1;

	llt ans = B[hb][wb];
	ans += B[hs-1][ws-1];
	ans -= B[hb][ws-1];
	ans -= B[hs-1][wb];

	printf("%lld\n", ans);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif    
    int nofkase = getInt();
	while(nofkase--){
		memset(A, 0, sizeof(A));
        N = getInt(); Q = getInt();
		H = W = 0;
		for(int h,w,i=0;i<N;++i){
            h = getInt();
			w = getInt();
			++A[h][w];
		}

		for(int i=1;i<=1000;++i)for(int j=1;j<=1000;++j){
			B[i][j] = B[i-1][j] + B[i][j-1] - B[i-1][j-1] + (llt)i * j * A[i][j];
		}

		while(Q--){
			proc();
		}
	}
    return 0;
}
