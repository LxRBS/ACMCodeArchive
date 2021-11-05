#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;

typedef int weight_t;
int const SIZE = 40100;

struct edge_t{
    int to;
    weight_t w;
    int next;
}Edge[SIZE<<1];
int ECnt;
int Vertex[SIZE];

inline void initTree(int n){
    ECnt = 1;
    fill(Vertex,Vertex+n+1,0);
}

inline void mkEdge(int a,int b,weight_t w=0){
    Edge[ECnt].to = b;
    Edge[ECnt].w = w;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt++;

    Edge[ECnt].to = a;
    Edge[ECnt].w = w;
    Edge[ECnt].next = Vertex[b];
    Vertex[b] = ECnt++;
}

int TmpSize[SIZE];
int Center,T4Center;
bool Flag[SIZE];

int dfsSize(int node,int parent){
   TmpSize[node] = 1;
   for(int next=Vertex[node];next;next=Edge[next].next){
       int son = Edge[next].to;
       if ( son == parent || Flag[son] ) continue;
       TmpSize[node] += dfsSize(son,node);
   }
   return TmpSize[node];
}

void dfsCenter(int node,int parent,int totalCnt){
    int tmp = totalCnt - TmpSize[node];
    for(int next=Vertex[node];next;next=Edge[next].next){
        int son = Edge[next].to;
        if ( son == parent || Flag[son] ) continue;
        dfsCenter(son,node,totalCnt);
        if ( tmp < TmpSize[son] ) tmp = TmpSize[son];
    }
    if ( tmp < T4Center || ( tmp == T4Center && node < Center) ) T4Center = tmp, Center = node;
}

inline int getCenter(int root){
    T4Center = INT_MAX;
    dfsCenter(root,0,dfsSize(root,0));
    return Center;
}

int N,M;
weight_t K;
bool read(){
    if ( EOF == scanf("%d%d",&N,&M) ) return false;
    initTree(N);

    int a,b;
    weight_t c;
    char s[4];
    for(int i=0;i<M;++i){
        scanf("%d%d%d%s",&a,&b,&c,s);
        mkEdge(a,b,c);
    }

    scanf("%d",&K);
    return true;
}

weight_t D[SIZE];
int WCnt;
void dfsDistance(int node,int parent,weight_t d){
    D[WCnt++] = d;
    for(int next=Vertex[node];next;next=Edge[next].next){
        int son = Edge[next].to;
        if ( son == parent || Flag[son] ) continue;
        dfsDistance(son,node,d + Edge[next].w);
    }
}

int calc(int node,weight_t d){
    WCnt = 0;
    dfsDistance(node,0,d);
    sort(D,D+WCnt);

    int ret = 0;
    for(int i=0,j=WCnt-1;i<j&&D[i]<=K;++i){
        while( D[i] + D[j] > K && i < j ) --j;
        ret += j - i;
    }
    return ret;
}

int dfs(int node){
    int center = getCenter(node);
    Flag[center] = true;

    int ret = calc(center,0);
    for(int next=Vertex[center];next;next=Edge[next].next){
        int son = Edge[next].to;
        if ( Flag[son] ) continue;

        ret -= calc(son,Edge[next].w);
        ret += dfs(son);
    }
    return ret;
}
int main(){
    //freopen("1.txt","r",stdin);
    while ( read() ){
        fill(Flag,Flag+N+1,false);
        printf("%d\n",dfs(1));
    }
    return 0;
}

