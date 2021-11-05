#include <cstdio>
#include <cstring>
using namespace std;

int N,S;
double D[1010][1010];//Dij表示从位置(i,j)到达(N,S)的期望
void dp(){
    D[N][S] = 0.;
    for(int i=N;i>=0;--i)for(int j=S;j>=0;--j){
        if ( i != N || j != S )
        D[i][j] = ( ( N - i ) * j * D[i+1][j] + i * ( S - j ) * D[i][j+1] + ( N - i ) * ( S - j ) * D[i+1][j+1] + N * S ) / ( N * S - i * j );
    }
}
int main(){
    while( EOF != scanf("%d%d",&N,&S) ){
        dp();
        printf("%.4f\n",D[0][0]);
    }
    return 0;
}
