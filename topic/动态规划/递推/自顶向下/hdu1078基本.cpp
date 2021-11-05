/*
    n×n的棋盘，每个位置有奶酪
    从起点出发，每一步最多走K格，且下一个位置必须比上一个位置奶酪要多
    问最多能拿到多少奶酪
*/
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

int A[110][110];
int N,K;
bool read(){
    scanf("%d%d",&N,&K);
    if ( -1 == N && -1 == K ) return false;

    for(int i=0;i<N;++i)for(int j=0;j<N;++j)scanf("%d",A[i]+j);
    return true;
}

int const DR[] = {-1,1,0,0};
int const DC[] = {0,0,-1,1};

inline bool isValid(int r,int c,int dr,int dc){
    return 0 <= dr && dr < N && 0 <= dc && dc < N && A[r][c] < A[dr][dc];
}

int D[110][110];//Dij表示从(i,j)开始往下搜索能够得到的最大值
int dfs(int r,int c){
    if ( D[r][c] != -1 ) return D[r][c];

    int ret = 0;
    for(int k=1;k<=K;++k)for(int i=0;i<4;++i){
        int dr = r + k * DR[i];
        int dc = c + k * DC[i];
        if ( isValid(r,c,dr,dc) ) ret = max(ret,dfs(dr,dc));
    }
    return D[r][c] = A[r][c] + ret;
}


int main(){
    while( read() ){
        memset(D,-1,sizeof(D));
        printf("%d\n",dfs(0,0));
    }
    return 0;
}
