/*
    平面上有若干点，给定起点和终点
    要求从起点跳到终点
    要使得这条路径上的最长的边最短
    最短路径的变形 
    最短路径本质上是求路径上所有边的和
    而这道题是求路径上所有边的最大值
*/
#include <stdio.h>
#include <math.h>
#include <queue>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 1010;
int const SIZE_OF_EDGES = 50000;
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
	ECnt = 1;
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
void Dijkstra(int s,int vn,weight_t d[],bool flag[]/*,int pre[]*/){
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
                                             //就是这里改一下即可
            if ( !flag[v = Edge[next].to] && (tmp=max(d[u],Edge[next].weight)) < d[v] ){
            	//pre[v] = u;
            	q.push(dijkstra_t(v,d[v]=tmp));
	        }
        }
    }
}

int N;
int X[210],Y[210];

inline int dist2(int idx,int jdx){
    int x = X[idx] - X[jdx];
    int y = Y[idx] - Y[jdx];
    return x * x + y * y;
}

bool read(){
    scanf("%d",&N);
    if ( 0 == N ) return false;

    for(int i=1;i<=N;++i)scanf("%d%d",X+i,Y+i);

    initGraph(N);
    for(int i=1;i<N;++i)for(int j=i+1;j<=N;++j){
        mkEdge(i,j,dist2(i,j));
    }
    return true;
}

bool Flag[SIZE_OF_VERTICES];
weight_t D[SIZE_OF_VERTICES];

int main(){
    //freopen("1.txt","r",stdin);
    for(int kase=1;read();++kase){
        Dijkstra(1,N,D,Flag);
        printf("Scenario #%d\nFrog Distance = %.3lf\n\n",kase,sqrt((double)D[2]));
    }
    return 0;
}

