/*
    一个树，边有权值
    求距离每个节点的最远点的距离

    Ai是节点i到i子树中的最远距离
    Bi是节点从父节点过来的最远距离
    Di为所求 Di = max{Ai,Bi}

    但是A和B不能同时求得，要分先后
    令Ci为i子树中的次远距离

    Ai = max{Aj+wij}，j是i的儿子
    Bi = wji + max{Bj,Aj或Cj}，j是i的父亲
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int const SIZE = 20010;

struct edge_t{
    int from,to;
    int weight;
    int next;
}Edge[SIZE];
int ECnt;
int Vertex[SIZE];

inline void initTree(int n){
    fill(Vertex,Vertex+n+1,0);
    ECnt = 1;
}

inline void mkEdge(int a,int b,int w){
    Edge[ECnt].from = a;
    Edge[ECnt].to = b;
    Edge[ECnt].weight = w;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt++;
}

int N;
int W[SIZE];

int A[SIZE],B[SIZE],C[SIZE];

//求A和C，子树内最远和次远
void dfs1(int u,int parent){
    A[u] = C[u] = 0;

    for(int v,next=Vertex[u];next;next=Edge[next].next){
        dfs1(v=Edge[next].to,u);

        int tmp = A[v] + Edge[next].weight;
        if ( A[u] <= tmp ){
            C[u] = A[u];A[u] = tmp;
        }else if ( C[u] < tmp ){
            C[u] = tmp;
        }
    }
}

//求B
void dfs2(int u,int parent,int w){
    B[u] = w + max(B[parent],A[parent]==A[u]+w?C[parent]:A[parent]);

    for(int next=Vertex[u];next;next=Edge[next].next){
        dfs2(Edge[next].to,u,Edge[next].weight);
    }
}

int main(){
    //freopen("1.txt","r",stdin);

    while( 1 == scanf("%d",&N) ){
        initTree(N);

        int a,w;
        for(int i=2;i<=N;++i){
            scanf("%d%d",&a,&w);
            mkEdge(a,i,w);
        }

        fill(A,A+N+1,0);
        fill(B,B+N+1,0);
        fill(C,C+N+1,0);

        dfs1(1,0);
        dfs2(1,0,0);

        for(int i=1;i<=N;++i)printf("%d\n",max(A[i],B[i]));
    }
    return 0;
}
