/*
    ����һ��������N������Լ���еȸ���ѡ��һ��������N = N / d
    �ظ�������裬ֱ��N���1���ʲ���������
    ��DiΪi��1����������
    Di = SIGMA( P(i��j�ĸ���) * ( Dj + 1 ) )
    ���� j = i / d�� ע�⵽jֵ�п��ܻ����i����i��Լ������Ϊni�����������õ�
    Di = ( n + SIGMA( Dj(jΪ��i��Լ��) ) / ( n - 1 )
*/

#include <stdio.h>
#include <vector>
#include <numeric>
using namespace std;

vector<int> A[100001];//Ai������i������Լ��

void sieve(){
    for(int i=1;i<100001;++i) A[i].push_back(1);

    for(int i=2;i<100001;++i){
        for(int j=i;j<100001;j+=i){
            A[j].push_back(i);
        }
    }
}

double D[100001];
void dp(){
    D[1] = 0.;
    for(int i=2;i<100001;++i){
        D[i] = 0.0;
        for(unsigned j=0;j<A[i].size()-1;++j){
            D[i] += D[A[i][j]];
        }
        D[i] += A[i].size();
        D[i] /= ( A[i].size() - 1 );
    }
}

int main(){
    sieve();
    dp();

    int n,nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        scanf("%d",&n);
        printf("Case %d: %.10f\n",kase,D[n]);
    }
    return 0;
}

