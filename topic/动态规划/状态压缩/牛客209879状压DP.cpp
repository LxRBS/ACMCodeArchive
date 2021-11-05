/**
    һ��N��M�ĵ�ͼ����һ����㣬�����15��T������һЩ�ϰ���
    �ʴ�S�����߱����е�T�ٷ���S����̾����Ƕ���
    Tֻ��15��������״ѹ
    ��D[state][i]��ʾ�߱�state�е�T�����ͣ���ڵ�i������̾���
    �����min{D[11...1][i]+Si֮��ľ���}
    ״̬ת�Ʒ���Ҳ�Ƚ�����ȷ��
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
int Dist[16][16];//��¼����֮�����̾���

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

//D[state][pos]��ʾ��S��ʼ�߱�state
//�����ͣ��pos����̾���
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

    ///��T��S
    for(int i=0;i<N;++i)for(int j=0;j<M;++j){
        if('S' == A[i][j]) {
            Pos2Idx[SX=i][SY=j] = 16;
        }else if('T' == A[i][j]){
            Vec.push_back(pii{i,j});
            Pos2Idx[i][j] = Vec.size();
        }
    }
    TSize = Vec.size();

    ///ȷ����̾���
    for(auto p: Vec) bfs(p.first, p.second);

    /*����֮�����̾��룬������ȷ
    for(int i=1;i<=TSize;++i){
        printf("%d-16: %d %d\n",i,Dist[16][i],Dist[i][16]);
    }
    puts("");
    //*/

    ///����Ƿ��в��ܴﵽ�ĵ��߸�
    for(int i=1;i<=TSize;++i){
        if(0==Dist[i][16]){
            puts("-1");
            return 0;
        }
    }

    ///״ѹһ�£��ȳ�ʼ��
    for(int i=1;i<=TSize;++i){
        D[1<<(i-1)][i] = Dist[16][i];
    }
    /*��ʼ����ȷ
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


