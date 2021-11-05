/*
    有N个加工设备，每个设备输入某种半成品输出另外某种半成品
    整个成品有P个部分构成，半成品则是由其中某些部分构成
    每个加工设备同时最多加工Q个产品
    问怎么安排，使得整个流水线加工最大，并且输出安排
    拆点最大流
*/
#include <stdio.h>
#include <limits.h>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef int weight_t;
weight_t const INF = 2000000000;

//just as its names
int const SIZE_OF_VERTICES = 500;
int const SIZE_OF_EDGES = 50000;

struct edge_t{
	int from,to;
	weight_t weight;
	int next;//Index of the array is used as pointers, ZERO means NULL
}Edge[SIZE_OF_EDGES];
int ECnt;
int Vertex[SIZE_OF_VERTICES];

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	ECnt = 2;//ECnt从2开始，空指针用0表示，反向边用^1计算
	fill(Vertex,Vertex+n+1,0);
}

//to build bi-directional edge
inline void mkEdge(int a,int b,weight_t w){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].weight = 0;//反向边的容量为0
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

int L[SIZE_OF_VERTICES];//层次图
int Queue[SIZE_OF_VERTICES];//队列
//建立残留网络从源s到汇t的层次图，n为顶点总数
bool bfs(int s,int t,int n){
	fill(L+1,L+n+1,-1);

	int u,v,head,tail = 0;
	L[Queue[tail++] = s] = 0;

	for(head=0;head<tail;++head){
		//寻找还有残量的边
		for(int p=Vertex[u = Queue[head]];p;p=Edge[p].next){
            //如果有残量又没有被搜索过的，则标记层次
			if ( Edge[p].weight > 0 && -1 == L[v = Edge[p].to] ){
                L[Queue[tail++]=v] = L[u] + 1;
			}
		}
	}

	return -1 != L[t];
}

//在层次图上搜索增广路径，本质上就是搜索可以增广的流量
//这个流量是各层之间流量的最小值
//u为当前节点，cf为已经搜索出的结果，t为汇点
weight_t dfs(int u,weight_t cf,int t){
	if ( u == t ) return cf;

	weight_t tf = 0;//tf记录u往下一层的总可行流量
	for(int p=Vertex[u];p;p=Edge[p].next){
		int v = Edge[p].to;
		weight_t c = Edge[p].weight;

		if ( L[u] + 1 == L[v] && c > 0 && cf > tf ){
			weight_t f = dfs(v,min(c,cf-tf),t);
			if ( 0 == f ) continue;

			Edge[p].weight -= f;//正向边减去可行流量
			Edge[p^1].weight += f;//反向边加上
			tf += f;
		}
	}
	if ( 0 == tf ) L[u] = -1;//修改层次图
	return tf;
}

//Dinic算法，s为源，t为汇，n为图顶点总数
weight_t Dinic(int s,int t,int n){
	weight_t ret = 0;
	while( bfs(s,t,n) ){//第一步建立分层图
		weight_t ans;
		//第二步在分层图上查找一条增广路径的可行流量
		while( ans = dfs(s,INT_MAX,t) )
			ret += ans;
	}
	return ret;
}

int P,N;
int In[55][12],Out[55][12];
int const SOUT[12] = {0};
int const TIN[12] = {1,1,1,1,1,1,1,1,1,1,1,1};
int S,T;//源汇

bool f(int const out[],int const in[]){
    for(int i=1;i<=P;++i){
        if ( in[i] != 2 && in[i] != out[i] ) return false;
    }
    return true;
}

bool read(){
    if ( EOF == scanf("%d%d",&P,&N) ) return false;

    S = N + N + 1;
    initGraph(T=N+N+2);

    int q;
    for(int i=1;i<=N;++i){
        scanf("%d",&q);
        mkEdge(i,i+N,q);//拆点

        for(int j=1;j<=P;++j)scanf("%d",In[i]+j);
        for(int j=1;j<=P;++j)scanf("%d",Out[i]+j);
    }

    for(int i=1;i<=N;++i){
        if ( f(SOUT,In[i]) ) mkEdge(S,i,INF);
        if ( f(Out[i],TIN) ) mkEdge(i+N,T,INF);

        for(int j=i+1;j<=N;++j){
            if ( f(Out[i],In[j]) ) mkEdge(i+N,j,INF);
            if ( f(Out[j],In[i]) ) mkEdge(j+N,i,INF);
        }
    }

    return true;
}

int A[100],B[100],W[100];
int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        int ret = Dinic(S,T,T);
        int v, cnt = 0;

        //检查所有的反向边
        for(int i=1;i<=N;++i)for(int next=Vertex[i];next;next=Edge[next].next){
            if ( Edge[next].weight && N < (v=Edge[next].to) && v <= N+N && v!=i+N ){
                A[cnt] = v-N;
                B[cnt] = i;
                W[cnt++] = Edge[next].weight;
            }
        }

        printf("%d %d\n",ret,cnt);
        for(int i=0;i<cnt;++i)printf("%d %d %d\n",A[i],B[i],W[i]);
    }
    return 0;
}
