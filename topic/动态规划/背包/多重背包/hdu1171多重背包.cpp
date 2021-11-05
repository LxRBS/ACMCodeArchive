//一堆数，要求尽可能的平均分成2组
//背包，数值本身既是代价又是收益
//令所有数的和为S，看D[S/2]是多少

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

int A[50],C[50];
int Dp[125002];
int main(){
	int n;
	while( scanf("%d",&n) && n>=0 ){
        for(int i=1;i<=n;++i) scanf("%d%d",A+i,C+i);
        int sum = inner_product(A+1,A+n+1,C+1,0);
        fill(Dp,Dp+(sum>>1)+1,0);
		for(int i=1;i<=n;++i)multipleKnapsack(Dp,sum>>1,A[i],A[i],C[i]);
	    printf("%d %d\n",sum-Dp[sum>>1],Dp[sum>>1]);
	}
	return 0;
}

