/**
   跳马问题，给定棋盘尺寸、起点和终点
   问最少步数
   棋盘尺寸300×300，双向广搜
*/
#include <stdio.h>
#include <string.h>
#include <utility>
#include <queue>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair

int const DR[] = {-2,-2,-1,+1,+2,+2,+1,-1};
int const DC[] = {-1,+1,+2,+2,+1,-1,-2,-2};

int N,SX,SY,EX,EY;
int A[310][310],B[310][310];

int bibfs(){
    if(SX==EX&&SY==EY) return 0;

    memset(A,-1,sizeof(A));
    memset(B,-1,sizeof(B));

    A[SX][SY] = B[EX][EY] = 0;
    queue<pii> qa,qb;

    qa.push(mp(SX,SY));
    qb.push(mp(EX,EY));
    while(!qa.empty()&&!qb.empty()){
        pii u = qa.front();qa.pop();
        for(int dr,dc,i=0;i<8;++i){
            dr = u.fi + DR[i];
            dc = u.se + DC[i];
            if(0<=dr&&dr<N&&0<=dc&&dc<N&&-1==A[dr][dc]){
                if(B[dr][dc]!=-1) return A[u.fi][u.se] + B[dr][dc] + 1;
                A[dr][dc] = A[u.fi][u.se] + 1;
                qa.push(mp(dr,dc));
            }
        }

        u = qb.front();qb.pop();
        for(int dr,dc,i=0;i<8;++i){
            dr = u.fi + DR[i];
            dc = u.se + DC[i];
            if(0<=dr&&dr<N&&0<=dc&&dc<N&&-1==B[dr][dc]){
                if(A[dr][dc]!=-1) return B[u.fi][u.se] + A[dr][dc] + 1;
                B[dr][dc] = B[u.fi][u.se] + 1;
                qb.push(mp(dr,dc));
            }
        }
    }

    while(!qa.empty()){
        pii u = qa.front();qa.pop();
        for(int dr,dc,i=0;i<8;++i){
            dr = u.fi + DR[i];
            dc = u.se + DC[i];
            if(0<=dr&&dr<N&&0<=dc&&dc<N&&-1==A[dr][dc]){
                if(B[dr][dc]!=-1) return A[u.fi][u.se] + B[dr][dc] + 1;
                A[dr][dc] = A[u.fi][u.se] + 1;
                qa.push(mp(dr,dc));
            }
        }
    }

    while(!qb.empty()){
        pii u = qb.front();qb.pop();
        for(int dr,dc,i=0;i<8;++i){
            dr = u.fi + DR[i];
            dc = u.se + DC[i];
            if(0<=dr&&dr<N&&0<=dc&&dc<N&&-1==B[dr][dc]){
                if(A[dr][dc]!=-1) return B[u.fi][u.se] + A[dr][dc] + 1;
                B[dr][dc] = B[u.fi][u.se] + 1;
                qb.push(mp(dr,dc));
            }
        }
    }
}

int main(){
    //freopen("1.txt","r",stdin);

    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
		scanf("%d%d%d%d%d",&N,&SX,&SY,&EX,&EY);
        printf("%d\n", bibfs());
	}
	return 0;
}

