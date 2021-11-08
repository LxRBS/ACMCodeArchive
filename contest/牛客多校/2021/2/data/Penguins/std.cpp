#include<bits/stdc++.h>
#define M 21
using namespace std;
int D[4][4]={
    {1,0,1,0},
    {0,-1,0,1},
    {0,1,0,-1},
    {-1,0,-1,0}
};
struct node{
    char x1,y1,x2,y2,dir;
    int step,f;
}Q[M*M*M*M];
char mp[2][M][M];
bool mark[M][M][M][M];
char OP[]={"DLRU"};
int pos[4]={19,19,19,0};
bool check(int x,int y,int k){
    return x>=0&&y>=0&&x<20&&y<20&&mp[k][x][y]=='.';
}
void Print(int k){
    if(Q[k].f==-1)return;
    Print(Q[k].f);
    mp[0][Q[k].x1][Q[k].y1]='A';
    mp[1][Q[k].x2][Q[k].y2]='A';
    printf("%c",OP[Q[k].dir]); 
}
int BFS(){
    int L=0,R=0;
    mark[19][19][19][0]=1;
    node now,nxt;
    now.x1=19,now.y1=19,now.x2=19,now.y2=0;
    mark[19][19][19][0]=1;
    now.step=0,now.f=-1;
    Q[R++]=now;
    while(L<R){
        now=Q[L]; 
        for(int i=0;i<4;i++){
            nxt=now;
            if(check(nxt.x1+D[i][0],nxt.y1+D[i][1],0)){
                nxt.x1+=D[i][0];
                nxt.y1+=D[i][1];
            }
            if(check(nxt.x2+D[i][2],nxt.y2+D[i][3],1)){
                nxt.x2+=D[i][2];
                nxt.y2+=D[i][3];
            }
            if(!mark[nxt.x1][nxt.y1][nxt.x2][nxt.y2]){
                mark[nxt.x1][nxt.y1][nxt.x2][nxt.y2]=1;
                nxt.f=L;nxt.dir=i;nxt.step++;
                Q[R]=nxt;
                if(nxt.x1==0&&nxt.y1==19&&nxt.x2==0&&nxt.y2==0){ 
                    return R;
                }
                R++;
            }
        } 
        L++;
    }
    return -1;
}
int main(){
    for(int i=0;i<20;i++)
        scanf("%s %s",mp[0][i],mp[1][i]);
    int k=BFS();
    if(k==-1)puts("-1");
    else{
        printf("%d\n",Q[k].step);
        mp[0][19][19]='A';mp[1][19][0]='A'; 
        Print(k);puts("");
        for(int i=0;i<20;i++)
            printf("%s %s\n",mp[0][i],mp[1][i]);    
    } 
    return 0;
}
