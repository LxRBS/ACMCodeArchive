/**
    有向图上的，K短路，A*算法

*/
#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 1100;
int const SIZE_OF_EDGES = 220000;
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

inline void mkEdge(int a,int b,weight_t w=weight_t()){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
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
void Dijkstra(int s,int vn,weight_t d[],bool flag[]){
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

        for(int next=Vertex[u];next;next=Edge[next].next){
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

weight_t D[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];
int Cnt[SIZE_OF_VERTICES];
int A_start(int s,int t,int k,int vn){
    if(D[s]==INF) return -1;
    if ( s == t ) ++k;

    fill(Flag,Flag+vn+1,false);
    priority_queue<dijkstra_t> q;
    q.push(dijkstra_t(s,D[s]));

    while(!q.empty()){
        dijkstra_t head = q.top();
        q.pop();

        if(++Cnt[head.u]==k&&t==head.u)return head.w;
        if(Cnt[head.u]>k) continue;
        for(int v,w,p=Vertex[head.u];p;p=Edge[p].next){
            v = Edge[p].to, w = Edge[p].weight;
            q.push(dijkstra_t(v,head.w-D[head.u]+w+D[v]));
        }
    }
    return -1;
}

int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    int m = getUnsigned();
    initGraph(n);
    while(m--){//首先建一个反向图
        int a = getUnsigned();
        int b = getUnsigned();
        mkEdge(b,a,getUnsigned());
    }
    int s = getUnsigned();
    int t = getUnsigned();
    int k = getUnsigned();
    //对T跑一遍最短路
    Dijkstra(t,n,D,Flag);
    //再把图正过来
    fill(Vertex,Vertex+n+1,0);
    for(int i=1;i<=ECnt;++i){
        swap(Edge[i].from,Edge[i].to);
        Edge[i].next = Vertex[Edge[i].from];
        Vertex[Edge[i].from] = i;
    }
    //再跑一个A*算法
    printf("%d\n",A_start(s,t,k,n));
    return 0;
}
