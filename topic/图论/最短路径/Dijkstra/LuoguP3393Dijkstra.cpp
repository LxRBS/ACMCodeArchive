/**
    N个城市M条双向边
    K个城市有僵尸，与其距离不超过S的城市点权为Q
    其他安全的城市点权为P
    从1到N最小点权是多少
*/
#include <bits/stdc++.h>
using namespace std;


//type of edge's weight
typedef long long int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 101000;
int const SIZE_OF_EDGES = 200100<<1;
weight_t const INF = 1000000000000000LL;

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

int Type[101000];//0是安全，1是不安全，2是僵尸占领
queue<int> Queue;
weight_t D[101000];
bool Flag[101000];

int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    int m = getUnsigned();
    int k = getUnsigned();
    int s = getUnsigned();
    int p = getUnsigned();
    int q = getUnsigned();
    for(int i=0;i<k;++i) {
        int a = getUnsigned();
        Queue.push(a);
        Type[a] = 2;
    }
    initGraph(n);
    while(m--){
        int a = getUnsigned();
        int b = getUnsigned();
        mkEdge(a,b,0);
    }
    //确定不安全的城市
    while(!Queue.empty()){
        int v,u = Queue.front();
        Queue.pop();
        for(int p=Vertex[u];p;p=Edge[p].next){
            if(0==Type[v=Edge[p].to]){
                D[v] = D[u] + 1;
                Type[v] = 1;
                if(D[v]<s) Queue.push(v);
            }
        }
    }
    //将点权修改为边权
    for(int v,i=1;i<=ECnt;++i)if((v=Edge[i].to)!=1&&v!=n){
        if(2==Type[v])Edge[i].weight = INF;
        else if(1==Type[v])Edge[i].weight = q;
        else if(0==Type[v])Edge[i].weight = p;
        else throw runtime_error("XX");
    }
    Dijkstra(1,n,D,Flag);
    printf("%lld\n",D[n]);
    return 0;
}
