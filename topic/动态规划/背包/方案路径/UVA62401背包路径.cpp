/**
   01背包，输出具体方案
   要求多种方案时输出数量最多的
*/
#include <bits/stdc++.h>
using namespace std;
typedef int gains_t;//type of gains
int Path[22][10100];
int Cnt[10100];
void zeroOneKnapsack(int index,gains_t d[],int maxv,int cost,gains_t gains){
    for(int v=maxv;v>=cost;--v){
        if(d[v]<d[v-cost]+gains){
            d[v] = d[v-cost]+gains;
            Cnt[v] = Cnt[v-cost]+1;
            Path[index][v] = 1;//表示第index个物体在耗费v的情况下要选
        }else if(d[v]==d[v-cost]+gains&&Cnt[v]<Cnt[v-cost]+1){
            d[v] = d[v-cost]+gains;
            Cnt[v] = Cnt[v-cost]+1;
            Path[index][v] = 1;//表示第index个物体在耗费v的情况下要选
        }
    }
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}
int N,Sum;
int Cost[22];
int D[1000010];
void output(int index,int cost){
    if(index-1>=0){
        output(index-1,cost-(Path[index][cost]?Cost[index]:0));
    }
    if(Path[index][cost]) printf("%d ",Cost[index]);
}
int main(){
    //freopen("1.txt","r",stdin);
    while(EOF!=scanf("%d",&Sum)){
        N=getUnsigned();
        for(int i=0;i<N;++i)Cost[i]=getUnsigned();
        fill(D,D+Sum+1,0);
        fill(Cnt,Cnt+Sum+1,0);
        memset(Path,0,sizeof(Path));
        for(int i=0;i<N;++i){
            zeroOneKnapsack(i,D,Sum,Cost[i],Cost[i]);
        }
        output(N-1,Sum);
        printf("sum:%d\n",D[Sum]);
    }
    return 0;
}
