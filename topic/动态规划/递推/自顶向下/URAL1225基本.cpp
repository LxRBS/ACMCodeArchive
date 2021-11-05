/*
    3种颜色染色
    相邻颜色不能相同
    蓝色两边的颜色不能相同
*/
#include <cstdio>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;

ull Dp[2][50] = {{0ULL,1ULL,1ULL},{0ULL,1ULL,1ULL}};
ull dp(int color,int n){
    if ( -1 != Dp[color][n] ) return Dp[color][n];

    int c = color ^ 1;
    return Dp[color][n] = dp(c,n-1) + dp(c,n-2);
}
int N;
bool read(){
    if ( EOF == scanf("%d",&N) ) return false;

    fill(Dp[0]+3,Dp[0]+46,-1);
    fill(Dp[1]+3,Dp[1]+46,-1);
    printf("%I64u\n",dp(0,N)+dp(1,N));
    return true;
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() );
    return 0;
}

