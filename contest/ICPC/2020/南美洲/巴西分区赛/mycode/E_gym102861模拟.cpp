/**
    给定一个字符串，表示一个羽毛球的比赛
    对每一个Q，要求输出当时的比分情况
*/
#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define fi first
#define se second

int const LEFT = 0;
int const RIGHT = 1;

char A[1010], B[1010];

int main(){
    //freopen("1.txt","r",stdin);
    scanf("%s", A);

    int game[2] = {0};  // 局数
    int score[2] = {0}; // 分数
    int cur = LEFT; // 当前发球者
    for(char *p=A;*p;++p){
        if('Q'==*p){
            if(game[0]<2&&game[1]<2){//未结束，报必分
                sprintf(B, "%d (%d) - %d (%d)", game[LEFT], score[LEFT], game[RIGHT],score[RIGHT]);
                if(LEFT==cur){
                    char *p=B;
                    while(*p!=')')putchar(*p++);
                    putchar('*');
                    puts(p);
                }else{
                    int n = strlen(B);
                    B[n-1] = '\0';
                    printf("%s*)\n", B);
                }
            }else if(2==game[0]){
                printf("2 (winner) - %d\n", game[1]);
            }else if(2==game[1]){
                printf("%d - 2 (winner)\n", game[0]);
            }else{
                throw runtime_error("YYYY");
            }
        }else{
            if('S'==*p){ //发球者得分
                ++score[cur];
            }else if('R'==*p){ //接球者得分，交换发球权
                cur ^= 1;
                ++score[cur];
            }
            int osn = cur ^ 1;
            if(10==score[cur]||(score[cur]>=5&&score[cur]>=2+score[osn])){ //一局结束
                ++game[cur];
                score[0] = score[1] = 0;
                /// 要不要对局数进行判断?
            }
        }
    }
    return 0;
}