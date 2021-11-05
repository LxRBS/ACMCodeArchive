/*
    ��N�����ӣ�������ӵĽ���ż���������ǳ��ӵĽ���������
    ��ץ���ɳ����ж���ż��һ������M��
    �����ÿ�����ӵ���ż�ԣ�������һ�⣬Ҳ���ܶ�⣬��һ��������Ҫ�������˳����������ķ��̵ĸ���
    N��δ֪����M������
*/
#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

int const SIZE_OF_COLUMN = 2010;


//a���������cntOfEq�С�(cntOfUnknown+1)��
//x�ǽ⣬һ��������
//cntOfEq�Ƿ��̵ĸ�����cntOfUnknown��δ֪���ĸ���
//���뱣֤�н�
int Gauss(int(*a)[SIZE_OF_COLUMN],int x[],int cntOfEq,int cntOfUnknown){
    int row = 0,col = 0, ret = 0;
    for(;row<cntOfEq&&col<cntOfUnknown;++row,++col){
        //������Ԫ
        int maxr = row;
        while( maxr < cntOfEq && 0 == a[maxr][col] ) ++maxr;

        //��ǰ��ԪΪ0�������ɱ�Ԫ��˵���ж��
        if ( maxr == cntOfEq ){
            return 0;
        }

        //maxr�ǽⷽ������Ҫ�õ�����Զ�ķ��̱�ţ���0��ʼ
        ret = max(ret,maxr);

        //����
        if ( row != maxr ){
            for(int j=col;j<=cntOfUnknown;++j){
                swap(a[row][j],a[maxr][j]);
            }
        }

        //����row�����µ��еĵ�col������
        for(int i=row+1;i<cntOfEq;++i)if(a[i][col]){
            for(int j=col;j<=cntOfUnknown;++j){
                a[i][j] ^= a[row][j];
            }
        }
    }

    //��Ψһ�⣬��⣬��ʱa����������
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
