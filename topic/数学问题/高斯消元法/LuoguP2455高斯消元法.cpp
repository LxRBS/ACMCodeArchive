/**
    ��nԪһ�����Է�����
    ����������δ֪��������һ�µ�
    Ҫ���жϽ�������0�⣬1�⣬���
    1������»���Ҫ�����
*/
#include <bits/stdc++.h>
using namespace std;

int const SIZE_OF_COLUMN = 55;//TODO

double const EPS = 1E-12;
inline double is0(double x){return -EPS<x&&x<EPS;}

//ax = b, and b will be the result after calling, a will be the identity matrix, 0 indexed
//cntOfEq is the amount of equations, it is count of rows in fact.
//cntOfUnkown is the amount of X, it is count of columns in fact.
//returns 1 if there is a solution, 2 if there are multi solutions, 0 if no solution
int GaussColumnPivot(double (*a)[SIZE_OF_COLUMN],double b[],int cntOfEq,int cntOfUnkown){
    for(int k=0,col=0;k<cntOfEq&&col<cntOfUnkown;++k,++col){
        int maxr = k;
        for(int i=k+1;i<cntOfEq;++i){
            if ( fabs(a[i][col]) > fabs(a[maxr][col]) ){
                maxr = i;
            }
        }

        if ( is0(a[maxr][col]) ) continue;

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
    //�жϽ�����
    //������̵���������δ֪������������b���붼Ϊ0�������޽�
    for(int i=cntOfUnkown;i<cntOfEq;++i){
        if(!is0(b[i])) return 0;
    }
    int ret = cntOfUnkown > cntOfEq ? 2: 1;
    for(int i=cntOfEq-1;i>=0;--i){
        //�����Ԫ֮��ȫΪ0����bi������0
        bool flag = true;
        for(int j=i;j<cntOfUnkown;++j){
            if(!is0(a[i][j])){
                flag = false;
                break;
            }
        }
        //�����Ԫ֮��ȫΪ0����b��Ϊ0�����޽�;bΪ0����ܶ��
        if(flag){
            if(!is0(b[i])) return 0;
            ret = 2;
        }
    }
    return ret;
}

double A[55][55],B[55];
int main(){
    //freopen("1.txt","r",stdin);
    int n,m;
    scanf("%d",&n);
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j)scanf("%lf",A[i]+j);
        scanf("%lf",B+i);
    }
    int ret = GaussColumnPivot(A,B,n,n);
    if(ret!=1) {
        printf("%d\n",ret==2?0:-1);
        return 0;
    }
    for(int i=0;i<n;++i)printf("x%d=%.2f\n",i+1,B[i]);
    return 0;
}

