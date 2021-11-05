//点权，单点更新，子树更新，查询根到指定节点的路径和
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

int InIdx[SIZE],OutIdx[SIZE];
int InOut[SIZE<<1];
int NewIdx[SIZE<<1];
int NCnt;

void dfs(int node,int parent){
    NewIdx[NCnt] = node;
    InOut[NCnt] = 1;
    InIdx[node] = NCnt++;
    for(int next=Vertex[node];next;next=Edge[next].next){
        int son = Edge[next].to;
        if ( son != parent ) dfs(son,node);
    }
    NewIdx[NCnt] = node;
    InOut[NCnt] = -1;
    OutIdx[node] = NCnt++;
}

int N;
weight_t StSum[SIZE<<3];
weight_t Lazy[SIZE<<3];
int Flag[SIZE<<3];//The count of the positive number in the range

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}

inline void _pushUp(int t){
    StSum[t] = StSum[lson(t)] + StSum[rson(t)];
    Flag[t] = Flag[lson(t)] + Flag[rson(t)];
}

inline void _pushDown(int t){
    if ( 0LL == Lazy[t] ) return;

    weight_t& x = Lazy[t];

    int son = lson(t);
    StSum[son] += Flag[son] * x;
    Lazy[son] += x;

    son = rson(t);
    StSum[son] += Flag[son] * x;
    Lazy[son] += x;

    x = 0LL;
}

void build(int t,int s,int e){
    Lazy[t] = 0LL;
    if ( s == e ){
        StSum[t] = InOut[s] * W[NewIdx[s]];
        Flag[t] = InOut[s];
        return;
    }

    int m = ( s + e ) >> 1;
    build(lson(t),s,m);
    build(rson(t),m+1,e);
    _pushUp(t);
}

void modify(int t,int s,int e,int a,int b,weight_t delta){
    if ( a <= s && e <= b ){
        StSum[t] += Flag[t] * delta;
        Lazy[t] += delta;
        return;
    }

    _pushDown(t);
    int m = ( s + e ) >> 1;
    if ( a <= m ) modify(lson(t),s,m,a,b,delta);
    if ( m < b ) modify(rson(t),m+1,e,a,b,delta);
    _pushUp(t);
}

weight_t query(int t,int s,int e,int a,int b){
    if ( a <= s && e <= b ){
        return StSum[t];
    }

    _pushDown(t);

    weight_t ret = 0LL;
    int m = ( s + e ) >> 1;
    if ( a <= m ) ret += query(lson(t),s,m,a,b);
    if ( m < b ) ret += query(rson(t),m+1,e,a,b);
    return ret;
}

inline weight_t query(int x){
    return query(1,1,N<<1,1,InIdx[x]);
}

inline void modify(int x,weight_t delta){
    modify(1,1,N<<1,InIdx[x],InIdx[x],delta);
    modify(1,1,N<<1,OutIdx[x],OutIdx[x],delta);
}

inline void modifySubtree(int x,weight_t delta){
    modify(1,1,N<<1,InIdx[x],OutIdx[x],delta);
}

inline void initTree(int n){
    ECnt = NCnt = 1;
    fill(Vertex,Vertex+n+1,0);
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

    dfs(1,0);
    build(1,1,N<<1);
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
        case 3:printf("%lld\n",query(x));break;
        }
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ) proc();
    return 0;
}

