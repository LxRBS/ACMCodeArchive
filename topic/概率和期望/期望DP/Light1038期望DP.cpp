/*
    给定一个正整数N，从其约数中等概率选择一个，并令N = N / d
    重复这个步骤，直到N变成1，问步数的期望
    设Di为i到1的期望，则
    Di = SIGMA( P(i到j的概率) * ( Dj + 1 ) )
    其中 j = i / d， 注意到j值有可能会等于i，令i的约数个数为ni，经过移项后得到
    Di = ( n + SIGMA( Dj(j为非i的约数) ) / ( n - 1 )
*/

#include <stdio.h>
#include <vector>
#include <numeric>
using namespace std;

vector<int> A[100001];//Ai保存了i的所有约数

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

