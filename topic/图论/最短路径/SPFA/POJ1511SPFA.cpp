#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

typedef unsigned long long ull;

#define SIZE 1000002

struct _t{
	int node;
	int weight;
	int next;
	_t(int a=0,int b=0,int c=0):node(a),weight(b),next(c){}
}Edge[SIZE],AntiEdge[SIZE];

int Graph[SIZE]; //图，邻接矩阵

int AntiGraph[SIZE]; 

ull Dist[SIZE];
ull AntiDist[SIZE];
bool Flag[SIZE];

int Queue[SIZE]; //模拟双端队列
int QHead,QTail; //头尾，左闭右开
int QSize;

//SPFA算法，g为图，e为边，s为源,p为节点个数，dist为距离
//使用SLF和LLL优化
void spfa(int const g[],_t const e[],int s,int p,ull dist[]){
    fill(dist+1,dist+p+1,0xFFFFFFFFFFF);
	dist[s] = 0;
	fill(Flag+1,Flag+p+1,false);
	Flag[s] = true;

	QHead = QTail = QSize = 0;
    Queue[QTail++] = s;
	++QSize;

	//队列和值
	ull sum = 0ULL;	

	while( QHead != QTail ){
		int u = Queue[QHead];
		++QHead;
		if ( QHead > SIZE ) QHead -= SIZE;
		
		//LLL优化
		while ( dist[u] * QSize > sum ){
			Queue[QTail++] = u;
			if ( QTail > SIZE ) QTail -= SIZE;

			u = Queue[QHead];	

			++QHead;
			if ( QHead > SIZE ) QHead -= SIZE;
		} 

		Flag[u] = false;
		sum -= dist[u];
		--QSize;

		if ( 0 == g[u] ) continue;
		
		int next = g[u];
		while(next){
            int v = e[next].node;
            ull tmp = dist[u] + (ull)e[next].weight;
			if ( tmp < dist[v] ){
				if ( Flag[v] ){
					sum = sum - dist[v] + tmp;
				}else{
					sum = sum + tmp;
				}
				dist[v] = tmp;
				if ( !Flag[v] ){
					//SLF优化
					if ( dist[v] < dist[u] ) {
					    --QHead;
						if ( QHead < 0 ) QHead += SIZE;
						Queue[QHead] = v;
					}else{
						Queue[QTail++] = v;
						if ( QTail > SIZE ) QTail -= SIZE;//队列不会满
					}
//					Queue[QTail++] = v;
					++QSize;					
					Flag[v] = true;					
				}
			}
			next = e[next].next;
		}
	}
}

int main(){
	int kase;
	scanf("%d",&kase);
	while(kase--){
		int p,q;
		scanf("%d%d",&p,&q);

		fill(Graph,Graph+p+1,0);
		fill(AntiGraph,AntiGraph+p+1,0);
        
		for(int i=1;i<=q;++i){
			int a,b,w;
			scanf("%d%d%d",&a,&b,&w);

			Edge[i].node = b;
			Edge[i].weight = w;
			Edge[i].next = Graph[a];
			Graph[a] = i;

			AntiEdge[i].node = a;
			AntiEdge[i].weight = w;
			AntiEdge[i].next = AntiGraph[b];
			AntiGraph[b] = i;
		}

		spfa(Graph,Edge,1,p,Dist);
		spfa(AntiGraph,AntiEdge,1,p,AntiDist);
		ull ans = accumulate(Dist+2,Dist+p+1,0ULL);
		ans = accumulate(AntiDist+2,AntiDist+p+1,ans);
        printf("%I64u\n",ans);
	}
	return 0;
}