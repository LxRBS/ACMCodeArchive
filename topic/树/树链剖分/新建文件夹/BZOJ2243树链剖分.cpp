//点权，路径更新，路径查询，查询权值的段数，连续相同的权值认为是一段
#include <cstdio>
#include <algorithm>
using namespace std;

int const SIZE = 100010;
typedef int weight_t;

struct edge_t{
    int to;
    int next;
}Edge[SIZE<<1];
int ECnt;
int Vertex[SIZE];
weight_t W[SIZE];

inline void mkEdge(int a,int b){
	Edge[ECnt].to = b;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].to = a;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

struct node_t{
    int parent;
    int heavy_son;
    int depth;
    int size;
    int top;
    int nid;
}Node[SIZE] = {{0,0,0,0,0,0}};
int NCnt;
int NewIdx[SIZE];

void dfsHeavyEdge(int node,int parent,int depth){
    Node[node].depth = depth;
    Node[node].parent = parent;
    Node[node].size = 1;
    Node[node].heavy_son = 0;

    for(int next=Vertex[node];next;next=Edge[next].next){
        int to = Edge[next].to;
        if ( to == parent ) continue;
        dfsHeavyEdge(to,node,depth+1);
        Node[node].size += Node[to].size;

        if ( Node[to].size > Node[Node[node].heavy_son].size ) Node[node].heavy_son = to;
    }
}

void dfsHeavyPath(int node,int top){
    Node[node].top = top;
    Node[node].nid = NCnt++;
    NewIdx[Node[node].nid] = node;

    if ( 0 == Node[node].heavy_son ) return;
    dfsHeavyPath(Node[node].heavy_son,top);

    for(int next=Vertex[node];next;next=Edge[next].next){
        int to = Edge[next].to;
        if ( to != Node[node].parent && to != Node[node].heavy_son ) dfsHeavyPath(to,to);
    }
}

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;};

int St[SIZE<<2];
int L[SIZE<<2],R[SIZE<<2];
int Lazy[SIZE<<2];

inline void _pushUp(int t){
    St[t] = St[lson(t)] + St[rson(t)] - ( R[lson(t)] == L[rson(t)] ? 1 : 0 );
    L[t] = L[lson(t)];
    R[t] = R[rson(t)];
}

inline void _pushDown(int t){
    if ( 0 == Lazy[t] ) return;

    St[lson(t)] = St[rson(t)] = 1;
    L[lson(t)] = R[lson(t)] = L[rson(t)] = R[rson(t)] = Lazy[lson(t)] = Lazy[rson(t)] = Lazy[t];
    Lazy[t] = 0;
}

void build(int t,int s,int e){
    Lazy[t] = 0;
    if ( s == e ){
        St[t] = 1;
        L[t] = R[t] = W[NewIdx[s]];
        return;
    }

    int m = ( s + e ) >> 1;
    build(lson(t),s,m);
    build(rson(t),m+1,e);
    _pushUp(t);
}

void modify(int t,int s,int e,int a,int b,weight_t newValue){
    if ( a <= s && e <= b ){
        St[t] = 1;
        L[t] = R[t] = Lazy[t] = newValue;
        return;
    }

    _pushDown(t);
    int m = ( s + e ) >> 1;
    if ( a <= m ) modify(lson(t),s,m,a,b,newValue);
    if ( m < b ) modify(rson(t),m+1,e,a,b,newValue);
    _pushUp(t);
}

struct _t{
    int ans;
    int left,right;
    _t(int a=0,int b=0,int c=0):ans(a),left(b),right(c){}
};
_t query(int t,int s,int e,int a,int b){
    if ( a <= s && e <= b ) return _t(St[t],L[t],R[t]);

    _pushDown(t);
    int m = ( s + e ) >> 1;
    _t ret;
    _t tmp1,tmp2;
    if ( a <= m ) tmp1 = query(lson(t),s,m,a,b);
    if ( m < b ) tmp2 = query(rson(t),m+1,e,a,b);
    ret.ans = tmp1.ans + tmp2.ans - ( a <= m && m < b && R[lson(t)] == L[rson(t)] ? 1 : 0 );
    ret.left = ( a <= m ) ? tmp1.left : tmp2.left;
    ret.right = ( m < b ) ? tmp2.right : tmp1.right;
    return ret;
}

int N,M;

void change(int x,int y,int newValue){
    while( Node[x].top != Node[y].top ){
        if ( Node[Node[x].top].depth < Node[Node[y].top].depth ) swap(x,y);
        modify(1,1,N,Node[Node[x].top].nid,Node[x].nid,newValue);
        x = Node[Node[x].top].parent;
    }
    if ( Node[x].depth > Node[y].depth ) swap(x,y);
    modify(1,1,N,Node[x].nid,Node[y].nid,newValue);
}

int query(int x,int y){
    int ret = 0;
    _t t,xt,yt;
    while( Node[x].top != Node[y].top ){
        if ( Node[Node[x].top].depth < Node[Node[y].top].depth ) swap(x,y),swap(xt,yt);
        t = query(1,1,N,Node[Node[x].top].nid,Node[x].nid);
        ret += t.ans;
        ret -= t.right == xt.left ? 1 : 0;
        xt = t;
        x = Node[Node[x].top].parent;
    }
    if ( Node[x].depth > Node[y].depth ) swap(x,y),swap(xt,yt);
    t = query(1,1,N,Node[x].nid,Node[y].nid);
    return ret + t.ans - ( xt.left == t.left ? 1 : 0 ) - ( yt.left == t.right ? 1 : 0 );
}

inline void initTree(int n){
    ECnt = NCnt = 1;
    fill(Vertex,Vertex+N+1,0);
}
int getUnsigned(){
	char ch = getchar();
	while( ch > '9' || ch < '0' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}
char getChar(){
	char ch = getchar();
	while( ch < 'A' || ch > 'z' || ( 'Z' < ch && ch < 'a' ) ) ch = getchar();
	return ch;
}
bool read(){
    if ( EOF == scanf("%d",&N) ) return false;
    M = getUnsigned();

    initTree(N);
    for(int i=1;i<=N;++i) W[i] = getUnsigned() + 1;
    int a,b;
    for(int i=1;i<N;++i){
        a = getUnsigned();
        b = getUnsigned();
        mkEdge(a,b);
    }
    dfsHeavyEdge(1,0,0);
    dfsHeavyPath(1,1);
    build(1,1,N);
    return true;
}
void proc(){
    char cmd;
    int a,b,c;
    while( M-- ){
        cmd = getChar();
        a = getUnsigned();
        b = getUnsigned();
        if ( 'C' == cmd ){
            c = getUnsigned() + 1;
            change(a,b,c);
        }else{
            printf("%d\n",query(a,b));
        }
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ) proc();
    return 0;
}

