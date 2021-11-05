/*
    在一个长方体中，每次选择一个子长方体，将其中格子的状态改变。
    初始所有格子为off。
    问K轮以后，为on的格子数量的期望
    令P(i,pos)为前i轮以后，pos位置上为on的概率
    P(i,pos) = P(i-1,pos) * P(pos在第i轮未被选中的概率) + ( 1 - P(i-1,pos) ) * P(pos选中的概率)
    由于每个pos位置是独立的，所以对每个pos都有
    Pi = Pi-1 * ( 1 - P选中 ) + ( 1 - Pi-1 ) * P选中，且 P0 = 0
    有
    Pi = ( 1 - 2P选中 ) * Pi-1 + P选中
    即 Pi = a Pi-1 + b， 令Gi=Pi+x， 则 Gi = a Gi-1， 有 x = b / (a-1) = -1/2，且G0 = -1/2
    代回有
    Pi = 1/2 - (1-2P)^i / 2
    所以对每个位置而言，需要计算每一轮被选中的概率（该概率每一轮都是不变的）
    对于特定的x位置，总范围为1~X，则该x位置未被选中的概率是 ( (x-1)^2+(X-x)^2 ) / X^2
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

