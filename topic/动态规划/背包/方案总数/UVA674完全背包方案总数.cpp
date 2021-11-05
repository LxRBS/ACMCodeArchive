//完全背包的方案总数
#include <cstdio>
#include <algorithm>
using namespace std;

int C[] = {1,5,10,25,50};
int D[7500];//滚动数组

typedef int gains_t;
//one iteration of complete knapsack problem
//d is the result array
//maxv is the upper bound of the cost namely it is volume in classical problem
//cost is the current cost
void completeKnapsack(gains_t d[],int maxv,int cost){
    for(int v=cost;v<=maxv;++v){
        d[v] = d[v] + d[v-cost];//把标准完全背包修改一下即可
    }
}

void init(){
    D[0] = 1;
    for(int i=0;i<5;++i) completeKnapsack(D,7500,C[i]);
}
int main(){
    init();

    int n;
    while( EOF != scanf("%d",&n) ){
        printf("%d\n",D[n]);
    }
    return 0;
}
