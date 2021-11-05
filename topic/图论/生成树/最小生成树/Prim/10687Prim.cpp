//稠密图的Prim算法 
#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;
#define SIZE 2001
int Graph[SIZE][SIZE];

int Dist[SIZE];//用于保存每个顶点到中间结果的最小长度
bool Flag[SIZE];//标记数组

//Prim算法，n表示顶点的个数，返回MST的长度
int Prim(int n){
    fill(Dist,Dist+n,INT_MAX);
	Dist[0] = 0;

	fill(Flag,Flag+n,false);

	int ret = 0;
	for(int i=0;i<n;++i){
		int k = -1;
		//找出未标记顶点中距离中间结果最近的点
		for(int j=0;j<n;++j){
			if ( !Flag[j] && ( -1 == k || Dist[j] < Dist[k] ) )
				k = j;
		}
		Flag[k] = true;
		ret += Dist[k];

		//更新中间结果距离
		for(int j=0;j<n;++j)
			if ( !Flag[j] && Graph[k][j] < Dist[j] )
				Dist[j] = Graph[k][j];
	}
	return ret;
}
char Str[SIZE][8];
int fun(int x,int y){
	int ret = 0;
	for(int i=0;i<7;++i)
		if ( Str[x][i] != Str[y][i] )
			++ret;
	return ret;
}
int main(){
	int n;
	while( scanf("%d",&n) && n ){
        for(int i=0;i<n;++i)scanf("%s",Str[i]);
		for(int i=0;i<n-1;++i){
			Graph[i][i] = 0;
			for(int j=i+1;j<n;++j)
			    Graph[i][j] = Graph[j][i] = fun(i,j);
		}
		printf("The highest possible quality is 1/%d.\n",Prim(n));
	}
	return 0;
}