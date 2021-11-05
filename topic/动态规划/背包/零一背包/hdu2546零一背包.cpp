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


int A[1000];
int Dp[50002];
int main(){
	int n;
	while( scanf("%d",&n) && n ){
		for(int i=0;i<n;++i)scanf("%d",A+i);
		sort(A,A+n);
		int m;
		scanf("%d",&m);
		if ( m < 5 ){
			printf("%d\n",m);
			continue;
		}
		int sum = accumulate(A,A+n,0);
		if ( sum <= m ){
			printf("%d\n",m-sum);
			continue;
		}
		fill(Dp,Dp+m-4,0);
		for(int i=0;i<n-1;++i)zeroOneKnapsack(Dp,m-5,A[i],A[i]);
		printf("%d\n",m-Dp[m-5]-A[n-1]);
	}
	return 0;
}

