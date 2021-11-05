//给定地图，用最少的步骤将机器人从s走到t
//典型的广搜
#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

bool F[16][65536];
bool G[16][16];
int N,M,S,T;
int Start;

void read(){
    memset(F,0,sizeof(F));
    memset(G,0,sizeof(G));

    scanf("%d%d%d%d",&N,&M,&S,&T);
    Start = 1 << (S-1);

    int x,y;
    for(int i=0;i<M;++i){
        scanf("%d",&x);
        Start |= 1 << (x-1);
    }
    for(int i=1;i<N;++i){
        scanf("%d%d",&x,&y);
        G[x][y] = G[y][x] = true;
    }
}

struct _t{
    int pos;//机器人所在的位置
    int status;//当前局面
    vector<pair<int,int> > v;//历史记录
    _t(int aa=0,int bb=0,vector<pair<int,int> >vv=vector<pair<int,int> >()):pos(aa),status(bb),v(vv){}
};

_t Ans;
bool bfs(){
    queue<_t> q;
    q.push(_t(S,Start));
    F[S][Start] = true;

    while( !q.empty() ){
        _t u = q.front();
        q.pop();

        //对每一个可能移动的东西，对每一个可能移动到的位置
        for(int i=1,status=1;i<=N;++i,status<<=1)if(status&u.status)for(int j=1;j<=N;++j)if(G[i][j]&&!(u.status&(1<<j-1))){
            int newStatus = ( u.status - status ) | ( 1 << j-1 );
            int newPos = ( i == u.pos ) ? j : u.pos;

            if ( F[newPos][newStatus] ) continue;

            Ans.v.assign(u.v.begin(),u.v.end());
            Ans.v.push_back(make_pair(i,j));

            if ( newPos == T ) return true;

            q.push(_t(newPos,newStatus,Ans.v));
            F[newPos][newStatus] = true;
        }
    }

    return false;
}


int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        read();
        printf("CASE %d: ",kase);

        bool flag = bfs();
        if ( !flag ){
            printf("-1\n\n");
            continue;
        }

        printf("%d\n",Ans.v.size());
        for(vector<pair<int,int> >::iterator it=Ans.v.begin();it!=Ans.v.end();++it) printf("%d %d\n",it->first,it->second);
        printf("\n");
    }
    return 0;
}
