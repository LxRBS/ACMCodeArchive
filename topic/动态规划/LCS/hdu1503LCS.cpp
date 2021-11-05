//LCS, and need to print.

#include <cstdio>
#include <cstring>
using namespace std;
int const SIZE = 105;

int DP[SIZE][SIZE] = {0};
int Flag[SIZE][SIZE];//用来标识最长序列的方向
int const LEFT = 1;
int const DIAG = 2;
int const UP = 4;

//source strings
char A[SIZE],B[SIZE];

//LCS dp function
void lcs(char const a[],int la,char const b[],int lb){
    memset(Flag,0,sizeof(Flag));

    for(int i=1;i<=la;++i)Flag[i][0] = UP;
    for(int j=1;j<=lb;++j)Flag[0][j] = LEFT;

    //索引要减1
    for(int i=1;i<=la;++i)for(int j=1;j<=lb;++j){
        if (a[i-1] == b[j-1]){
            DP[i][j] = DP[i-1][j-1] + 1;
            Flag[i][j] = DIAG;
            continue;
        }

        if ( DP[i-1][j] > DP[i][j-1] ){
            DP[i][j] = DP[i-1][j];
            Flag[i][j] = UP;
        }else{
            DP[i][j] = DP[i][j-1];
            Flag[i][j] = LEFT;
        }
    }
}

void output(int idx,int jdx){
    if (0 == idx && 0 == jdx ) return;

    if (DIAG == Flag[idx][jdx]){
        output(idx-1,jdx-1);
        putchar(A[idx-1]);
    }else if (UP == Flag[idx][jdx]){
        output(idx-1,jdx);
        putchar(A[idx-1]);
    }else if (LEFT == Flag[idx][jdx]){
        output(idx,jdx-1);
        putchar(B[jdx-1]);
    }
}

void proc(){
    lcs(A,strlen(A),B,strlen(B));
    output(strlen(A),strlen(B));
    putchar('\n');
}

int main()
{
    while(EOF != scanf("%s%s",A,B)) proc();
    return 0;
}
