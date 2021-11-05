//������ȡģ��ģ����
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

long long const MOD = 1000000007LL;

struct matrix_t{
    typedef long long int value_t;
    enum{SIZE=100};
    value_t data[SIZE][SIZE];
    int size;

    matrix_t(int s=0):size(s){memset(data,0,sizeof(data));}

    //���Լ����s��s�ĵ�λ����
    void i(int s){
        size = s;
        for(int i=0;i<size;++i){
            fill(data[i],data[i]+size,0);
            data[i][i] = 1;
        }
    }

    //���
    void copy(matrix_t const &rhs){
        size = rhs.size;
        for(int i=0;i<size;++i){
            std::copy(rhs.data[i],rhs.data[i]+size,data[i]);
        }
    }

    //���ھ�������ݣ������������ͬ
    static void multiply(matrix_t const&lhs,matrix_t const&rhs,matrix_t&ret){
        ret.size = lhs.size;
        for(int i=0;i<ret.size;++i)for(int j=0;j<ret.size;++j){
            ret.data[i][j] = 0;
            for(int k=0;k<ret.size;++k) ret.data[i][j] = ( ret.data[i][j] + lhs.data[i][k] * rhs.data[k][j] % MOD ) % MOD;
        }
    }

    //���ڼ�������ݵ��м����
    static matrix_t t1,t2,t3;

    //����mat��n�η�
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

int M;
matrix_t Mat;
int main(){
    scanf("%d%d",&Mat.size,&M);
    for(int i=0;i<Mat.size;++i)for(int j=0;j<Mat.size;++j) scanf("%lld",Mat.data[i]+j);

    matrix_t& ret = matrix_t::power(Mat,M);
    for(int i=0;i<ret.size;++i){
        printf("%lld",ret.data[i][0]);
        for(int j=1;j<ret.size;++j) printf(" %lld",ret.data[i][j]);
        putchar('\n');
    }
    return 0;
}
