/*
    给出一个由括号构成的字符串
    求匹配的括号总数
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char S[101];
int Dp[101][101];
int dp(int s,int e){
    if ( -1 != Dp[s][e] ) return Dp[s][e];
    if ( s + 1 == e ) return Dp[s][e] = '(' == S[s] && ')' == S[e] || ( '[' == S[s] && ']' == S[e] ) ? 2 : 0;

    int ret = 0;
    if ( '(' == S[s] && ')' == S[e] || ( '[' == S[s] && ']' == S[e] ) ){
        ret = 2 + dp(s+1,e-1);
    }

    for(int k=s+1;k<e;++k){
        ret = max(ret,dp(s,k)+dp(k,e));
    }

    return Dp[s][e] = ret;
}
bool read(){
    gets(S);
    if ( 'e' == *S ) return false;

    for(int i=0,n=strlen(S);i<n;++i){
        fill(Dp[i],Dp[i]+n,-1);
        Dp[i][i] = 0;
    }
    printf("%d\n",dp(0,strlen(S)-1));
    return true;
}
int main(){
    //freopen("1.txt","r",stdin);
    while( read() );
    return 0;
}

