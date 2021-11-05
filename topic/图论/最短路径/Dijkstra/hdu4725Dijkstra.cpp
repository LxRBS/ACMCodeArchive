/*
    Nya图一共有N个节点
    每个节点属于某一个层
    从x层的某个节点移动到x+1层的某个节点，
    需要花费C，注意道路是双向的
    另外有M条边，每条边连接u、v，且花费为w
    问从节点1到节点N的最小花费

    首先不能简单的将两层之间的所有节点连边
    因为点的总数为1E5，如果平均分为10层，
    每层的点数就是1E4，两层之间两两连边，
    就是1E4的平方，超时
    
    所以需要考虑其他建图的方法
    将层数也看作是点，建边
    但是仍然要考虑一些问题
    1
    3 0 1
    1 1 1
    答案应该是-1
*/

#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

typedef int weight_t;

//just as its names
int const SIZE_OF_VERTICES = 1000010;
int const SIZE_OF_EDGES = 1000010;
weight_t const INF = 2000000000;

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

//单向边
inline void mkEdge(int a,int b,weight_t w=weight_t()){
	Edge[ECnt].from = a;
	Edge[ECnt].to = b;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[a];
	Vertex[a] = ECnt ++;
/*
	Edge[ECnt].from = b;
	Edge[ECnt].to = a;
	Edge[ECnt].weight = w;
	Edge[ECnt].next = Vertex[b];
	Vertex[b] = ECnt ++;
*/
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
            if ( !flag[v = Edge[next].to] && (tmp=d[u]+Edge[next].weight) < d[v] ){
            	//pre[v] = u;
            	q.push(dijkstra_t(v,d[v]=tmp));
	        }
        }
    }
}

int N,M,C;
int Layer[SIZE_OF_VERTICES];
bool Flag[SIZE_OF_VERTICES];

void read(){
    scanf("%d%d%d",&N,&M,&C);

    initGraph(N+N);

    //读入层数
    fill(Flag,Flag+N+1,false);
    for(int i=1;i<=N;++i){
        scanf("%d",Layer+i),Flag[Layer[i]] = true;
    }

    //M条边
    int a,b,w;
    for(int i=0;i<M;++i){
        scanf("%d%d%d",&a,&b,&w);
        mkEdge(a,b,w);
        mkEdge(b,a,w);
    }

    //层与层之间建边
    for(int i=1;i<N;++i)if(Flag[i]&&Flag[i+1]){
        mkEdge(N+i,N+i+1,C);
        mkEdge(N+i+1,N+i,C);
    }

    //层与点之间建边
    for(int i=1;i<=N;++i){
        //层到点建一条单向边
        mkEdge(Layer[i]+N,i,0);
        //点到相邻层建一条单向边
        if ( Layer[i] > 1 ) mkEdge(i,Layer[i]+N-1,C);
        if ( Layer[i] < N ) mkEdge(i,Layer[i]+N+1,C);
    }
}

weight_t D[SIZE_OF_VERTICES];

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        read();
        Dijkstra(1,N+N,D,Flag);
        printf("Case #%d: %d\n",kase,INF!=D[N]?D[N]:-1);
    }
}