/*
    三维迷宫，求最短时间走出
*/
#include <stdio.h>
#include <queue>
using namespace std;

int L,R,C;
char A[33][33][33];
bool read(){
    scanf("%d%d%d",&L,&R,&C);
    if ( 0 == R && 0 == C && 0 == L ) return false;

    for(int i=0;i<L;++i)for(int j=0;j<R;++j)scanf("%s",A[i][j]);
    return true;
}

struct _t{
    int h,r,c;
    int step;
    _t(int aa=0,int bb=0,int cc=0,int dd=0):h(aa),r(bb),c(cc),step(dd){}
};

int const DL[] = {-1,1,0,0,0,0};
int const DR[] = {0,0,-1,1,0,0};
int const DC[] = {0,0,0,0,-1,1};

int bfs(){
    queue<_t> q;

    //找出S的位置
    for(int i=0;i<L;++i)for(int j=0;j<R;++j)for(int k=0;k<C;++k)if('S'==A[i][j][k]){
        q.push(_t(i,j,k,0));
        A[i][j][k] = '#';
        goto L;
    }

L:
    while( !q.empty() ){
        _t u = q.front();
        q.pop();

        for(int i=0;i<6;++i){
            int dh = u.h + DL[i];
            int dr = u.r + DR[i];
            int dc = u.c + DC[i];

            if ( 0 <= dh && dh < L && 0 <= dr && dr < R && 0 <= dc && dc < C ){
                if ( 'E' == A[dh][dr][dc] ) return u.step + 1;

                if ( '.' == A[dh][dr][dc] ){
                    q.push(_t(dh,dr,dc,u.step+1));
                    A[dh][dr][dc] = '#';
                }
            }
        }
    }
    return -1;
}
int main(){
    while( read() ){
        int r = bfs();
        if ( -1 == r ) printf("Trapped!\n");
        else printf("Escaped in %d minute(s).\n",r);
    }
    return 0;
}
