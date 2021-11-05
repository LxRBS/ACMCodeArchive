/**
   1/5/10/25的硬币，支付指定的价格
   硬币数量均在10000以内
   硬币用的越多越好
   求方案
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef int gains_t;//type of gains
int const NINF = -100000000;
int Num[10010];
int Path[4][10010];

void zeroOneKnapsack(int index,gains_t d[],int maxv,int cost,gains_t gains,int real_cnt){
    int tmp;
    for(int v=maxv;v>=cost;--v)if(d[v-cost]!=NINF){
        if(d[v]<(tmp=d[v-cost]+gains)){
            d[v] = tmp;
            Num[v] = Num[v-cost] + real_cnt;
            Path[index][v] = real_cnt;
        }else if(d[v]==tmp&&Num[v]<Num[v-cost]+real_cnt){
            d[v] = tmp;
            Num[v] = Num[v-cost] + real_cnt;
            Path[index][v] = real_cnt;
        }
    }
}

void completeKnapsack(int index,gains_t d[],int maxv,int cost,gains_t gains){
    int tmp;
    for(int v=cost;v<=maxv;++v)if(d[v-cost]!=NINF){
        if(d[v]<(tmp=d[v-cost]+gains)){
            d[v] = tmp;
            Num[v] = Num[v-cost] + 1;
            Path[index][v] = 1;
        }else if(d[v]==tmp&&Num[v]<Num[v-cost]+1){
            d[v] = tmp;
            Num[v] = Num[v-cost] + 1;
            Path[index][v] = 1;
        }
    }
}

void multipleKnapsack(int index,gains_t d[],int maxv,int cost,gains_t gains,int cnt){
    if ( cost * cnt >= maxv ){
        completeKnapsack(index,d,maxv,cost,gains);
        return;
    }

    for(int k=1;k<cnt;k<<=1){
        zeroOneKnapsack(index,d,maxv,k*cost,k*gains,k);
        cnt -= k;
    }

    if(cnt) zeroOneKnapsack(index,d,maxv,cnt*cost,cnt*gains,cnt);
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int Sum;
int Cnt[4];
int const Cost[] = {1,5,10,25};
int D[10010];

void output(int index,int cost){
    if(index<0) return;
    if(Path[index][cost]){
        output(index,cost-Cost[index]*Path[index][cost]);
        Cnt[index] += Path[index][cost];
    }else{
        output(index-1,cost);
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    while(1){
        Sum = getUnsigned();
        for(int i=0;i<4;++i)Cnt[i]=getUnsigned();
        if(0==Sum&&Cnt[0]==0&&Cnt[1]==0&&Cnt[2]==0&&Cnt[3]==0) break;

        fill(D,D+Sum+1,NINF);
        fill(Num,Num+Sum+1,0);
        memset(Path,0,sizeof(Path));

        D[0] = 0;
        for(int i=0;i<4;++i)if(Cnt[i]){
            multipleKnapsack(i,D,Sum,Cost[i],Cost[i],Cnt[i]);
        }
        fill(Cnt,Cnt+4,0);
        output(3,Sum);
        if(D[Sum]==NINF){
            puts("Charlie cannot buy coffee.");
        }else{
            printf("Throw in %d cents, %d nickels, %d dimes, and %d quarters.\n",Cnt[0],Cnt[1],Cnt[2],Cnt[3]);
        }
    }
    return 0;
}
