//01背包的略微变形
#include <cstdio>
#include <vector>
#include <cstring>
#include <functional>
#include <algorithm>
using namespace std;


typedef double gains_t;//type of gains

//one iteration of 01 knapsack problem
//d is the result array
//maxv is the upper bound of the cost namely it is volume in classical problem
//cost is the current cost
//gains is the current gains
void zeroOneKnapsack(gains_t d[],int maxv,int cost,gains_t gains){
    for(int v=maxv;v>=cost;--v){
        d[v] = max(d[v],d[v-cost]*gains);//将标准的01背包改造一下，概率要使用乘法
    }
}

int N;
double P;
double Gain[110];
int Cost[110];
int MaxV;
void read(){
    scanf("%lf%d",&P,&N);
    P = 1.0 - P;

    MaxV = 0;
    for(int i=0;i<N;++i)scanf("%d%lf",Cost+i,Gain+i), MaxV += Cost[i], Gain[i] = 1.0 - Gain[i];
}

double D[10010];
int dp(){
    fill(D,D+MaxV+1,0.0);

    D[0] = 1.0;
    for(int i=0;i<N;++i) zeroOneKnapsack(D,MaxV,Cost[i],Gain[i]);
    for(int v=MaxV;v>=0;--v)if(D[v]>=P)return v;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        read();
        printf("%d\n",dp());
    }
    return 0;
}
