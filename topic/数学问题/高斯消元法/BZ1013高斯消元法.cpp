/*
    ����������n+1��������꣬����������
    ����������Ϊ(x1,x2,...,xn)��һ��n��δ֪��
    ���ڸ����ĵ�i���㣬��
    (xi1-x1)^2 + ... + (xin-xn)^2 = R^2
    ��
    2 xi1 x1 + ... + 2 xin xn = SIGMA( xij ^ 2 ) + SIGMA( xi ^ 2 ) - R ^ 2
    �������������
    2 ( xi1 - xi+11 ) xi + ... + 2 ( xin - xi+1n) xn = SIGMA( xij^2 ) - SIGMA( xi+1j^2 )
*/
#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;


double const EPS = 1E-8;
int const SIZE_OF_COLUMN = 12;

inline bool is0(double x){return -EPS<x&&x<EPS;}

//a���������cntOfEq�С�(cntOfUnknown+1)��
//cntOfEq�Ƿ��̵ĸ�����cntOfUnknown��δ֪���ĸ���
//���뱣֤��Ψһ��
int Gauss(double(*a)[SIZE_OF_COLUMN],int cntOfEq,int cntOfUnknown){
    for(int row=0,col=0;row<cntOfEq&&col<cntOfUnknown;++row,++col){
        //������Ԫ
        int maxr = row;
        for(int i=row+1;i<cntOfEq;++i){
            if ( fabs(a[i][col]) > fabs(a[maxr][col]) ){
                maxr = i;
            }
        }

        //��Ψһ�⣬����Ԫ������Ϊ0�����ж�

        //����
        if ( row != maxr ){
            for(int j=col;j<=cntOfUnknown;++j){
                swap(a[row][j],a[maxr][j]);
            }
        }

        //����row�е�col�й�һ��
        for(int j=col+1;j<=cntOfUnknown;++j) a[row][j] /= a[row][col];
        a[row][col] = 1.0;

        //����col��������Ԫ�ر�Ϊ0
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
