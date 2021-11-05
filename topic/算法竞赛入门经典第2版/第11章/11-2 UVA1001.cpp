//三维空间给定若干个洞，洞内空间可以瞬移，其他空间10秒1个单位
//问从起点到终点的最少时间
//建图，最多102个顶点的完全图

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <queue>
#include <algorithm>
using namespace std;

//type of edge's weight
typedef double weight_t;

//just as its names
int const SIZE_OF_VERTICES = 110;
int const SIZE_OF_EDGES = 30000;
double const INF = 1E30;

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
	ECnt = 2;
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
void Dijkstra(int s,int vn,weight_t d[],bool flag[]){
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
            if ( !flag[v = Edge[next].to] && (tmp=d[u]+Edge[next].weight) < d[v] ){
            	//pre[v] = u;
            	q.push(dijkstra_t(v,d[v]=tmp));
	        }
        }
    }
}

int N;
double X[110],Y[110],Z[110],R[110];
double SX,SY,SZ,EX,EY,EZ;
bool read(){
    scanf("%d",&N);
    if ( -1 == N ) return false;

    for(int i=1;i<=N;++i) scanf("%lf%lf%lf%lf",X+i,Y+i,Z+i,R+i);
    scanf("%lf%lf%lf%lf%lf%lf",&SX,&SY,&SZ,&EX,&EY,&EZ);

    initGraph(N+2);

    //建图
    for(int i=1;i<N;++i)for(int j=i+1;j<=N;++j){
        double x = X[i] - X[j], y = Y[i] - Y[j], z = Z[i] - Z[j];
        double d = sqrt(x*x+y*y+z*z);
        if ( d < R[i] + R[j] ) mkEdge(i,j,0.0);
        else mkEdge(i,j,d-R[i]-R[j]);
    }

    //起点
    for(int i=1;i<=N;++i){
        double x = X[i] - SX, y = Y[i] - SY, z = Z[i] - SZ;;
        double d = sqrt(x*x+y*y+z*z);
        if ( d < R[i] ) mkEdge(N+1,i,0.0);
        else mkEdge(N+1,i,d-R[i]);
    }

    //终点
    for(int i=1;i<=N;++i){
        double x = X[i] - EX, y = Y[i] - EY, z = Z[i] - EZ;;
        double d = sqrt(x*x+y*y+z*z);
        if ( d < R[i] ) mkEdge(N+2,i,0.0);
        else mkEdge(N+2,i,d-R[i]);
    }

    //起点终点直达
    double x = SX-EX, y = SY-EY, z = SZ-EZ;
    double d = sqrt(x*x+y*y+z*z);
    mkEdge(N+1,N+2,d);
    return true;
}

double D[110];
bool Flag[110];

int main(){
    //freopen("1.txt","r",stdin);
    for(int kase=1;read();++kase){
        Dijkstra(N+1,N+2,D,Flag);
        printf("Cheese %d: Travel time = %.0lf sec\n",kase,D[N+2]*10.0);
    }
    return 0;
}
