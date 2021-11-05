/*
    一个树，每个节点有权值
    父子不能同时入选
    要求选出若干节点使得权值最大，求这个最大的权值

    设Di为节点i所表示的子树的能选出的最大值
    Ai表示i入选时i子树的最大值，Bi表示i不入选时i子树的最大值
    Di = max(Ai,Bi)
    Ai = Wi + SIGMA(Bj)，其中j是i的儿子
    Bi = SGIMA(Dj)
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int const SIZE = 6010;

struct edge_t{
    int to;
    int next;
}Edge[SIZE];
int ECnt;
int Vertex[SIZE];

inline void initTree(int n){
    fill(Vertex,Vertex+n+1,0);
    ECnt = 1;
}

inline void mkEdge(int a,int b){
    Edge[ECnt].to = b;
    Edge[ECnt].next = Vertex[a];
    Vertex[a] = ECnt++;
}

int N;
int W[SIZE];

int A[SIZE],B[SIZE],D[SIZE];

void dfs(int root){
    A[root] = W[root];
    B[root] = 0;

    int v;
    for(int next=Vertex[root];next;next=Edge[next].next){
        dfs(v=Edge[next].to);

        A[root] += B[v];
        B[root] += D[v];
    }

    D[root] = max(A[root],B[root]);
}

bool Flag[SIZE];

int main(){
    //freopen("1.txt","r",stdin);

    while( 1 == scanf("%d",&N) ){
        for(int i=1;i<=N;++i)scanf("%d",W+i);

        initTree(N);
        fill(Flag,Flag+N+1,false);

        int a,b;
        while( scanf("%d%d",&b,&a),a ){
            mkEdge(a,b);
            Flag[b] = true;
        }

        int ans = 0;
        for(int i=1;i<=N;++i)if(!Flag[i]){
            dfs(i);
            ans += D[i];
        }

        printf("%d\n",ans);
    }
    return 0;
}
