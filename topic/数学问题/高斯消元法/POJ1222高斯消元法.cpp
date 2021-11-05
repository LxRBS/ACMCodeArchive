/*
    5�С�6�п��أ�ÿ����1�����ػ�Ӱ��4����
    ������ʼ״̬������ΰ�����ȫ����
    ��Ȼÿ������Ҫô����Ҫô������
    һ����30�����أ���30��δ֪����ÿ����Ҫô��0Ҫô��1.
    ���ڵ�i�����ض��ԣ����j1234���������ܹ��������Ӱ�������4�����أ�����
    xi + xj1 + xj2 + xj3 + xj4 + bi = 0
    ���ڴ˴��ļӷ��ǰ�λ�ӣ����Եȼ���
    xi + xj1 + xj2 + xj3 + xj4 = bi
    ��ÿһ��i����һ�����·��̣�30��δ֪����30�����̡�
    �����뱣֤��Ψһ�⣬����ʹ�ø�˹��Ԫ����
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

//a���������x�ǽ�
//cntOfEq�Ƿ��̵ĸ�����cntOfUnknown��δ֪���ĸ���
//���뱣֤��Ψһ��
int Gauss(int(*a)[SIZE_OF_COLUMN],int x[],int cntOfEq,int cntOfUnknown){
    int row = 0,col = 0;
    for(;row<cntOfEq&&col<cntOfUnknown;++row,++col){
        //�ҵ�����Ԫ���˴�Ϊ1����
        int maxr = row;
        while( maxr < cntOfEq && 0 == a[maxr][col] ) ++maxr;

        //����
        if ( maxr != row ){
            for(int j=col;j<=cntOfUnknown;++j){
                swap(a[row][j],a[maxr][j]);
            }
        }

        //����row�����µ��еĵ�col��Ԫ������
        for(int i=row+1;i<cntOfEq;++i)if(a[i][col]){
            for(int j=col;j<=cntOfUnknown;++j){
                a[i][j] ^= a[row][j];
            }
        }
    }

    //disp(a,cntOfEq,cntOfUnknown);

    //��ʱaӦ����һ����������
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
