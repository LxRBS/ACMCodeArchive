//标准的二维完全背包
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef int gains_t;
int const SIZE = 101;

//one iteration of 2D complete knapsack
//d is the result
//maxv1 and maxv2 are upper bounds of 2D respectively
//cost1 and cost2 are current costs
//gains is current gains
void completeKnapsack(gains_t d[][SIZE],int maxv1,int maxv2,int cost1,int cost2,gains_t gains){
    for(int v1=cost1;v1<=maxv1;++v1)for(int v2=cost2;v2<=maxv2;++v2){
        d[v1][v2] = max(d[v1][v2],d[v1-cost1][v2-cost2]+gains);
    }
}

int N,M,K,S;
int A[110],B[110];
bool read(){
    if ( EOF == scanf("%d%d%d%d",&N,&M,&K,&S) ) return false;
    for(int i=0;i<K;++i)scanf("%d%d",A+i,B+i);
    return true;
}

int D[SIZE][SIZE];//Dijk表示前i种怪物、用了j忍耐度、k只怪物能够拿到的最大经验，i维度使用滚动数组
int dp(){
    memset(D,0,sizeof(D));

    for(int i=0;i<K;++i) completeKnapsack(D,M,S,B[i],1,A[i]);

    for(int i=0;i<=M;++i)for(int j=S;j>=0;--j)if(D[i][j]>=N)return M - i;
    return -1;
}

int main(){
    //freopen("1.txt","r",stdin);
    while ( read() ){
        printf("%d\n",dp());
    }
    return 0;
}
