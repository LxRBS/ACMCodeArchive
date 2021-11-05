/*
    N个银行，每个银行有一个钱数，有一个被抓的概率
    问：在被抓概率低于P的情况下最多能抢多少钱
    这实际上是一个01背包问题
    令Dij是前i个银行抢j个钱的安全的概率
    Dij = max( Di-1,j , D[i-1][j-Mi] * ( 1 - Pi ) )
*/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <numeric>
using namespace std;

int N;
double P;
int M[110],Total;
double PP[110];
void read(){
    scanf("%lf%d",&P,&N);
    P = 1.0 - P;

    for(int i=0;i<N;++i) scanf("%d%lf",M+i,PP+i);
    Total = accumulate(M,M+N,0);
}

double D[10010];
int dp(){
    fill(D,D+10001,0.0);

    D[0] = 1.0;
    for(int i=0;i<N;++i){
        for(int j=Total;j>=M[i];--j){
            D[j] = max(D[j],D[j-M[i]]*(1.0-PP[i]));
        }
    }

    for(int i=Total;i;--i){
        if ( D[i] > P ){
            return i;
        }
    }
    return 0;
}

int main(){
    //freopen("1.txt","r",stdin);

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        read();
        printf("Case %d: %d\n",kase,dp());
    }
    return 0;
}

