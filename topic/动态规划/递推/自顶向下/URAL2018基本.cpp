/*
    长度为n的字符串，最多a个连续的0，b个连续的1
    这样的字符串一共有多少个
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int const MOD = 1000000007;

int N;
int L[2];
int Dp[2][50001] = {{1,1},{1,1}};
int dp(int song,int n){
    if ( -1 != Dp[song][n] ) return Dp[song][n];

    int ret = 0;
    int other = song ^ 1;
    int start = n - L[song];
    if ( start < 0 ) start = 0;
    for(int i=start;i<n;++i){
        ret = ( ret + dp(other,i) ) % MOD;
    }
    return Dp[song][n] = ret;
}

bool read(){
    if ( EOF == scanf("%d%d%d",&N,L,L+1) ) return false;

    fill(Dp[0]+2,Dp[0]+N+1,-1);
    fill(Dp[1]+2,Dp[1]+N+1,-1);
    printf("%d\n",(dp(0,N)+dp(1,N))%MOD);
    return true;
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() );
    return 0;
}

