#include <cstdio>
#include <cstring>

char A[10][10];
char Cmd[10000];
int main(){
    //freopen("1.txt","r",stdin);

    for(int kase=1;;++kase){
        gets(A[0]);    //��ʽ�ı���������ʹ��gets���������ֻʹ��fgets������Ҫע��fgets����'\n'��'\0'��β����getsֻ����'\0'��β�����Ӱ����������еľ����ж�����
        if ( 'Z' == A[0][0] && '\0' == A[0][1] ) break;

        gets(A[1]);gets(A[2]);gets(A[3]);gets(A[4]);

        //find the empty position
        int row = 0, col = 0;
        for(;row<5;++row){
            for(col=0;col<5;++col){
                if ( ' ' == A[row][col] || '\0' == A[row][col] ){
                    A[row][col] = ' ';//ע��ո���п�����һ�е�ĩβ
                    goto L;
                }
            }
        }

        L:
        bool isOK = true;
        bool flag = true;
        bool continueEnabled = false;
        while(flag){
            gets(Cmd);      //ָ������ж��У����Ա����ָ����꣬�����Ƿ��ܹ���ȷִ��
            int len = strlen(Cmd);
            if ( '0' == Cmd[len-1] ) Cmd[len-1] = '\0', flag = false;

            if ( continueEnabled ) continue;

            for(char *p=Cmd;*p;++p){//��ÿ��ָ���ж��Ƿ���У��Ӷ�������Ӧ�ı�־λ����ִ��
                switch(*p){
                case 'A':{
                    if ( 0 == row ){
                        isOK = false;
                        continueEnabled = true;
                        goto L2;
                    }
                    A[row][col] = A[row-1][col];
                    A[row-1][col] = ' ';
                    --row;
                }break;
                case 'B':{
                    if ( 4 == row ){
                        isOK = false;
                        continueEnabled = true;
                        goto L2;
                    }
                    A[row][col] = A[row+1][col];
                    A[row+1][col] = ' ';
                    ++row;
                }break;
                case 'L':{
                    if ( 0 == col ){
                        isOK = false;
                        continueEnabled = true;
                        goto L2;
                    }
                    A[row][col] = A[row][col-1];
                    A[row][col-1] = ' ';
                    --col;
                }break;
                case 'R':{
                    if ( 4 == col ){
                        isOK = false;
                        continueEnabled = true;
                        goto L2;
                    }
                    A[row][col] = A[row][col+1];
                    A[row][col+1] = ' ';
                    ++col;
                }break;
                default:isOK = false;
                        continueEnabled = true;
                        goto L2;
                }
            }
            L2:;//nothing here
        }
        //output
        if ( kase > 1 ) printf("\n");
        printf("Puzzle #%d:\n",kase);

        if ( !isOK ){
            printf("This puzzle has no final configuration.\n");
            continue;
        }

        for(int i=0;i<5;++i){
            printf("%c",A[i][0]);
            for(int j=1;j<5;++j)printf(" %c",A[i][j]);
            printf("\n");
        }
    }

    return 0;
}
