/**
 * 给定一个点权树，问子树i的第k大值，k规模为20
 * 对每个子树，求出第1到第20大的值
 * 一遍DFS即可。树型DP
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
int const SIZE = 100010;
#endif

typedef vector<int> vi;

int N, Q;
int W[SIZE];
vi G[SIZE];
vi D[SIZE];

void dfs(int u, int p){
	vi &vec = D[u];
	for(int v: G[u]){
		if(v == p) continue;
		dfs(v, u);
		vi tmp(vec.size()+D[v].size(), 0);
		merge(vec.begin(), vec.end(), D[v].begin(), D[v].end(), tmp.begin(), greater<int>());
		vec.assign(tmp.begin(), tmp.begin()+min(20, (int)tmp.size()));
	}
    auto it = lower_bound(vec.begin(), vec.end(), W[u], greater<int>());
    vec.insert(it, W[u]);
	if(vec.size() > 20) vec.erase(--vec.end());
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt(); Q = getInt();
	for(int i=1;i<=N;++i) W[i] = getInt();
	for(int a,b,i=1;i<N;++i){
		a = getInt(); b = getInt();
        G[a].push_back(b); G[b].push_back(a);
	}
	dfs(1, 0);
	for(int u,k,q=1;q<=Q;++q){
        u = getInt(); k = getInt() - 1;
		printf("%d\n", D[u][k]);
	}
    return 0;
}