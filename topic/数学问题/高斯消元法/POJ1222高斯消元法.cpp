/*
    5行×6列开关，每按下1个开关会影响4邻域
    给定初始状态，问如何按才能全按灭。
    显然每个开关要么按，要么不按。
    一共有30个开关，即30个未知数，每个解要么是0要么是1.
    对于第i个开关而言，令第j1234个开关是能够对其造成影响的另外4个开关，则有
    xi + xj1 + xj2 + xj3 + xj4 + bi = 0
    由于此处的加法是按位加，所以等价于
    xi + xj1 + xj2 + xj3 + xj4 = bi
    对每一个i都有一个如下方程，30个未知数，30个方程。
    且输入保证有唯一解，可以使用高斯消元法。
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int const SIZE_OF_COLUMN = 32;

void disp(int(*a)[SIZE_OF_COLUMN],int row,int col){
    for(int i=0;i<row;++i){
        for(int j=0;j<=col;++j){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//a是增广矩阵，x是解
//cntOfEq是方程的个数，cntOfUnknown是未知数的个数
//输入保证有唯一解
int Gauss(int(*a)[SIZE_OF_COLUMN],int x[],int cntOfEq,int cntOfUnknown){
    int row = 0,col = 0;
    for(;row<cntOfEq&&col<cntOfUnknown;++row,++col){
        //找到列主元，此处为1即可
        int maxr = row;
        while( maxr < cntOfEq && 0 == a[maxr][col] ) ++maxr;

        //交换
        if ( maxr != row ){
            for(int j=col;j<=cntOfUnknown;++j){
                swap(a[row][j],a[maxr][j]);
            }
        }

        //将第row行以下的行的第col列元素清零
        for(int i=row+1;i<cntOfEq;++i)if(a[i][col]){
            for(int j=col;j<=cntOfUnknown;++j){
                a[i][j] ^= a[row][j];
            }
        }
    }

    //disp(a,cntOfEq,cntOfUnknown);

    //此时a应该是一个上三角阵
    for(int i=cntOfEq-1;i>=0;--i){
        x[i] = a[i][cntOfUnknown];
        for(int j=i+1;j<cntOfEq;++j){
            x[i] ^= ( x[j] && a[i][j] );
        }
    }

    return 1;
}

int const DR[] = {-1,1,0,0};
int const DC[] = {0,0,-1,1};

int A[SIZE_OF_COLUMN][SIZE_OF_COLUMN];
int X[SIZE_OF_COLUMN];

void read(){
    memset(A,0,sizeof(A));

    for(int i=0;i<30;++i){
        A[i][i] = 1;

        int r = i / 6;
        int c = i % 6;

        for(int d=0;d<4;++d){
            int dr = r + DR[d];
            int dc = c + DC[d];

            if ( 0 <= dr && dr < 5 && 0 <= dc && dc < 6 ){
                int di = dr * 6 + dc;
                A[di][i] = 1;
            }
        }

        scanf("%d",A[i]+30);
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        read();
        Gauss(A,X,30,30);

        printf("PUZZLE #%d\n",kase);
        for(int i=0;i<5;++i){
            putchar('0'+X[i*6]);
            for(int j=1;j<6;++j){
                putchar(' '),putchar('0'+X[i*6+j]);
            }
            putchar('\n');
        }
    }
    return 0;
}
