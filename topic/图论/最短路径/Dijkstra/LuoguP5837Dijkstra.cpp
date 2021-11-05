/**
    N个点M条双向边，每条边有费用和流量
    从1到N，最大化路径流量与路径花费之比
    花费范围在1000，枚举每个花费就最短路，
    比当前枚举值小的边当做不存在
*/
#include <bits/stdc++.h>
using namespace std;


//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 1010;
int const SIZE_OF_EDGES = 2010<<1;
weight_t const INF = 1000000000;

struct edge_t{
	int from,to,cost;
	weight_t weight;
	int next;//Index of the array is used as pointers, ZERO means NULL
}Edge[SIZE_OF_EDGES];
int ECnt;
int Vertex[SIZE_OF_VERTICES];

//Don't forget calling it
//n is the amount of vertices
inline void initGraph(int n){
	ECnt = 1;
	fill(Vertex,Vertex+n+1,0);
}

//to build bi-directional edge
inline void mkEdge(int a,int b,int cost,weight_t w=weight_t()){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].cost = cost;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;

	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].cost = cost;
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
void Dijkstra(int s,int vn,weight_t d[],bool flag[],int limit){
    fill(d,d+vn+1,INF);
    fill(flag,flag+vn+1,false);

    priority_queue<dijkstra_t> q;
    q.push(dijkstra_t(s,0));

    d[s] = 0;

    while( 1 ){
        while( !q.empty() && flag[q.top().u] ) q.pop();

        if ( q.empty() ) return;

        dijkstra_t head = q.top();
        q.pop();
        int v,u = head.u;
        weight_t tmp;
        flag[u] = true;

        for(int next=Vertex[u];next;next=Edge[next].next)if(Edge[next].cost>=limit){
            if ( !flag[v = Edge[next].to] && (tmp=d[u]+Edge[next].weight) < d[v] ){
            	q.push(dijkstra_t(v,d[v]=tmp));
	        }
        }
    }
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}


weight_t D[1010];
bool Flag[1010];

int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    int m = getUnsigned();
    int maxflow = 0, minflow = INF;
    initGraph(n);
    while(m--){
        int a = getUnsigned();
        int b = getUnsigned();
        int w = getUnsigned();
        int flow = getUnsigned();
        mkEdge(a,b,flow,w);
        minflow = min(minflow,flow);
        maxflow = max(maxflow,flow);
    }
    int ans = 0;
    for(int flow=minflow;flow<=maxflow;++flow){
        Dijkstra(1,n,D,Flag,flow);
        ans = max(ans,flow*1000000/D[n]);
    }
    printf("%d\n",ans);
    return 0;
}
