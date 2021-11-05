/**
    高斯消元法解方程，实型，模板题
*/
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
using namespace std;

int const SIZE_OF_COLUMN = 110;//TODO

double const EPS = 1E-6;
inline double is0(double x){return -EPS<x&&x<EPS;}

//ax = b, and b will be the result after calling, a will be the identity matrix
//index from 0
//cntOfEq is the amount of equations, it is count of rows in fact.
//cntOfUnkown is the amount of X, it is count of columns in fact.
//returns 1 if there is solution
int GaussColumnPivot(double (*a)[SIZE_OF_COLUMN],double b[],int cntOfEq,int cntOfUnkown){
    for(int k=0,col=0;k<cntOfEq&&col<cntOfUnkown;++k,++col){
        int maxr = k;
        for(int i=k+1;i<cntOfEq;++i){
            if ( fabs(a[i][col]) > fabs(a[maxr][col]) ){
                maxr = i;
            }
        }

        if ( is0(a[maxr][col]) ) return 0;

        if ( k != maxr ){
            for(int j=col;j<cntOfUnkown;++j) swap(a[k][j],a[maxr][j]);
            swap(b[k],b[maxr]);
        }

        b[k] /= a[k][col];
        for(int j=col+1;j<cntOfUnkown;++j) a[k][j] /= a[k][col];
        a[k][col] = 1.0;

        for(int i=0;i<cntOfEq;++i){
            if ( i == k ) continue;

            b[i] -= a[i][k] * b[k];
            for(int j=col+1;j<cntOfUnkown;++j) a[i][j] -= a[k][j] * a[i][col];
            a[i][col] = 0.0;
        }
    }
    return 1;
}

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

double A[SIZE_OF_COLUMN][SIZE_OF_COLUMN],B[SIZE_OF_COLUMN];

int main(){
    //freopen("1.txt","r",stdin);
    int n = getInt();
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j)A[i][j] = getInt();
        B[i] = getInt();
    }
    int ret = GaussColumnPivot(A,B,n,n);
    if(!ret){
        printf("No Solution\n");
        return 0;
    }
    for(int i=0;i<n;++i)printf("%.2f\n",B[i]);
    return 0;
}
