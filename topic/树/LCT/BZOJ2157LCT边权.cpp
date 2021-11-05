//边权，支持单点更新、路径查询、成段取反
//查询最小值、最大值及求和
#include <cstdio>
#include <climits>
#include <cstring>
#include <algorithm>
using namespace std;

typedef int value_t;

int const SIZE = 20100;
int const LEFT = 0;
int const RIGHT = 1;

struct edge_t{
    int to;
    value_t w;
    int next;
    int idx;
}Edge[SIZE<<1];
int ECnt;
int Vertex[SIZE];
int E2V[SIZE];

inline void mkEdge(int a,int b,value_t w,int idx){
    Edge[ECnt].to = b;
    Edge[ECnt].w = w;
    Edge[ECnt].idx = idx;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt++;

    Edge[ECnt].to = a;
    Edge[ECnt].w = w;
    Edge[ECnt].idx = idx;
    Edge[ECnt].next = Vertex[b];
    Vertex[b] = ECnt++;
}

struct node_t{
    int parent;//Splay的父节点或者原树上的path_parent
    int son[2];
    //int size;
    value_t value;
    value_t peak;
    value_t valley;
    value_t sum;
    //bool flip;
    bool opp;//取相反数的lazy标记
}Node[SIZE];
int NCnt;

inline void _pushUp(int t){
    //*
    //Node[t].size = 1;
    Node[t].sum = Node[t].valley = Node[t].peak = Node[t].value;

    int son = Node[t].son[LEFT];
    if ( son ){
        //Node[t].size += Node[son].size;
        Node[t].sum += Node[son].sum;
        if ( Node[t].peak < Node[son].peak ) Node[t].peak = Node[son].peak;
        if ( Node[t].valley > Node[son].valley ) Node[t].valley = Node[son].valley;
    }

    son = Node[t].son[RIGHT];
    if ( son ){
        //Node[t].size += Node[son].size;
        Node[t].sum += Node[son].sum;
        if ( Node[t].peak < Node[son].peak ) Node[t].peak = Node[son].peak;
        if ( Node[t].valley > Node[son].valley ) Node[t].valley = Node[son].valley;
    }
    //*/
}

inline void _pushDown(int t){
    /*
    if ( Node[t].flip ){
        Node[t].flip = false;
        swap(Node[t].son[LEFT],Node[t].son[RIGHT]);

        int son = Node[t].son[LEFT];
        if ( son ) Node[son].flip ^= 1;
        son = Node[t].son[RIGHT];
        if ( son ) Node[son].flip ^= 1;
    }
    //*/
    if ( Node[t].opp ){
        Node[t].opp = false;

        int son = Node[t].son[LEFT];
        if ( son ){
            Node[son].sum = - Node[son].sum;
            value_t tmp = Node[son].valley;
            Node[son].valley = - Node[son].peak;
            Node[son].peak = - tmp;
            Node[son].opp ^= 1;
            Node[son].value = - Node[son].value;
        }

        son = Node[t].son[RIGHT];
        if ( son ){
            Node[son].sum = - Node[son].sum;
            value_t tmp = Node[son].valley;
            Node[son].valley = - Node[son].peak;
            Node[son].peak = - tmp;
            Node[son].opp ^= 1;
            Node[son].value = - Node[son].value;
        }
    }
}

//判断t节点是否为本splay的根
inline bool _isRoot(int t){
    int parent = Node[t].parent;
    return Node[parent].son[LEFT] != t && Node[parent].son[RIGHT] != t;
}

//计算t的排行, t must not be the root
inline int _getSN(int t){
    int parent = Node[t].parent;
    return Node[parent].son[RIGHT] == t;
}

inline void _link(int p,int sn,int t){
    Node[p].son[sn] = t;
    Node[t].parent = p;
}

//t must not be the root
inline void _rotate(int t){
    int p = Node[t].parent;
    int g = Node[p].parent;
    int sn = _getSN(t);
    int osn = sn ^ 1;

    _link(p,sn,Node[t].son[osn]);
    Node[t].parent = g;
    if ( !_isRoot(p) ) Node[g].son[_getSN(p)] = t;
    _link(t,osn,p);

    _pushUp(p);
}

//将t到根的延迟标记逐级下放
int _maintain(int t){
    int root = t;
    if ( !_isRoot(t) ) root = _maintain(Node[t].parent);
    _pushDown(t);
    return root;
}

void _splay(int t){
    _maintain(t);
    while( !_isRoot(t) ){
        int p = Node[t].parent;
        if ( !_isRoot(p) ) _getSN(t) == _getSN(t) ? _rotate(p) : _rotate(t);
        _rotate(t);
    }
    _pushUp(t);
}

//LCT的关键操作
int _access(int x){
    int t = 0;
    for(;x;x=Node[t=x].parent){
        _splay(x);
        Node[x].son[RIGHT] = t;//这里不能使用_link
        _pushUp(x);
    }
    return t;
}

//x和y的最近公共祖先
inline int lca(int x,int y){
    _access(x);
    return _access(y);
}

