#include <cstdio>
#include <numeric>
#include <algorithm>
using namespace std;
typedef int gains_t;//type of gains

//one iteration of complete knapsack problem
//d is the result array
//maxv is the upper bound of the cost namely it is volume in classical problem
//cost is the current cost
//gains is the current gains
void completeKnapsack(gains_t d[],int maxv,int cost,gains_t gains){
    for(int v=cost;v<=maxv;++v){
        d[v] = max(d[v],d[v-cost]+gains);
    }
}

int N,M;
int Gains[5005],Cost[5005];
int Dp[10005];
inline bool read(){
	double x;
	scanf("%d%lf",&N,&x);
	M = static_cast<int>( 100.0 * x + 0.5 );
	if ( 0 == N && 0 == M ) return false;
	for(int i=0;i<N;++i){
		scanf("%d%lf",Gains+i,&x);
	    Cost[i] = static_cast<int>( 100.0 * x + 0.5 );
	}
	return true;
}
int main(){
	while( read() ){
		fill(Dp,Dp+M+1,0);
		for(int i=0;i<N;++i)completeKnapsack(Dp,M,Cost[i],Gains[i]);
		printf("%d\n",Dp[M]);
	}
	return 0;
}

