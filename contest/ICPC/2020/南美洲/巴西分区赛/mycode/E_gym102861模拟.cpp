/**
    ����һ���ַ�������ʾһ����ë��ı���
    ��ÿһ��Q��Ҫ�������ʱ�ıȷ����
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

    int game[2] = {0};  // ����
    int score[2] = {0}; // ����
    int cur = LEFT; // ��ǰ������
    for(char *p=A;*p;++p){
        if('Q'==*p){
            if(game[0]<2&&game[1]<2){//δ���������ط�
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
            if('S'==*p){ //�����ߵ÷�
                ++score[cur];
            }else if('R'==*p){ //�����ߵ÷֣���������Ȩ
                cur ^= 1;
                ++score[cur];
            }
            int osn = cur ^ 1;
            if(10==score[cur]||(score[cur]>=5&&score[cur]>=2+score[osn])){ //һ�ֽ���
                ++game[cur];
                score[0] = score[1] = 0;
                /// Ҫ��Ҫ�Ծ��������ж�?
            }
        }
    }
    return 0;
}
