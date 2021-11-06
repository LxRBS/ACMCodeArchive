/**
    给定01矩阵A和B，要求矩阵X，使得
    AX = B.X
    问解的数量一共有多少个
    其中B.X表示B和X的元素乘法，即对应元素相乘
*/
#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define hash_t unordered_map

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

typedef long long int llt;
llt const MOD = 998244353LL;

//returns a^n%mod
llt powerMod(llt a,llt n){
    llt ret = 1;
    a %= MOD;

    while( n ){
        if ( n & 1 ) ret = ret * a % MOD;
        n >>= 1;
        a = a * a % MOD;
    }
    return ret;
}

int const SIZE_OF_COLUMN = 210;

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

int N;
int A[SIZE_OF_COLUMN][SIZE_OF_COLUMN];
int B[SIZE_OF_COLUMN][SIZE_OF_COLUMN];
int Xishu[SIZE_OF_COLUMN][SIZE_OF_COLUMN];

int main(){
    //freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
    N = getUnsigned();
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j)A[i][j] = getUnsigned();
    }
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j)B[i][j] = getUnsigned();
    }

    /// 第i列
    llt ans = 0LL;
    for(int col=0;col<N;++col){
        memset(Xishu,0,sizeof(Xishu));
        /// 第i行系数是Aij
        for(int i=0;i<N;++i){
            copy(A[i],A[i]+N,Xishu[i]);
            Xishu[i][i] ^= B[i][col];
            // printf("%d %d, %d %d\n",i,i,i,col);
        }
        /// 高斯消元
        int n = Gauss(Xishu,N,N);
        // if(-1==n){ // 无解
        //     ans = 0;
        //     goto L;
        // }
        // ans = ans * powerMod(2, n) % MOD;
        ans += n;
    }
L:
    printf("%lld\n", powerMod(2, ans));
    return 0;
}

