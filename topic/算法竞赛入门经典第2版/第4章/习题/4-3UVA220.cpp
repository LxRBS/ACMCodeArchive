/**
  黑白棋，给定初始局面
  再给定一些指令，要求进行相应的操作
  L:打印所有合法操作
  Mrc：走一步棋
  Q:退出并打印当前棋盘
*/
#include <cstdio>

int const DR[] = {-1,-1,0,1,1,+1,00,-1};
int const DC[] = {00,+1,1,1,0,-1,-1,-1};

char B[15][15];
char Cur[10];
char Cmd[10];

inline bool isValid(int r,int c){
    return 1 <= r && r <= 8 && 1 <= c && c <= 8;
}

int isMoveOK(int r,int c,int orient,char cur){
    int ans = 0;
    int dr = r + DR[orient];
    int dc = c + DC[orient];
    char const opp = 'W' - cur + 'B';

    while( isValid(dr,dc) && opp == B[dr][dc] ) dr += DR[orient], dc += DC[orient], ++ans;

    if ( isValid(dr,dc) && cur == B[dr][dc] ) return ans;
    return 0;
}

bool isMoveOK(int r,int c,char cur){
    for(int i=0;i<8;++i){
        if ( isMoveOK(r,c,i,cur) ) return true;
    }
    return false;
}

void go(int r,int c,char cur){
    B[r][c] = cur;
    for(int i=0;i<8;++i){
        int k = isMoveOK(r,c,i,cur);
        int dr = r + DR[i];
        int dc = c + DC[i];
        for(int j=0;j<k;++j){
            B[dr][dc] = cur;
            dr += DR[i];
            dc += DC[i];
        }
    }
}

void proc(){
    while(1){
        scanf("%s",Cmd);
        if ( 'Q' == *Cmd ) return;

        if ( 'M' == *Cmd ){
            int r = Cmd[1] - '0';
            int c = Cmd[2] - '0';
            if ( isMoveOK(r,c,*Cur) ) go(r,c,*Cur);
            else go(r,c,*Cur='W'-*Cur+'B');

            int white = 0, black = 0;
            for(int i=1;i<=8;++i)for(int j=1;j<=8;++j){
                if ( 'B' == B[i][j] ) ++black;
                else if ( 'W' == B[i][j] ) ++white;
            }
            printf("Black - %2d White - %2d\n",black,white);

            *Cur = 'W'-*Cur+'B';
            continue;
        }

        int flag = 0;
        for(int i=1;i<=8;++i)for(int j=1;j<=8;++j){
            if ( 'W' == B[i][j] || 'B' == B[i][j] ) continue;

            if ( isMoveOK(i,j,*Cur) ){
                if ( flag ) printf(" ");
                printf("(%d,%d)",i,j);
                ++flag;
            }
        }
        if ( 0 == flag ) printf("No legal move.");
        printf("\n");
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for (int kase=0;kase<nofkase;++kase){
        for(int i=1;i<=8;++i)scanf("%s",B[i]+1);
        scanf("%s",Cur);

        if ( kase )printf("\n");

        proc();

        for(int i=1;i<=8;++i){
            printf("%s\n",B[i]+1);
        }
    }
    return 0;
}