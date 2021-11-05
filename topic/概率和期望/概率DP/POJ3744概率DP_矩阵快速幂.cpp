#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//用于计算矩阵快速幂的方阵
struct matrix_t{
    typedef double value_t;
    enum{SIZE=2};
    value_t data[SIZE][SIZE];
    int size;

    matrix_t(int s=0):size(s){memset(data,0,sizeof(data));}

    //把自己变成s×s的单位矩阵
    void i(int s){
        size = s;
        for(int i=0;i<size;++i){
            fill(data[i],data[i]+size,0.0);
            data[i][i] = 1.0;
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

int N;
double P;
int A[12] = {0};

matrix_t Mat(2);
//计算从s到e的概率，[s,e]之间均安全
inline double calc(int s,int e){
    matrix_t& m = matrix_t::power(Mat,e-s);
    return m.data[0][0];
}

bool read(){
    if ( EOF == scanf("%d%lf",&N,&P) ) return false;
    for(int i=1;i<=N;++i)scanf("%d",A+i);
    sort(A+1,A+N+1);
    return true;
}

double dp(){
    Mat.data[0][0] = P;
    Mat.data[0][1] = 1.0 - P;
    Mat.data[1][0] = 1.0;
    Mat.data[1][1] = 0.0;

    double ret = 1.0;
    for(int i=1;i<=N;++i){
        if ( A[i] == A[i-1] + 1 ) return 0.0;
        ret *= ( 1.0 - P ) * calc(A[i-1]+1,A[i]-1);
    }
    return ret;
}

int main(){
    //freopen("1.txt","r",stdin);
    while( read() ){
        printf("%.7f\n",dp());
    }
    return 0;
}
