//标准的01背包
#include <cstdio>
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

int N,M;
int Cost[3500],Gain[3500];
int D[12900];
int main(){
    scanf("%d%d",&N,&M);

    int totalCost = 0;
    for(int i=0;i<N;++i)scanf("%d%d",Cost+i,Gain+i),totalCost+=Cost[i];

    if ( totalCost > M ) totalCost = M;
    fill(D,D+totalCost+1,0);

    for(int i=0;i<N;++i)zeroOneKnapsack(D,totalCost,Cost[i],Gain[i]);
    while( 0 == D[totalCost] ) --totalCost;
    printf("%d\n",D[totalCost]);
    return 0;
}
