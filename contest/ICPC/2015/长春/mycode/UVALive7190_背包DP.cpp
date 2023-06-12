/*
  给定度数到收益的映射
  要求构造一棵树，使得收益最大

  例如3节点的树，必然2个1度、1个2度，所以收益是固定的
  但是4节点树，可以3个1度、1个3度，也可以2个2度、2个1度，收益有变化。

  N节点的树，所有点的度数和必然是2N-2，
  每个度数的收益是已知的，要求在总和一定下的最大收益，背包
  但不能直接用多重包，因为必须有1度的点
  所以将代价看作是N-2，相当于每个点的度数至少是1，
  然后将剩余的度往各处分配，这样出来的分配方案必然合法
  直接用完全背包即可
*/
#include <bits/stdc++.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

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

int Gain[3300];
int N;
int D[5500];

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        for(int i=1;i<N;++i) Gain[i] = getUnsigned();

        fill(D,D+N,-2000000000);
        D[0] = 0;
        for(int i=2;i<N;++i)completeKnapsack(D,N-2,i-1,Gain[i]-Gain[1]);
        printf("%d\n",D[N-2]+N*Gain[1]);
    }
    return 0;
}

