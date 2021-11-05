/*
    һ����������Ȩֵ
    �����ÿ���ڵ����Զ��ľ���

    Ai�ǽڵ�i��i�����е���Զ����
    Bi�ǽڵ�Ӹ��ڵ��������Զ����
    DiΪ���� Di = max{Ai,Bi}

    ����A��B����ͬʱ��ã�Ҫ���Ⱥ�
    ��CiΪi�����еĴ�Զ����

    Ai = max{Aj+wij}��j��i�Ķ���
    Bi = wji + max{Bj,Aj��Cj}��j��i�ĸ���
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

//��A��C����������Զ�ʹ�Զ
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

//��B
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
