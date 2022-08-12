/*
     10×10的地图
     起点为(0,5)，终点为(10,5)
     中间有若干竖直的墙
     问起点到终点的最短距离
*/
#include <stdio.h>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;

double const EPS = 1E-9;
inline bool is0(double x){return -EPS<x&&x<EPS;}
//return true iff x >= y
inline bool isGE(double x,double y){return x-y>-EPS;}

struct point_t{
    double x,y;
    point_t(double a=0.0,double b=0.0):x(a),y(b){}
};

inline double cross(point_t const&O,point_t const&A,point_t const&B){
    double xoa = A.x - O.x;
    double yoa = A.y - O.y;
    double xob = B.x - O.x;
    double yob = B.y - O.y;
    return xoa * yob - xob * yoa;
}

struct lineseg_t{
    point_t s,e;
    lineseg_t(point_t const&a=point_t(),point_t const&b=point_t()):s(a),e(b){}
};

//判断线段a和b是否相交
inline bool isInter(lineseg_t const&a,lineseg_t const&b){
	return min(a.s.x,a.e.x) <= max(b.s.x,b.e.x)
		&& min(b.s.x,b.e.x) <= max(a.s.x,a.e.x)
		&& min(a.s.y,a.e.y) <= max(b.s.y,b.e.y)
		&& min(b.s.y,b.e.y) <= max(a.s.y,a.e.y)
		&& isGE(cross(a.s,b.s,a.e) * cross(a.s,a.e,b.e),0)
		&& isGE(cross(b.s,a.e,b.e) * cross(b.s,b.e,a.s),0);
}

inline double dist(point_t const&A,point_t const&B){
    double x = A.x - B.x;
    double y = A.y - B.y;
    return sqrt(x*x+y*y);
}

//type of edge's weight
typedef double weight_t;

//just as its names
int const SIZE_OF_VERTICES = 10000;
int const SIZE_OF_EDGES = 30000;
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
            	//pre[v] = u;
            	q.push(dijkstra_t(v,d[v]=tmp));
	        }
        }
    }
}

int N;
int Cnt,S,T;
//每堵墙形成4个点3条线段
point_t P[20][4];
lineseg_t Ls[20][3];
int Idx[20][4];
point_t const PS(0,5),PT(10,5);

//看指定线段是否与[s,e)区间内的墙有交点，
//有返回false，没有返回true
bool isOK(lineseg_t const&ls,int s,int e){
    for(int i=s;i<e;++i){
        int a = isInter(ls,Ls[i][0]);
    int b = isInter(ls,Ls[i][1]);
    int c = isInter(ls,Ls[i][2]);
        if ( isInter(ls,Ls[i][0]) || isInter(ls,Ls[i][1]) || isInter(ls,Ls[i][2]) )
            return false;
    }
    return true;
}

bool read(){
    scanf("%d",&N);
    if ( -1 == N ) return false;

    Cnt = 0;
    double x;
    for(int i=0;i<N;++i){
        //读入点
        scanf("%lf%lf%lf%lf%lf",&x,&P[i][0].y,&P[i][1].y,&P[i][2].y,&P[i][3].y);
        P[i][0].x = P[i][1].x = P[i][2].x = P[i][3].x = x;

        //安排好线段
        Ls[i][0].s = point_t(x,0),Ls[i][0].e = P[i][0];
        Ls[i][1].s = P[i][1], Ls[i][1].e = P[i][2];
        Ls[i][2].s = P[i][3], Ls[i][2].e = point_t(x,10);

        //安排好图的顶点编号
        Idx[i][0] = ++Cnt;
        Idx[i][1] = ++Cnt;
        Idx[i][2] = ++Cnt;
        Idx[i][3] = ++Cnt;
    }

    S = ++Cnt;
    T = ++Cnt;

    initGraph(Cnt);
    //建图
    //对起点
    for(int i=0;i<N;++i){
        //每堵墙有四个点
        if ( isOK(lineseg_t(PS,P[i][0]),0,i) ) mkEdge(S,Idx[i][0],dist(PS,P[i][0]));
        if ( isOK(lineseg_t(PS,P[i][1]),0,i) ) mkEdge(S,Idx[i][1],dist(PS,P[i][1]));
        if ( isOK(lineseg_t(PS,P[i][2]),0,i) ) mkEdge(S,Idx[i][2],dist(PS,P[i][2]));
        if ( isOK(lineseg_t(PS,P[i][3]),0,i) ) mkEdge(S,Idx[i][3],dist(PS,P[i][3]));
    }

    //对终点
    for(int i=0;i<N;++i){
        //每堵墙有四个点
        if ( isOK(lineseg_t(P[i][0],PT),i+1,N) ) mkEdge(Idx[i][0],T,dist(P[i][0],PT));
        if ( isOK(lineseg_t(P[i][1],PT),i+1,N) ) mkEdge(Idx[i][1],T,dist(P[i][1],PT));
        if ( isOK(lineseg_t(P[i][2],PT),i+1,N) ) mkEdge(Idx[i][2],T,dist(P[i][2],PT));
        if ( isOK(lineseg_t(P[i][3],PT),i+1,N) ) mkEdge(Idx[i][3],T,dist(P[i][3],PT));
    }

    //对都在墙上的点
    for(int i=0;i<N;++i)for(int j=i+1;j<N;++j){
        for(int u=0;u<4;++u)for(int v=0;v<4;++v){
            if ( isOK(lineseg_t(P[i][u],P[j][v]),i+1,j) ){
                mkEdge(Idx[i][u],Idx[j][v],dist(P[i][u],P[j][v]));
            }
        }
    }

    return true;
}

weight_t D[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];

int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        //起点终点可能直连
        if ( isOK(lineseg_t(PS,PT),0,N) ){
            puts("10.00");
            continue;
        }

        Dijkstra(S,Cnt,D,Flag);
        printf("%.2f\n",D[T]);
    }
    return 0;
}
