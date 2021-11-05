/*
    F0 = a, F1 = b
    Fn = F(n-1) + F(n-2)
    给定abnm
    求Fn的后m位
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

//用于计算矩阵快速幂的方阵
struct matrix_t{
    typedef int value_t;
    enum{SIZE=2};
    value_t data[SIZE][SIZE];
    int size;

    matrix_t(int s=0):size(s){memset(data,0,sizeof(data));}

    //把自己变成s×s的单位矩阵
    void i(int s){
        size = s;
        for(int i=0;i<size;++i){
            fill(data[i],data[i]+size,0);
            data[i][i] = 1;
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
            for(int k=0;k<ret.size;++k) ret.data[i][j] += lhs.data[i][k] * rhs.data[k][j];
        }
    }

    //带模乘法
    static void mulMod(matrix_t const&lhs,matrix_t const&rhs,matrix_t &ret,value_t const mod){
        ret.size = lhs.size;
        for(int i=0;i<ret.size;++i)for(int j=0;j<ret.size;++j){
            ret.data[i][j] = 0;
            for(int k=0;k<ret.size;++k) ret.data[i][j] =  ( ret.data[i][j] + lhs.data[i][k] * rhs.data[k][j] % mod ) % mod;
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

    //带模幂
    static matrix_t& powerMod(matrix_t const& mat,int n,value_t const mod){
        matrix_t *rp = &t1, *tp = &t2, *mp = &t3;
        rp->i(mat.size);mp->copy(mat);

        while( n ){
            if ( n & 1 ){
                mulMod(*rp,*mp,*tp,mod);
                swap(rp,tp);
            }

            mulMod(*mp,*mp,*tp,mod);
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

matrix_t A(2);
int const MOD[] = {1,10,100,1000,10000};

int main(){
    A.data[0][0] = A.data[0][1] = A.data[1][0] = 1;

    int a,b,n,m,nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        scanf("%d%d%d%d",&a,&b,&n,&m);

        int const& mod = MOD[m];
        if ( 0 == n ){
            printf("%d\n",a%mod);
            continue;
        }
        if ( 1 == n ){
            printf("%d\n",b%mod);
            continue;
        }

        matrix_t& ans = matrix_t::powerMod(A,n-1,mod);
        int ret = ( ans.data[0][0] * b % mod + ans.data[0][1] * a % mod ) % mod;
        printf("%d\n",ret);
    }
    return 0;
}
