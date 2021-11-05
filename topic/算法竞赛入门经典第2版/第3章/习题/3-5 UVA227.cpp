#include <cstdio>
#include <cstring>

char A[10][10];
char Cmd[10000];
int main(){
    //freopen("1.txt","r",stdin);

    for(int kase=1;;++kase){
        gets(A[0]);    //老式的编译器还能使用gets，但是最好只使用fgets，但是要注意fgets会以'\n'加'\0'结尾，而gets只会以'\0'结尾，这会影响下面代码中的具体判断条件
        if ( 'Z' == A[0][0] && '\0' == A[0][1] ) break;

        gets(A[1]);gets(A[2]);gets(A[3]);gets(A[4]);

        //find the empty position
        int row = 0, col = 0;
        for(;row<5;++row){
            for(col=0;col<5;++col){
                if ( ' ' == A[row][col] || '\0' == A[row][col] ){
                    A[row][col] = ' ';//注意空格很有可能在一行的末尾
                    goto L;
                }
            }
        }

        L:
        bool isOK = true;
        bool flag = true;
        bool continueEnabled = false;
        while(flag){
            gets(Cmd);      //指令可能有多行，所以必须把指令都读完，无论是否能够正确执行
            int len = strlen(Cmd);
            if ( '0' == Cmd[len-1] ) Cmd[len-1] = '\0', flag = false;

            if ( continueEnabled ) continue;

            for(char *p=Cmd;*p;++p){//对每个指令判断是否可行，从而设置相应的标志位并且执行
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
