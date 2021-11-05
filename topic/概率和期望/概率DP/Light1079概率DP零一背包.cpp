/*
    N�����У�ÿ��������һ��Ǯ������һ����ץ�ĸ���
    �ʣ��ڱ�ץ���ʵ���P������������������Ǯ
    ��ʵ������һ��01��������
    ��Dij��ǰi��������j��Ǯ�İ�ȫ�ĸ���
    Dij = max( Di-1,j , D[i-1][j-Mi] * ( 1 - Pi ) )
*/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <numeric>
using namespace std;

int N;
double P;
int M[110],Total;
double PP[110];
void read(){
    scanf("%lf%d",&P,&N);
    P = 1.0 - P;

    for(int i=0;i<N;++i) scanf("%d%lf",M+i,PP+i);
    Total = accumulate(M,M+N,0);
}

double D[10010];
int dp(){
    fill(D,D+10001,0.0);

    D[0] = 1.0;
    for(int i=0;i<N;++i){
        for(int j=Total;j>=M[i];--j){
            D[j] = max(D[j],D[j-M[i]]*(1.0-PP[i]));
        }
    }

    for(int i=Total;i;--i){
        if ( D[i] > P ){
            return i;
        }
    }
    return 0;
}

int main(){
    //freopen("1.txt","r",stdin);

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        read();
        printf("Case %d: %d\n",kase,dp());
    }
    return 0;
}

