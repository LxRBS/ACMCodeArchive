#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int N;
char A[1010][1010];
int D[1010][1010];//Dij表示以(i,j)为左下角的斜对称阵

int calc(int r,int c,int n){
    if ( r < n ) n = r;
    if ( N - c - 1 < n ) n = N - c - 1;

    int ret = 0;
    for(int i=1;i<=n;++i){
        if ( A[r-i][c] == A[r][c+i] ) ++ret;
        else break;
    }
    return ret;
}
int Ans;
void dp(){
    for(int i=0;i<N;++i) D[0][i] = D[i][N-1] = 1;

    for(int i=1;i<N;++i){
        for(int j=N-2;j>=0;--j){
            D[i][j] = calc(i,j,D[i-1][j+1]) + 1;
            if ( Ans < D[i][j] ) Ans = D[i][j];
        }
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    while( scanf("%d",&N) && N ){
        for(int i=0;i<N;++i)scanf("%s",A[i]);
        Ans = 1;
        dp();
        printf("%d\n",Ans);
    }
    return 0;
}
