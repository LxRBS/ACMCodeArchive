#include <bits/stdc++.h>
using namespace std;

int N;
int A[50][50];

int DR[] = {-1,1,0,0};
int DC[] = {0,0,-1,1};

void dfs(int r,int c){
    A[r][c] = 2;
    for(int i=0;i<4;++i){
        int nr = r + DR[i];
        int nc = c + DC[i];
        if(0<=nr&&nr<N&&0<=nc&&nc<N&&0==A[nr][nc]) dfs(nr,nc);
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    scanf("%d",&N);
    for(int i=0;i<N;++i)for(int j=0;j<N;++j)scanf("%d",A[i]+j);

    //把所有连通外面的点变成2
    for(int i=0;i<N;++i){
        if(0==A[0][i]) dfs(0,i);
        if(0==A[N-1][i]) dfs(N-1,i);
        if(0==A[i][0]) dfs(i,0);
        if(0==A[i][N-1]) dfs(i,N-1);
    }

    for(int i=0;i<N;++i){
        printf("%d",2-A[i][0]);
        for(int j=1;j<N;++j)printf(" %d",2-A[i][j]);
        printf("\n");
    }
    return 0;
}
