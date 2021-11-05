#include <cstdio>
#include <algorithm>
using namespace std;
#define SIZE 10000003

int Graph[27][27];

int Dist[27];
bool Flag[27];

//Prim算法，n表示顶点个数
int Prim(int n){
    fill(Dist,Dist+n,INT_MAX);
	Dist[0] = 0;
    fill(Flag,Flag+n,false);

	int ret = 0;
	for(int i=0;i<n;++i){
		int k = -1;
		for(int j=0;j<n;++j){
			if( !Flag[j] && ( -1==k || Dist[j] < Dist[k] ) )
				k = j;
		}

		Flag[k] = true;
		ret += Dist[k];

		for(int j=0;j<n;++j){
			if ( !Flag[j] && Graph[k][j] && Dist[j] > Graph[k][j] )
				Dist[j] = Graph[k][j];
		}
	}
    return ret;
}
int main(){
    int n;
	while( scanf("%d%*c",&n) && n ){
		memset(Graph,0,sizeof(Graph));

		for(int i=0;i<n-1;++i){
			char ch;
			int k;
			scanf("%c%*c%d%*c",&ch,&k);
			for(int j=0;j<k;++j){
				char cc;
				int w;
				scanf("%c%*c%d%*c",&cc,&w);
                Graph[i][cc-'A'] = Graph[cc-'A'][i] = w;                
			}
		}
		printf("%d\n",Prim(n));
	}
	return 0;
}