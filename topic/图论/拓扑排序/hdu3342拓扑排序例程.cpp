#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef int weight_t; 

#define SIZE 101

int N,M;

//边的结构
struct edge_t{
	int node;
	weight_t w;//本题中该域无用
	edge_t* next;
}Edge[SIZE];
int ECnt;

//顶点的入度
int InDeg[SIZE];

//图的邻接表
edge_t* Ver[SIZE];

//生成有向边
inline void mkEdge(int a,int b,weight_t w=0){
	++InDeg[b];
	Edge[ECnt].node = b;
	Edge[ECnt].w = w;
	Edge[ECnt].next = Ver[a];
	Ver[a] = Edge + ECnt ++;
}

//初始化
inline void init(){
	ECnt = 0;
	fill(Ver,Ver+N,(edge_t*)0);
	fill(InDeg,InDeg+N,0);
}

//拓扑排序，返回可拓扑的点的个数
int topoSort(){
	int ret = 0;

	//保存入度为0的点
	vector<int> vec;
	for(int i=0;i<N;++i)
		if ( 0 == InDeg[i] )
			vec.push_back(i);

	//计算每一个入度为0的点
	while( !vec.empty() ){
		int u = vec.back();
		vec.pop_back();
		++ret;

		//对u的每一条出边
		for(edge_t*p=Ver[u];p;p=p->next){
			int v = p->node;
			--InDeg[v];
			if ( 0 == InDeg[v] ) vec.push_back(v);
		}
	}
	
	return ret;
}

bool read(){
	scanf("%d%d",&N,&M);
	if ( 0 == N ) return false;
	
	init();
	for(int i=0;i<M;++i){
		int a,b;
		scanf("%d%d",&a,&b);
		mkEdge(a,b);
	}
	
	return true;
}

int main(){
	while( read() ){
		printf( topoSort() == N ? "YES\n" : "NO\n" );
	}
	return 0;
}