/*
    有N条虫子，地球虫子的脚是偶数个，外星虫子的脚是奇数个
    任抓若干虫子判断奇偶，一共进行M次
    最后问每个虫子的奇偶性，至少有一解，也可能多解，在一解的情况下要求输出按顺序的用于求解的方程的个数
    N个未知数，M个方程
*/
#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

int const SIZE_OF_COLUMN = 2010;


//a是增广矩阵，cntOfEq行×(cntOfUnknown+1)列
//x是解，一个列向量
//cntOfEq是方程的个数，cntOfUnknown是未知数的个数
//输入保证有解
int Gauss(int(*a)[SIZE_OF_COLUMN],int x[],int cntOfEq,int cntOfUnknown){
    int row = 0,col = 0, ret = 0;
    for(;row<cntOfEq&&col<cntOfUnknown;++row,++col){
        //找列主元
        int maxr = row;
        while( maxr < cntOfEq && 0 == a[maxr][col] ) ++maxr;

        //当前主元为0，是自由变元，说明有多解
        if ( maxr == cntOfEq ){
            return 0;
        }

        //maxr是解方程所需要用到的最远的方程编号，从0开始
        ret = max(ret,maxr);

        //交换
        if ( row != maxr ){
            for(int j=col;j<=cntOfUnknown;++j){
                swap(a[row][j],a[maxr][j]);
            }
        }

        //将第row行以下的行的第col列清零
        for(int i=row+1;i<cntOfEq;++i)if(a[i][col]){
            for(int j=col;j<=cntOfUnknown;++j){
                a[i][j] ^= a[row][j];
            }
        }
    }

    //有唯一解，求解，此时a是上三角阵
    for(int i=cntOfEq-1;i>=0;--i){
        x[i] = a[i][cntOfUnknown];
        for(int j=i+1;j<cntOfEq;++j){
            x[i] ^= ( x[j] & a[i][j] );
        }
    }

    return ret + 1;
}

int N,M;
int A[SIZE_OF_COLUMN][SIZE_OF_COLUMN],X[SIZE_OF_COLUMN];
char S[SIZE_OF_COLUMN];
int main(){
    //freopen("1.txt","r",stdin);

    scanf("%d%d",&N,&M);
    for(int i=0;i<M;++i){
        scanf("%s%d",S,A[i]+N);
        for(int j=0;j<N;++j) A[i][j] = S[j] - '0';
    }

    int ret = Gauss(A,X,M,N);
    if ( 0 == ret ) {
        printf("Cannot Determine\n");
        return 0;
    }

    printf("%d\n",ret);
    for(int i=0;i<N;++i){
        printf(X[i]?"?y7M#\n":"Earth\n");
    }
    return 0;
}
