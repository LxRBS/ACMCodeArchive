/*
  给定n个数，从中挑选一些使其乘积为完全平方数，问一共有多少种挑法
  显然要挑成对的质因子，使用异或高斯消元法
  用01列向量X表示是否选择某个数，
  设质因子总数为m个，则对每一个质因子可以列出一个方程，有：
  AX = 0
  系数矩阵aij的涵义是如果第j个数能够带来奇数个第i个质因子，则为1，否则为0
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

typedef long long int llt;
llt const MOD = 1000000007LL;

//线性筛法
int const SIZE = 2000;//
bool isComp[SIZE] = {false};//isComp[i]为真说明i是合数
int P[SIZE];//P[i]为第i个素数，i从0开始
int PCnt = 0;//PCnt记录1~SIZE之间的素数的个数
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

//a是增广矩阵
//cntOfEq是方程的个数，cntOfUnknown是未知数的个数
//输入保证有解
int Gauss(int(*a)[SIZE_OF_COLUMN],int cntOfEq,int cntOfUnknown){
    int row = 0, col = 0;
    for(;row<cntOfEq&&col<cntOfUnknown;++row,++col){
        //找列主元，此处为1即可
        int maxr = row;
        while( maxr < cntOfEq && 0 == a[maxr][col] ) ++maxr;

        //该元有可能为自由变元
        if ( maxr == cntOfEq ){
            --row;
            continue;
        }

        //交换
        if ( maxr != row ){
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

    //disp(a,cntOfEq,cntOfUnknown);

    return cntOfUnknown - row;//返回自由变元的数量
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
        //构造系数矩阵
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
