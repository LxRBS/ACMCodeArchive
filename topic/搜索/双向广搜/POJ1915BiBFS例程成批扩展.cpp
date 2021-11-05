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

bool FA[310][310],FB[310][310];

int bibfs(){
    if(SX==EX&&SY==EY) return 0;

    memset(FA,0,sizeof(FA));
    memset(FB,0,sizeof(FB));
    FA[SX][SY] = FB[EX][EY] = true;

    queue<pii> qa,qb;

    int a = 0, b = 0;

    qa.push(mp(SX,SY));
    qb.push(mp(EX,EY));

    while(!qa.empty()&&!qb.empty()){
        ++a;
        int sz = qa.size();
        while(sz--){
            pii u = qa.front();qa.pop();
            for(int dr,dc,i=0;i<8;++i){
                dr = u.fi + DR[i];
                dc = u.se + DC[i];
                if(0<=dr&&dr<N&&0<=dc&&dc<N&&!FA[dr][dc]){
                    if(FB[dr][dc]) return a + b;
                    FA[dr][dc] = true;
                    qa.push(mp(dr,dc));
                }
            }
        }

        ++b;
        sz = qb.size();
        while(sz--){
            pii u = qb.front();qb.pop();
            for(int dr,dc,i=0;i<8;++i){
                dr = u.fi + DR[i];
                dc = u.se + DC[i];
                if(0<=dr&&dr<N&&0<=dc&&dc<N&&!FB[dr][dc]){
                    FB[dr][dc] = true;
                    if(FA[dr][dc]) return a + b;
                    qb.push(mp(dr,dc));
                }
            }
        }
    }

    while(!qa.empty()){
        ++a;
        int sz = qa.size();
        while(sz--){
            pii u = qa.front();qa.pop();
            for(int dr,dc,i=0;i<8;++i){
                dr = u.fi + DR[i];
                dc = u.se + DC[i];
                if(0<=dr&&dr<N&&0<=dc&&dc<N&&!FA[dr][dc]){
                    if(FB[dr][dc]) return a + b;
                    FA[dr][dc] = true;
                    qa.push(mp(dr,dc));
                }
            }
        }
    }

    while(!qb.empty()){
        ++b;
        int sz = qb.size();
        while(sz--){
            pii u = qb.front();qb.pop();
            for(int dr,dc,i=0;i<8;++i){
                dr = u.fi + DR[i];
                dc = u.se + DC[i];
                if(0<=dr&&dr<N&&0<=dc&&dc<N&&!FB[dr][dc]){
                    FB[dr][dc] = true;
                    if(FA[dr][dc]) return a + b;
                    qb.push(mp(dr,dc));
                }
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

