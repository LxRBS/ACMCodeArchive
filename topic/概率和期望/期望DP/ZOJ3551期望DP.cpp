/*
    初始有N-1个人，1个吸血鬼
    每天有2个人相遇，如果一个是吸血鬼一个是人，
    则该人有P的概率变成吸血鬼
    问达到N个吸血鬼的天数的期望
    设Di为已经有i个吸血鬼，再变成N个吸血鬼的期望
    设 Q = i * (N-i) / C(N,2) * P；
    Di = Q * D(i+1) + (1-Q) * Di + 1
    所以 Di = ( QD(i+1) + 1 ) / Q
    且 Dn = 0,  求D1
*/
#include <stdio.h>
#include <numeric>
#include <algorithm>
using namespace std;

double const EPS = 1E-6;
inline bool is0(double x){return -EPS<x&&x<EPS;}

int N;
double P;
int main(){
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        scanf("%d%lf",&N,&P);

        if ( 2 == N &&  is0(1.0-P) ){
            printf("1.000\n");
            continue;
        }

        double dplus = 0.0, d;
        for(int i=N-1;i>=1;--i){
            double q = P * 2.0 * i * ( N - i ) / N / ( N - 1 );
            d = ( 1.0 + q * dplus ) / q;
            dplus = d;
        }
        printf("%.3f\n",dplus);
    }
    return 0;
}
