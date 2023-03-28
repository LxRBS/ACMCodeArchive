namespace TULUN{

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


}