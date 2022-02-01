/**
 * 路径修改，路径查询连续的段数
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

void getString(char *p){
	char ch = __hv007();
	while(!isalpha(ch)) ch = __hv007();

	*p++ = ch;
	while(isalpha(ch = __hv007())) *p++ = ch;
	*p++ = '\0';
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
	// int mdes; // 指示子树的最后一个节点
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
	NewIdx[/*Node[u].mdes = */Node[u].nid = ++NCnt] = u;
	if(0 == Node[u].heavy_son) return;

	dfsHeavyPath(Node[u].heavy_son, top);
	// Node[u].mdes = max(Node[u].mdes, Node[Node[u].heavy_son].mdes);

	for(auto v: G[u]){
		if(v == Node[u].parent || v == Node[u].heavy_son) continue;
		dfsHeavyPath(v, v);
		// Node[u].mdes = max(Node[u].mdes, Node[v].mdes);
	}
}

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}

int St[SIZE<<2];    // 连续的段数
int Front[SIZE<<2]; // 前端颜色
int Back[SIZE<<2];  // 后端颜色
int Lazy[SIZE<<2]; 

inline void _pushUp(int t){
    Front[t] = Front[lson(t)];
	Back[t] = Back[rson(t)];
	St[t] = St[lson(t)] + St[rson(t)] - (Back[lson(t)] == Front[rson(t)] ? 1 : 0);
}

inline void _pushDown(int t){
	int &lazy = Lazy[t];
    if(0 == lazy) return;

	int son = lson(t);
	St[son] = 1;
	Lazy[son] = Front[son] = Back[son] = lazy;

    son = rson(t);
	St[son] = 1;
	Lazy[son] = Front[son] = Back[son] = lazy;

	lazy = 0;
}

void modify(int t, int s, int e, int a, int b, llt newValue){
    if(a<=s && e<=b){
		St[t] = 1;
		Lazy[t] = Front[t] = Back[t] = newValue;
		return;
	}

    _pushDown(t);
	int mid = (s + e) >> 1;
	if(a<=mid) modify(lson(t), s, mid, a, b, newValue);
	if(mid<b) modify(rson(t), mid+1, e, a, b, newValue);
	_pushUp(t);	
}

typedef tuple<int, int, int> t3t;
/// merge时，左右不能弄反
inline t3t merge(const t3t &a, const t3t &b){
	if(-1 == get<0>(a)) return b;
	if(-1 == get<0>(b)) return a;
	return {
		get<0>(a)+get<0>(b)-(get<2>(a)==get<1>(b)?1:0)
		, get<1>(a)
		, get<2>(b)
	};	
}

t3t query(int t, int s, int e, int a, int b){
	if(a<=s && e<=b){
		return {St[t], Front[t], Back[t]};
	}

	_pushDown(t);

	int mid = (s + e) >> 1;
	t3t lans = {-1, -1, -1};
	t3t rans = {-1, -1, -1};
	if(a<=mid) lans = query(lson(t), s, mid, a, b);
	if(mid<b) rans = query(rson(t), mid+1, e, a, b);
	return merge(lans, rans);
}

void build(int t, int s, int e){
	if(s == e){
		St[t] = 1;
		Front[t] = Back[t] = W[NewIdx[s]];
		return;
	}

	int mid = (s + e) >> 1;
	build(lson(t), s, mid);
	build(rson(t), mid+1, e);
	_pushUp(t);
}

void modify(int u, int v, int newValue){
	while(Node[u].top != Node[v].top){
		if(Node[Node[u].top].depth < Node[Node[v].top].depth) swap(u, v);

		modify(1, 1, N, Node[Node[u].top].nid, Node[u].nid, newValue);
		u = Node[Node[u].top].parent;
	}
    if(Node[u].depth > Node[v].depth) swap(u, v);
	modify(1, 1, N, Node[u].nid, Node[v].nid, newValue);
	return;
}

t3t query(int u, int v){
	t3t uans = {-1, -1, -1};
	t3t vans = {-1, -1, -1};
	while(Node[u].top != Node[v].top){
		if(Node[Node[u].top].depth < Node[Node[v].top].depth){
			swap(u, v); swap(uans, vans);
		} 

		uans = merge(query(1, 1, N, Node[Node[u].top].nid, Node[u].nid), uans);	
		u = Node[Node[u].top].parent;	
	}
	if(Node[u].depth > Node[v].depth){
		swap(u, v); swap(uans, vans);
	}
	/// 要保证合并的顺序
	vans = merge(query(1, 1, N, Node[u].nid, Node[v].nid), vans);
	swap(get<1>(uans), get<2>(uans));
	return merge(uans, vans);
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
	
	char cmd[22];
	for(int q=1;q<=M;++q){
        getString(cmd);
		if(*cmd == 'C'){
            int u = getInt();
			int v = getInt();
			int newValue = getInt();
			modify(u, v, newValue);
		}else if(*cmd == 'Q'){
            int u = getInt();
			int v = getInt();
			printf("%d\n", get<0>(query(u, v)));
		}else{
			throw runtime_error("XX");
		}
	}
    return 0;
}
