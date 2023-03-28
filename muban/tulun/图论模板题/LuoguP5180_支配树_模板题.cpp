#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_cxx;
using namespace __gnu_pbds;


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
int const SIZE = 21;
#else
int const SIZE = 2E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using ull = unsigned long long;
// using i128 = __int128_t;
using Real = long double;

Real const EPS = 1E-14;
inline int sgn(Real x) {return x > EPS ? 1 : (x < -EPS ? -1 : 0);}
inline bool is0(Real x) {return 0 == sgn(x);}


struct DominatorTree_Lengauer_Tarjan{

using vi = vector<int>;
using vvi = vector<vi>;

vvi g; // 1-indexed
vvi ig;

void init(int n){
    g.assign(n + 1, vi());
	ig.assign(n + 1, vi());
}

void mkEdge(int a, int b){
	g[a].push_back(b);
	ig[b].push_back(a);
}



int S;
vi Dfn; // Dfn[i]表示节点i的dfs序
vi Ord; // Ord[i]表示排名第i位的节点
vi Parent; // Parent[i]表示深搜树上i节点的父节点
int Stamp; 

vi uni, mn;
vi Sdom; // Sdom[i]表示i的半支配点
vi Idom; // Idom[i]表示i的直接支配点

vvi SdomTree;

void Lengauer_Tarjan(int s){
	int n = this->g.size() - 1;

    /// 确定dfs序
	Dfn.assign(this->g.size(), Stamp = 0);
	Ord.assign(this->g.size(), 0);
	Parent.assign(this->g.size(), 0);
	dfs(S = s);

	/// 求解半支配点与支配点的中间答案
	Sdom.assign(this->g.size(), 0);
	uni.assign(this->g.size(), 0);
	mn.assign(this->g.size(), 0);
	SdomTree.assign(this->g.size(), vi());
	Idom.assign(this->g.size(), 0);
	calcSdom();

    /// 最后确定支配点
	for(int i=2;i<=n;++i){
		int u = Ord[i];
		if(Idom[u] ^ Sdom[u]){
			Idom[u] = Idom[Idom[u]];
		}
	}
	return;
}

void dfs(int u){
	Ord[Dfn[u] = ++Stamp] = u;
	for(auto v : g[u]){
		if(0 == Dfn[v]){
			Parent[v] = u;
			dfs(v);
		}		
	}
	return;
}

void calcSdom(){
	int n = this->g.size() - 1;
	for(int i=1;i<=n;++i) Sdom[i] = mn[i] = uni[i] = i;
	for(int i=n;i>=2;--i){
		int u = Ord[i]; // 排名第i位的节点是u
		for(int v : ig[u]){
			if(0 == Dfn[v]) continue;
			uni_query(v);
			if(Dfn[Sdom[mn[v]]] < Dfn[Sdom[u]]){
				Sdom[u] = Sdom[mn[v]];
			} 
		}
		uni[u] = Parent[u];
		SdomTree[Sdom[u]].push_back(u);
		for(int v : SdomTree[u = Parent[u]]){
			uni_query(v);
			Idom[v] = (u == Sdom[mn[v]]) ? u : mn[v]; 
		}
		SdomTree[u].clear();
	}
	return;
}

int uni_query(int u){
	if(u == uni[u]) return u;
	int ans = uni_query(uni[u]);
	if(Dfn[Sdom[mn[uni[u]]]] < Dfn[Sdom[mn[u]]]) mn[u] = mn[uni[u]];
	return uni[u] = ans;
}

};

int N, M;
DominatorTree_Lengauer_Tarjan D;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    N = getInt(); M = getInt();
	D.init(N);
	for(int a,b,i=0;i<M;++i){
        a = getInt(); b = getInt();
		D.mkEdge(a, b);
	}
	D.Lengauer_Tarjan(1);
    vi ans(N+1, 0);
	for(int i=N;i>=2;--i) ans[D.Idom[D.Ord[i]]] += ++ans[D.Ord[i]];
	++ans[1];
	for(int i=1;i<=N;++i) printf("%d ", ans[i]); printf("\n");
    return 0; 
}

