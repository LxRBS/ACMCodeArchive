/*
    10×10的棋盘，玩蛇和梯子的游戏。到达蛇头会无条件向下跳到蛇尾，到达梯底会无条件跳到梯顶
    每一步掷一个6面骰子，如果某一步会越过终点，则该步的效果相当于原地不动
    问从起点到终点的期望步数
    令Di为从i到终点的期望步数，则
    Di = SIGMA( P(i到j的概率) * ( Dj + 1 ) )
    其中j为i+1到i+6
    如果没有蛇的存在，则求Di所需的Dj均在Di之前会被求出
    但有蛇存在，则未必，因此求Di时，可能某个Dj还处于未知状况，需要列方程求解
    题目保证有解
*/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int const SIZE_OF_COLUMN = 101;

FILE *fp = fopen("2.txt","w");
void disp(FILE *fp,double(*a)[SIZE_OF_COLUMN],int row,int col){
    for(int i=0;i<row;++i){
        for(int j=0;j<=col;++j){
            fprintf(fp,"%10.3f ",a[i][j]);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp,"\n");
}

//a是增广矩阵，cntOfEq是方程个数即行数，cntOfUnknown是未知数个数即列数
int Gauss(double(*a)[SIZE_OF_COLUMN],int cntOfEq,int cntOfUnknown){
    int row = 0, col = 0;
    for(;row<cntOfEq&&col<cntOfUnknown;++row,++col){
        //找主元
        int maxr = row;
        for(int i=row+1;i<cntOfEq;++i){
            if ( fabs(a[maxr][col]) < fabs(a[i][col]) ){
                maxr = i;
            }
        }

        //主元为0，说明有自由变元，此处不可能

        //交换
        if ( maxr != row ){
            for(int j=col;j<=cntOfUnknown;++j){
                swap(a[maxr][j],a[row][j]);
            }
        }

        //将row行第col列归一化
        for(int j=col+1;j<=cntOfUnknown;++j) a[row][j] /= a[row][col];
        a[row][col] = 1.0;

        //将第col列其他行元素变为0
        for(int i=0;i<cntOfEq;++i)if(i!=row){
            for(int j=col+1;j<=cntOfUnknown;++j){
                a[i][j] -= a[row][j] * a[i][col];
            }
            a[i][col] = 0.0;
        }
    }

    //disp(fp,a,cntOfEq,cntOfUnknown);

    return 1;
}

int N;
int Jump[101];

void read(){
    memset(Jump,-1,sizeof(Jump));

    scanf("%d",&N);

    int a,b;
    for(int i=0;i<N;++i){
        scanf("%d%d",&a,&b);
        Jump[--a] = --b;
    }
}

double A[101][101];
double dp(){
    memset(A,0,sizeof(A));

    //因为Gauss消元法使用的数组是0索引的，所以这里将地图范围也改为0~99
    A[99][99] = 1.0;
    A[99][100] = 0.0;
    for(int i=98;i>=0;--i){
        A[i][i] = 1.0;

        if ( -1 != Jump[i] ){
            A[i][Jump[i]] = -1.0;
            A[i][100] = 0.0;
            continue;
        }

        int cnt = ( i + 6 > 99 ) ? 99 - i : 6;
        for(int j=1;j<=cnt;++j){
            A[i][i+j] = - 1.0 / cnt;
        }
        A[i][100] = 6.0 / cnt;
    }

    Gauss(A,100,100);

    return A[0][100];
}

int main(){
    //freopen("1.txt","r",stdin);

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        read();
        printf("Case %d: %.10f\n",kase,dp());
    }
    return 0;
}

