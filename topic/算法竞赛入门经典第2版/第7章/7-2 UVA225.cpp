//在有障碍物的平面上行进，4个方向，第i步需要走i个单位，且必须转弯且不能后退
//最后需要回到起点
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;

int N,M;
int X[55],Y[55];
int F[500][500];
inline bool isValid(int x,int y){
    return -250 < x && x < 250 && -250 < y && y < 250;
}
inline bool isOK(int x,int y,int dx,int dy){
    if ( x == dx ){
        if ( y > dy ) swap(y,dy);
        for(int i=y;i<=dy;++i)if(2==F[x+250][i+250])return false;
        return true;
    }

    if ( x > dx ) swap(x,dx);
    for(int i=x;i<=dx;++i)if(2==F[i+250][y+250])return false;
    return true;
}
bool read(){
    memset(F,0,sizeof(F));

    scanf("%d%d",&N,&M);
    for(int i=0;i<M;++i){
        scanf("%d%d",X+i,Y+i);
        if ( isValid(X[i],Y[i]) ) F[X[i]+250][Y[i]+250] = 2;
    }
}

int const DX[] = {1,0,0,-1};
int const DY[] = {0,1,-1,0};
char const CH[] = "ensw";
char Ans[30];
int Cnt;

//depth表示已经做了多少步
void dfs(int depth,int x,int y,int orient){
    if ( depth == N ){
        if ( 0 == x && 0 == y ){
            printf("%s\n",Ans);
            ++Cnt;
        }
        return;
    }

    for(int i=0;i<4;++i)if(i!=orient&&i+orient!=3){
        int dx = x + DX[i]*(depth+1);
        int dy = y + DY[i]*(depth+1);
        if ( !isValid(dx,dy) || !isOK(x,y,dx,dy) || F[dx+250][dy+250] ) continue;

        F[dx+250][dy+250] = 1;
        Ans[depth] = CH[i];
        Ans[depth+1] = '\0';

        dfs(depth+1,dx,dy,i);

        Ans[depth] = '\0';
        F[dx+250][dy+250] = 0;
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);

    while( nofkase-- ){
        read();
        Cnt = 0;
        Ans[0] = '\0';
        dfs(0,0,0,-1);
        printf("Found %d golygon(s).\n\n",Cnt);
    }
    return 0;
}
