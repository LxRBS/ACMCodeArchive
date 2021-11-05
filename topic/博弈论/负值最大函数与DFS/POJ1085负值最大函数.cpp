#include <cstdio>
#include <algorithm>
using namespace std;

int const INF_MIN = -1000000;

#define B(n) (1<<(n))
#define B0 B(0)
#define B1 B(1)
#define B2 B(2)
#define B3 B(3)
#define B4 B(4)
#define B5 B(5)
#define B6 B(6)
#define B7 B(7)
#define B8 B(8)
#define B9 B(9)
#define BA B(10)
#define BB B(11)
#define BC B(12)
#define BD B(13)
#define BE B(14)
#define BF B(15)
#define BG B(16)
#define BH B(17)

int Point2Edge[11][11] = {
//     0 1  2  3  4  5  6  7  8  9  10
/*0*/ {0},
/*1*/ {0,0, B0,B1},
/*2*/ {0,B0,0, B2,B3,B4},
/*3*/ {0,B1,B2,0, 0, B5,B6},
/*4*/ {0,0, B3,0, 0, B7,0, B9,BA},
/*5*/ {0,0, B4,B5,B7,0, B8,0, BB,BC},
/*6*/ {0,0, 0, B6,0, B8,0, 0, 0, BD,BE},
/*7*/ {0,0, 0, 0, B9,0, 0, 0, BF},
/*8*/ {0,0, 0, 0, BA,BB,0, BF,0, BG},
/*9*/ {0,0, 0, 0, 0, BC,BD,0, BG,0, BH},
/*10*/{0,0, 0, 0, 0, 0, BE,0, 0, BH}
};

int State,Ans;
int DP[0x3FFFF+1];

//move one step, modify state and return 0 or 1 or 2
int move(int edgebit){
    State = State | edgebit;

    switch(edgebit){
    case B0:return (State&B1)&&(State&B2)?1:0;
    case B1:return (State&B0)&&(State&B2)?1:0;
    case B2:return ((State&B0)&&(State&B1)) + ((State&B4)&&(State&B5));
    case B3:return (State&B4)&&(State&B7)?1:0;
    case B4:return ((State&B2)&&(State&B5)) + ((State&B3)&&(State&B7));
    case B5:return ((State&B2)&&(State&B4)) + ((State&B6)&&(State&B8));
    case B6:return (State&B5)&&(State&B8)?1:0;
    case B7:return ((State&B3)&&(State&B4)) + ((State&BA)&&(State&BB));
    case B8:return ((State&B5)&&(State&B6)) + ((State&BC)&&(State&BD));
    case B9:return (State&BA)&&(State&BF)?1:0;
    case BA:return ((State&B7)&&(State&BB)) + ((State&B9)&&(State&BF));
    case BB:return ((State&B7)&&(State&BA)) + ((State&BC)&&(State&BG));
    case BC:return ((State&B8)&&(State&BD)) + ((State&BB)&&(State&BG));
    case BD:return ((State&B8)&&(State&BC)) + ((State&BE)&&(State&BH));
    case BE:return (State&BD)&&(State&BH)?1:0;
    case BF:return (State&B9)&&(State&BA)?1:0;
    case BG:return (State&BB)&&(State&BC)?1:0;
    case BH:return (State&BD)&&(State&BE)?1:0;
    }

    return 0;
}

inline void unmove(int bit){
    State = State ^ bit;
}

inline void init(){
    State = Ans = 0;
    fill(DP,DP+0x3FFFF+1,INF_MIN);
}

int read(){
    int m;
    scanf("%d",&m);

    int flag = 1;
    while(m--){
        int from,to;
        scanf("%d%d",&from,&to);
        int num = move(Point2Edge[from][to]);
        if ( num > 0 ) Ans += flag * num;
        else flag *= -1;
    }

    return flag;
}

int negaMax(){
    if ( State == 0x3FFFF ) return 0;
    if ( INF_MIN != DP[State] ) return DP[State];

    int ret = INF_MIN;
    for(int i=0;i<18;++i){
        if ( State & B(i) ) continue;

        int t;
        int num = move(B(i));
        if ( num > 0 ) t = num + negaMax();
        else t = num - negaMax();
        if ( ret < t ) ret = t;
        unmove(B(i));
    }

    return DP[State] = ret;
}

int main(){
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        init();
        int flag = read();
        Ans += flag * negaMax();
        printf(Ans > 0 ? "Game %d: A wins.\n":"Game %d: B wins.\n",kase);
    }
    return 0;
}
