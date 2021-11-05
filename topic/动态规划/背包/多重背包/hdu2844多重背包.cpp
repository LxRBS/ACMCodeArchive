#include <cstdio>
#include <numeric>
#include <algorithm>
using namespace std;
typedef int gains_t;//type of gains

//one iteration of 01 knapsack problem
//d is the result array
//maxv is the upper bound of the cost namely it is volume in classical problem
//cost is the current cost
//gains is the current gains
void zeroOneKnapsack(gains_t d[],int maxv,int cost,gains_t gains){
    for(int v=maxv;v>=cost;--v){
        d[v] = max(d[v],d[v-cost]+gains);
    }
}

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

//one iteration of multiple knapsack problem
//d is the result array
//maxv is the upper bound of the cost namely it is volume in classical problem
//cost is the current cost
//gains is the current gains
//cnt is the current available count
void multipleKnapsack(gains_t d[],int maxv,int cost,gains_t gains,int cnt){
    if ( cost * cnt >= maxv ){
        completeKnapsack(d,maxv,cost,gains);
        return;
    }

    for(int k=1;k<cnt;k<<=1){
        zeroOneKnapsack(d,maxv,k*cost,k*gains);
        cnt -= k;
    }

    zeroOneKnapsack(d,maxv,cnt*cost,cnt*gains);
}

int A[111],C[111];
int Dp[100111];
int main(){
	int n,m;
	while( scanf("%d%d",&n,&m) ){
		if ( 0 == n && 0 == m ) return 0;

		for(int i=0;i<n;++i)scanf("%d",A+i);
		for(int i=0;i<n;++i)scanf("%d",C+i);

		if ( m < 0 ){
			printf("0\n");
			continue;
		}

		fill(Dp,Dp+m+1,0);
		for(int i=0;i<n;++i)multipleKnapsack(Dp,m,A[i],A[i],C[i]);
		int ret = 0;
		for(int i=1;i<=m;++i)if(Dp[i]==i)++ret;
		printf("%d\n",ret);
	}
	return 0;
}

