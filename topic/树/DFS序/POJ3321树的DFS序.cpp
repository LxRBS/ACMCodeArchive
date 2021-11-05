/*
     一棵树，两种操作
     C x：切换状态
     Q x：以x为根的子树一共有多少个苹果

     相当于树上操作：
     单点更新，子树查询

     可以使用树链剖分或者DFS序将树拍平
     然后使用树状数组或者线段树
*/
#include <stdio.h>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;

typedef int weight_t;
int const SIZE = 200010;

//边
struct edge_t{
    int to;
    int next;
}Edge[SIZE<<1];
int Vertex[SIZE];
int ECnt;
weight_t W[SIZE];//权值

inline void initGraph(int n){
    ECnt = 1;
    fill(Vertex,Vertex+n+1,0);
}

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
    NewIdx[++NCnt] = node;
    InOut[NCnt] = 1;
    InIdx[node] = NCnt;
    for(int next=Vertex[node];next;next=Edge[next].next){
        int son = Edge[next].to;
        if ( son != parent ) dfs(son,node);
    }
    NewIdx[++NCnt] = node;
    InOut[NCnt] = -1;
    OutIdx[node] = NCnt;
}

weight_t C[SIZE];//树状数组

inline int lowbit(int x){ return x & (-x);}

//求[1,n]的区间和
weight_t query(int n){
    int sum = 0;
    while( n > 0 ){
        sum += C[n];
        n = n - lowbit(n);
    }
    return sum;
}

inline weight_t query(int s,int e){
    return query(e) - query(s-1);
}

//单点修改，将第idx个位置增加delta
void modify(int idx,int delta,int n){
    while( idx <= n ){
        C[idx] += delta;
        idx += lowbit(idx);
    }
}

//树上操作转树状数组查询
//建树，初始时节点全为1
void build(int n){
    fill(W,W+n+1,1);

    for(int i=1;i<=n;++i){
        modify(InIdx[i],1,n+n);//入节点
        modify(OutIdx[i],1,n+n);//出节点
    }
}

//将第pos个节点的状态改变，1变0或者0变1
void change(int pos,int n){
    if ( W[pos] ){
        modify(InIdx[pos],-1,n+n);
        modify(OutIdx[pos],-1,n+n);
    }else{
        modify(InIdx[pos],1,n+n);
        modify(OutIdx[pos],1,n+n);
    }
    W[pos] ^= 1;
}

//子树查询
weight_t querySubtree(int pos){
    return query(InIdx[pos],OutIdx[pos]) >> 1;
}

int N;
void read(){
    scanf("%d",&N);

    initGraph(N);
    int a,b;
    for(int i=1;i<N;++i){
        scanf("%d%d",&a,&b);
        mkEdge(a,b);
    }

    dfs(1,0);
    build(N);
}
int main(){
    //freopen("1.txt","r",stdin);

    read();

    int m;
    scanf("%d",&m);

    char cmd[3];
    int idx;
    while(m--){
        scanf("%s%d",cmd,&idx);
        if ( 'Q' == *cmd ){
            printf("%d\n",querySubtree(idx));
        }else{
            change(idx,N);
        }
    }
    return 0;
}
