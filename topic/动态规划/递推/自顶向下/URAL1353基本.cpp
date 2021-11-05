/*
    从1到N中，各位数字之和为S的数一共有多少个
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int S;
int Dp[11][91] = {{0},{1,1,1,1,1,1,1,1,1,1,0}};
int dp(int length,int s){
    if ( -1 != Dp[length][s] ) return Dp[length][s];
    if ( s > length * 9 ) return Dp[length][s] = 0;
    if ( s == length * 9 ) return Dp[length][s] = 1;

    int ret = 0;
    for(int i=0;i<=9&&s-i>0;++i) ret += dp(length-1,s-i);
    return Dp[length][s] = ret;
}

bool read(){
    if ( EOF == scanf("%d",&S) ) return false;
    return true;
}
int main(){
    //freopen("1.txt","r",stdin);
    for(int i=2;i<11;++i){
        fill(Dp[i],Dp[i]+91,-1);
        Dp[i][1] = 1;
    }
    while( read() ){
        int ret = 0;
        for(int i=1;i<10;++i) ret += dp(i,S);
        printf("%d\n",1==S?ret+1:ret);

    }
    return 0;
}


