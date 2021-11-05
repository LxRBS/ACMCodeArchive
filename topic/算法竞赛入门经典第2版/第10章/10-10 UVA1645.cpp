/*
n���ڵ���и�����ʹ��ÿ��������нڵ���ӽڵ���Ŀ��ͬ���ʷ�����������һ���ж��ٸ�
��DijΪi���ڵ����Ϊj��������������
Dij = sigma( Dt,j-1 )
���У�t��i-1��Լ����
*/
#include <vector>
#include <stdio.h>
using namespace std;

vector<int> Vec[1001];
void sieve(){
    for(int i=1;i<=1000;++i){
        for(int j=i;j<=1000;j+=i){
            Vec[j].push_back(i);
        }
    }
}

int const MOD = 1000000007;
int D[1001][1001] = {0};
int A[1001] = {0,1,1};

void dp(){
    for(int i=1;i<=1000;++i){
        D[i][1] = 0;
        D[i][i] = 1;
    }
    D[2][2] = 1;

    for(int i=3;i<=1000;++i){
        A[i] = D[i][i];
        for(int j=2;j<i;++j){
            for(vector<int>::const_iterator it=Vec[i-1].begin();it!=Vec[i-1].end();++it){
                int t = (i-1)/(*it);
                D[i][j] += D[t][j-1];
                D[i][j] %= MOD;
            }
            A[i] += D[i][j];
            A[i] %= MOD;
        }
    }
}
int main(){
    sieve();
    dp();
    int n;
    for(int kase=1;EOF!=scanf("%d",&n);++kase){
        printf("Case %d: %d\n",kase,A[n]);
    }
    return 0;
}
