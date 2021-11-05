#include <cstdio>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

struct edge_t{
    int u;//节点
	int c;//容量
	edge_t* next;
}Edge[40000];
int ECnt;
edge_t* Ver[201];

int N,M;
int L[201];//层次图

//求负向边，总是和正向边相邻
inline edge_t* neg(edge_t* p){return Edge + ( ( p - Edge ) ^ 1 );}

//建立层次图,s为源点，t为汇点
bool bfs(int s,int t){
	fill(L,L+M+1,-1);
	queue<int> q;
	q.push(s);
	L[s] = 0;

	while( !q.empty() ){
		int u = q.front();
		q.pop();

		for(edge_t* p=Ver[u];p;p=p->next){
			int v = p->u;
			int c = p->c;
			if ( -1 == L[v] && c > 0 )
				q.push(v), L[v] = L[u] + 1;
		}
	}
	return -1 != L[t];
}
//在层次图上搜索增广路,cf为当前层的流，t是汇点
int dfs(int u,int cf,int t){
	if ( u == t ) return cf;
      int tf = 0;//为u往下一层的总可行流
	for(edge_t*p=Ver[u];p;p=p->next){
		int v = p->u;
		int c = p->c;
		if ( L[u]+1==L[v] && c>0 && cf > tf ){
			int f = dfs(v,min(c,cf-tf),t);
		    if ( 0 == f ) continue;

			p->c -= f;//正向边减去流量
			neg(p)->c += f;//负向边
                  tf += f;
		}
	}
      if ( 0 == tf ) L[u] = -1;//修改层次图，u不必再搜
	return tf;
}
//Dinic算法
int Dinic(){
	int ret = 0;
	while( bfs(1,M) ){//第一步bfs建分层图
		int res;//第二步dfs在分层图上搜索增广路
		while( res = dfs(1,INT_MAX,M) )
			ret += res;
	}
	return ret;
}
void mkEdge(int s,int e,int c){
	Edge[ECnt].u = e;
	Edge[ECnt].c = c;
	Edge[ECnt].next = Ver[s];
	Ver[s] = Edge + ECnt ++;

	Edge[ECnt].u = s;
	Edge[ECnt].c = 0;
	Edge[ECnt].next = Ver[e];
	Ver[e] = Edge + ECnt ++;
}
bool read(){
	if ( EOF == scanf("%d%d",&N,&M) )return false;
	
	fill(Ver,Ver+N+1,(edge_t*)0);
	ECnt = 0;
	
	for(int i=0;i<N;++i){
        int s,e,c;
		scanf("%d%d%d",&s,&e,&c);
		mkEdge(s,e,c);
	}
	return true;
}
int main(){
	while( read() ) printf("%d\n",Dinic());
	return 0;
}