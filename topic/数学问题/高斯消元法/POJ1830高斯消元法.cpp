/*
    N个开关，操作每个开关时还会影响到其他若干开关
    给定初始状态和目标状态，问有多少种方法可以达到。
    令第i个开关初始状态为Si，终态为Ti，该开关会被若干个其他开关影响，标记为j，有
    Xi + SIGMA( Xj ) + Si = Ti
    由于是按位加，等价于
    Xi +SIGMA( Xj ) = Si +Ti
    N个未知数，N个方程
    未必有唯一解，实际上就是求解变元的个数。每个变元都可以任取0或者1
    只需求出变元的个数，无需求解
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

//a是增广矩阵
//cntOfEq是方程的个数，cntOfUnknown是未知数的个数
//输入存在多解、一解和零解的情况，输出为自由变元的数量
int Gauss(int(*a)[SIZE_OF_COLUMN],int cntOfEq,int cntOfUnknown){
    int row = 0, col = 0;
    for(;row<cntOfEq&&col<cntOfUnknown;++row,++col){
        //找列主元，此处为1即可
        int maxr = row;
        while( maxr < cntOfEq && 0 == a[maxr][col] ) ++maxr;

        //该列第row行及以下全为0，则要考虑第row行的下一列
        if ( maxr == cntOfEq ) {
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

    //检查全0行的增广列是否也为0
    for(int i=row;i<cntOfEq;++i){
        if ( a[i][col] ) return -1;//无解
    }

    return cntOfUnknown - row;//返回变元的个数，数量为0即唯一解
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