//获取x所在树的根节点
int _getRoot(int x){
    _access(x);
    _splay(x);
    while( Node[x].son[LEFT] ) x = Node[x].son[LEFT];
    return x;
}

inline bool isConnect(int x,int y){
    return _getRoot(x) == _getRoot(y);
}

//单点更新
inline void change(int x,value_t newValue){
    _access(x);
    _splay(x);
    Node[x].value = newValue;
    _pushUp(x);
}
//路径取反
inline void modify(int x,int y){
    int g = lca(x,y);
    _access(x);
    _splay(g);
    int son = Node[g].son[RIGHT];
    if ( son ){
        Node[son].sum = - Node[son].sum;
        int tmp = Node[son].peak;
        Node[son].peak = - Node[son].valley;
        Node[son].valley = - tmp;
        Node[son].opp ^= 1;
        Node[son].value = - Node[son].value;
    }

    _access(y);
    _splay(g);
    son = Node[g].son[RIGHT];
    if ( son ){
        Node[son].sum = - Node[son].sum;
        int tmp = Node[son].peak;
        Node[son].peak = - Node[son].valley;
        Node[son].valley = - tmp;
        Node[son].opp ^= 1;
        Node[son].value = - Node[son].value;
    }
}

//路径查询和
inline value_t qSum(int x,int y){
    value_t ret = 0;
    int g = lca(x,y);

    _access(x);
    _splay(g);
    int son = Node[g].son[RIGHT];
    if ( son ) ret += Node[son].sum;

    _access(y);
    _splay(g);
    son = Node[g].son[RIGHT];
    if ( son ) ret += Node[son].sum;

    return ret;
}
//路径查询最大值
inline value_t qMax(int x,int y){
    value_t ret = INT_MIN;
    int g = lca(x,y);

    _access(x);
    _splay(g);
    int son = Node[g].son[RIGHT];
    if ( son ) ret = max(ret,Node[son].peak);

    _access(y);
    _splay(g);
    son = Node[g].son[RIGHT];
    if ( son ) ret = max(ret,Node[son].peak);

    return ret;
}
//路径查询最小值
inline value_t qMin(int x,int y){
    value_t ret = INT_MAX;
    int g = lca(x,y);

    _access(x);
    _splay(g);
    int son = Node[g].son[RIGHT];
    if ( son ) ret = min(ret,Node[son].valley);

    _access(y);
    _splay(g);
    son = Node[g].son[RIGHT];
    if ( son ) ret = min(ret,Node[son].valley);

    return ret;
}
void initTree(int n){
    ECnt = 1;
    fill(Vertex,Vertex+n+1,0);
    memset(Node,0,(n+1)*sizeof(node_t));
}

int N,Q;
int getUnsigned(){
	char ch = getchar();
	while( ch > '9' || ch < '0' ) ch = getchar();

	int ret = 0;
	do ret = ret * 10 + (int)(ch-'0');while( '0' <= (ch=getchar()) && ch <= '9' );
	return ret;
}
bool getUnsigned(int&x){
    char ch = getchar();
    while( ( ch > '9' || ch < '0' ) && ch != EOF ) ch = getchar();

    if ( EOF == ch ) return false;

    x = 0;
    do{
        x = x * 10 + (int)(ch-'0');
    }while( '0' <= ( ch = getchar() ) && ch <= '9' );

    return true;
}
int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ( ch > '9' || ch < '0' ) && ch != '-' ) ch = getchar();
	if ( '-' == ch ){
		sgn = -1;
		do ch = getchar(); while(ch>'9'||ch<'0');
	}

	int ret = 0;
	do ret = ret * 10 + (int)(ch-'0');while('0'<=(ch=getchar())&&ch<='9');
	return ret * sgn;
}
void dfs(int node,int parent){
    for(int next=Vertex[node];next;next=Edge[next].next){
        int to = Edge[next].to;
        if ( to == parent ) continue;
        Node[to].value = Node[to].peak = Node[to].sum = Node[to].valley = Edge[next].w;
        Node[to].parent = node;//相当于设置path_parent
        E2V[Edge[next].idx] = to;
        dfs(to,node);
    }
}

bool read(){
    if ( !getUnsigned(N) ) return false;
    initTree(N);

    int a,b;
    value_t w;
    for(int i=1;i<N;++i){
        a = getUnsigned();
        b = getUnsigned();
        w = getInt();
        mkEdge(++a,++b,w,i);
    }
    dfs(1,0);
    return true;
}
char Cmd[10];
void proc(){
    Q = getUnsigned();
    int a,b;
    while(Q--){
        scanf("%s",Cmd);
        a = getUnsigned();
        b = getInt();
        switch(*Cmd){
        case 'S':printf("%d\n",qSum(++a,++b));break;
        case 'M':printf("%d\n",'A'==Cmd[1]?qMax(++a,++b):qMin(++a,++b));break;
        case 'N':modify(++a,++b);break;
        case 'C':change(E2V[a],b);break;
        }
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ) proc();
    return 0;
}
