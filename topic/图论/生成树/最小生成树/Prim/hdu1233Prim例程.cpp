#include <cstdio>
#include <algorithm>
using namespace std;

typedef int weight_t; 

#define SIZE 101

int N;

//图的邻接矩阵
weight_t Graph[SIZE][SIZE];

//各顶点到中间结果的最短距离，始终维护
weight_t D[SIZE];

//标志位
bool Flag[SIZE];

//Prim算法，返回MST的长度
weight_t Prim(){
	//初始化数组
	fill(D,D+SIZE,INT_MAX);
	fill(Flag,Flag+SIZE,false);

	//初始化第一个计算的点
	D[1] = 0;

	weight_t ans = 0;

	for(int i=1;i<=N;++i){
		//找出距离中间结果最近的点
		int k = -1;
		for(int j=1;j<=N;++j)
			if ( !Flag[j] && ( -1 == k || D[j] < D[k] ) )
				k = j;

		//将k点加入中间结果
		Flag[k] = true;
		ans += D[k];

		//更新剩余点到中间结果的最短距离
		for(int j=1;j<=N;++j)
			if ( !Flag[j] && Graph[k][j] < D[j] )
				D[j] = Graph[k][j];
	}

	return ans;
}

bool read(){
	scanf("%d",&N);
	if ( 0 == N ) return false;
	
	for(int i=0;i<N*(N-1)/2;++i){
		int a,b,w;
		scanf("%d%d%d",&a,&b,&w);
		Graph[a][b] = Graph[b][a] = w;
	}
	
	return true;
}

int main(){
	while( read() ){
		printf("%d\n",Prim());
	}
	return 0;
}