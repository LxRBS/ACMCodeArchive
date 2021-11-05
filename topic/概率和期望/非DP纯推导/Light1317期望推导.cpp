/*
    N个人投M个篮，一共投K轮，问最后进球的期望数
    由于每一轮每个篮互不干扰，因此计算一轮即可，也不用考虑M
    根据期望公式：E = SIGMA( i * Pi ) ，Pi是进i个球的概率
    Pi = C(N,i) * p ^ i * ( 1 - p ) ^ ( N - i )
*/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int C[17][17];
void initC(){
    C[0][0] = 1;
	for(int i=1;i<=16;++i){
        C[i][0] = C[i][i] = 1;
        for(int j=1;j<i;++j) C[i][j] = C[i-1][j] + C[i-1][j-1];
	}
}

int N,M,K;
double P;
int main(){
    //freopen("1.txt","r",stdin);
    initC();

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        scanf("%d%d%d%lf",&N,&M,&K,&P);

        double ans = 0.0;
        for(int i=1;i<=N;++i){
            ans += C[N][i] * pow(P,i) * pow(1.-P,N-i) * i;
        }

        printf("Case %d: %.10f\n",kase,ans*K);
    }
    return 0;
}

