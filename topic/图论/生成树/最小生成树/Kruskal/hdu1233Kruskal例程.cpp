#include <cstdio>
#include <algorithm>
using namespace std;

typedef int weight_t; 

#define SIZE 101

//并查集结构
int Father[SIZE];
void init(int n){for(int i=0;i<=n;Father[i]=i++);}
int find(int x){return Father[x]==x?x:Father[x]=find(Father[x]);}
void unite(int x,int y){Father[find(y)]=Father[find(x)];}

int N;

//边结构
struct edge_t{
	int s;
	int e;
	weight_t w;
}Edge[SIZE*SIZE/2];
int ECnt = 0;

//重载，用于边排序
bool operator < (edge_t const&lhs,edge_t const&rhs){
	if ( lhs.w != rhs.w ) return lhs.w < rhs.w;
	if ( lhs.s != rhs.s ) return lhs.s < rhs.s;
	return lhs.e < rhs.e;
}

//生成边
inline void mkEdge(int a,int b,weight_t w){
	if ( a > b ) swap(a,b);

	Edge[ECnt].s = a;
	Edge[ECnt].e = b;
	Edge[ECnt++].w = w;
}

//Kruskal算法，vn是点的数量，en是边的数量，返回MST的长度
weight_t Kruskal(int vn,int en){
	init(vn);//并查集初始化
	sort(Edge,Edge+en);//边排序

	weight_t ans = 0;
	for(int i=0;i<en;++i){
		//该边已存在于MST中
		if ( find(Edge[i].s) == find(Edge[i].e) )
			continue;

		//将该边加入MST
		ans += Edge[i].w;
		unite(Edge[i].s,Edge[i].e);
		--vn;

		//MST已完全生成
		if ( 1 == vn ) break;
	}

	return ans;
}

bool read(){
	scanf("%d",&N);
	if ( 0 == N ) return false;
	
	ECnt = 0;
	for(int i=0;i<N*(N-1)/2;++i){
		int a,b,w;
		scanf("%d%d%d",&a,&b,&w);
		mkEdge(a,b,w);
	}
	
	return true;
}

int main(){
	while( read() ){
		printf("%d\n",Kruskal(N,ECnt));
	}
	return 0;
}