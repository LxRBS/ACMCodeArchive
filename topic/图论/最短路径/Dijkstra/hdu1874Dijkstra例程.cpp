#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 100;
int const SIZE_OF_EDGES = 10000;
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
void Dijkstra(int s,int vn,weight_t d[],int pre[],bool flag[]){
    fill(d,d+vn+1,INF);
    fill(flag,flag+vn+1,false);

    priority_queue<dijkstra_t> q;
    q.push(dijkstra_t(s,0));

    flag[s] = false;
    pre[s] = 0;
    d[s] = 0;

    while( 1 ){
        while( !q.empty() && flag[q.top().u] ) q.pop();

        if ( q.empty() ) return;

        dijkstra_t head = q.top();
        q.pop();
        int u = head.u;
        flag[u] = true;

        for(int next=Vertex[u];next;next=Edge[next].next){
            int v = Edge[next].to;
            if ( flag[v] ) continue;

            weight_t t = d[u] + Edge[next].weight;
            if ( t < d[v] ){
                d[v] = t;
                pre[v] = u;
                q.push(dijkstra_t(v,t));
            }
        }
    }
}
int N,M,S,T;
bool read(){
	if ( EOF == scanf("%d%d",&N,&M) ) return false;

	initGraph(N);
	for(int i=0;i<M;++i){
		int a,b,w;
		scanf("%d%d%d",&a,&b,&w);
		mkEdge(a+1,b+1,w);
	}
	scanf("%d%d",&S,&T);

	return true;
}

weight_t D[SIZE_OF_VERTICES];
int Pre[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];

void proc(){
    Dijkstra(S+1,N,D,Pre,Flag);

	if ( INF == D[T+1] ) printf("-1\n");
	else printf("%d\n",D[T+1]);
}

int main(){
    //freopen("1.txt","r",stdin);
    for(int kase=1;read();++kase){
        //printf("Case #%d: ",kase);
        proc();
    }
    return 0;
}

