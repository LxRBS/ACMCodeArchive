/*
    20个顶点，每个顶点3条边
    给定m，问从m出发最后回到m的Hamilton回路
    求所有的回路
*/

#include <stdio.h>
#include <algorithm>
using namespace std;

char Output[100];
int OutPos = 0;
void out(int x){
    Output[OutPos++] = ' ';
    if ( x >= 10 ) Output[OutPos++] = x / 10 + '0';
    Output[OutPos++] = x % 10 + '0';
}

int G[22][3];
bool Flag[22];
int M;
int SCnt;

void dfs(int u,int cnt){
    if ( 20 == cnt ){
        if ( M == G[u][0] || M == G[u][1] || M == G[u][2] ) printf("%d: %s\n",++SCnt,Output);
        return;
    }

    int v,offset = OutPos;
    for(int i=0;i<3;++i){
        if ( !Flag[ v=G[u][i] ] ){
            out(v);
            Flag[v] = true;
            dfs(v,cnt+1);
            Flag[v] = false;
            OutPos = offset;//还原
        }
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    for(int i=1;i<=20;++i){
        scanf("%d%d%d",G[i],G[i]+1,G[i]+2);
        sort(G[i],G[i]+3);
    }

    while( scanf("%d",&M) , M ){
        fill(Flag,Flag+21,false);
        SCnt = OutPos = 0;

        Output[51] = ' ';
        if ( M >= 10 ) Output[52] = M / 10 + '0', Output[53] = M % 10 + '0',Output[54] = '\0';
        else Output[52] = M % 10 + '0',Output[53] = '\0';;


        out(M);
        Flag[M] = true;
        dfs(M,1);
    }
    return 0;
}
