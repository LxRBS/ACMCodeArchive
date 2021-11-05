#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

struct _t{
    int step;
    int time;
    _t(int st=0,int ti=0):step(st),time(ti){}
};

deque<_t> Q;
int MiniAbove;
int Step[4000];

int A[20];
int M;
int N;

_t bfs(){
    Q.clear();
    fill(Step,Step+3601,0);
    MiniAbove = 4000;

    Q.push_back(_t(Step[0]=0,0));

    while( !Q.empty() ){
        _t head = Q.front();
        Q.pop_front();

        for(int i=0;i<N;++i){
            int time = head.time + A[i];
            if ( time < 0 ) time = 0;
            if ( time > 3600 ) time = 3600;
            if ( time >= M && time < MiniAbove ) MiniAbove = time;

            if ( time == M ) return _t(head.step+1,M);

            if ( Step[time] ) continue;

             Q.push_back(_t(Step[time] = head.step+1,time));
        }
    }

    return _t(Step[MiniAbove],MiniAbove);
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        scanf("%d%d",&N,&M);
        for(int i=0;i<N;++i)scanf("%d",A+i);

        if ( 0 == M ){
            printf("0 0\n");
            continue;
        }

        _t ans = bfs();

        printf("%d %d\n",ans.step,ans.time-M);
    }
    return 0;
}

