/**
   蜂巢地图，问从S到T最少经过几个蜂巢
   显然BFS
*/
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair

int const DR[] = {-2,-1,+1,+2,+1,-1};
int const DC[] = {+0,-3,-3,+0,+3,+3};

int R,C,N,M;
char A[4100][6100];
int SX,SY,EX,EY;

int bfs(){
    //找S和T的位置
    int t = 0;
    for(int i=0;i<N;++i){
        for(int j=0,ch;ch=A[i][j];++j){
            if('S'==ch){
                SX=i,SY=j,t|=1;
                if(3==t) goto L;
            }else if('T'==ch){
                EX=i,EY=j,t|=2;
                if(3==t) goto L;
            }
        }
    }
L:
    queue<pii> q;
    q.push(mp(SX,SY));
    int sz, ans = 1;
    while(!q.empty()){
        ++ans;
        sz = q.size();
        while(sz--){
            pii h = q.front();q.pop();
            for(int i=0;i<6;++i){
                int nr = h.fi + DR[i];
                int nc = h.se + DC[i];
                if(' ' == A[nr][nc]){
                    int nnr = nr + DR[i];
                    int nnc = nc + DC[i];
                    if(EX==nnr&&EY==nnc) return ans;
                    if(' '==A[nnr][nnc]){
                        A[nnr][nnc] = '*';
                        q.push(mp(nnr, nnc));
                    }
                }
            }
        }
    }
    return -1;
}
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        scanf("%d%d",&R,&C);
        N = 4 * R + 3;
        fgets(A[0], 6090, stdin);
        for(int i=0;i<N;++i)fgets(A[i], 6090, stdin);
        printf("%d\n", bfs());
    }

    return 0;
}

