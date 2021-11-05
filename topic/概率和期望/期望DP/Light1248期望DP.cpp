/*
    给定一个N面骰子，问掷出所有面的期望次数
    令Di为已经掷出i面以后，再到达终态的期望次数，显然Dn = 0
    则有(n-i)/n的概率掷出新面，i/n的概率没有新面，所以
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

