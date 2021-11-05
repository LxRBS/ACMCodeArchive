/**
    N个城市，划分成r个州
    同一个州的城市之间的道路称为内部道路
    要求每个城市相连的内部道路为偶数
    问满足条件的最小的r是多少，并且给出方案
    N为2000
    考虑r=2的情况，令xi为第i个点所属的部分，则xi取值范围为0和1
    对于度数为偶数的点，则其邻点的SIGMA(xj)=0
    对于度数为奇数的点，则其邻点的SIGMA(xj)=1+xi
    可以证明该方程一定有解，所以答案不是1就是2
*/
#include <bits/stdc++.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int N,M;
int Deg[2020];

///判断1个部分是否可行
bool isOK1(){
    for(int i=1;i<=N;++i)if(Deg[i]&1)return false;
    return true;
}

int const SIZE_OF_COLUMN = 2001;

//a是增广矩阵，x是解
//cntOfEq是方程的个数，cntOfUnknown是未知数的个数
int Gauss(int(*a)[SIZE_OF_COLUMN],int x[],int cntOfEq,int cntOfUnknown){
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

    //*
    //检查全0行的增广列是否也为0
    for(int i=row;i<cntOfEq;++i){
        if ( a[i][col] ) return -1;//无解
    }//*/

    //得到其中一个解
    for(int i=cntOfEq-1;i>=0;--i){
        //对每一行取第一个未知数
        //其他的要么已经求出,要么是自由变元，取0
        int k = i;
        while(k<cntOfUnknown&&a[i][k]==0) ++k;
        if(k==cntOfUnknown) continue;

        x[k] = a[i][cntOfUnknown];
        for(int j=k+1;j<cntOfUnknown;++j){
            x[k] ^= ( x[j] && a[i][j] );
        }
    }

    return cntOfUnknown - row;//返回变元的个数，数量为0即唯一解
}

int A[SIZE_OF_COLUMN][SIZE_OF_COLUMN];
int X[SIZE_OF_COLUMN];
vector<int> Graph[SIZE_OF_COLUMN];

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        fill(Deg,Deg+(N = getUnsigned())+1,0);
        M = getUnsigned();
        for(int i=1;i<=N;++i)Graph[i].clear();

        for(int a,b,i=0;i<M;++i){
            ++Deg[a = getUnsigned()];
            ++Deg[b = getUnsigned()];
            Graph[a].push_back(b);
            Graph[b].push_back(a);
        }

        ///检测1个部分是否可行
        if(isOK1()){
            puts("1");
            putchar('1');
            for(int i=2;i<=N;++i)putchar(' '),putchar('1');
            puts("");
            continue;
        }

        ///列方程
        for(int i=0;i<N;++i)fill(A[i],A[i]+N+1,0);
        fill(X,X+N,0);

        for(int i=1;i<=N;++i){
            if(Deg[i]&1){//奇数
                for(auto v: Graph[i]){
                    A[i-1][v-1] = 1;
                }
                A[i-1][i-1] = A[i-1][N] = 1;
            }else{//偶数
                for(auto v: Graph[i]){
                    A[i-1][v-1] = 1;
                }
            }
        }

        ///解方程
        int t = Gauss(A,X,N,N);
        if(t==-1) throw runtime_error("XXXX");
        ///输出
        puts("2");
        printf("%d",X[0]?1:2);
        for(int i=1;i<N;++i){
            printf(" %d",X[i]?1:2);
        }
        puts("");
    }
    return 0;
}
