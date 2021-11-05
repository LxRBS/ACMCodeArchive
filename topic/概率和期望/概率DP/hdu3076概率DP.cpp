/*
    A��B�������г�ʼѪ����
    ÿһ����һ���ĸ���AѪ��һ��BѪ��һ��ƽ��
    ˭�ȵ�0˭�䣬��Aʤ�ĸ���
    ���������⣬�ȶ������B��Ѫ����������A��
*/
#include <stdio.h>
#include <numeric>
#include <algorithm>
using namespace std;

double const EPS = 1E-6;
inline bool is0(double x){return -EPS<x&&x<EPS;}

int A,B;
double PA[6],PB[6];
double TA,TB,TT;//����A��һ�ĸ��ʡ�B��һ�ĸ��ʡ�ƽ�ֵĸ���

bool read(){
    if ( EOF == scanf("%d%d",&B,&A) ) return false;

    for(int i=0;i<6;++i) scanf("%lf",PA+i);
    for(int i=0;i<6;++i) scanf("%lf",PB+i);

    //ƽ�ֵĸ���
    TT = inner_product(PA,PA+6,PB,0.0);

    //A��һ�ĸ��ʼ�AС��B�ĸ���
    TA = 0.0;
    for(int i=0;i<5;++i)for(int j=i+1;j<6;++j) TA += PA[i] * PB[j];

    TB = 1.0 - TA - TT;
    return true;
}

//Dab��ʾA��ʤ�ʣ���a��b��������
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
