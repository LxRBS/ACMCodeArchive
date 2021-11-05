/*
    A、B两个人有初始血量，
    每一轮有一定的概率A血减一、B血减一、平局
    谁先到0谁输，问A胜的概率
    数据有问题，先读入的是B的血量，而不是A的
*/
#include <stdio.h>
#include <numeric>
#include <algorithm>
using namespace std;

double const EPS = 1E-6;
inline bool is0(double x){return -EPS<x&&x<EPS;}

int A,B;
double PA[6],PB[6];
double TA,TB,TT;//单轮A减一的概率、B减一的概率、平局的概率

bool read(){
    if ( EOF == scanf("%d%d",&B,&A) ) return false;

    for(int i=0;i<6;++i) scanf("%lf",PA+i);
    for(int i=0;i<6;++i) scanf("%lf",PB+i);

    //平局的概率
    TT = inner_product(PA,PA+6,PB,0.0);

    //A减一的概率即A小于B的概率
    TA = 0.0;
    for(int i=0;i<5;++i)for(int j=i+1;j<6;++j) TA += PA[i] * PB[j];

    TB = 1.0 - TA - TT;
    return true;
}

//Dab表示A的胜率，在a点b点的情况下
//Dab = TA * D(a-1,b) + TB * D(a,b-1) + TT * Dab
//Dab = ( TA * D(a-1,b) + TB * D(a,b-1) ) / ( 1 - TT )
double D[2001][2001];
double dp(){
    if ( is0(1.0-TT) ) return 0.0;

    fill(D[0],D[0]+B+1,0.0);
    for(int i=1;i<=A;++i) D[i][0] = 1.0;

    double t = TA + TB;
    for(int i=1;i<=A;++i)for(int j=1;j<=B;++j) D[i][j] = ( TA * D[i-1][j] + TB * D[i][j-1] ) / t;

    return D[A][B];
}
int main(){
    while( read() ){
        printf("%.6f\n",dp());
    }
    return 0;
}
