//求MST的长度 
#include <cstdio>
#include <algorithm>
using namespace std;

#define SIZE 105

//并查集
int Father[SIZE];
void init(int n){for(int i=0;i<n;++i)Father[i]=i;} 
int find(int x){return x==Father[x]?x:Father[x]=find(Father[x]);}
void unite(int x,int y){Father[find(y)]=find(x);}

struct edge_t{
	int a;
	int b;
	int w;
}Edge[SIZE*SIZE];
int ECnt;

bool operator < (edge_t const&l,edge_t const&r){
	return l.w < r.w || ( l.w == r.w && l.a < r.a )
	    || ( l.w == r.w && l.a == r.a && l.b < r.b );
}

//此处只要加一条边即可 
void mkEdge(int a,int b,int w){
	Edge[ECnt].a = a;
	Edge[ECnt].b = b;
	Edge[ECnt++].w = w;
}

bool Flag[SIZE];
//vn表示顶点个数, en表示边的个数 
int Kruskal(int vn,int en){
	init(vn);
    sort(Edge,Edge+en);
	
	int ret = 0;
	int cnt = 0;
	for(int i=0;i<en;++i){
	    if ( find(Edge[i].a) == find(Edge[i].b) )continue;
	    
	    unite(Edge[i].a,Edge[i].b);
	    ret += Edge[i].w;
	    ++cnt;
	    if ( vn - 1 == cnt ) break;
	}      
	return ret;
}

int main(){
	int n;

	while( EOF != scanf("%d",&n) ){
		ECnt = 0;
        for(int i=0;i<n;i++)for(int j=0;j<n;j++){
        	int w;
        	scanf("%d",&w);
        	if ( i != j ) mkEdge(i,j,w);
		}
			
        printf("%d\n",Kruskal(n,ECnt));
	}

	return 0;
}

