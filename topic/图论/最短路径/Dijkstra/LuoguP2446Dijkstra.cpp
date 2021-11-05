/**
    N个城市，M个单向边
    城市u被若干个城市ui保护
    问从1出发，摧毁N至少要多少时间
    改造一下Dijkstra
*/
#include <bits/stdc++.h>
using namespace std;

//type of edge's weight
typedef long long int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 3100;
int const SIZE_OF_EDGES = 100100;
weight_t const INF = 10000000000000000LL;

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

vector<int> G[3100];
int InDeg[3100];

//s is the source
//vn is the amount of vertices, all vertices are indexed from 1 to vn
//di records the shortest distance from s to i
//pre records the previous vertex of i in the shortest path
//flag is auxiliary array
void Dijkstra(int s,int vn,weight_t d[],bool flag[]){
    fill(d,d+vn+1,INF);
    fill(flag,flag+vn+1,false);

    priority_queue<dijkstra_t> q;
    q.push(dijkstra_t(s,d[s] = 0));

    while( 1 ){
        while( !q.empty() && flag[q.top().u] ) q.pop();

        if ( q.empty() ) return;

        dijkstra_t head = q.top();
        q.pop();
        int v,u = head.u;
        weight_t tmp;
        flag[u] = true;

        for(int next=Vertex[u];next;next=Edge[next].next){
            if(d[v=Edge[next].to] > (tmp = d[u]+Edge[next].weight)){
                d[v] = tmp;
            }
            if(0==InDeg[v]) q.push(dijkstra_t(v,d[v]));
        }

        for(vector<int>::const_iterator it=G[u].begin();it!=G[u].end();++it){
            d[*it] = max(d[*it],d[u]);
            if(0==--InDeg[*it]) q.push(dijkstra_t(*it,d[*it]));
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

weight_t D[3100];
bool Flag[3100];


int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    int m = getUnsigned();
    initGraph(n);
    while(m--){
        int a = getUnsigned();
        int b = getUnsigned();
        mkEdge(a,b,getUnsigned());
    }
    for(int i=1;i<=n;++i){
        int nn = getUnsigned();
        while(nn--){
            G[getUnsigned()].push_back(i);
            ++InDeg[i];
        }
    }
    Dijkstra(1,n,D,Flag);
    printf("%lld\n",D[n]);
    return 0;
}
