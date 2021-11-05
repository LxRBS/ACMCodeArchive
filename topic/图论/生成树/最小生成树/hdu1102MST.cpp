//已经存在一些边, 构造MST 

#include <cstdio>
#include <algorithm>
using namespace std;

int const SIZE = 105;

//并查集 
int Father[SIZE];
void init(int n){
	for(int i=0;i<=n;++i)Father[i]=i;
}
int find(int x){
	return x == Father[x] ? x : Father[x] = find(Father[x]);
}
void unite(int x,int y){
	Father[find(y)] = find(x);
}

//边 
struct edge_t{
	int a,b;
	int w;
}Edge[5005];
int ECnt = 0;
bool operator < (edge_t const&l,edge_t const&r){
	return l.w < r.w || ( l.w == r.w && l.a < r.a ) || ( l.w == r.w && l.a == r.a && l.b < r.b );
}

void mkEdge(int a,int b,int w){
	Edge[ECnt].a = a;
	Edge[ECnt].b = b;
	Edge[ECnt++].w = w;
}

int N,K;
bool read(){
	if ( EOF == scanf("%d",&N) ) return false;
	ECnt = 0;
	init(N);
	for(int i=1;i<=N;++i){
		for(int j=1;j<=N;++j){
			int w;
			scanf("%d",&w);
			if ( i < j ) mkEdge(i,j,w);
		}
	}
	int Q;
	scanf("%d",&Q);
	K = 1;
	for(int i=0;i<Q;++i){
		int a,b;
		scanf("%d%d",&a,&b);
		if ( find(a) == find(b) ) continue;
		unite(a,b);
		++K;
	}
	return true;
}
int Kruskal(){
	sort(Edge,Edge+ECnt);

    int ret = 0;
	for(int i=0;i<ECnt;++i){
		if ( find(Edge[i].a) == find(Edge[i].b) ) continue;
		
		unite(Edge[i].a,Edge[i].b);
		ret += Edge[i].w;
		++K;
		if ( K == N ) break;
	}
	return ret;
}
int main(){
	while( read() ) printf("%d\n",Kruskal());
}
