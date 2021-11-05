/*
    ���̵�������δ֪�����������ܲ�ͬ
    Nյ�ƣ�M�����أ�ÿ�����ؿ������ɸ��ơ�
    ������ʼ״̬��Ҫ�����еư���һ���ж����ַ�����
    ���뱣֤������һ�֡�
    ���i�����������ɸ�j���ؿ��Ƶģ���ʼ״̬ΪBi����
    Bi + SIGMA( Xj ) = 0
    �����ǰ�λ�ӣ��ȼ���
    SIGMA( Xj ) = Bi
    һ����N�����̣�M��δ֪��
    ʵ���Ͼ����󷽳̽�ı�Ԫ�ĸ���������Ϊ0��ʾ��Ψһ��
    ���뱣֤�н�
*/
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int const SIZE_OF_COLUMN = 101;

void disp(int(*a)[SIZE_OF_COLUMN],int row,int col){
    for(int i=0;i<row;++i){
        for(int j=0;j<=col;++j){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

char S[101][40] = {'\0'};
void initPowOf2(){
    S[0][0] = '1';
    for(int i=1;i<=100;++i){
        int j=0, carry = 0;
        for(;S[i-1][j];++j){
            S[i][j] = ( (S[i-1][j]-'0') << 1 ) + carry;
            carry = S[i][j] / 10;
            S[i][j] = S[i][j]%10 +'0';
        }

        if ( carry ) S[i][j] = '1';
        reverse(S[i-1],S[i-1]+j);
    }

    reverse(S[100],S[100]+strlen(S[100]));
}

//a���������
//cntOfEq�Ƿ��̵ĸ�����cntOfUnknown��δ֪���ĸ���
//���뱣֤�н�
int Gauss(int(*a)[SIZE_OF_COLUMN],int cntOfEq,int cntOfUnknown){
    int row = 0, col = 0;
    for(;row<cntOfEq&&col<cntOfUnknown;++row,++col){
        //������Ԫ���˴�Ϊ1����
        int maxr = row;
        while( maxr < cntOfEq && 0 == a[maxr][col] ) ++maxr;

        //��Ԫ�п���Ϊ���ɱ�Ԫ
        if ( maxr == cntOfEq ){
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

    return cntOfUnknown - row;//���ر�Ԫ�ĸ���������Ϊ0��Ψһ�⣬���̱�֤�н�
}

int A[SIZE_OF_COLUMN][SIZE_OF_COLUMN];
int N,M;
void read(){
    memset(A,0,sizeof(A));

    scanf("%d%d",&N,&M);
    for(int i=0;i<N;++i) scanf("%d",A[i]+M);

    int t,d;
    for(int i=0;i<M;++i){
        scanf("%d",&d);
        while(d--){
            scanf("%d",&t);
            A[--t][i] = 1;
        }
    }
}

int main(){
    //freopen("1.txt","w",stdout);
    initPowOf2();

    int ans,nofkase;
    scanf("%d",&nofkase);

    while(nofkase--){
        read();
        ans = Gauss(A,N,M);
        printf("%s\n",S[ans]);
    }
    return 0;
}
