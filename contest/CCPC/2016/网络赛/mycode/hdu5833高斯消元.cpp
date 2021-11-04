/*
  ����n������������ѡһЩʹ��˻�Ϊ��ȫƽ��������һ���ж���������
  ��ȻҪ���ɶԵ������ӣ�ʹ������˹��Ԫ��
  ��01������X��ʾ�Ƿ�ѡ��ĳ������
  ������������Ϊm�������ÿһ�������ӿ����г�һ�����̣��У�
  AX = 0
  ϵ������aij�ĺ����������j�����ܹ�������������i�������ӣ���Ϊ1������Ϊ0
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef long long int llt;
llt const MOD = 1000000007LL;

//����ɸ��
int const SIZE = 2000;//
bool isComp[SIZE] = {false};//isComp[i]Ϊ��˵��i�Ǻ���
int P[SIZE];//P[i]Ϊ��i��������i��0��ʼ
int PCnt = 0;//PCnt��¼1~SIZE֮��������ĸ���
void sieve(){
    for(int i=2;i<SIZE;++i){
        if ( !isComp[i] ) P[PCnt++] = i;

        for(int j=0;j<PCnt&&i*P[j]<SIZE;++j){
            isComp[i*P[j]] = true;
            if ( 0 == i % P[j] ) break;
        }
    }
}

//returns a^n%mod
llt powerMod(llt a,llt n,llt mod){
    llt ret = 1;
    a %= mod;

    while( n ){
        if ( n & 1 ) ret = ret * a % mod;
        n >>= 1;
        a = a * a % mod;
    }
    return ret;
}

int const SIZE_OF_COLUMN = 310;

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

    return cntOfUnknown - row;//�������ɱ�Ԫ������
}

int N,M;
int P2I[2100];
int A[SIZE_OF_COLUMN][SIZE_OF_COLUMN];

void read(){
    M = 0;
    fill(P2I,P2I+2100,-1);
    memset(A,0,sizeof(A));

    scanf("%d",&N);
    llt a;
    for(int i=0;i<N;++i){
        scanf("%I64d",&a);
        //����ϵ������
        //*
        for(int k=0;a!=1;++k){
            if ( a % P[k] ) continue;

            int kk = 0;
            while( 0 == a%P[k] ) a/=P[k], kk^=1;

            if ( -1 == P2I[P[k]] ) P2I[P[k]] = M++;
            A[P2I[P[k]]][i] = kk;
        }
        //*/
        /*
        for(int k=0;k<PCnt;++k){
            if ( a%P[k] ) continue;

            int kk=0;
            while( 0 == a%P[k] ) a/=P[k], kk^=1;
            A[k][i] = kk;
        }
        //*/
    }
    return;
}

int main(){
    //freopen("1.txt","r",stdin);
    sieve();//printf("%d ",PCnt);for(int i=0;i<PCnt;++i)printf("%d ",P[i]);

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        read();

        int ans = Gauss(A,M,N);
        ans = powerMod(2LL,ans,MOD);
        printf("Case #%d:\n%d\n",kase,--ans);
    }
    return 0;
}
