/**
 * 给定一个无根树，2000个节点，每个节点上有一个字母
 * 对所有路径(u, v)，求其最长的回文子序列的长度
 * 与数组上的最长回文子序列一样，类似一个区间DP
 * D[i][j] = max(D[i+1][j], D[i][j-1], 2 + D[i+1][j-1] if Si==Sj)
 * 在树的路径上则需要分别求出u和v在路径上的邻点，如果u和v分居不同链很容易求
 * 如果u恰好是v的祖先，则v的很容易求，u的不太好求
 * 考虑到整个题目的复杂度，可以用换根的方法来做。
 * 对所有的节点u，以其为根节点跑一遍DFS，求出其他所有节点v的父节点，记作Father[u][v]
 * 则Father[u][v]记录了u、v路径上v的邻点
 * 同理，Father[v][u]记录了u的邻点
 * 再跑一遍递归的DP即可
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
int const SIZE = 2100;
#endif

using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;

int N;
char S[SIZE];
vvi G;
vvi Father;
vvi D;

void dfs(int u, int p, vi & father){
	father[u] = p;
    for(int v : G[u]){
		if(v == p) continue;
		dfs(v, u, father);
	}
}

int dp(int u, int v){
	if(D[u][v] != -1) return D[u][v];

	int fu = Father[v][u];
	int fv = Father[u][v];

	if(fu == v){
		assert(fv == u);
		if(S[u] == S[v]) return D[u][v] = D[v][u] = 2;
		return D[u][v] = D[v][u] = 1;
	}

	int ans = 0;
	if(S[u] == S[v]){
		ans = max(ans, dp(fu, fv) + 2);
	}

	ans = max(ans, dp(fv, u));
	ans = max(ans, dp(fu, v));

    return D[u][v] = D[v][u] = ans;
}

int proc(){
    Father.assign(N+1, vi(N+1, 0));
    for(int i=1;i<=N;++i){
		dfs(i, 0, Father[i]);
	}

    D.assign(N+1, vi(N+1, -1));
    for(int i=1;i<=N;++i) D[i][i] = 1;

    int ans = 0;
	for(int i=1;i<=N;++i)for(int j=1;j<=N;++j){
        ans = max(ans, dp(i, j));
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase; scanf("%d", &nofkase);
	for(int kase=1;kase<=nofkase;++kase){
		// cout << "Case " << kase << ":\n";
        scanf("%d", &N);
		G.assign(N+1, vi());
		scanf("%s", S+1);
		for(int a,b,i=1;i<N;++i){
            scanf("%d%d", &a, &b);
			G[a].push_back(b);
			G[b].push_back(a);
		}
		printf("%d\n", proc());
	}
    return 0;
}