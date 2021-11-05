/*
    ��һ���������У�ÿ��ѡ��һ���ӳ����壬�����и��ӵ�״̬�ı䡣
    ��ʼ���и���Ϊoff��
    ��K���Ժ�Ϊon�ĸ�������������
    ��P(i,pos)Ϊǰi���Ժ�posλ����Ϊon�ĸ���
    P(i,pos) = P(i-1,pos) * P(pos�ڵ�i��δ��ѡ�еĸ���) + ( 1 - P(i-1,pos) ) * P(posѡ�еĸ���)
    ����ÿ��posλ���Ƕ����ģ����Զ�ÿ��pos����
    Pi = Pi-1 * ( 1 - Pѡ�� ) + ( 1 - Pi-1 ) * Pѡ�У��� P0 = 0
    ��
    Pi = ( 1 - 2Pѡ�� ) * Pi-1 + Pѡ��
    �� Pi = a Pi-1 + b�� ��Gi=Pi+x�� �� Gi = a Gi-1�� �� x = b / (a-1) = -1/2����G0 = -1/2
    ������
    Pi = 1/2 - (1-2P)^i / 2
    ���Զ�ÿ��λ�ö��ԣ���Ҫ����ÿһ�ֱ�ѡ�еĸ��ʣ��ø���ÿһ�ֶ��ǲ���ģ�
    �����ض���xλ�ã��ܷ�ΧΪ1~X�����xλ��δ��ѡ�еĸ����� ( (x-1)^2+(X-x)^2 ) / X^2
*/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <numeric>
using namespace std;

double f(int x,int total){
    int a = x - 1;
    int b = total - x;
    return 1.0 - ( (double)(a*a) + b * b ) / ( total * total );
}

int X,Y,Z,K;
int main(){
    //freopen("1.txt","r",stdin);

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        scanf("%d%d%d%d",&X,&Y,&Z,&K);

        double ans = 0.0;
        for(int i=1;i<=X;++i)for(int j=1;j<=Y;++j)for(int k=1;k<=Z;++k){
            double p = f(i,X) * f(j,Y) * f(k,Z);
            ans += 0.5 - 0.5 * pow(1-2.0*p,K);
        }

        printf("Case %d: %.10f\n",kase,ans);
    }
    return 0;
}

