/**
   跳马问题，给定棋盘尺寸、起点和终点
   问最少步数
   棋盘尺寸300×300，Astar, WA
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

inline int ABS(int x){return x>=0?x:-x;}

int const DR[] = {-2,-2,-1,+1,+2,+2,+1,-1};
int const DC[] = {-1,+1,+2,+2,+1,-1,-2,-2};

int N,SX,SY,EX,EY;

bool FA[310][310],FB[310][310];

struct _t{
    int x,y,step;
    int g,h,f;
    bool operator < (const _t & k) const{      //重载比较运算符
        return f > k.f;
    }
};

priority_queue<_t> Q;                        //最小优先级队列(开启列表)

int Heuristic(const _t &a){                    //manhattan估价函数
    return (ABS(a.x-EX)+ABS(a.y-EY))*10;
}

int Astar(){                                      //A*算法
    if(EX==SX&&EY==SY) return 0;

    //push头结点
    _t h;
    h.x = SX, h.y = SY, h.step = 0;
    h.f = 0, h.g = 0, h.h = Heuristic(h);
    Q.push(h);

    while(!Q.empty()){
        _t u = Q.top();Q.pop();
        FA[u.x][u.y]=true;

        if(u.x==EX && u.y==EY){
            return u.step;
        }
        for(int i=0;i<8;i++){
            h.x = u.x + DR[i];
            h.y = u.y + DC[i];
            if(0<=h.x&&h.x<N&&0<=h.y&&h.y<N&&!FA[h.x][h.y]){
                h.g = u.g + 23;                 //23表示根号5乘以10再取其ceil
                h.h = Heuristic(h);
                h.f = h.g + h.h;
                h.step = u.step + 1;
                Q.push(h);
            }
        }
    }
}

int main(){
    //freopen("1.txt","r",stdin);

    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        //初始化
        while(!Q.empty()) Q.pop();
        memset(FA,0,sizeof(FA));

		scanf("%d%d%d%d%d",&N,&SX,&SY,&EX,&EY);
        printf("%d\n", Astar());
	}
	return 0;
}

