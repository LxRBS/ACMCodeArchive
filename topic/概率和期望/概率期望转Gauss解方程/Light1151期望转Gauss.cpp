/*
    10��10�����̣����ߺ����ӵ���Ϸ��������ͷ������������������β�������ݵ׻������������ݶ�
    ÿһ����һ��6�����ӣ����ĳһ����Խ���յ㣬��ò���Ч���൱��ԭ�ز���
    �ʴ���㵽�յ����������
    ��DiΪ��i���յ��������������
    Di = SIGMA( P(i��j�ĸ���) * ( Dj + 1 ) )
    ����jΪi+1��i+6
    ���û���ߵĴ��ڣ�����Di�����Dj����Di֮ǰ�ᱻ���
    �����ߴ��ڣ���δ�أ������Diʱ������ĳ��Dj������δ֪״������Ҫ�з������
    ��Ŀ��֤�н�
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

//a���������cntOfEq�Ƿ��̸�����������cntOfUnknown��δ֪������������
int Gauss(double(*a)[SIZE_OF_COLUMN],int cntOfEq,int cntOfUnknown){
    int row = 0, col = 0;
    for(;row<cntOfEq&&col<cntOfUnknown;++row,++col){
        //����Ԫ
        int maxr = row;
        for(int i=row+1;i<cntOfEq;++i){
            if ( fabs(a[maxr][col]) < fabs(a[i][col]) ){
                maxr = i;
            }
        }

        //��ԪΪ0��˵�������ɱ�Ԫ���˴�������

        //����
        if ( maxr != row ){
            for(int j=col;j<=cntOfUnknown;++j){
                swap(a[maxr][j],a[row][j]);
            }
        }

        //��row�е�col�й�һ��
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

    //��ΪGauss��Ԫ��ʹ�õ�������0�����ģ��������ｫ��ͼ��ΧҲ��Ϊ0~99
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

