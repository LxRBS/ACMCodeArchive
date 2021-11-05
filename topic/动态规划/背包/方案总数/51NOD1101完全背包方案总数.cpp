#include <stdio.h>

typedef long long llt;

llt const MOD = 1000000007LL;
int const Cost[] = {1,2,5,10,20,50,100,200,500,1000,2000,5000,10000};

//one iteration of complete knapsack problem
//d is the result array
//maxv is the upper bound of the cost namely it is volume in classical problem
//cost is the current cost
void completeKnapsack(llt d[],int maxv,int cost){
    for(int v=cost;v<=maxv;++v){
        d[v] = ( d[v] + d[v-cost] ) % MOD;
    }
}

llt D[100100] = {1LL,0LL};
int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<13;++i) completeKnapsack(D,n,Cost[i]);
    printf("%lld\n",D[n]);
    return 0;
}
