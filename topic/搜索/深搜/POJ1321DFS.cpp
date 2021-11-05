/*
    指定棋盘上放k个车的方案总数
    做成一个二分图，搜索匹配数为k的方案总数
*/

#include <stdio.h>
#include <string.h>

bool G[40][40];
int N,K;
char A[10][10];

bool read(){
    scanf("%d%d",&N,&K);
    if ( -1 == N && -1 == K ) return false;

    for(int i=0;i<N;++i) scanf("%s",A[i]);

    memset(G,0,sizeof(G));
    for(int i=0;i<N;++i)for(int j=0;j<N;++j)if('#'==A[i][j])G[i+1][j+1]=true;

    return true;
}

int Ans;
bool Flag[40];

//a为已经搜过的点，k为已经摆下的棋子
void dfs(int a,int k){
    if ( k == K ) {++Ans;return;}
    if ( a > N ) return;

    for(int i=a+1;i<=N;++i)for(int j=1;j<=N;++j)if(G[i][j]&&!Flag[j]){
        Flag[j] = true;
        dfs(i,k+1);
        Flag[j] = false;
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        Ans = 0;
        memset(Flag,0,sizeof(Flag));
        dfs(0,0);
        printf("%d\n",Ans);
    }
    return 0;
}