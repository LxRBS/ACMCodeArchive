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

int Cost[1001],Gains[1001];
int Dp[1001];
int main(){
	int nofkase;
	scanf("%d",&nofkase);
	while(nofkase--){
		int n,v;
		scanf("%d%d",&n,&v);
		for(int i=0;i<n;++i)scanf("%d",Gains+i);
		for(int i=0;i<n;++i)scanf("%d",Cost+i);

		fill(Dp,Dp+v+1,0);
		for(int i=0;i<n;++i)
			zeroOneKnapsack(Dp,v,Cost[i],Gains[i]);

        printf("%d\n",Dp[v]);
	}
	return 0;
}

