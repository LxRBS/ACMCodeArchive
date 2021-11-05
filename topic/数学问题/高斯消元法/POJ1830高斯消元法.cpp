/*
    N�����أ�����ÿ������ʱ����Ӱ�쵽�������ɿ���
    ������ʼ״̬��Ŀ��״̬�����ж����ַ������Դﵽ��
    ���i�����س�ʼ״̬ΪSi����̬ΪTi���ÿ��ػᱻ���ɸ���������Ӱ�죬���Ϊj����
    Xi + SIGMA( Xj ) + Si = Ti
    �����ǰ�λ�ӣ��ȼ���
    Xi +SIGMA( Xj ) = Si +Ti
    N��δ֪����N������
    δ����Ψһ�⣬ʵ���Ͼ�������Ԫ�ĸ�����ÿ����Ԫ��������ȡ0����1
    ֻ�������Ԫ�ĸ������������
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int const SIZE_OF_COLUMN = 30;

void disp(int(*a)[SIZE_OF_COLUMN],int row,int col){
    for(int i=0;i<row;++i){
        for(int j=0;j<=col;++j){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//a���������
//cntOfEq�Ƿ��̵ĸ�����cntOfUnknown��δ֪���ĸ���
//������ڶ�⡢һ���������������Ϊ���ɱ�Ԫ������
int Gauss(int(*a)[SIZE_OF_COLUMN],int cntOfEq,int cntOfUnknown){
    int row = 0, col = 0;
    for(;row<cntOfEq&&col<cntOfUnknown;++row,++col){
        //������Ԫ���˴�Ϊ1����
        int maxr = row;
        while( maxr < cntOfEq && 0 == a[maxr][col] ) ++maxr;

        //���е�row�м�����ȫΪ0����Ҫ���ǵ�row�е���һ��
        if ( maxr == cntOfEq ) {
            --row;
            continue;
        }

        //����
        if ( maxr != row ){
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

    //disp(a,cntOfEq,cntOfUnknown);

    //���ȫ0�е��������Ƿ�ҲΪ0
    for(int i=row;i<cntOfEq;++i){
        if ( a[i][col] ) return -1;//�޽�
    }

    return cntOfUnknown - row;//���ر�Ԫ�ĸ���������Ϊ0��Ψһ��
}

int A[SIZE_OF_COLUMN][SIZE_OF_COLUMN];
int N;
void read(){
    memset(A,0,sizeof(A));

    scanf("%d",&N);
    for(int i=0;i<N;++i) scanf("%d",A[i]+N);

    int t;
    for(int i=0;i<N;++i){
        scanf("%d",&t);
        A[i][N] ^= t;
        A[i][i] = 1;
    }

    int a,b;
    while(scanf("%d%d",&a,&b)&&a&&b){
        --a,--b;
        A[b][a] = 1;
    }
}
int main(){
    //freopen("1.txt","r",stdin);

    int ans,nofkase;
    scanf("%d",&nofkase);

    while(nofkase--){
        read();
        if ( -1 == (ans=Gauss(A,N,N)) ) printf("Oh,it's impossible~!!\n");
        else printf("%d\n",1<<ans);
    }
    return 0;
}
