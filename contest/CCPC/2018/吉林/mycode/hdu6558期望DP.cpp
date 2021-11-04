/**
  ����һ��������̣���ʼq=2%��ÿ���غ�
  1���Ը���pȷ��ʤ��
  2�����ʤ���Ը���q����������q��2%����ൽ1���ص�1
  3�����������q��1.5%����ൽ1���ص�1
  �ʽ����������غ���

  ���ض���qֵ����������Ӧ����һ���ģ�����Ӧ����q��Ϊ״̬DP
  qҪô��������Ҫô��.5�����Խ�q��2��Ϊ״̬

  ��q=100ʱ����Ȼ��ɼ��ηֲ����ɹ�һ�μ�ֹͣʵ�顣��ʱ��������1/p
  ĳ��qʱ����pq�ĸ���1�Ͻ�����p(1-q)�ĸ��ʵ���q+2��(1-p)����q+1.5
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


