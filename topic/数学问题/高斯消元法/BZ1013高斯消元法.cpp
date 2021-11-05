/*
    给定球面上n+1个点的坐标，求球心坐标
    设球心坐标为(x1,x2,...,xn)，一共n个未知数
    对于给定的第i个点，有
    (xi1-x1)^2 + ... + (xin-xn)^2 = R^2
    即
    2 xi1 x1 + ... + 2 xin xn = SIGMA( xij ^ 2 ) + SIGMA( xi ^ 2 ) - R ^ 2
    方程两两相减有
    2 ( xi1 - xi+11 ) xi + ... + 2 ( xin - xi+1n) xn = SIGMA( xij^2 ) - SIGMA( xi+1j^2 )
*/
#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;


double const EPS = 1E-8;
int const SIZE_OF_COLUMN = 12;

inline bool is0(double x){return -EPS<x&&x<EPS;}

//a是增广矩阵，cntOfEq行×(cntOfUnknown+1)列
//cntOfEq是方程的个数，cntOfUnknown是未知数的个数
//输入保证有唯一解
int Gauss(double(*a)[SIZE_OF_COLUMN],int cntOfEq,int cntOfUnknown){
    for(int row=0,col=0;row<cntOfEq&&col<cntOfUnknown;++row,++col){
        //找列主元
        int maxr = row;
        for(int i=row+1;i<cntOfEq;++i){
            if ( fabs(a[i][col]) > fabs(a[maxr][col]) ){
                maxr = i;
            }
        }

        //有唯一解，列主元不可能为0，不判断

        //交换
        if ( row != maxr ){
            for(int j=col;j<=cntOfUnknown;++j){
                swap(a[row][j],a[maxr][j]);
            }
        }

        //将第row行第col列归一化
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

    return 1;
}

int N;
double Z[12][12];
double A[SIZE_OF_COLUMN][SIZE_OF_COLUMN],X[SIZE_OF_COLUMN];
int main(){
    scanf("%d",&N);
    for(int i=0;i<=N;++i){
        for(int j=0;j<N;++j){
            scanf("%lf",Z[i]+j);
        }
    }
    for(int i=0;i<N;++i){
        A[i][N] = 0.0;
        for(int j=0;j<N;++j){
            A[i][j] = 2.0 * ( Z[i][j] - Z[i+1][j] );
            A[i][N] += Z[i][j] * Z[i][j] - Z[i+1][j] * Z[i+1][j];
        }
    }

    Gauss(A,N,N);

    printf("%.3f",A[0][N]);
    for(int i=1;i<N;++i) printf(" %.3f",A[i][N]);
    putchar('\n');

    return 0;
}
