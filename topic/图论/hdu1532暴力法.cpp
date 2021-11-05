#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define SIZE 205

typedef int weight_t;

int N,M;

//边的结构
struct edge_t{
	int node;
	weight_t c;//c为容量
	edge_t* next;
	edge_t* redge;//指向反向边
	bool isU;//正向边
}Edge[SIZE*2];
int ECnt;

//图的邻接表
edge_t* Ver[SIZE];

void init(){
	ECnt = 0;
	fill(Ver+1,Ver+M+1,(edge_t*)0);
}

//生成双向边
void mkEdge(int a,int b,weight_t c){
	int t1 = ECnt++;
	int t2 = ECnt++;

	Edge[t1].node = b;
	Edge[t1].c = c;
	Edge[t1].next = Ver[a];
	Edge[t1].redge = Edge + t2;
	Edge[t1].isU = true;
	Ver[a] = Edge + t1;

	Edge[t2].node = a;
	Edge[t2].c = 0;
	Edge[t2].next = Ver[b];
	Edge[t2].redge = Edge + t1;
	Edge[t2].isU = false;
	Ver[b] = Edge + t2;
}



bool read(){
	if ( EOF == scanf("%d%d",&N,&M) )
		return false;

	init();
	for(int i=0;i<N;++i){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		mkEdge(a,b,c);
	}
	return true;
}
bool F[SIZE];
//u当前节点,f为当前流
int dfs(int u,int f){
	if ( u == M ) return f;

	F[u] = true;
	for(edge_t*p=Ver[u];p;p=p->next){
		int v = p->node;
		if( F[v] ) continue;
		weight_t c = p->c;

		if ( c > 0 ){
			int t = dfs(v,min(c,f));
			if ( 0 == t ) continue;

			p->c -= t;
			p->redge->c += t;
			return t;
		}
	}

	return 0;
}

int solve(){
	int ret = 0;
	while(1){
		fill(F+1,F+M+1,false);
		int t = dfs(1,INT_MAX);
		if ( 0 == t ) return ret;
		ret += t;
	}
}

int main(){
	while( read() )
		printf("%d\n",solve());
	return 0;
}