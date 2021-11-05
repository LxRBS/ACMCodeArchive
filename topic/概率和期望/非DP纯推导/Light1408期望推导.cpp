/*
    ����out�ĸ���ΪP����out�ĸ���ΪQ=1-P
    �������K1����out������ϰ����
    �������K2����out������ϰ����
    �ʵ���ϰ����������ĸ���������

    ��Ai����֪����i����out���ٵ�K1����������
    ��Bi����֪����i����out���ٵ�K2����������

    ����
    Ai = QA(i+1) + PB1 + 1
    Bi = PB(i+1) + QA1 + 1
    ��
    A(K1) = B(K2) = 0

    �۲���ƹ�ʽ��������һ����ȱ����У���
    Ai+x = Q( A(i+1) + x )����Ai = QA(i+1) - Px
    ��� x = -B1 - 1/P
    �� Fi = Ai + x����Fi = QF(i+1)��Fi��һ���ȱ�����
    ����  F1 = Q^(K1-1) * F(K1)
    ��F1��FK1�����
    A1 - B1 - 1/P = Q^(K1-1) * ( -B1 - 1/P )

    ͬ��������Gi=Bi+y�����y= -A1 - 1/Q
    ��G1��GK2�����
    B1 - A1 - 1/Q = P^(K2-1) * ( -A1 - 1/Q )

    �������̿��Խ��
          (1-P^(K2-1))*(1-Q^(K1-1))/Q + (1-Q^(K1-1))/P
    A1 = -----------------------------------------------
                1 - (1-P^(K2-1))*(1-Q^(K1-1))

    B1 = (1-P^(K2-1))/Q + A1 * (1-P^(K2-1))

    �ٸ�������Ĺ�ʽ����
    A0 = QA1 + PB1 + 1
    B0 = PB1 + QA1 + 1
    ��Ϊ  QA0 + PB0

    ����Ҫע�������Ƶ�����ȻҪ��P��Q��Ϊ�㣬P��QΪ�������ǳ�����ȷ��
*/
#include <stdio.h>
#include <math.h>
using namespace std;

double P,Q;
int K1,K2;

int main(){
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        scanf("%lf%d%d",&P,&K1,&K2);
        Q = 1.0 - P;

        if ( fabs(P) < 1E-6 ){
            printf("Case %d: %d\n",kase,K1);
            continue;
        }

        if ( fabs(Q) < 1E-6 ){
            printf("Case %d: %d\n",kase,K2);
            continue;
        }

        double PK2 = 1.0 - pow(P,K2-1);
        double QK1 = 1.0 - pow(Q,K1-1);

        double A1 = PK2*QK1/Q + QK1 / P;
        A1 /= 1 - PK2 * QK1;

        double B1 = PK2 / Q + PK2 * A1;

        double A0 = Q * A1 + P * B1 + 1;
        double B0 = P * B1 + Q * A1 + 1;

        printf("Case %d: %.10f\n",kase,Q*A0+P*B0);
    }
    return 0;
}
