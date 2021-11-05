#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;

typedef int weight_t;
int const SIZE = 20100;

struct node_t{
    int to;
    weight_t w;
    int next;
}Node[SIZE<<1];
int NCnt;
int Head[SIZE];

inline void initTrees(int n){
    NCnt = 1;
    fill(Head,Head+n+1,0);
}

inline void mkEdge(int a,int b,weight_t w=0){
    Node[NCnt].to = b;
    Node[NCnt].w = w;
    Node[NCnt].next = Head[a];
    Head[a] = NCnt++;

    Node[NCnt].to = a;
    Node[NCnt].w = w;
    Node[NCnt].next = Head[b];
    Head[b] = NCnt++;
}

int TmpSize[SIZE];
int Center,T4Center;

void dfs4Center(int node,int parent,int totalCnt){
    TmpSize[node] = 1;
    int tmp = 0;
    for(int next=Head[node];next;next=Node[next].next){
        int son = Node[next].to;
        if ( son == parent ) continue;
        dfs4Center(son,node,totalCnt);

        TmpSize[node] += TmpSize[son];
        if ( tmp < TmpSize[son] ) tmp = TmpSize[son];
    }
    if ( tmp < totalCnt - TmpSize[node] ) tmp = totalCnt - TmpSize[node];
    if ( tmp < T4Center || ( tmp == T4Center && Center < node ) ) T4Center = tmp, Center = node;
}

inline int getCenter(int root,int totalCnt){
    T4Center = INT_MAX;
    dfs4Center(root,0,totalCnt);
    return Center;
}

int N;
bool read(){
    scanf("%d",&N);
    initTrees(N);

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
        getCenter(1,N);
        printf("%d %d\n",Center,T4Center);
    }
    return 0;
}
