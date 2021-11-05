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
	Ver[a] = Edge + t1;

	Edge[t2].node = a;
	Edge[t2].c = 0;
	Edge[t2].next = Ver[b];
	Edge[t2].redge = Edge + t1;
	Ver[b] = Edge + t2;
}

int L[SIZE];//层次图

//建立残留网络从源s到汇t的层次图
bool bfs(int s,int t){
	fill(L+1,L+M+1,-1);
	vector<int> q;
	q.push_back(s);
	L[s] = 0;

	while( !q.empty() ){
		int u = q.back();
		q.pop_back();
		
		//寻找还有残量的边
		for(edge_t*p=Ver[u];p;p=p->next){
			if ( p->c <= 0 ) continue;

			int v = p->node;
			if ( -1 != L[v] ) continue;

			q.push_back(v);
			L[v] = L[u] + 1;
		}
	}

	return -1 != L[t];
}

//在层次图上搜索增广路径，本质上就是搜索可以增广的流量
//这个流量是各层之间流量的最小值
//u为当前节点，cf为已经搜索出的结果，t为汇点
int dfs(int u,int cf,int t){
	if ( u == t ) return cf;

	int tf = 0;//tf记录u往下一层的总可行流量
	for(edge_t*p=Ver[u];p;p=p->next){
		int v = p->node;
		weight_t c = p->c;

		if ( L[u] + 1 == L[v] && c > 0 && cf > tf ){
			int f = dfs(v,min(c,cf-tf),t);
			if ( 0 == f ) continue;

			p->c -= f;//正向边减去可行流量
			p->redge->c += f;//反向边加上
			tf += f;
		}
	}
	if ( 0 == tf ) L[u] = -1;//修改层次图
	return tf;
}

//Dinic算法，s为源，t为汇
int Dinic(int s,int t){
	int ret = 0;
	while( bfs(s,t) ){//第一步建立分层图
		int ans;
		//第二步在分层图上查找一条增广路径的可行流量
		while( ans = dfs(s,INT_MAX,t) )
			ret += ans;
	}
	return ret;
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

int main(){
	while( read() )
		printf("%d\n",Dinic(1,M));
	return 0;
}