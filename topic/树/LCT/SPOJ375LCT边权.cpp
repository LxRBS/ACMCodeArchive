//֧�ֻ�����֧��link��cut�����ⲻ����Щ����
//��Ȩ��֧�ֵ�����º�·����ѯ
#include <cstdio>
#include <climits>
#include <cstring>
#include <algorithm>
using namespace std;

typedef int value_t;

int const SIZE = 10100;
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
    int parent;//Splay�ĸ��ڵ����ԭ���ϵ�path_parent
    int son[2];
    //int size;
    value_t value;
    value_t peak;
    //value_t lazy;
    bool flip;
}Node[SIZE];
int NCnt;

inline void _pushUp(int t){
    //*
    //Node[t].size = 1;
    Node[t].peak = Node[t].value;

    int son = Node[t].son[LEFT];
    if ( son ){
        //Node[t].size += Node[son].size;
        if ( Node[t].peak < Node[son].peak ) Node[t].peak = Node[son].peak;
    }

    son = Node[t].son[RIGHT];
    if ( son ){
        //Node[t].size += Node[son].size;
        if ( Node[t].peak < Node[son].peak ) Node[t].peak = Node[son].peak;
    }
    //*/
}

inline void _pushDown(int t){
    if ( Node[t].flip ){
        Node[t].flip = false;
        swap(Node[t].son[LEFT],Node[t].son[RIGHT]);

        int son = Node[t].son[LEFT];
        if ( son ) Node[son].flip ^= 1;
        son = Node[t].son[RIGHT];
        if ( son ) Node[son].flip ^= 1;
    }
}

//�ж�t�ڵ��Ƿ�Ϊ��splay�ĸ�
inline bool _isRoot(int t){
    int parent = Node[t].parent;
    return Node[parent].son[LEFT] != t && Node[parent].son[RIGHT] != t;
}

//����t������, t must not be the root
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

//��t�������ӳٱ�����·�
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

//LCT�Ĺؼ�����
int _access(int x){
    int t = 0;
    for(;x;x=Node[t=x].parent){
        _splay(x);
        Node[x].son[RIGHT] = t;//���ﲻ��ʹ��_link
        _pushUp(x);
    }
    return t;
}

//��x��Ϊԭ���ĸ�
inline void _makeRoot(int x){
    _access(x);
    _splay(x);
    Node[x].flip ^= 1;
}
//��child��parent���ӽڵ�
inline void link(int parent,int child){
    _makeRoot(child);
    Node[child].parent = parent;//���ﲻ��ʹ����չ����_link
}
//��child��parent��������
inline void cut(int parent,int child){
    _makeRoot(parent);
    _access(child);
    _splay(child);
    Node[child].son[LEFT] = Node[Node[child].son[LEFT]].parent = 0;
    _pushUp(child);
}
//��root������������£�x��y�������������
inline int lca(int root,int x,int y){
    _makeRoot(root);
    _access(x);
    return _access(y);
}

//��ȡx�������ĸ��ڵ�
int _getRoot(int x){
    _access(x);
    _splay(x);
    while( Node[x].son[LEFT] ) x = Node[x].son[LEFT];
    return x;
}

inline bool isConnect(int x,int y){
    return _getRoot(x) == _getRoot(y);
}

//��������·����ѯ
inline value_t query(int x,int y){
    int g = lca(1,x,y);
    _access(x);
    _splay(g);

    int son = Node[g].son[RIGHT];
    value_t ret = son ? Node[son].peak : INT_MIN;

    _access(y);
    _splay(g);
    son = Node[g].son[RIGHT];
    return max(ret,son?Node[son].peak:INT_MIN);
}
//�������
inline void modify(int x,value_t newValue){
    _access(x);
    _splay(x);
    Node[x].value = newValue;
    _pushUp(x);
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

void dfs(int node,int parent){
    for(int next=Vertex[node];next;next=Edge[next].next){
        int to = Edge[next].to;
        if ( to == parent ) continue;
        Node[to].value = Node[to].peak = Edge[next].w;
        Node[to].parent = node;//�൱������path_parent
        E2V[Edge[next].idx] = to;
        dfs(to,node);
    }
}

bool read(){
    N = getUnsigned();
    initTree(N);

    int a,b;
    value_t w;
    for(int i=1;i<N;++i){
        a = getUnsigned();
        b = getUnsigned();
        w = getUnsigned();
        mkEdge(a,b,w,i);
    }
    dfs(1,0);
    return true;
}
char Cmd[10];
void proc(){
    int a,b;
    while(1){
        scanf("%s",Cmd);
        if ( 'D' == *Cmd ) return;

        a = getUnsigned();
        b = getUnsigned();
        if ( 'Q' == *Cmd ){
            printf("%d\n",query(a,b));
        }else{
            modify(E2V[a],b);
        }
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    int kase = 0;
    while(nofkase--){
        if ( kase ) printf("\n");
        else kase = 1;

        read();
        proc();
    }
    return 0;
}
