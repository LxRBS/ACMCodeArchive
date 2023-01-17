/**
 * 将M个币分给N个人。每个人的得分为分到的币的数量除以当时的总币数
 * 问分配能够得到的最大分是多少。
 * 本题其实没有规律。注意到N、M在500，因此可以用O(N^3)的DP完成。
 * Dij是i个人分j个币的最大值，则
 * Dij = max(D[i-1][j-k] + k/j, for k=0...j)
 */
#include <bits/stdc++.h>
using namespace std;
 
char *__abc147, *__xyz258, __ma369[1000000];
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
int const SIZE = 23;
#else
int const SIZE = 450;
#endif

using Real = long double;
using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using prr = pair<Real, Real>;
using mvi = map<int, vi>;

int N, M;
Real D[510][510];
Real Ans;

Real dfs(int n, int m){
    if(D[n][m] >= 0) return D[n][m];

    auto & ans = D[n][m];
    ans = 0;
    
    for(int i=1;i<=m;++i){
        ans = max(ans, (Real)i/m + dfs(n-1, m-i));
    }
    return ans;
}

Real proc(){
    for(int i=0;i<=N;++i) D[i][0] = 0.0;
    for(int j=0;j<=M;++j) D[0][j] = 0.0;
    for(int i=1;i<=N;++i) D[i][1] = 1.0;
    for(int j=1;j<=M;++j) D[1][j] = 1.0;

    for(int j=2;j<=M;++j){
        for(int i=j;i<=N;++i){
            auto & a = D[i][j];
            a = 0.0;
            for(int k=j;k>=1;--k) a += 1.0 / (Real)k;
        }
    }
    dfs(N, M);
    return D[N][M];
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt(); M = getInt();
    for(int i=0;i<=N;++i)for(int j=0;j<=M;++j) D[i][j] = -1.0;
    printf("%.18Lf\n", proc());
    return 0;
}


