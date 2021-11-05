/*
已知数列：F1 = a,  F2 = b,  Fn = 2 * F(n-2) + F(n-1) + n^4
则 Fn = F(n-1) + 2F(n-2) + (n-1)^4 + 4(n-1)^3 + 6(n-1)^2 + 4(n-1) + 1
令列向量 X(n-1) = [ F(n-1) F(n-2) (n-1)^4 4(n-1)^3 6(n-1)^2 4(n-1) 1 ]T
则Xn = [ Fn Fn-1 n^4 4n^3 6n^2 4n 1 ]T
构造系数矩阵A使得 AXn-1 = Xn，有A如下

1 2 1 1 1 1 1
1 0 0 0 0 0 0 
0 0 1 1 1 1 1
0 0 0 1 2 3 4
0 0 0 0 1 3 6
0 0 0 0 0 1 4
0 0 0 0 0 0 1

初始向量 X2 = [ b a 2^4 4*2^3 6*2^2 4*2 1 ]T
Xn = A^(n-2) * X2

*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//用于计算矩阵快速幂的方阵，带模
long long const MOD = 2147493647LL;
struct matrix_t{
    typedef long long int value_t;
    enum{SIZE=7};
    value_t data[SIZE][SIZE];
    int size;

    matrix_t(int s=0):size(s){memset(data,0,sizeof(data));}

    //把自己变成s×s的单位矩阵
    void i(int s){
        size = s;
        for(int i=0;i<size;++i){
            fill(data[i],data[i]+size,0LL);
            data[i][i] = 1LL;
        }
    }

    //深拷贝
    void copy(matrix_t const &rhs){
        size = rhs.size;
        for(int i=0;i<size;++i){
            std::copy(rhs.data[i],rhs.data[i]+size,data[i]);
        }
    }

    //用于矩阵快速幂，参数需各不相同
    static void multiply(matrix_t const&lhs,matrix_t const&rhs,matrix_t&ret){
        ret.size = lhs.size;
        for(int i=0;i<ret.size;++i)for(int j=0;j<ret.size;++j){
            ret.data[i][j] = 0;
            for(int k=0;k<ret.size;++k){
                ret.data[i][j] = ( ret.data[i][j] + ( ( lhs.data[i][k] * rhs.data[k][j] ) % MOD ) ) % MOD;
            }
        }
    }

    //用于计算快速幂的中间变量
    static matrix_t t1,t2,t3;

    //计算mat的n次方
    static matrix_t& power(matrix_t const& mat,int n){
        matrix_t *rp = &t1, *tp = &t2, *mp = &t3;
        rp->i(mat.size);mp->copy(mat);

        while( n ){
            if ( n & 1 ){
                multiply(*rp,*mp,*tp);
                swap(rp,tp);
            }

            multiply(*mp,*mp,*tp);
            swap(mp,tp);
            n >>= 1;
        }

        return *rp;
    }

    static void swap(matrix_t *&pa,matrix_t *&pb){
        matrix_t *tp = pa; pa = pb; pb = tp;
    }
};
matrix_t matrix_t::t1;
matrix_t matrix_t::t2;
matrix_t matrix_t::t3;

matrix_t Mat(7);

long long int X[] = {0,0,16,32,24,8,1};
int main(){
    //初始化矩阵
    for(int i=0;i<7;++i) Mat.data[0][i] = 1;
    Mat.data[0][1] = 2;
    Mat.data[1][0] = 1;
    for(int i=2;i<7;++i) Mat.data[2][i] = 1;
    for(int i=1;i<=4;++i) Mat.data[3][2+i] = i;
    Mat.data[4][4] = Mat.data[5][5] = Mat.data[6][6] = 1;
    Mat.data[4][5] = 3; Mat.data[4][6] = 6;
    Mat.data[5][6] = 4;

    int nofkase;
    scanf("%d",&nofkase);
    while( nofkase -- ){
        int n;
        scanf("%d%lld%lld",&n,X+1,X);

        if ( 1 == n || 2 == n ){
            printf("%lld\n",X[n&1]);
            continue;
        }

        matrix_t& mat = matrix_t::power(Mat,n-2);
        long long ret = 0LL;
        for(int i=0;i<7;++i){
            ret = ( ret + ( ( mat.data[0][i] * X[i] ) % MOD ) ) % MOD;
        }
        printf("%lld\n",ret);
    }
    return 0;
}
