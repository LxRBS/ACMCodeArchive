/*
    Fi = F(i-1)+F(i-2)+...+F1+i^k
    �� Si = SIGMA(F)
    �� Si = 2S(i-1) + i^k
    �� Xi = (Si,i^k,i^(k-1),...,1)
    �� X(i+1) = AXi
    ���У�ϵ������AΪ
    2,1,C(k,1),C(k,2),...,1
    0,1,C(k,1),C(k,2),...,1
    0,0,1,C(k-1,1),......,1
    .......................
    0,0,.................,1
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
 
typedef long long llt;
 
llt MOD = 1000000007LL;
 
//���ڼ����������ݵķ���
struct matrix_t{
    typedef llt value_t;
    enum{SIZE=12};
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
    static matrix_t& power(matrix_t const& mat,value_t n){
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
    static matrix_t& powerMod(matrix_t const& mat,value_t n,value_t const mod){
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
 
llt C[13][13];//�����
 
//��ʼ����1��n�������������n
void initC(int n){
    C[0][0] = 1;
    for(int i=1;i<=n;++i){
        C[i][0] = C[i][i] = 1;
        for(int j=1;j<i;++j) C[i][j] = ( C[i-1][j] + C[i-1][j-1] ) % MOD;
    }
}
 
int main(){
    initC(10);
 
    llt n,k;
    scanf("%lld%lld",&n,&k);
    if ( 1 == n ) {
        printf("1\n");
        return 0;
    }
 
    //����ϵ������
    matrix_t a(k+2);
    a.data[0][0] = 2;
    for(int i=1;i<=k+1;++i) a.data[0][i] = C[k][i-1];
    for(int i=1;i<=k+1;++i)for(int j=i;j<=k+1;++j) a.data[i][j] = C[k-i+1][j-i];
    //������
    matrix_t& ans = matrix_t::powerMod(a,n-2,MOD);
    //����S(n-1)
    llt sii = 0LL;
    for(int i=0;i<=k+1;++i) sii = ( sii + ans.data[0][i] ) % MOD;
    //����Sn
    matrix_t ans2;
    matrix_t::mulMod(ans,a,ans2,MOD);
    llt si = 0LL;
    for(int i=0;i<=k+1;++i) si = ( si + ans2.data[0][i] ) % MOD;
    si -= sii;
    if ( si < 0 ) si += MOD;
    printf("%lld\n",si);
    return 0;
}