#include <cstdio>
#include <numeric>
#include <algorithm>
using namespace std;
typedef unsigned gains_t;//type of gains

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

unsigned Cost[101],Gains[101];
unsigned Dp[10001];
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		unsigned n,x;
		scanf("%u%u",&n,&x);
		for(int i=0;i<n;++i)scanf("%u",Gains+i);
		for(int i=0;i<n;++i)scanf("%u",Cost+i);

		fill(Dp,Dp+x+1,0);
		for(int i=0;i<n;++i)completeKnapsack(Dp,x,Cost[i],Gains[i]);
	    printf("%u\n",Dp[x]);
	}
}

