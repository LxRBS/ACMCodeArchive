/**
 * 一棵树，有边权
 * 两种操作
 * 1 v x，v点点权增加x
 * 2 v，把v当做根
 * 每次操作后，求SIGMA{wi*sumi}
 * 其中i是根的儿子，wi是根到i的边的边权，sumi是i子树的点权之和
 * 单点修改，子树查询，外加换根操作，可以用LCT
 * 其实没有必要
 * 最开始使用了unorderedmap和map来保存图，导致MLE
 * 还是要用vector
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

int const LEFT = 0;
int const RIGHT = 1;

struct _t{
	int parent;
	int son[2];
	int size;
	int total_size;
	int i_size;
	llt value;
    llt sum;
	// llt lazy;
	llt total_sum;
	llt i_sum;
	bool flip;	
}Node[SIZE];
int toUsed = 0;

inline int _newNode(llt v=0){
	memset(Node+(++toUsed), 0, sizeof(_t));
	Node[toUsed].value = v;
	return toUsed;
}

inline void _pushUp(int t){
	Node[t].size = 1;
	Node[t].sum = Node[t].value;
	Node[t].total_size = 1 + Node[t].i_size;
	Node[t].total_sum = Node[t].value + Node[t].i_sum;
	
	int son = Node[t].son[LEFT];
	if(son){
		Node[t].size += Node[son].size;
		Node[t].sum += Node[son].sum;
		Node[t].total_size += Node[son].total_size;
		Node[t].total_sum += Node[son].total_sum;
	}

	son = Node[t].son[RIGHT];
	if(son){
		Node[t].size += Node[son].size;
		Node[t].sum += Node[son].sum;
		Node[t].total_size += Node[son].total_size;
		Node[t].total_sum += Node[son].total_sum;
	}
}

inline void _pushDown(int t){
	if(0 == t) return;

	if(Node[t].flip){
		swap(Node[t].son[LEFT], Node[t].son[RIGHT]);
        int son = Node[t].son[LEFT];
		if(son) Node[son].flip ^= 1;
		son = Node[t].son[RIGHT];
		if(son) Node[son].flip ^= 1;
		Node[t].flip ^= 1;        
	}

	// if(Node[t].lazy){
	// 	llt &lazy = Node[t].lazy;
    //     int son = Node[t].son[LEFT];
	// 	if(son){
	// 		Node[son].value += lazy;
	// 		Node[son].lazy += lazy;
	// 		llt tmp = lazy * Node[son].size;
	// 		Node[son].sum += tmp;
	// 		Node[son].total_sum += tmp;
	// 	}
	// 	son = Node[t].son[RIGHT];
	// 	if(son){
	// 		Node[son].value += lazy;
	// 		Node[son].lazy += lazy;
	// 		llt tmp = lazy * Node[son].size;
	// 		Node[son].sum += tmp;
	// 		Node[son].total_sum += tmp;
	// 	}
	// 	lazy = 0;
	// }
}

inline bool _isRoot(int t){
	int p = Node[t].parent;
	if(0 == p) return true;
	if(Node[p].son[LEFT] != t && Node[p].son[RIGHT] != t) return true;
	return false;
}

inline int _getSN(int t){
	if(Node[Node[t].parent].son[LEFT] == t) return LEFT;
	return RIGHT;
}

inline void _link(int p, int sn, int t){
	Node[Node[t].parent = p].son[sn] = t;
}

inline void _rotate(int t){
	int p = Node[t].parent;
	int g = Node[p].parent;
	int sn = _getSN(t);
	int osn = sn ^ 1;

	_link(p, sn, Node[t].son[osn]);
	Node[t].parent = g;
	if(!_isRoot(p)){
		Node[g].son[_getSN(p)] = t;
	}
	_link(t, osn, p);
	_pushUp(p);
}

void _maintain(int t){
	if(!_isRoot(t)){
		_maintain(Node[t].parent);
	}
	_pushDown(t);
}

void _splay(int t){
	_maintain(t);
	while(!_isRoot(t)){
		int p = Node[t].parent;
		if(!_isRoot(p)) _getSN(t) == _getSN(p) ? _rotate(p) : _rotate(t);
		_rotate(t);
	}
	_pushUp(t);
}

inline void _mi(int x, int t){
	int son = Node[x].son[RIGHT];
	Node[x].i_size += Node[son].total_size - Node[t].total_size;
	Node[x].i_sum += Node[son].total_sum - Node[t].total_sum;
}

int _access(int x){
	int t = 0;
	for(;x;x=Node[t=x].parent){
		_splay(x);
		_mi(x, t);
		Node[x].son[RIGHT] = t;
		_pushUp(x);
	}
	return t;
}

inline void _makeRoot(int x){
	_access(x);
	_splay(x);
	Node[x].flip ^= 1;
}

int _getRoot(int x){
    _access(x);
    _splay(x);
    while( Node[x].son[LEFT] ) x = Node[x].son[LEFT];
    _splay(x);
    return x;
}

inline void link(int parent, int child){
	_makeRoot(child);
	Node[child].parent = parent;
	_access(parent);
	_splay(parent);
	Node[parent].i_size += Node[child].total_size;
	Node[parent].i_sum += Node[child].total_sum;
	_pushUp(parent);
}

llt query(int root, int u){
	_makeRoot(root);
	_access(u);
	_splay(u);
	return Node[u].value + Node[u].i_sum;
}

int size(int root, int u){
	_makeRoot(root);
	_access(u);
	_splay(u);
	return 1 + Node[u].i_size;
}

void modify(int x, llt delta){
	_makeRoot(x);
	_access(x);
	_splay(x);

	Node[x].value += delta;
	// Node[x].lazy += delta;
	llt tmp = Node[x].size * delta;
	Node[x].sum += tmp;
	Node[x].total_sum += tmp;
}

typedef pair<int, int> pii;
typedef vector<pii> vpii;

int N, Q;
vpii G[SIZE];

int Root;
llt query(){
    llt ans = 0;
	for(const auto &p: G[Root]){
		llt sz = query(Root, p.first);
		ans += p.second * sz;
	}
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt();
	for(int i=1;i<=N;++i){
		_pushUp(_newNode(0));
	}
	for(int a,b,w,i=1;i<N;++i){
        a = getInt(); b = getInt(); w = getInt();
        G[a].emplace_back(b, w);
		G[b].emplace_back(a, w);
		link(a, b);
	}
	_makeRoot(Root = 1);
	Q = getInt();
	for(int cmd,v,x,q=1;q<=Q;++q){
        if(1 == (cmd=getInt())){
            v = getInt(); x = getInt();
            modify(v, x);
		}else if(2 == cmd){
			v = getInt();
            _makeRoot(Root = v);
		}else{
			throw runtime_error("wrong cmd");
		}
		printf("%lld\n", query());
	}
    return 0;
}
