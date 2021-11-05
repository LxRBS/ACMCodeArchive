//点权，单点更新，路径查询和及最值
#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;

int const SIZE = 30100;
typedef int weight_t;

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

int N;
weight_t StPeak[SIZE<<2];
weight_t StSum[SIZE<<2];

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}

inline void _pushUp(int t){
    StPeak[t] = max(StPeak[lson(t)],StPeak[rson(t)]);
    StSum[t] = StSum[lson(t)] + StSum[rson(t)];
}

void build(int t,int s,int e){
    if ( s == e ){
        StPeak[t] = StSum[t] = W[NewIdx[s]];
        return;
    }

    int m = ( s + e ) >> 1;
    build(lson(t),s,m);
    build(rson(t),m+1,e);
    _pushUp(t);
}

void modify(int t,int s,int e,int idx,weight_t newValue){
    if ( s == e ){
        StPeak[t] = StSum[t] = newValue;
        return;
    }

    int m = ( s + e ) >> 1;
    if ( idx <= m ) modify(lson(t),s,m,idx,newValue);
    else modify(rson(t),m+1,e,idx,newValue);
    _pushUp(t);
}

weight_t qPeak(int t,int s,int e,int a,int b){
    if ( a <= s && e <= b ) return StPeak[t];

    int m = ( s + e ) >> 1;
    weight_t ret = INT_MIN;
    if ( a <= m ) ret = max(ret,qPeak(lson(t),s,m,a,b));
    if ( m < b ) ret = max(ret,qPeak(rson(t),m+1,e,a,b));
    return ret;
}

weight_t qSum(int t,int s,int e,int a,int b){
    if ( a <= s && e <= b ) return StSum[t];

    int m = ( s + e ) >> 1;
    weight_t ret = 0;
    if ( a <= m ) ret += qSum(lson(t),s,m,a,b);
    if ( m < b ) ret += qSum(rson(t),m+1,e,a,b);
    return ret;
}

inline void change(int x,weight_t newValue){
    modify(1,1,N,Node[x].nid,newValue);
}

weight_t qPeak(int x,int y){
    weight_t ret = INT_MIN;
    while( Node[x].top != Node[y].top ){
        if ( Node[Node[x].top].depth < Node[Node[y].top].depth ) swap(x,y);

        ret = max(ret,qPeak(1,1,N,Node[Node[x].top].nid,Node[x].nid));
        x = Node[Node[x].top].parent;
    }

    if ( Node[x].depth > Node[y].depth ) swap(x,y);
    ret = max(ret,qPeak(1,1,N,Node[x].nid,Node[y].nid));
    return ret;
}

weight_t qSum(int x,int y){
    weight_t ret = 0;
    while( Node[x].top != Node[y].top ){
        if ( Node[Node[x].top].depth < Node[Node[y].top].depth ) swap(x,y);

        ret += qSum(1,1,N,Node[Node[x].top].nid,Node[x].nid);
        x = Node[Node[x].top].parent;
    }

    if ( Node[x].depth > Node[y].depth ) swap(x,y);
    ret += qSum(1,1,N,Node[x].nid,Node[y].nid);
    return ret;
}

inline void initTree(int n){
    ECnt = NCnt = 1;
    fill(Vertex,Vertex+n+1,0);
}

bool read(){
    if ( EOF == scanf("%d",&N) ) return false;

    initTree(N);
    int a,b;
    for(int i=1;i<N;++i){
        scanf("%d%d",&a,&b);
        mkEdge(a,b);
    }
    for(int i=1;i<=N;++i)scanf("%d",W+i);

    dfsHeavyEdge(1,0,0);
    dfsHeavyPath(1,1);
    build(1,1,N);
    return true;
}

int Q;
char Cmd[10];
void proc(){
    scanf("%d",&Q);
    int a,b;
    while(Q--){
        scanf("%s%d%d",Cmd,&a,&b);
        if ( 'C' == *Cmd ){
            change(a,b);
        }else if ( 'M' == Cmd[1] ){
            printf("%d\n",qPeak(a,b));
        }else{
            printf("%d\n",qSum(a,b));
        }
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ) proc();
    return 0;
}

