//二分图的最小点覆盖等于最大匹配
#include <cstdio>
#include <cstring>
using namespace std;
#define SIZE 103
bool A[SIZE][SIZE];//二分图矩阵
int N,M,K;
void read(){
	memset(A,0,sizeof(A));
	scanf("%d%d%d",&N,&M,&K);
	for(int i=0;i<K;++i){
        double x,y;
		scanf("%lf%lf",&x,&y);
        A[(int)x+1][(int)y+1] = true;
	}
}
bool F[SIZE];
int L[SIZE] = {0};
int dfs(int node){
	//对B中的每个点
	for(int i=1;i<=M;++i){
		//如果没有边或者已在增广路上
		if ( !A[node][i] || F[i] ) continue;
		F[i] = true;
		//如果Bi尚未使用
        if ( 0 == L[i] ){
        	L[i] = node;
        	return 1;
        }

        if ( dfs(L[i]) ){
        	L[i] = node;
        	return 1;
        }
	}
	return 0;
}
int Hungary(){
	memset(L,0,sizeof(L));
	int ret = 0;
	for(int i=1;i<=N;++i){
		memset(F,0,sizeof(F));
		ret += dfs(i);
	}
	return ret;
}
int main() {
	int nofkase;
	scanf("%d",&nofkase);
	while(nofkase--){
        read();
        printf("%d\n",Hungary());
	}
	return 0;
}
