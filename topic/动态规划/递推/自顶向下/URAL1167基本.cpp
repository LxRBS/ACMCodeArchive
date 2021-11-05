/*
    N个马放入K个马厩，必须连续的放
    如果i个白马和j个黑马放入一个马厩，则痛苦指数加上i*j
    要求最后痛苦指数最小
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int const INF = 1000000000;

int N,K;
int Color[2][501];
int Dp[501][501] = {0};
int dp(int idx,int jdx){
    if ( -1 != Dp[idx][jdx] ) return Dp[idx][jdx];

    int ret = INF;
    int j = jdx - 1;
    for(int i=idx-1;i>=jdx-1;--i){
        int t = dp(i,j) + ( Color[0][idx] - Color[0][i] ) * ( Color[1][idx] - Color[1][i] ) ;
        if ( t < ret ) ret = t;
    }
    return Dp[idx][jdx] = ret;
}

bool read(){
    if ( EOF == scanf("%d%d",&N,&K) ) return false;

    for(int i=1;i<=N;++i){
        int c;
        scanf("%d",&c);
        Color[0][i] = Color[0][i-1];
        Color[1][i] = Color[1][i-1];
        ++Color[c][i];
    }
    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        for(int i=1;i<=N;++i){
            Dp[i][1] = Color[0][i] * Color[1][i];
        }

        for(int i=2;i<=N;++i){
            fill(Dp[i]+2,Dp[i]+N+1,-1);
        }

        printf("%d\n",dp(N,K));
    }
    return 0;
}


