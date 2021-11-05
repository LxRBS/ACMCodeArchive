/*
    ����һ��N�����ӣ����������������������
    ��DiΪ�Ѿ�����i���Ժ��ٵ�����̬��������������ȻDn = 0
    ����(n-i)/n�ĸ����������棬i/n�ĸ���û�����棬����
    Di = ( n - i ) / n * Di+1 + i / n * Di + 1
*/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int N;
double D[100010];
double dp(){
    D[N] = 0.0;
    for(int i=N-1;i>=0;--i){
        D[i] = D[i+1] + (double)N / (double)( N - i );
    }
    return D[0];
}

int main(){
    //freopen("1.txt","r",stdin);

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        scanf("%d",&N);
        printf("Case %d: %.10f\n",kase,dp());
    }
    return 0;
}

