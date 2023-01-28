/**
 * 给一个树，对x=1,2,...,N，连通块数量恰好是x的导出子图的数量是多少
 * 很典型的树形DP。设Aij是选i且子树i有j个连通块的方案数，Bij是不选i的方案数
 * 对i的每个儿子v， 原A[i][j] * B[v][k] 对 A[i][j+k]有贡献
 * 原Bi[j] * (Av[k] + Bv[k]) 对Bi[j+k]有贡献
 * 此外， 原Ai[j] * Av[k] 对Ai[j+k-1]有贡献
 * 每次更新一遍A和B，即可迭代计算
 * 严格限制每次计算的循环次数，可以保证整个树形DP是O(N^2)的。
 * 此外，空间上还可以滚动优化掉一维，但无必要。
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
int const SIZE = 3E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;
using vll = vector<llt>;
using vvll = vector<vll>;

llt const MOD = 998244353LL;

int N;
vvi G;

int Root = 1;
vi Size;

/// Aij是用了i、i子树j个连通块的方案数
/// Bij是不用i的方案数
vvll A, B; 


void dfs(int u, int p){
	auto total = Size[u];
    A[u][1] = 1;
	B[u][0] = 1;

	auto & a = A[u];
	auto & b = B[u];

	auto sz = 1;

    for(auto v : G[u]){
		if(v == p) continue;

		auto vs = Size[v];

		vll ta(total + 1, 0LL);
		vll tb(total + 1, 0LL);

		dfs(v, u);

        const auto & va = A[v];
		const auto & vb = B[v];

        for(int i=0;i<=sz;++i){
			for(int j=0;j<=vs;++j){
				/// ai表示选u且有i个连通分量，此时不选v且有j个连通分量就可以构成选u且有i+j个连通分量的方案
				(ta[i + j] += a[i] * vb[j]) %= MOD;
                (tb[i + j] += b[i] * (va[j] + vb[j])) %= MOD;
				/// 还有一种u和v相连的情况，此时只有i + j - 1个连通块
				if(i + j > 0) (ta[i + j - 1] += a[i] * va[j]) %= MOD;
			}
		}
		ta.swap(a);
		tb.swap(b);

		sz += vs;
	}
	return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    G.assign((N = getInt()) + 1, vi());
    for(int a,b,i=1;i<N;++i){
		a = getInt(); b = getInt();
		G[a].push_back(b); G[b].push_back(a);
	}

	Size.assign(N + 1, 0);
    A.assign(N + 1, vll());
	B.assign(N + 1, vll());

	function<void(int, int)> __dfs = [&](int u, int p)->void{
        Size[u] = 1;
		for(auto v : G[u]){
			if(v == p) continue;
			__dfs(v, u);
			Size[u] += Size[v];
		}
		A[u].assign(Size[u] + 1, 0LL);
		B[u].assign(Size[u] + 1, 0LL);
		return;
	};

	__dfs(1, 0);
    dfs(1, 0);

	for(int i=1;i<=N;++i){
		printf("%lld\n", (A[1][i] + B[1][i]) % MOD);
	}
    return 0;
}