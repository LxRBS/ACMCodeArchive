#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef int weight_t; 

#define SIZE 1005

int N,X,Y;

//边的结构
struct edge_t{
	int node;
	weight_t w;
	edge_t* next;
}Edge[SIZE*21];
int ECnt;

//图的邻接表
edge_t* Ver[SIZE];

//建立有向边
inline void mkEdge(int a,int b,weight_t w){
	Edge[ECnt].node = b;
	Edge[ECnt].w = w;
	Edge[ECnt].next = Ver[a];
	Ver[a] = Edge + ECnt ++;
}

//初始化
inline void init(){
	ECnt = 0;
	fill(Ver,Ver+N+1,(edge_t*)0);
}

//最短路的结果
weight_t D[SIZE];

//标志位
bool Flag[SIZE];

//入队次数
int Cnt[SIZE];

//可检查负环的SPFA，s为源
bool spfa(int s){
	//初始化数组
	fill(D,D+N+1,INT_MAX);
	fill(Flag,Flag+N+1,false);
	fill(Cnt,Cnt+N+1,0);

	//初始化源
	D[s] = 0;
	Flag[s] = true;
	Cnt[s] = 1;

	vector<int> q;
	q.push_back(s);

	while( !q.empty() ){
		int u = q.back();
		q.pop_back();
		Flag[u] = false;

		//对u的每一个出边
		for(edge_t*p=Ver[u];p;p=p->next){
			int v = p->node;
			weight_t tmp = D[u] + p->w;
			if ( tmp < D[v] ){
				D[v] = tmp;
				if ( !Flag[v] )
					Flag[v] = true, q.push_back(v), ++Cnt[v];
				//该图共有N+1个点
				if ( Cnt[v] > N + 1 ) return false;
			}
		}
	}
	return true;
}

void read(){
	scanf("%d%d%d",&N,&X,&Y);
	
	init();

	//相当于不等式b-a<=c
	for(int i=0;i<X;++i){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		mkEdge(a,b,c);
	}

	//相当于不等式b-a>=c，即a-b<=-c
	for(int i=0;i<Y;++i){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		mkEdge(b,a,-c);
	}

	//建立0点到其他节点的边
	for(int i=1;i<=N;++i)
		mkEdge(0,i,0);
	
	return;
}

int main(){
	int nofkase;
	scanf("%d",&nofkase);
	while( nofkase-- ){
		read();
		if ( spfa(1) ){
			if ( INT_MAX == D[N] ) printf("-2\n");
			else printf("%d\n",D[N]);
		}else{//存在负环，不等式组无解
			printf("-1\n");
		}
	}
	return 0;
}