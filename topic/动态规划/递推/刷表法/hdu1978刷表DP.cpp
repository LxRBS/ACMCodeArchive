/*
    从(1,1)到(n,m)一共有多少种走法？
    只能往右下走
    每走一步消耗一个能量
    走到某格时，可以拿到该格的能量，能量不能累加
    
    题目范围有误，是200
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int N,M;
int A[210][210];
int D[210][210];

//在位置(r,c)上，有能量e，能到达哪些格
void f(int r,int c,int e){
    for(int i=0;i<=e;++i)for(int j=0;j<=e-i;++j)if(i||j)
        D[r+i][c+j] = ( D[r+i][c+j] + D[r][c] ) % 10000;
}

int dp(){
    memset(D,0,sizeof(D));

    D[1][1] = 1;

    for(int i=1;i<=N;++i)for(int j=1;j<=M;++j){
        f(i,j,A[i][j]);
    }

    return D[N][M];
}

int main(){
    //freopen("1.txt","r",stdin);

    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        scanf("%d%d",&N,&M);
        for(int i=1;i<=N;++i)for(int j=1;j<=M;++j) scanf("%d",A[i]+j);

        printf("%d\n",dp());
    }
    return 0;
}
