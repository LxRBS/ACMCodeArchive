/**
 * 一棵树，有边权
 * 两种操作
 * 1 v x，v点点权增加x
 * 2 v，把v当做根
 * 每次操作后，求SIGMA{wi*sumi}
 * 其中i是根的儿子，wi是根到i的边的边权，sumi是i子树的点权之和
 * 单点修改，子树查询，外加换根操作
 * 但实际上不必真正换根。考虑v是新的根，但当前形态仍然是原来的root
 * 只需要将w[root][v] * (Total - sum[v])考虑进来即可
 * 需要用到子树查询，可以使用树链剖分
 * 由于没有成段修改操作，用树状数组即可。运行比线段树快一点
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
int const SIZE = 37;
#else
int const SIZE = 1E6+1;
#endif

typedef long long llt;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

int N, Q;
vpii G[SIZE];

struct _t{
    int parent;
	int heavy_son;
	int depth;
	int size;
	int top;
	int nid;
	int mdes;
}Node[SIZE] = {0};
int NCnt = 0;
int NewIdx[SIZE];

void dfsHeavyEdge(int u, int parent, int depth){
    Node[u].depth = depth;
	Node[u].parent = parent;
	Node[u].size = 1;
	
	
	int v;
	for(const auto &p: G[u]){
		if((v=p.first) == parent) continue;
		dfsHeavyEdge(v, u, depth+1);
		Node[u].size += Node[v].size;
		if(Node[Node[u].heavy_son].size < Node[v].size) Node[u].heavy_son = v;
	}
}

void dfsHeavyPath(int u, int top){
	Node[u].top = top;
	NewIdx[Node[u].mdes = Node[u].nid = ++NCnt] = u;
	if(0 == Node[u].heavy_son) return;

	dfsHeavyPath(Node[u].heavy_son, top);
	Node[u].mdes = max(Node[u].mdes, Node[Node[u].heavy_son].mdes);

	int v;
	for(const auto &p: G[u]){
		if((v=p.first) == Node[u].parent || v == Node[u].heavy_son) continue;
		dfsHeavyPath(v, v);
		Node[u].mdes = max(Node[u].mdes, Node[v].mdes);
	}	
}

inline int lowbit(int t){return t & -t;}
llt C[SIZE];

llt _qSum(int pos){
	llt ans = 0;
	for(;pos;pos-=lowbit(pos)) ans+=C[pos];
	return ans;
}

inline llt _qSum(int s, int e){return _qSum(e)-_qSum(s-1);}

void _modify(int pos, llt delta){
	for(;pos<=N;pos+=lowbit(pos)) C[pos] += delta;
}

inline void modify(int u, llt delta){
	_modify(Node[u].nid, delta);
}

inline llt query(int u){
	return _qSum(Node[u].nid, Node[u].mdes);
}

int Root;
llt query(){
	llt total = query(1);
    llt ans = 0;
	int parent = Node[Root].parent;
	llt ptmp = 0;
	for(const auto &p: G[Root]){
		int v = p.first;
		llt w = p.second;
        if(v == parent) {ptmp=w;continue;}
		llt tmp = query(v);
		ans += tmp * w;
	}
	if(1 == Root){
		return ans;
	}
	total -= query(Root);
	ans += total * ptmp;
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt();
	for(int a,b,w,i=1;i<N;++i){
        a = getInt(); b = getInt(); w = getInt();
        G[a].emplace_back(b, w);
		G[b].emplace_back(a, w);
	}

    dfsHeavyEdge(Root=1, 0, 0);
	dfsHeavyPath(1, 1);

	Q = getInt();
	for(int cmd,v,x,q=1;q<=Q;++q){
        if(1 == (cmd=getInt())){
            v = getInt(); x = getInt();
            modify(v, x);
		}else if(2 == cmd){
			Root = v = getInt();            
		}else{
			throw runtime_error("wrong cmd");
		}
		printf("%lld\n", query());
	}
    return 0;
}
