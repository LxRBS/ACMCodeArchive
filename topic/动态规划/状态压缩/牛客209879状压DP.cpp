/**
    一个N×M的地图，有一个起点，有最多15个T，还有一些障碍物
    问从S出发走遍所有的T再返回S的最短距离是多少
    T只有15，可以用状压
    令D[state][i]表示走遍state中的T且最后停留在第i个的最短距离
    则答案是min{D[11...1][i]+Si之间的距离}
    状态转移方程也比较容易确定
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;
typedef pair<int,int> pii;

int const DR[] = {-1,1,0,0};
int const DC[] = {0,0,-1,1};

int N,M,T;
char A[220][220];

int SX,SY;
vector<pii> Vec;
int TSize;

int Pos2Idx[220][220];
int Dist[16][16];//记录两两之间的最短距离

void bfs(int startx,int starty){
    int tidx, idx = Pos2Idx[startx][starty];

    int d[220][220] = {0};
    bool flag[220][220] = {false};

    queue<pii> q;
    q.push(pii({startx,starty}));
    flag[startx][starty] = true;
    while(!q.empty()){
        pii h = q.front();q.pop();
        for(int i=0;i<4;++i){
            int nr = h.first + DR[i];
            int nc = h.second + DC[i];
            if(0<=nr&&nr<N&&0<=nc&&nc<M&&!flag[nr][nc]&&'#'!=A[nr][nc]){
                d[nr][nc] = d[h.first][h.second] + 1;
                if(tidx=Pos2Idx[nr][nc]){
                    Dist[idx][tidx] = Dist[tidx][idx] = d[nr][nc];
                }
                flag[nr][nc] = true;
                q.push(pii({nr,nc}));
            }
        }
    }
}

//D[state][pos]表示从S开始走遍state
//且最后停在pos的最短距离
int D[1<<15][16];
int dfs(int state, int pos){
    if(D[state][pos]>0){
        return D[state][pos];
    }

    int ans = 1000000000;
    int olds = state ^ (1<<pos-1);
    for(int i=1;i<=TSize;++i)if((1<<i-1)&olds){
        ans = min(ans, dfs(olds, i)+Dist[i][pos]);
    }
    return D[state][pos] = ans;
}

int main(){
    //freopen("1.txt","r",stdin);
    scanf("%d%d%d",&N,&M,&T);
    for(int i=0;i<N;++i){
        scanf("%s",A[i]);
    }

    ///找T和S
    for(int i=0;i<N;++i)for(int j=0;j<M;++j){
        if('S' == A[i][j]) {
            Pos2Idx[SX=i][SY=j] = 16;
        }else if('T' == A[i][j]){
            Vec.push_back(pii{i,j});
            Pos2Idx[i][j] = Vec.size();
        }
    }
    TSize = Vec.size();

    ///确定最短距离
    for(auto p: Vec) bfs(p.first, p.second);

    /*互相之间的最短距离，调试正确
    for(int i=1;i<=TSize;++i){
        printf("%d-16: %d %d\n",i,Dist[16][i],Dist[i][16]);
    }
    puts("");
    //*/

    ///检查是否有不能达到的电线杆
    for(int i=1;i<=TSize;++i){
        if(0==Dist[i][16]){
            puts("-1");
            return 0;
        }
    }

    ///状压一下，先初始化
    for(int i=1;i<=TSize;++i){
        D[1<<(i-1)][i] = Dist[16][i];
    }
    /*初始化正确
    for(int i=1;i<=TSize;++i){
        printf("%d ",D[1<<(i-1)][i]);
    }
    puts("");
    //*/

    int ans = 1000000000;
    int state = (1<<TSize) - 1;

    for(int tmp, i=1;i<=TSize;++i){
        ans = min(ans, dfs(state, i)+Dist[i][16]);
    }
    printf("%lld\n", (llt)T*TSize+ans);
    return 0;
}


