
#include <cstdio>
#include <algorithm>
using namespace std;

#define SIZE 505

typedef bool weight_t;

int N,M;//A、B中点的数量
int K;

weight_t G[SIZE][SIZE]; //二分图矩阵
int L[SIZE];//L[i]为A中与Bi匹配的点，Bi尚未匹配则为0
bool F[SIZE];//F[i]表示Bi是否已在增广路上，在一次搜索中

void init(){
	for(int i=0;i<=N;++i)
		fill(G[i],G[i]+M+1,false);
	fill(L,L+M+1,0);
}

//dfs实现匈牙利算法，node为节点编号，A中的节点
bool dfs(int node){
	for(int i=1;i<=M;++i){
		//如果没有边或已在增广路上
		if ( !G[node][i] || F[i] ) continue;
		F[i] = true;

		//如果Bi尚未使用过，则此为单边交错轨
		if ( 0 == L[i] ){
			L[i] = node;
			return true;
		}

		//如果Bi已经使用过，则去搜索与其连接的A中的点
		if ( dfs(L[i]) ){
			L[i] = node;//相当于交换
			return true;
		}
	}
	return false;
}

int Hungary(){
	int ret = 0;
	for(int i=1;i<=N;++i){
		fill(F+1,F+M+1,false);//每次搜索均要清空
		if ( dfs(i) ) ++ret;
	}
	return ret;
}

bool read(){
	scanf("%d",&K);
	if ( 0 == K ) return false;

	scanf("%d%d",&N,&M);
	init();

	for(int i=0;i<K;++i){
		int a,b;
		scanf("%d%d",&a,&b);
		G[a][b] = true;
	}
	return true;
}

int main(){
	while( read() ) printf("%d\n",Hungary());
	return 0;
}
