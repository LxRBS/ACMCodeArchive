#include <cstdio>
#include <algorithm>
using namespace std;

typedef int weight_t; 

#define SIZE 205
int const INF = 4000000;

int N,M;
int S,T;

//图的邻接矩阵，也是Floyd的结果 
weight_t G[SIZE][SIZE]; 

//初始化
inline void init(){
	for(int i=0;i<N;++i){
	    fill(G[i],G[i]+N,INF);
	    G[i][i] = 0;
	}	    
}

//生成边
inline void mkEdge(int a,int b,weight_t w){
    if ( w < G[a][b] ) G[a][b] = G[b][a] = w;
}

//
void Floyd(){
	for(int k=0;k<N;++k)for(int i=0;i<N;++i)for(int j=0;j<N;++j)
	    G[i][j] = min(G[i][j],G[i][k]+G[k][j]);
}

bool read(){
	if ( EOF == scanf("%d%d",&N,&M) )
		return false;

	init();
	for(int i=0;i<M;++i){
		int a,b,w;
		scanf("%d%d%d",&a,&b,&w);
		mkEdge(a,b,w);
	}
	scanf("%d%d",&S,&T);

	return true;
}

int main(){
	while( read() ){
		Floyd();
		if ( INF == G[S][T] ) printf("-1\n");
		else printf("%d\n",G[S][T]);
	}
	return 0;
}
