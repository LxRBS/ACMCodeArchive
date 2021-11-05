/*
    给定有向图，给定s和t，
    问s到t的最短路径一共有多少条，
    不允许共边，即一条边只能用一次

    一条边只能用一次，这是一个限制
    可以考虑使用流量

    从s正向做一遍最短路
    从t反向做一遍最短路
    对每一条正向边(u,v)
    如果 d(s,u) + d(v,t) + w(u,v) = d(s,t)
    说明该边可以作为最短路的边
    就在u、v之间建一条边，容量为1
    最后从s到t跑一个最大流
*/

#include <stdio.h>
#include <limits.h>
#include <queue>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 1100;
int const SIZE_OF_EDGES = 300000;
weight_t const INF = 1000000000;

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
	ECnt = 2;//从2开始方便计算反向边
	fill(Vertex,Vertex+n+1,0);
}

//to build bi-directional edge
inline void mkEdge(int a,int b,weight_t w=weight_t()){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

//this is for heap
struct dijkstra_t{
    int u;
    weight_t w;
    dijkstra_t(int a,weight_t b):u(a),w(b){}
};
bool operator < (dijkstra_t const&lhs,dijkstra_t const&rhs){
    return rhs.w < lhs.w || ( lhs.w == rhs.w && rhs.u < lhs.u );
}

//s is the source
//vn is the amount of vertices, all vertices are indexed from 1 to vn
//di records the shortest distance from s to i
//pre records the previous vertex of i in the shortest path
//flag is auxiliary array
//orient为1表示用正向边，为0表示用反向边
void Dijkstra(int s,int vn,weight_t d[],bool flag[],int orient/*,int pre[]*/){
    fill(d,d+vn+1,INF);
    fill(flag,flag+vn+1,false);

    priority_queue<dijkstra_t> q;
    q.push(dijkstra_t(s,0));

    //pre[s] = 0;
    d[s] = 0;

    while( 1 ){
        while( !q.empty() && flag[q.top().u] ) q.pop();

        if ( q.empty() ) return;

        dijkstra_t head = q.top();
        q.pop();
        int v,u = head.u;
        weight_t tmp;
        flag[u] = true;

        for(int next=Vertex[u];next;next=Edge[next].next){
            if ( ((next&1)^orient) && !flag[v = Edge[next].to] && (tmp=d[u]+Edge[next].weight) < d[v] ){
            	//pre[v] = u;
            	q.push(dijkstra_t(v,d[v]=tmp));
	        }
        }
    }
}

//为流量准备
inline void mkEdge2(int a,int b,weight_t w){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].weight = 0;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
}

int __L[SIZE_OF_VERTICES];//层次图
int Queue[SIZE_OF_VERTICES];//队列
//建立残留网络从源s到汇t的层次图，n为顶点总数
bool bfs(int s,int t,int n){
	fill(__L+1,__L+n+1,-1);

	int u,v,head,tail = 0;
	__L[Queue[tail++] = s] = 0;

	for(head=0;head<tail;++head){
		//寻找还有残量的边
		for(int p=Vertex[u = Queue[head]];p;p=Edge[p].next){
            //如果有残量又没有被搜索过的，则标记层次
			if ( Edge[p].weight > 0 && -1 == __L[v = Edge[p].to] ){
                __L[Queue[tail++]=v] = __L[u] + 1;
			}
		}
	}

	return -1 != __L[t];
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

		if ( __L[u] + 1 == __L[v] && c > 0 && cf > tf ){
			weight_t f = dfs(v,min(c,cf-tf),t);
			if ( 0 == f ) continue;

			Edge[p].weight -= f;//正向边减去可行流量
			Edge[p^1].weight += f;//反向边加上
			tf += f;
		}
	}
	if ( 0 == tf ) __L[u] = -1;//修改层次图
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


int N,M,S,T;
void read(){
    scanf("%d%d",&N,&M);

    initGraph(N);
    int a,b,w;
    for(int i=0;i<M;++i){
        scanf("%d%d%d",&a,&b,&w);
        mkEdge(a,b,w);
    }
    scanf("%d%d",&S,&T);
}

int DS[SIZE_OF_VERTICES],DT[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];
edge_t EdgeBak[SIZE_OF_EDGES];
int V2V[SIZE_OF_VERTICES];

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        read();

        //从S跑一遍最短路
        Dijkstra(S,N,DS,Flag,1);

        //从T跑一遍最短路
        Dijkstra(T,N,DT,Flag,0);

        //对所有边
        fill(V2V,V2V+N+1,0);
        copy(Edge+2,Edge+ECnt,EdgeBak);
        initGraph(N);
        int a,b;
        for(int i=0;i<M+M;i+=2){
            //从a到b是一条最短路径的边
            if ( DS[a=EdgeBak[i].from] + DT[b=EdgeBak[i].to] + EdgeBak[i].weight == DS[T] ){
                mkEdge2(a,b,1);
            }
        }

        //跑一遍最大流
        printf("%d\n",Dinic(S,T,N));
    }
    return 0;
}
