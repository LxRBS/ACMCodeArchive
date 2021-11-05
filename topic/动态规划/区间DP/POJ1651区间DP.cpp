/*
    整数序列
    每次拿出一个数
    并且得到该数与左右两数的连乘积
    求最小
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int N;
int A[110];
int D[110][110];//Dij i、j相邻的最小值

void dp(){
    for(int i=0;i<N;++i) D[i][i+1] = 0;

    for(int i=N-1;i>=0;--i){
        for(int j=i+1;j<N;++j){
            D[i][j] = -1;
            for(int k=i+1;k<j;++k){
                int r = A[i] * A[k] * A[j] + D[i][k] + D[k][j];
                if ( -1 == D[i][j] || r < D[i][j] ) D[i][j] = r;
            }
            if ( -1 == D[i][j] ) D[i][j] = 0;
        }
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    while( EOF != scanf("%d",&N) ){
        for(int i=0;i<N;++i) scanf("%d",A+i);
        dp();
        printf("%d\n",D[0][N-1]);
    }
    return 0;
}
