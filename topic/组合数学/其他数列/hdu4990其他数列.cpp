/*
    F0 = 0
    Fn = 2F(n-1) + 1����nΪ����
    Fn = 2Fn����nΪż��
    ��Fn

    ���Եõ���������
    F(2n) = 4F(2n-2) + 2
    F(2n+1) = 4F(2n-1) + 1

    �������е�ϵ������ֱ�Ϊ
    | 4 2 | | 4 1 |
    | 0 1 | | 0 1 |
    ��ʼ�����ֱ�Ϊ (0 1) �� (1 1)

    �������Ƶ��������ĵ��ƹ�ʽ����ͨ�ʽ
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

//���ڼ����������ݵķ���
struct matrix_t{
    typedef long long int value_t;
    enum{SIZE=2};
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
            for(int k=0;k<ret.size;++k) ret.data[i][j] += lhs.data[i][k] * rhs.data[k][j];
        }
    }

    //��ģ�˷�
    static void mulMod(matrix_t const&lhs,matrix_t const&rhs,matrix_t &ret,value_t const mod){
        ret.size = lhs.size;
        for(int i=0;i<ret.size;++i)for(int j=0;j<ret.size;++j){
            ret.data[i][j] = 0;
            for(int k=0;k<ret.size;++k) ret.data[i][j] =  ( ret.data[i][j] + lhs.data[i][k] * rhs.data[k][j] % mod ) % mod;
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

    //��ģ��
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

typedef long long llt;
llt N,M;
matrix_t A[2];

int main(){
    A[0].size = A[1].size = 2;
    A[0].data[0][0] = A[1].data[0][0] = 4LL;
    A[0].data[0][1] = 2LL;
    A[1].data[0][1] = 1LL;
    A[0].data[1][1] = A[1].data[1][1] = 1LL;

    while(EOF != scanf("%I64d%I64d",&N,&M)){
        if ( 1 == N ){
            printf("%I64d\n",1%M);
            continue;
        }

        matrix_t& ans = matrix_t::powerMod(A[N&1],N>>1,M);
        llt ret = ( ans.data[0][0] * (N&1) + ans.data[0][1] ) % M;
        printf("%I64d\n",ret);
    }
    return 0;
}
