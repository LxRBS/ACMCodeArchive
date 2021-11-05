//点权，单点更新，子树更新，查询根到指定节点的权值和

#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;

int const SIZE = 100100;
typedef long long weight_t;

struct edge_t{
    int to;
    int next;
}Edge[SIZE<<1];
int Vertex[SIZE];
int ECnt;
weight_t W[SIZE];

inline void mkEdge(int a,int b){
    Edge[ECnt].to = b;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt++;

    Edge[ECnt].to = a;
    Edge[ECnt].next = Vertex[b];
    Vertex[b] = ECnt++;
}

struct node_t{
    int parent;
    int heavy_son;
    int depth;
    int size;
    int top;
    int nid;
    int mdes;//means the maximum index of all descendants
}Node[SIZE] = {{0,0,0,0,0,0}};
int NCnt;
int NewIdx[SIZE];

void dfsHeavyEdge(int node,int parent,int depth){
    Node[node].depth = depth;
    Node[node].parent = parent;
    Node[node].size = 1;

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
    Node[node].mdes = Node[node].nid = NCnt++;
    NewIdx[Node[node].nid] = node;

    if ( 0 == Node[node].heavy_son ) return;
    dfsHeavyPath(Node[node].heavy_son,top);
    Node[node].mdes = max(Node[node].mdes,Node[Node[node].heavy_son].mdes);

    for(int next=Vertex[node];next;next=Edge[next].next){
        int to = Edge[next].to;
        if ( to != Node[node].parent && to != Node[node].heavy_son ){
            dfsHeavyPath(to,to);
            Node[node].mdes = max(Node[node].mdes,Node[to].mdes);
        }
    }
}

int N;
weight_t StSum[SIZE<<2];
weight_t Lazy[SIZE<<2];

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}

inline void _pushUp(int t){
    StSum[t] = StSum[lson(t)] + StSum[rson(t)];
}

inline void _pushDown(int t,int s,int e){
    if ( 0LL == Lazy[t] ) return;

    weight_t& x = Lazy[t];

    int m = ( s + e ) >> 1;
    int son = lson(t);
    StSum[son] += x * ( m - s + 1 );
    Lazy[son] += x;

    son = rson(t);
    StSum[son] += x * ( e - m );
    Lazy[son] += x;

    x = 0LL;
}

void build(int t,int s,int e){
    if ( s == e ){
        StSum[t] = W[NewIdx[s]];
        Lazy[t] = 0LL;
        return;
    }

    int m = ( s + e ) >> 1;
    build(lson(t),s,m);
    build(rson(t),m+1,e);
    _pushUp(t);
}

void modify(int t,int s,int e,int a,int b,weight_t delta){
    if ( a <= s && e <= b ){
        StSum[t] += delta * ( e - s + 1 );
        Lazy[t] += delta;
        return;
    }

    _pushDown(t,s,e);
    int m = ( s + e ) >> 1;
    if ( a <= m ) modify(lson(t),s,m,a,b,delta);
    if ( m < b ) modify(rson(t),m+1,e,a,b,delta);
    _pushUp(t);
}

weight_t query(int t,int s,int e,int a,int b){
    if ( a <= s && e <= b ){
        return StSum[t];
    }

    _pushDown(t,s,e);

    weight_t ret = 0LL;
    int m = ( s + e ) >> 1;
    if ( a <= m ) ret += query(lson(t),s,m,a,b);
    if ( m < b ) ret += query(rson(t),m+1,e,a,b);
    return ret;
}

inline void initTree(int n){
    ECnt = NCnt = 1;
    fill(Vertex,Vertex+n+1,0);
    for(int i=1;i<=n;++i) Node[i].heavy_son = 0;
}

inline void modify(int x,weight_t delta){
    modify(1,1,N,Node[x].nid,Node[x].nid,delta);
}

inline void modifySubtree(int x,weight_t delta){
    modify(1,1,N,Node[x].nid,Node[x].mdes,delta);
}

weight_t query(int x,int y){
    weight_t ret = 0LL;
    while( Node[x].top != Node[y].top ){
        if ( Node[Node[x].top].depth < Node[Node[y].top].depth ) swap(x,y);

        ret += query(1,1,N,Node[Node[x].top].nid,Node[x].nid);
        x = Node[Node[x].top].parent;
    }

    if ( Node[x].depth > Node[y].depth ) swap(x,y);
    ret += query(1,1,N,Node[x].nid,Node[y].nid);
    return ret;
}

int M;
bool read(){
    if ( EOF == scanf("%d%d",&N,&M) ) return false;

    initTree(N);
    for(int i=1;i<=N;++i)scanf("%lld",W+i);

    int a,b;
    for(int i=1;i<N;++i){
        scanf("%d%d",&a,&b);
        mkEdge(a,b);
    }

    dfsHeavyEdge(1,0,0);
    dfsHeavyPath(1,1);
    build(1,1,N);
    return true;
}

void proc(){
    int cmd,x;
    weight_t a;
    while(M--){
        scanf("%d%d",&cmd,&x);
        switch(cmd){
        case 1:scanf("%lld",&a);modify(x,a);break;
        case 2:scanf("%lld",&a);modifySubtree(x,a);break;
        case 3:printf("%lld\n",query(1,x));break;
        }
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ) proc();
    return 0;
}

