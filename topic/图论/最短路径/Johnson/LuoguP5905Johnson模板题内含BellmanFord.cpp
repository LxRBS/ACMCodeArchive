/**
   Johnson全源最短路，模板题
*/
#include <bits/stdc++.h>
using namespace std;

//type of edge's weight
typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 3100;
int const SIZE_OF_EDGES = 120000;
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

//s是源，vn是点的数量，d是最短路径数组
bool Bellman_Ford(int s,int vn,weight_t d[]){
    fill(d+1,d+vn+1,INF);
    d[s] = 0;

    --vn;
    weight_t tmp;
    while(vn--){//循环vn-1次
        for(int v,i=1;i<=ECnt;++i){
            if((tmp=d[Edge[i].from]+Edge[i].weight)<d[v=Edge[i].to]){
                d[v] = tmp;
            }
        }
    }
    //判负环
    for(int i=1;i<=ECnt;++i){
        if(d[Edge[i].from]+Edge[i].weight<d[Edge[i].to]){
            return false;//有负环
        }
    }
    return true;//没有负环
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
void Dijkstra(int s,int vn,weight_t d[],bool flag[],int pre[]){
    fill(d,d+vn+1,INF);
    fill(flag,flag+vn+1,false);

    priority_queue<dijkstra_t> q;
    q.push(dijkstra_t(s,0));

    pre[s] = 0;
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
            	pre[v] = u;
            	q.push(dijkstra_t(v,d[v]=tmp));
	        }
        }
    }
}

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

typedef long long llt;
weight_t D[3100];
weight_t DD[3100];
int Pre[3100];
bool Flag[3100];
int main(){
    //freopen("1.txt","r",stdin);
    int n = getInt();
    int m = getInt();
    initGraph(n+1);
    while(m--){
        int a = getInt();
        int b = getInt();
        mkEdge(a,b,getInt());
    }
    //建立一个超级源点
    for(int i=1;i<=n;++i)mkEdge(n+1,i,0);
    //跑一遍Bellman-Ford
    if(!Bellman_Ford(n+1,n+1,D)){
        puts("-1");
        return 0;
    }
    //改造原图
    for(int i=1;i<=ECnt;++i){
        Edge[i].weight += D[Edge[i].from] - D[Edge[i].to];
    }
    //对每一个点跑Dijkstra
    for(int i=1;i<=n;++i){
        Dijkstra(i,n,DD,Flag,Pre);
        llt sum = 0;
        for(llt j=1;j<=n;++j){
            sum += (DD[j]==INF?INF:DD[j]+D[j]-D[i])*j;
        }
        printf("%lld\n",sum);
    }
    return 0;
}
