//广搜，最小权值走出地图
#include <stdio.h>
#include <string.h>
#include <queue>
#include <deque>
#include <algorithm>
using namespace std;

int K,W,H;
int L2I[128] = {0};
char A[1010][1010] = {'\0'};

struct _t{
    int r,c,w;
    _t(int a=0,int b=0,int ww=0):r(a),c(b),w(ww){}
    int d()const{int t=r-1;if(t>H-r)t=H-r;if(t>c-1)t=c-1;if(t>W-c)t=W-c;return t;}
}Start;

bool operator < (_t const&l,_t const&r){
    return l.w > r.w || ( l.w == r.w && l.d() < r.d() );
}

void read(){
    scanf("%d%d%d",&K,&W,&H);

    char a[3];
    for(int i=0;i<K;++i){
        scanf("%s",a);
        scanf("%d",&L2I[*a]);
    }

    fgets(A[1]+1,1009,stdin);
    bool flag = true;
    for(int i=1;i<=H;++i){
        fgets(A[i]+1,1009,stdin);
        if(flag)for(char*p=A[i]+1;*p!='\n';++p)if('E'==*p){Start.r=i,Start.c=p-A[i],flag=false;break;}
    }
}

inline bool isBoarder(int r,int c){
    return 1 == r || H == r || 1 == c || W == c;
}

int const DR[] = {-1,1,0,0};
int const DC[] = {0,0,-1,1};

bool Flag[1010][1010] = {false};
int bfs(){
    if ( isBoarder(Start.r,Start.c) ) return 0;

    for(int i=1;i<=H;++i) fill(Flag[i]+1,Flag[i]+1+W,false);

    priority_queue<_t> q;
    q.push(Start);
    Flag[Start.r][Start.c] = true;

    while( !q.empty() ){
        _t u = q.top();
        q.pop();

        if ( isBoarder(u.r,u.c) ) return u.w;

        for(int i=0;i<4;++i){
            int dr = u.r + DR[i];
            int dc = u.c + DC[i];

            if ( !Flag[dr][dc] ){
                Flag[dr][dc] = true;
                q.push(_t(dr,dc,u.w + L2I[A[dr][dc]]));
            }
        }
    }
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
