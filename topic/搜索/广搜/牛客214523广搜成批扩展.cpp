/**
    给个迷宫，问最少拐几个弯可以从起点到终点
*/
#include <bits/stdc++.h>
using namespace std;

struct _t{
    int r,c;
    int o;//方向，上下左右
    _t(int rr=0,int cc=0,int oo=0):r(rr),c(cc),o(oo){}
};

int N,M;
int SX,SY,EX,EY;

char A[5010][5010];
bool F[5010][5010];

queue<_t> Q;
void moveUp(int r,int c){
    int nr = r - 1;
    while(nr>=0){
        if('1'==A[nr][c]) break;
        if(!F[nr][c]){
            Q.push(_t(nr, c, 0x1));
            F[nr][c] = true;
        }
        --nr;
    }
}
void moveDown(int r,int c){
    int nr = r + 1;
    while(nr<N){
        if('1'==A[nr][c]) break;
        if(!F[nr][c]){
            Q.push(_t(nr, c, 0x2));
            F[nr][c] = true;
        }
        ++nr;
    }
}
void moveLeft(int r,int c){
    int nc = c - 1;
    while(nc>=0){
        if('1'==A[r][nc]) break;
        if(!F[r][nc]){
            Q.push(_t(r, nc, 0x10));
            F[r][nc] = true;
        }
        --nc;
    }
}
void moveRight(int r,int c){
    int nc = c + 1;
    while(nc<M){
        if('1'==A[r][nc]) break;
        if(!F[r][nc]){
            Q.push(_t(r, nc, 0x20));
            F[r][nc] = true;
        }
        ++nc;
    }
}
int bfs(){
    if('1'==A[SX][SY]||'1'==A[EX][EY]) return -1;
    if(SX==EX&&SY==EY) return 0;

    for(int i=0;i<N;++i)fill(F[i],F[i]+M,false);
    while(!Q.empty()) Q.pop();

    F[SX][SY] = true;

    moveUp(SX, SY);
    moveDown(SX, SY);
    moveLeft(SX, SY);
    moveRight(SX, SY);

    if(F[EX][EY]) return 0;

    int ans = 0;
    while(!Q.empty()){
        ++ans;
        int sz = Q.size();
        while(sz--){
            _t h = Q.front();Q.pop();
            if(h.o&0x3){//只走左右
                moveLeft(h.r, h.c);
                moveRight(h. r, h.c);
            }
            if(h.o&0x30){
                moveUp(h.r, h.c);
                moveDown(h.r, h.c);
            }
            if(F[EX][EY]) return ans;
        }
    }

    return -1;
}

int main(){
    //freopen("1.txt","r",stdin);
    while(6==scanf("%d%d%d%d%d%d",&N,&M,&SX,&SY,&EX,&EY)){
        for(int i=0;i<N;++i)scanf("%s", A[i]);

        printf("%d\n", bfs());
    }
    return 0;
}
