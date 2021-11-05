/*
    给定地图，地图上有若干KFC
    Y和M约定在其中一个KFC见面
    要求使得总路程最短
    总是有解
*/
#include <stdio.h>
#include <queue>
#include <vector>
using namespace std;

int const DR[] = {-1,1,0,0};
int const DC[] = {0,0,-1,1};

int N,M;
char A[210][210];

struct _t{
    int r,c;
    _t(int aa=0,int bb=0):r(aa),c(bb){}
};

int D[2][210][210];
void bfs(int r[],int c[],int tt){
    for(int i=0;i<N;++i)fill(D[tt][i],D[tt][i]+M,-1);

    queue<_t> q;
    q.push(_t(r[tt],c[tt]));
    D[tt][r[tt]][c[tt]] = 0;

    while( !q.empty() ){
        _t u = q.front();
        q.pop();

        for(int i=0;i<4;++i){
            int dr = u.r + DR[i];
            int dc = u.c + DC[i];

            if ( 0 <= dr && dr < N && 0 <= dc && dc < M && '#' != A[dr][dc] && -1 == D[tt][dr][dc] ){
                D[tt][dr][dc] = D[tt][u.r][u.c] + 1;
                q.push(_t(dr,dc));
            }
        }
    }
}

vector<_t> V;
int main(){
    //freopen("1.txt","r",stdin);

    while( 2 == scanf("%d%d",&N,&M) ){
        for(int i=0;i<N;++i) scanf("%s",A[i]);

        int r[2],c[2];
        V.clear();
        for(int i=0;i<N;++i)for(int j=0;j<M;++j){
            if ( '@' == A[i][j] ) V.push_back(_t(i,j));
            else if ( 'Y' == A[i][j] ) r[0] = i, c[0] = j;
            else if ( 'M' == A[i][j] ) r[1] = i, c[1] = j;
        }

        bfs(r,c,0);
        bfs(r,c,1);

        int ans = 0x3f3f3f3f;
        for(vector<_t>::iterator it=V.begin();it!=V.end();++it){
            ans = min(ans,D[0][it->r][it->c]+D[1][it->r][it->c]);
        }
        printf("%d\n",ans*11);
    }
    return 0;
}
