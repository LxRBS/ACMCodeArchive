/*
    ��ʼ��N-1���ˣ�1����Ѫ��
    ÿ����2�������������һ������Ѫ��һ�����ˣ�
    �������P�ĸ��ʱ����Ѫ��
    �ʴﵽN����Ѫ�������������
    ��DiΪ�Ѿ���i����Ѫ���ٱ��N����Ѫ�������
    �� Q = i * (N-i) / C(N,2) * P��
    Di = Q * D(i+1) + (1-Q) * Di + 1
    ���� Di = ( QD(i+1) + 1 ) / Q
    �� Dn = 0,  ��D1
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
