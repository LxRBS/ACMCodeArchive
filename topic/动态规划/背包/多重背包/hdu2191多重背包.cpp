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

int Cost[101],Gains[101],Cnt[101];
int Dp[2002];
int main(){
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i=0;i<m;++i)scanf("%d%d%d",Cost+i,Gains+i,Cnt+i);
        fill(Dp,Dp+n+1,0);
        for(int i=0;i<m;++i)multipleKnapsack(Dp,n,Cost[i],Gains[i],Cnt[i]);
        printf("%d\n",Dp[n]);
    }
    return 0;
}

