#include <cstdio>
#include <climits>
#include <queue>
#include <algorithm>
#include <numeric>
using namespace std;

#define SIZE 1000002
typedef unsigned long long ull;
//邻接表的边
struct edge_t{
	int node;
	int weight;
	int next;
}Edge[SIZE],AEdge[SIZE];

//邻接表
int Graph[SIZE],AGraph[SIZE];

//最短路径
int Dist[SIZE],ADist[SIZE];

//入队标识数组
bool Flag[SIZE];

//SPFA算法，1始终作为源点
void spfa(
    int const g[],   //邻接表
	edge_t const e[],//边
	int const n,     //顶点的数量
	int d[]          //最短路径
){
    fill(d,d+n+1,INT_MAX);
	d[1] = 0;

	fill(Flag,Flag+n+1,false);
	Flag[1] = true;

	queue<int> q;
	q.push(1);

	while( !q.empty() ){
        int u = q.front();
		q.pop();
		Flag[u] = false;

		int next = g[u];
		while( next ){
			int v = e[next].node;
			int tmp = d[u] + e[next].weight;
			if ( tmp < d[v] ){
				d[v] = tmp;
				if ( !Flag[v] ) q.push(v),Flag[v] = true;
			}
			next = e[next].next;
		}
	}
	return;
}

int main(){
	int kase;
	scanf("%d",&kase);
	while(kase--){
		int p,q;
		scanf("%d%d",&p,&q);

		fill(Graph,Graph+p+1,0);
		fill(AGraph,AGraph+p+1,0);

		//正反双向建图
		for(int i=1;i<=q;++i){
			int a,b,w;
			scanf("%d%d%d",&a,&b,&w);

			Edge[i].node = b;
			Edge[i].weight = w;
			Edge[i].next = Graph[a];
			Graph[a] = i;

			AEdge[i].node = a;
			AEdge[i].weight = w;
			AEdge[i].next = AGraph[b];
			AGraph[b] = i;
		}

		spfa(Graph,Edge,p,Dist);
		spfa(AGraph,AEdge,p,ADist);

		ull ans = accumulate(Dist+2,Dist+p+1,0ULL);
		printf("%I64u\n",accumulate(ADist+2,ADist+p+1,ans));
	}
	return 0;
}