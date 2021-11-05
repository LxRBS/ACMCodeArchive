/**
    LCA模板题，倍增算法
*/
#include <bits/stdc++.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

//just as its names
int const SIZE_OF_VERTICES = 1100;
int const SIZE_OF_EDGES = SIZE_OF_VERTICES<<1;

struct edge_t{
	int from,to;
	//weight_t weight;
	int next;//Index of the array is used as pointers, ZERO means NULL
	edge_t(int a=0,int b=0,int c=0):from(a),to(b),next(c){}
}Edge[SIZE_OF_EDGES];
int ECnt;
int Vertex[SIZE_OF_VERTICES];

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	ECnt = 2;
	fill(Vertex,Vertex+n+1,0);
}

//to build bi-directional edge
inline void mkEdge(int a,int b){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	//Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
}

//Pij表示第i个节点的2^j级别的祖先
//例如Pi0就是i的父节点
int Parent[SIZE_OF_VERTICES][22];
int Depth[SIZE_OF_VERTICES];//根节点的深度是1
//Log2[i]就是以2为底i的对数加1，取整，需要预先算出来
int Log2[SIZE_OF_VERTICES];

void dfs(int u,int parent){
    Parent[u][0] = parent;
    Depth[u] = Depth[parent] + 1;
    //确定u的各级祖先
    for(int i=1,n=Log2[Depth[u]];i<=n;++i){
        Parent[u][i] = Parent[Parent[u][i-1]][i-1];
    }
    for(int v,p=Vertex[u];p;p=Edge[p].next){
        if((v=Edge[p].to)!=parent)dfs(v,u);
    }
}

int lca(int x,int y){
    if(Depth[x]<Depth[y]) swap(x,y);
    //把x和y调整到一个深度区间内
    while(Depth[x]>Depth[y]) x = Parent[x][Log2[Depth[x]-Depth[y]]-1];
    if(x==y) return x;
    //一起往上跳
    for(int k=Log2[Depth[x]]-1;k>=0;--k){
        if(Parent[x][k]!=Parent[y][k]){
            x = Parent[x][k];
            y = Parent[y][k];
        }
    }
    return Parent[x][0];
}

int N,M,S;
int main(){
    //freopen("1.txt","r",stdin);
    //初始化Log2数组
    for(int i=1;i<SIZE_OF_VERTICES;++i){
        Log2[i] = Log2[i-1] + ( (1 << Log2[i-1])==i?1:0 );
    }

    int nofkase = getUnsigned();
    for(int kase=1;kase<=nofkase;++kase){
        //读入数据
        initGraph(N = getUnsigned());
        //1总是树根
        for(int i=1;i<=N;++i){
            int m = getUnsigned();
            for(int j=0;j<m;++j){
                mkEdge(i,getUnsigned());
            }
        }
        //初始化数据
        dfs(1,0);
        //答问题
        printf("Case %d:\n",kase);
        int q = getUnsigned();
        while(q--){
            int a=getUnsigned();
            printf("%d\n",lca(a, getUnsigned()));
        }
    }
    return 0;
}

