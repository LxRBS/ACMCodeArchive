/*
    给定一个字符串，删除若干个字符使之变成回文串
    问一共有多少种方法
*/
#include <cstdio>
#include <cstring>
typedef long long llt;

char A[65];
llt D[65][65];
llt dp(int s,int e){
    if ( -1LL != D[s][e] ) return D[s][e];
    if ( s == e ) return D[s][e] = 1LL;
    if ( e < s ) return D[s][e] = 0LL;

    D[s][e] = dp(s,e-1) + dp(s+1,e) - dp(s+1,e-1);
    if ( A[s] == A[e] ) D[s][e] += dp(s+1,e-1) + 1;

    return  D[s][e];
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        scanf("%s",A);
        memset(D,-1,sizeof(D));
        printf("Case %d: %lld\n",kase,dp(0,strlen(A)-1));
    }
    return 0;
}
