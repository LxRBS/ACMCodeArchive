/*
    将字符串从A变成B需要的最少步数
    每一步可以将A的某个子串刷成一样的字符
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

char A[110],B[110];
int D[110][110];//Dij表示从空刷成Bij需要的最小步数

void dp(int n){
    memset(D,0,sizeof(D));

    D[n-1][n-1] = 1;

    for(int i=n-2;i>=0;--i){
        D[i][i] = 1;

        for(int j=i+1;j<n;++j){
            D[i][j] = D[i+1][j] + 1;

            for(int k=i+1;k<=j;++k)if ( B[i] == B[k] ){
                D[i][j] = min(D[i][j],D[i+1][k-1]+D[k][j]);
            }
        }
    }
}

int Ans[110];
int main(){
    //freopen("1.txt","r",stdin);
    while( EOF != scanf("%s%s",A,B) ){
        int n = strlen(A);
        dp(n);

        for(int i=0;i<n;++i){
            Ans[i] = D[0][i];
            if ( A[i] == B[i] ){
                Ans[i] = i ? Ans[i-1] : 0;
            }
            for(int j=0;j<i;++j){
                Ans[i] = min(Ans[i],Ans[j]+D[j+1][i]);
            }
        }
        printf("%d\n",Ans[n-1]);
    }
    return 0;
}
