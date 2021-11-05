#include <bits/stdc++.h>
using namespace std;

//иообвСср
int const DX[]={-1,1,0,0};
int const DY[]={0,0,-1,1};

bool G[11][11]={false};
int SX,SY,FX,FY;
int N,M,T;
int Ans = 0;

void dfs(int x,int y){
    if(x==FX&&y==FY){
        ++Ans;
        return;
    }

    for(int i=0;i<4;++i){
        int nx = x + DX[i];
        int ny = y + DY[i];

        if(1<=nx&&nx<=N&&1<=ny&&ny<=M&&!G[nx][ny]){
            G[nx][ny] = true;
            dfs(nx,ny);
            G[nx][ny] = false;
        }
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    scanf("%d%d%d",&N,&M,&T);
    scanf("%d%d%d%d",&SX,&SY,&FX,&FY);
    for(int i=0;i<T;++i){
        int a,b;
        scanf("%d%d",&a,&b);
        G[a][b] = true;
    }
    G[SX][SY] = true;
    dfs(SX,SY);
    printf("%d\n",Ans);
    return 0;
}
