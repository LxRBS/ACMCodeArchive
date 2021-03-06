//给定一个无向图，要从1点到N点再返回1点，每条边最多走一次，问最短需要走多远
//题目给出了N个点、M条边, 边的容量均为1 
//添加一个源、连接1点、容量为2
//添加一个汇, N点到汇，容量为2 
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

typedef int capa_t;
typedef int cost_t;

#define SIZE 1010

int N,M;

//边
struct edge_t{
	int s;//起点
	int e;//终点
	capa_t capa;//容量
	cost_t cost;//费用
	edge_t* next;
}Edge[SIZE*40];
int ECnt;

//图
edge_t* Ver[SIZE];

void init(){
	ECnt = 0;
	fill(Ver,Ver+N+2,(edge_t*)0);
}
//建立边
void mkEdge(int a,int b,capa_t capa,cost_t cost){
	Edge[ECnt].s = a;
	Edge[ECnt].e = b;
	Edge[ECnt].capa = capa;
	Edge[ECnt].cost = cost;
	Edge[ECnt].next = Ver[a];
	Ver[a] = Edge + ECnt ++;

	Edge[ECnt].s = b;
	Edge[ECnt].e = a;
	Edge[ECnt].capa = 0;
	Edge[ECnt].cost = -cost;
	Edge[ECnt].next = Ver[b];
	Ver[b] = Edge + ECnt ++;
}

inline edge_t* neg(edge_t* p){
	return Edge + ( ( p - Edge ) ^ 1 );
}

cost_t D[SIZE];
bool Flag[SIZE];
edge_t* Pre[SIZE];//边，通过该数组可以还原最短路径
//SPFA算法，使用cost作为权值来衡量最短路径
void spfa(int s){
	fill(D,D+N+2,INT_MAX);
	fill(Flag,Flag+N+2,false);
	fill(Pre,Pre+N+2,(edge_t*)0);

	D[s] = 0;
	Flag[s] = true;

	queue<int> q;
	q.push(s);

	while( !q.empty() ){
		int u = q.front();
		q.pop();
		Flag[u] = false;

		for(edge_t*p=Ver[u];p;p=p->next){
			if ( p->capa <= 0 ) continue;
			int v = p->e;
			cost_t tmp = D[u] + p->cost;
			if ( tmp < D[v] ){
				D[v] = tmp;
				Pre[v] = p;
				if ( !Flag[v] )
					q.push(v), Flag[v] = true;
			}
		}
	}
}

//最小费用最大流，s为源，t为汇
int mcmf(int s,int t){
    int miniCost = 0;

	while(1){
		spfa(s);
		//说明找不到增广路
		if ( INT_MAX == D[t] ) break;

		//找出该增广路的可行流
		int flow = INT_MAX;
		for(edge_t*p=Pre[t];p;p=Pre[p->s])
			if ( flow > p->capa )
				flow = p->capa;

		//更新该网络
		for(edge_t*p=Pre[t];p;p=Pre[p->s]){
			p->capa -= flow;
			neg(p)->capa += flow;
		}

            //更新费用
		miniCost += D[t] * flow;
	}
	return miniCost;
}

bool read(){
	if ( EOF == scanf("%d%d",&N,&M) )
		return false;

	init();
	for(int i=0;i<M;++i){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		mkEdge(a,b,1,c);
		mkEdge(b,a,1,c);
	}
    //建立源到1的边
	mkEdge(0,1,2,0);
	//建立N到汇的边
	mkEdge(N,N+1,2,0);

	return true;
}

int main(){
	while( read() )
		printf("%d\n",mcmf(0,N+1));
	return 0;
}
