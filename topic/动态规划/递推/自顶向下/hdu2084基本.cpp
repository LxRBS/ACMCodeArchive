/*
    从数塔顶到最底层能够获得的最大和值
*/
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int const SIZE = 101;
int const INF = 2000000000;

int N;
int A[101][101];

void read(){
    cin >> N;
    for(int i=0;i<N;++i)for(int j=0;j<=i;++j)cin>>A[i][j];
}

int Dp[101][101];//Dij表示从位置(i,j)到达最底层的最大值
int dp(int row,int col){
    if ( -1 != Dp[row][col] ) return Dp[row][col];
    if ( N - 1 == row ) return Dp[row][col] = A[row][col];
    return Dp[row][col] = A[row][col] + max(dp(row+1,col),dp(row+1,col+1));
}
int main(){
    //freopen("1.txt","r",stdin);
    int kase;
    cin >> kase;
    while(kase--){
        read();
        for(int i=0;i<N;++i)fill(Dp[i],Dp[i]+N,-1);
        cout<<dp(0,0)<<endl;
    }
    return 0;
}

