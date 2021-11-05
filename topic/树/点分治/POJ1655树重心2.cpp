#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;

typedef int weight_t;
int const SIZE = 20100;

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

int dfsSize(int node,int parent){
   TmpSize[node] = 1;
   for(int next=Vertex[node];next;next=Edge[next].next){
       int son = Edge[next].to;
       if ( son == parent ) continue;
       TmpSize[node] += dfsSize(son,node);
   }
   return TmpSize[node];
}

void dfsCenter(int node,int parent,int totalCnt){
    int tmp = totalCnt - TmpSize[node];
    for(int next=Vertex[node];next;next=Edge[next].next){
        int son = Edge[next].to;
        if ( son == parent ) continue;
        dfsCenter(son,node,totalCnt);
        if ( tmp < TmpSize[son] ) tmp = TmpSize[son];
    }
    if ( tmp < T4Center || ( tmp == T4Center && node < Center) ) T4Center = tmp, Center = node;
}

inline int getCenter(int root,int totalCnt){
    T4Center = INT_MAX;
    dfsCenter(root,0,totalCnt);
    return Center;
}

int N;
bool read(){
    scanf("%d",&N);
    initTree(N);

    int a,b;
    for(int i=1;i<N;++i){
        scanf("%d%d",&a,&b);
        mkEdge(a,b);
    }

    return true;
}
int main(){
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        read();
        getCenter(1,dfsSize(1,0));
        printf("%d %d\n",Center,T4Center);
    }
    return 0;
}

