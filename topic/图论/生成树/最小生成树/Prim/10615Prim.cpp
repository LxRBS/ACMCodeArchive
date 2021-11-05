#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;
#define SIZE 505

int Graph[SIZE][SIZE];

int Dist[SIZE];
bool Flag[SIZE];

//Prim算法，n是顶点的个数
int Prim(int n){
    fill(Dist,Dist+n,INT_MAX);
	Dist[0] = 0;
	fill(Flag,Flag+n,false);

	int ans = 0;
	for(int i=0;i<n;++i){
        int k = -1;
		for(int j=0;j<n;++j)
		    if ( !Flag[j] && (-1==k || Dist[j]<Dist[k]) )
			    k = j;

		Flag[k] = true;
		if ( Dist[k] > ans ) ans = Dist[k];

		//更新
		for(int j=0;j<n;++j)
			if ( !Flag[j] && Graph[k][j] < Dist[j] )
				Dist[j] = Graph[k][j];
	}
	return ans;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i)for(int j=0;j<n;++j)
		scanf("%d",Graph[i]+j);
	printf("%d\n",Prim(n));
	return 0;
}