/*
    给定地图
    J从起点往边界跑
    同时有火向四周蔓延
    问J是否能逃出
    质量比较好的题目
*/
#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;

int const DR[] = {-1,1,0,0};
int const DC[] = {0,0,-1,1};

int N,M;
char A[1010][1010];

struct _t{
    int r,c,flag;
    _t(int aa=0,int bb=0,int cc=0):r(aa),c(bb),flag(cc){}
};

int D[1010][1010];
int bfs(){
    for(int i=0;i<N;++i)fill(D[i],D[i]+M,-1);

    queue<_t> q;

    //找到J的位置和火的位置
    int dr,dc;
    for(int i=0;i<N;++i)for(int j=0;j<M;++j){
        if ( 'F' == A[i][j] ){
            q.push(_t(i,j,1));
        }else if ( 'J' == A[i][j] ){
            dr = i, dc = j;
        }
    }

    q.push(_t(dr,dc,0));
    D[dr][dc] = 0;

    while( !q.empty() ){
        _t u = q.front();
        q.pop();

        if ( 0 == u.flag ){//J走一步
            for(int i=0;i<4;++i){
                dr = u.r + DR[i];
                dc = u.c + DC[i];

                //成功
                if ( -1 == dr || N == dr || -1 == dc || M == dc ) return D[u.r][u.c] + 1;

                if ( 0 <= dr && dr < N && 0 <= dc && dc < M && '.' == A[dr][dc] && -1 == D[dr][dc] ){
                    D[dr][dc] = D[u.r][u.c] + 1;
                    q.push(_t(dr,dc,0));
                }
            }
        }else{//烧火
            for(int i=0;i<4;++i){
                int dr = u.r + DR[i];
                int dc = u.c + DC[i];

                if ( 0 <= dr && dr < N && 0 <= dc && dc < M && '.' == A[dr][dc] ){
                    A[dr][dc] = 'F';
                    q.push(_t(dr,dc,1));
                }
            }
        }
    }

    return -1;
}

void read(){
    scanf("%d%d",&N,&M);
    for(int i=0;i<N;++i)scanf("%s",A[i]);
}
int main(){
    //freopen("1.txt","r",stdin);

    int kase;
    scanf("%d",&kase);
    while(kase--){
        read();
        int ret = bfs();
        if ( -1 != ret ) printf("%d\n",ret);
        else puts("IMPOSSIBLE");
    }
    return 0;
}
