/**
   暴力法发现当行数大于等于4时，答案固定
   只需计算行数为123即可
   当行数为1时:
   Di = D[i-1]+D[i-2]，D0=0, D1=2，快速幂
   当行数为2时：
   D[2][i] = D[1][i]的平方
   当行数为3时：
   系数矩阵是
   010000
   110000
   011000
   001100
   000110
   000011
   从第6个数开始计算，前5个直接暴力
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;

llt const MOD = 1000000007LL;

inline llt add(llt a,llt b){return (a+b)%MOD;}
inline llt mul(llt a,llt b){return a*b%MOD;}

//���ڼ����������ݵķ���
struct matrix_t{
    typedef llt value_t;
    enum{SIZE=10};
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

llt f1(llt m){
    matrix_t a(2);
    a.data[0][0] = a.data[0][1] = a.data[1][0] = 1;
    const matrix_t& ans = matrix_t::powerMod(a, m, MOD);
    return mul(2LL, add(ans.data[1][0],ans.data[1][1]));
}

llt f2(llt m){
    llt ans = f1(m);
    return mul(ans, ans);
}

llt f3(llt m){
    if(1==m) return 6;
    if(2==m) return 36;
    if(3==m) return 32;
    if(4==m) return 44;
    if(5==m) return 64;
    matrix_t a(6);
    a.data[0][1] = 1;
    a.data[1][0] = a.data[1][1] = 1;
    a.data[2][1] = a.data[2][2] = 1;
    a.data[3][2] = a.data[3][3] = 1;
    a.data[4][3] = a.data[4][4] = 1;
    a.data[5][4] = a.data[5][5] = 1;
    const matrix_t& ans = matrix_t::powerMod(a, m-6, MOD);
    static const llt v[] = {0,20,20,40,60,104};
    llt ret = 0;
    for(int i=0;i<6;++i){
        ret = add(ret, mul(v[i], ans.data[5][i]));
    }
    return ret;
}

llt f(llt n, llt m){
    if(n>m) swap(n, m);
    if(4==n) return 4==m?18:14;
    if(4==m) {
        if(1==n) return 10;
        if(2==n) return 100;
        if(3==n) return 44;
        throw runtime_error("4 wrong");
    }
    if(n>=5) return 8;
    if(1==n) return f1(m);
    if(2==n) return f2(m);
    if(3==n) return f3(m);
    throw runtime_error("1234 wrong");
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    cin>>nofkase;
    while(nofkase--){
        llt n, m;
        cin>>n>>m;
        cout<<f(n, m)<<endl;
    }
    return 0;
}
