#include <cstdio>
#include <algorithm>
using namespace std;

int N,K[4],X[3];
double D[600];//Di表示从i到N的期望次数，这个数组其实用不到
/*
Di = SIGMA{Ps*Di+s} + P0 * D0 + 1
令
Di = Ai * D0 + Bi
则
Di = SIGMA{Ps*Ai+s} * D0 + SIGMA{Ps*Bi+s} + P0 * D0 + 1
所以
Ai = SIGMA{Ps*Ai+s} + P0;
Bi = SIGMA{Ps*Bi+s} + 1
*/
double A[600],B[600];
double P[20];
double dp(){
    fill(P,P+20,0.0);
    //首先计算得到各种点数的概率
    double p0 = 1.0 / K[1] / K[2] / K[3];
    for(int i=1;i<=K[1];++i)for(int j=1;j<=K[2];++j)for(int k=1;k<=K[3];++k){
        P[i+j+k] += p0;
    }
    P[X[1]+X[2]+X[3]] -= p0;

    int t = K[1] + K[2] + K[3];
    fill(A+N,A+N+t+1,0.0);
    fill(B+N,B+N+t+1,0.0);
    for(int i=N;i>=0;--i){
        A[i] = p0, B[i] = 1.0;
        for(int j=1;j<=t;++j){
            A[i] += A[i+j] * P[j];//超范围的概率均为0
            B[i] += B[i+j] * P[j];
        }
    }
    return B[0] / ( 1.0 - A[0] );
}
int main(){
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        scanf("%d%d%d%d%d%d%d",&N,K+1,K+2,K+3,X+1,X+2,X+3);
        printf("%.16f\n",dp());
    }
    return 0;
}
