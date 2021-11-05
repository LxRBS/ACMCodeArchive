#include <cstdio>

int N,M,T;
int SX,SY,EX,EY;//起终点
int TCnt;//点的总数
char Board[8][8];

//四周围上
void fillX(){
    for(int i=0;i<M+2;++i)Board[0][i] = Board[N+1][i] = 'X';
    for(int i=1;i<=N;++i)Board[i][0] = Board[i][M+1] = 'X';
}

int dist(int x1,int y1,int x2,int y2){
    int x = x1 - x2;
    int y = y1 - y2;
    if ( x < 0 ) x = -x;
    if ( y < 0 ) y = -y;
    return x + y;
}

//上下左右
int DX[] = {-1,1,0,0};
int DY[] = {0,0,-1,1};

bool dfs(int time,int x,int y){
    if ( time == T ){
        return EX == x && EY == y;
    }

    for(int i=0;i<4;++i){
        int dx = x + DX[i];
        int dy = y + DY[i];

        if ( 'X' == Board[dx][dy] ) continue;
        
        //如果时间不够用
        int d = dist(dx,dy,EX,EY);
        int tleft = T - time - 1;
        if ( d > tleft ) continue;

        //如果时间有多，必须多余偶数时间
        if ( ( tleft - d ) & 1 ) continue;

        Board[dx][dy] = 'X';
        bool t = dfs(time+1,dx,dy);
        if ( t ) return true;
        Board[dx][dy] = '.';
    }

    return false;
}

int main(){
    while( scanf("%d%d%d",&N,&M,&T) && N && M && T ){
        for(int i=1;i<=N;++i)scanf("%s",Board[i]+1);
        fillX();
        TCnt = 0;
        for(int i=1;i<=N;++i)for(int j=1;j<=M;++j){
            if ( 'S' == Board[i][j] ) SX = i, SY = j;
            else if ( 'D' == Board[i][j] ) EX = i, EY = j;
            else if ( '.' == Board[i][j] ) ++TCnt;
        }
        
        int d = dist(SX,SY,EX,EY);
        if ( TCnt+1 < T || d > T || ( (T-d) & 1 ) ){
            printf("NO\n");
            continue;
        }

        Board[SX][SY] = 'X';
        printf(dfs(0,SX,SY)?"YES\n":"NO\n");
    }
    return 0;
}
