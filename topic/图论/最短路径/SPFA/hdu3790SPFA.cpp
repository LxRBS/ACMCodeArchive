#include <cstdio>
#include <climits>
#include <queue>
#include <algorithm>
using namespace std;

struct _t{
    int length;
    int price;
    _t(int a=0,int b=0):length(a),price(b){}
};
bool operator < (_t const&lhs,_t const& rhs){
    return lhs.length < rhs.length ||
        ( lhs.length == rhs.length && lhs.price < rhs.price );
}
_t operator + (_t const&lhs,_t const& rhs){
    return _t(lhs.length+rhs.length,lhs.price+rhs.price);
}

typedef _t weight_t;

#define SIZE 200005

int N,M;
int S,T;

//边的结构
struct edge_t{
	int node;
	weight_t w;
	edge_t* next;
}Edge[SIZE];
int ECnt = 0;

//图的邻接表
edge_t* Ver[1010];

//初始化
inline void init(){
	ECnt = 0;
	fill(Ver,Ver+N,(edge_t*)0);
}

//生成双向边
inline void mkEdge(int a,int b,weight_t w){
	Edge[ECnt].node = b;
	Edge[ECnt].w = w;
	Edge[ECnt].next = Ver[a];
	Ver[a] = Edge + ECnt ++;

	Edge[ECnt].node = a;
	Edge[ECnt].w = w;
	Edge[ECnt].next = Ver[b];
	Ver[b] = Edge + ECnt ++;
}

//最短路径的结果
weight_t D[1010];

//标志位
bool Flag[1010];

//spfa算法，输入保证没有负环，s为源
void spfa(int s){
	//初始化
	fill(D,D+N+1,_t(INT_MAX,INT_MAX));
	fill(Flag,Flag+N+1,false);

	//初始化源
	D[s] = _t(0,0);
	Flag[s] = true;

	//队列
	queue<int> q;
	q.push(s);

	while( !q.empty() ){
		int u = q.front();
		q.pop();
		Flag[u] = false;

		//对u的每一条边
		for(edge_t*p=Ver[u];p;p=p->next){
			int v = p->node;
			weight_t tmp = D[u] + p->w;
			if ( tmp < D[v] ){
				D[v] = tmp;
				if ( !Flag[v] )
					Flag[v] = true, q.push(v);
			}
		}
	}

	return;
}

bool read(){
    scanf("%d%d",&N,&M);
	if ( 0 == N && 0 == M )	return false;

	init();
	for(int i=0;i<M;++i){
		int a,b,w,p;
		scanf("%d%d%d%d",&a,&b,&w,&p);
		mkEdge(a,b,_t(w,p));
	}
	scanf("%d%d",&S,&T);

	return true;
}

int main(){
	while( read() ){
		spfa(S);
		printf("%d %d\n",D[T].length,D[T].price);
	}
	return 0;
}
