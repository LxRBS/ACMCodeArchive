/*
    参加万圣节聚会，可以在衣服上套衣服
    每个聚会结束，可以套一件新衣服也可以依次脱掉若干件衣服
    脱掉的衣服不能再使用
    每个聚会有指定的衣服
    问最少需要多少件衣服
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int N;
int A[110];
int D[110][110];

int dp(int s,int e){
    if ( -1 != D[s][e] ) return D[s][e];
    if ( s == e ) return D[s][e] = 1;
    if ( e < s ) return D[s][e] = 0;

    int& r = D[s][e];
    r = dp(s+1,e) + 1;

    for(int k=s+1;k<=e;++k)if(A[s]==A[k]){
        r = min(r,dp(s+1,k-1)+dp(k,e));
    }

    return r;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        scanf("%d",&N);
        for(int i=0;i<N;++i) scanf("%d",A+i);

        memset(D,-1,sizeof(D));
        printf("Case %d: %d\n",kase,dp(0,N-1));
    }
    return 0;
}
