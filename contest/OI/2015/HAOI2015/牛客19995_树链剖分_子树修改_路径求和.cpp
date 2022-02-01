/**
 * 树链剖分
 * 子树修改，单点修改，查询路径和
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

typedef long long llt;
typedef vector<int> vi;

#ifndef ONLINE_JUDGE
int const SIZE = 11;
#else
int const SIZE = 100110;
#endif

int N, M;
vi G[SIZE];
int W[SIZE];

struct node_t{ // 树链节点
    int parent;
	int heavy_son;
	int depth;
	int size;
	int top;
	int nid;  // 在树链中的新编号
	int mdes; // 指示子树的最后一个节点
}Node[SIZE] = {{0, 0, 0, 0, 0, 0}};
int NCnt = 0;
int NewIdx[SIZE]; // NewIdx[i]表示新编号为i的节点的原编号

/// dfs确定重儿子与深度
void dfsHeavyEdge(int u, int parent, int depth){
    Node[u].depth = depth;
	Node[u].parent = parent;
	Node[u].size = 1;

	for(auto v: G[u]){
		if(v == parent) continue;
		dfsHeavyEdge(v, u, depth+1);
		Node[u].size += Node[v].size;
		if(Node[Node[u].heavy_son].size < Node[v].size) Node[u].heavy_son = v;
	}
}

/// dfs确定重链
void dfsHeavyPath(int u, int top){
	Node[u].top = top;
	NewIdx[Node[u].mdes = Node[u].nid = ++NCnt] = u;
	if(0 == Node[u].heavy_son) return;

	dfsHeavyPath(Node[u].heavy_son, top);
	Node[u].mdes = max(Node[u].mdes, Node[Node[u].heavy_son].mdes);

	for(auto v: G[u]){
		if(v == Node[u].parent || v == Node[u].heavy_son) continue;
		dfsHeavyPath(v, v);
		Node[u].mdes = max(Node[u].mdes, Node[v].mdes);
	}
}

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}

llt St[SIZE<<2];         // 线段树求和
llt Lazy[SIZE<<2] = {0}; // delta延迟

inline void _pushUp(int t){
	St[t] = St[lson(t)] + St[rson(t)];
}

inline void _pushDown(int t, int s, int e){
    llt &lazy = Lazy[t];
    if(0 == lazy) return;

    int mid = (s + e) >> 1;
    int son = lson(t);
	St[son] += lazy * (mid - s + 1);
	Lazy[son] += lazy;

	son = rson(t);
	St[son] += lazy * (e - mid);
	Lazy[son] += lazy;

	lazy = 0;
}

llt qSum(int t, int s, int e, int a, int b){
	if(a<=s && e<=b){
		return St[t];
	}

	int mid = (s + e) >> 1;
	_pushDown(t, s, e);
	llt ans = 0;
	if(a<=mid) ans += qSum(lson(t), s, mid, a, b);
	if(mid<b) ans += qSum(rson(t), mid+1, e, a, b);
	return ans;
}

void modify(int t, int s, int e, int a, int b, llt delta){
    if(a<=s && e<=b){
		St[t] += delta * (e - s + 1);
		Lazy[t] += delta;
		return;
	}

	int mid = (s + e) >> 1;
	_pushDown(t, s, e);
	if(a<=mid) modify(lson(t), s, mid, a, b, delta);
	if(mid<b) modify(rson(t), mid+1, e, a, b, delta);
	_pushUp(t);	
}

void build(int t, int s, int e){
	if(s == e){
		St[t] = W[NewIdx[s]];
		return;
	}

	int mid = (s + e) >> 1;
	build(lson(t), s, mid);
	build(rson(t), mid+1, e);
	_pushUp(t);
}

void modify(int u, llt delta){
	modify(1, 1, N, Node[u].nid, Node[u].nid, delta);
}

void modifySubTree(int u, llt delta){
    modify(1, 1, N, Node[u].nid, Node[u].mdes, delta);
}

llt query(int u, int v){
	llt ret = 0;
    while(Node[u].top != Node[v].top){
        if(Node[Node[u].top].depth < Node[Node[v].top].depth) swap(u, v);

		ret += qSum(1, 1, N, Node[Node[u].top].nid, Node[u].nid);
		u = Node[Node[u].top].parent;
	}
	if(Node[u].depth  > Node[v].depth) swap(u, v);
	ret += qSum(1, 1, N, Node[u].nid, Node[v].nid);
	return ret;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt(); M = getInt();
	for(int i=1;i<=N;++i)W[i] = getInt();
	for(int a,b,i=1;i<N;++i){
		a = getInt();
		b = getInt();
		G[a].push_back(b);
		G[b].push_back(a);
	}
	dfsHeavyEdge(1, 1, 0);
	dfsHeavyPath(1, 1);
	build(1, 1, N);
	for(int cmd,q=1;q<=M;++q){
        cmd = getInt();
		switch(cmd){
			case 1:{
				int x = getInt();
				llt a = getInt();
				modify(x, a);
			}break;
			case 2:{
				int x = getInt();
				llt a = getInt();
				modifySubTree(x, a);
			}break;
			case 3:{
				int x = getInt();
				printf("%lld\n", query(1, x));
			}break;
			default: throw runtime_error("XX");
		}
	}
    return 0;
}
