/*
    掷球out的概率为P，不out的概率为Q=1-P
    如果连续K1个球不out，则练习结束
    如果连续K2个球out，则练习结束
    问到练习结束，掷球的个数的期望

    设Ai是已知连续i个球不out，再到K1结束的期望
    设Bi是已知连续i个球out，再到K2结束的期望

    则有
    Ai = QA(i+1) + PB1 + 1
    Bi = PB(i+1) + QA1 + 1
    且
    A(K1) = B(K2) = 0

    观察递推公式很明显是一个类等比数列，令
    Ai+x = Q( A(i+1) + x )，则Ai = QA(i+1) - Px
    解出 x = -B1 - 1/P
    令 Fi = Ai + x，则Fi = QF(i+1)，Fi是一个等比数列
    所以  F1 = Q^(K1-1) * F(K1)
    将F1和FK1代入得
    A1 - B1 - 1/P = Q^(K1-1) * ( -B1 - 1/P )

    同理，可以令Gi=Bi+y，解出y= -A1 - 1/Q
    将G1和GK2代入得
    B1 - A1 - 1/Q = P^(K2-1) * ( -A1 - 1/Q )

    联立方程可以解出
          (1-P^(K2-1))*(1-Q^(K1-1))/Q + (1-Q^(K1-1))/P
    A1 = -----------------------------------------------
                1 - (1-P^(K2-1))*(1-Q^(K1-1))

    B1 = (1-P^(K2-1))/Q + A1 * (1-P^(K2-1))

    再根据最早的公式，有
    A0 = QA1 + PB1 + 1
    B0 = PB1 + QA1 + 1
    答案为  QA0 + PB0

    另外要注意上述推导中显然要求P和Q不为零，P、Q为零的情况非常容易确定
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
