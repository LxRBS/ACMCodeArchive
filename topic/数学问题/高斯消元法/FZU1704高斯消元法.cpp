/*
    方程的数量和未知数的数量可能不同
    N盏灯，M个开关，每个开关控制若干个灯。
    给定初始状态，要将所有灯按灭，一共有多少种方法。
    输入保证至少有一种。
    令第i个灯是由若干个j开关控制的，初始状态为Bi，则
    Bi + SIGMA( Xj ) = 0
    由于是按位加，等价于
    SIGMA( Xj ) = Bi
    一共有N个方程，M个未知数
    实际上就是求方程解的变元的个数，个数为0表示有唯一解
    输入保证有解
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

    return cntOfUnknown - row;//返回变元的个数，数量为0即唯一解，方程保证有解
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
