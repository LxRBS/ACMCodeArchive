//一个迷宫，里面有若干会移动的障碍物，问从左下角到右上角的最短时间，存在不能到达的情况
//障碍物的移动是有限制的，若干时间以后，障碍物就不会再动了
//将二维迷宫按照时间添加一维，变成三维迷宫，因为规模较小，也不用做优化。
#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;

int R,C,K,T;
bool Maze[225+30][15][15];
int A[20][6];

inline int f(int pr,int pc,int qr,int qc,int dr,int dc){
    int tr = 0;
    if ( dr > 0 ) tr = R - qr - 1;
    else if ( dr < 0 ) tr = pr;

    int tc = 0;
    if ( dc > 0 ) tc = C - qc - 1;
    else if ( dc < 0 ) tc = pc;

    return max(tr,tc);
}
inline void get(int& pr,int& pc,int& qr,int& qc,int dr,int dc){
    if ( dr < 0 && 0 == pr || ( dr > 0 && R - 1 == qr ) || ( dc < 0 && 0 == pc ) || ( dc > 0 && C - 1 == qc ) ) return;

    pr += dr, qr += dr, pc += dc, qc += dc;
}
void read(){
    scanf("%d%d%d",&R,&C,&K);

    memset(Maze,0,sizeof(Maze));
    T = 0;
    for(int i=0;i<K;++i){
        scanf("%d%d%d%d%d%d",A[i],A[i]+1,A[i]+2,A[i]+3,A[i]+4,A[i]+5);
        int t = f(A[i][0],A[i][1],A[i][2],A[i][3],A[i][4],A[i][5]);
        if ( T < t ) T = t;
    }

    //对每一个时刻
    for(int t=0;t<=T;++t)for(int k=0;k<K;++k){
        for(int i=A[k][0];i<=A[k][2];++i)for(int j=A[k][1];j<=A[k][3];++j){
            Maze[t][i][j] = true;
        }
        get(A[k][0],A[k][1],A[k][2],A[k][3],A[k][4],A[k][5]);
    }

    //将最后一个时刻拷贝R*C-1次
    for(int i=1;i<R*C;++i)memcpy(Maze[i+T],Maze[T],sizeof(Maze[T]));
}

struct _t{
    int r,c,t;
    _t(int rr=0,int cc=0,int tt=0):r(rr),c(cc),t(tt){}
};

int const DR[] = {0,1,-1,0,0};
int const DC[] = {0,0,0,-1,1};

inline bool isValid(int r,int c){
    return 0 <= r && r < R && 0 <= c && c < C;
}

_t Queue[225*15*15];
void dispQueue(int head,int tail){
    for(int i=head;i<tail;++i)printf("(%d,%d,%d)",Queue[i].r,Queue[i].c,Queue[i].t);
    printf("\n");
}
int bfs(){
    if ( 1 == R && 1 == C ) return 0;

    int head = 0, tail = 0;
    Queue[tail].r = Queue[tail].c = Queue[tail].t = 0;
    ++tail;

    while( head < tail ){
        //dispQueue(head,tail);

        for(int i=0;i<5;++i){
            int dr = Queue[head].r + DR[i];
            int dc = Queue[head].c + DC[i];
            int dt = Queue[head].t + 1;

            if ( R-1 == dr && C-1 == dc ) return dt;

            if ( isValid(dr,dc) && dt < T + R * C && !Maze[dt][dr][dc] ){
                Queue[tail].r = dr;
                Queue[tail].c = dc;
                Queue[tail++].t = dt;
                Maze[dt][dr][dc] = true;
            }
        }

        ++head;
    }
    return -1;
}


int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        read();
        printf("%d\n",bfs());
    }
    return 0;
}
