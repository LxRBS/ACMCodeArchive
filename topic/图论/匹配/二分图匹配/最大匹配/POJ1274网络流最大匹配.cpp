//网络流解决二分图最大匹配
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define SIZE 405

typedef int weight_t;

int N,M;

//边结构
struct edge_t{
	int node;
	weight_t w;
	edge_t* next;
}Edge[SIZE*200];
int ECnt;

//邻接表
edge_t* Ver[SIZE];

void init(){
	ECnt = 0;
	fill(Ver,Ver+N+M+2,(edge_t*)0);
}

//生成双向边
void mkEdge(int a,int b,weight_t w){
	Edge[ECnt].node = b;
	Edge[ECnt].w = w;
	Edge[ECnt].next = Ver[a];
	Ver[a] = Edge + ECnt ++;

	Edge[ECnt].node = a;
	Edge[ECnt].w = 0;
	Edge[ECnt].next = Ver[b];
	Ver[b] = Edge + ECnt ++;
}

//获取反向边
inline edge_t* neg(edge_t* p){
	return Edge + ( ( p - Edge ) ^ 1 );
}


//层次图
int L[SIZE];

//建立层次图,s为源，t为汇
bool bfs(int s,int t){
	fill(L,L+N+M+2,-1);

	vector<int> q;
	q.push_back(s);
	L[s] = 0;

	while( !q.empty() ){
		int u = q.back();
		q.pop_back();

		for(edge_t*p=Ver[u];p;p=p->next){
			if ( p->w <= 0 || -1 != L[p->node] ) continue;

			q.push_back(p->node);
			L[p->node] = L[u] + 1;
		}
	}

	return -1 != L[t];
}

//在层次图上搜索增广路径
int dfs(int u,int cf,int t){
	if ( u == t ) return cf;

	int tf = 0;
	for(edge_t*p=Ver[u];p;p=p->next){
		int v = p->node;
		weight_t w = p->w;

		if ( L[u]+1 == L[v] && w > 0 && cf > tf ){
			int f = dfs(v,min(w,cf-tf),t);
			if ( 0 == f ) continue;

			p->w -= f;
			neg(p)->w += f;
			tf += f;
		}
	}
	if ( 0 == tf ) L[u] = -1;
	return tf;
}

//Dinic算法，s为源，t为汇
int Dinic(int s,int t){
	int ret = 0;
	while( bfs(s,t) ){
		int res;
		while( res = dfs(s,INT_MAX,t) )
			ret += res;
	}
	return ret;
}

bool read(){
	if ( EOF == scanf("%d%d",&N,&M) )
		return false;

	init();
	for(int i=1;i<=N;++i){
		int n;
		scanf("%d",&n);
		for(int j=0;j<n;++j){
			int x;
			scanf("%d",&x);
			mkEdge(i,N+x,1);
		}
	}

	//源点到左半部建立边
	for(int i=1;i<=N;++i)
		mkEdge(0,i,1);

	//右半部到汇点建立边
	for(int i=1;i<=M;++i)
		mkEdge(N+i,N+M+1,1);

	return true;
}

int main(){
	while( read() ) 
		printf("%d\n",Dinic(0,N+M+1));
	return 0;
}