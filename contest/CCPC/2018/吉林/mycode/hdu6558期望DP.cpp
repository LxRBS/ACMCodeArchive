/**
  如下一个随机过程，初始q=2%，每个回合
  1、以概率p确定胜负
  2、如果胜，以概率q结束。否则将q加2%，最多到1。回到1
  3、如果负，将q加1.5%，最多到1。回到1
  问结束的期望回合数

  对特定的q值，其期望数应该是一样的，所以应该用q作为状态DP
  q要么是整数，要么是.5，所以将q×2作为状态

  当q=100时，显然变成几何分布：成功一次即停止实验。此时的期望是1/p
  某个q时，有pq的概率1合结束，p(1-q)的概率到达q+2，(1-p)到达q+1.5
  D[2q]=pq+p(1-q)(D[2(q+2)]+1)+(1-p)(D[2(q+1.5)]+1)
*/
#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

double D[210];
int main(){
    //freopen("2.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        int p;
        scanf("%d",&p);

        D[200] = 100.0/p;

        for(int i=199;i>=4;--i){
            double q = (double)(i>>1) + ((i&1)?0.5:0.0);
            q/=100.0;

            D[i] = 1.0 + p/100.0*(1.0-q)*D[min(i+4,200)]+(100.0-p)/100.0*D[min(i+3,200)];
        }

        printf("Case %d: %.8f\n",kase,D[4]);
    }
    return 0;
}


