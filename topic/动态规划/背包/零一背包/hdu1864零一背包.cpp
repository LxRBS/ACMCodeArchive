/*
    给定报销额度Q
    有N张发票
    问最多能报销多少
    
    首先对每张发票本身做一个判定
    对所有符合条件的发票，存在选和不选两种选择，在报销额度以内 
    所以是一个01背包问题，代价和收益均是发票金额 
*/
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

double Q;
int N;
int Cost[33];
gains_t Gains[33];
gains_t Dp[3010000];
bool read(){
    scanf("%lf%d",&Q,&N);
    if ( 0 == N ) return false;

    int k = 1;
    for(int i=0;i<N;++i){
        int m;
        scanf("%d",&m);

        double total = 0.0;
        double a[3] = {0.0};
        bool flag = true;
        for(int j=0;j<m;++j){
            char type[100];
            scanf("%s",type);
            if ( !flag  ) continue;

            int tt = *type - 'A';
            if ( tt >= 3 ){
                flag = false;
                continue;
            }

            double price;
            sscanf(type+2,"%lf",&price);
            a[tt] += price;
            if ( a[tt] > 600.0 ){
                flag = false;
                continue;
            }

            total += price;
        }
        if ( flag && total <= 1000.0 ){
            Cost[k] = Gains[k] = (int)(total * 100.0);
            ++k;
        }
    }

    int maxv = int(Q*100.0);
    fill(Dp,Dp+maxv+1,0);
    for(int i=1;i<k;++i){
        zeroOneKnapsack(Dp,maxv,Cost[i],Gains[i]);
    }
    printf("%.2f\n",Dp[maxv]/100.0);
    return true;
}


int main(){
    //freopen("1.txt","r",stdin);
    while ( read() );
    return 0;
}

