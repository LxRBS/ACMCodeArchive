//大数乘法模板
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long llt;
int const SIZE_OF_OMEGA = 20;
int const SIZE = 1 << SIZE_OF_OMEGA;
llt const NTT_MOD = (479LL << 21) | 1LL;//大质数
llt const G = 3LL;   //大质数的原根
llt  Omega[SIZE_OF_OMEGA];


//快速幂取模
llt powerMod(llt a, llt n){
    llt ans = 1LL;
    a %= NTT_MOD;
    while(n){
        if(n & 1LL) ans = ans * a % NTT_MOD;
        a = a * a % NTT_MOD;n >>= 1;
    }
    return ans;
}

void initOmega(){
    for(int i=0;i<SIZE_OF_OMEGA;++i){
        int t = 1 << i;
        Omega[i] = powerMod(G, (NTT_MOD - 1) / t);
    }
}

//快速数论变换，a为输入输出参数，n为长度，必须是2的幂
void ntt(llt a[], int n, bool isInv=false){
    //
    int tmp = n >> 1;
    for(int i=1;i<n-1;++i){
        if ( i < tmp ) swap(a[i],a[tmp]);
        int k = n >> 1;
        while( tmp >= k ) tmp -= k, k >>= 1;
        if ( tmp < k ) tmp += k;
    }

    for(int h=2,id=1;h<=n;h<<=1,++id){
        for(int j = 0; j < n; j += h){
            llt u,v,w = 1LL;
            for(int k=j,tmp=j+(h>>1);k<tmp;++k){
                u = a[k] % NTT_MOD;
                v = w * a[k+(h>>1)] % NTT_MOD;
                a[k] = ( u + v ) % NTT_MOD;
                a[k+(h>>1)] = ( u - v + NTT_MOD) % NTT_MOD;
                w = w * Omega[id] % NTT_MOD;
            }
        }
    }
    if(isInv){
        for(int i=1,tmp=n>>1; i < tmp; ++i) swap(a[i], a[n-i]);
        llt invv = powerMod(n, NTT_MOD - 2LL);
        for(int i=0;i<n;++i) a[i] = a[i] * invv % NTT_MOD;
    }
}

//将字符串转换为大数，长度指定为n，字符串的长度为sn
void str2Poly(char const s[],int sn,llt a[],int n){
    for(int i=0;i<sn;++i) a[sn-1-i] = s[i] - '0';
    fill(a+sn,a+n,0LL);
}

llt A[SIZE], B[SIZE];
char SA[SIZE],SB[SIZE];
int main(){
    initOmega();
    while( EOF != scanf("%s%s",SA,SB) ){
        //确定长度
        int la = strlen(SA), lb = strlen(SB);
        int n = 1;
        while( n < ( la + lb ) ) n <<= 1;

        //准备好大数
        str2Poly(SA,la,A,n);
        str2Poly(SB,lb,B,n);

        //数论变换
        ntt(A,n);
        ntt(B,n);

        //逐项乘
        for(int i=0;i<n;++i) A[i] = A[i] * B[i] % NTT_MOD;

        //逆变换
        ntt(A,n,true);

        //准备输出
        A[n] = 0LL;
        for(int i=0;i<n;++i) A[i+1] += A[i] / 10LL, A[i] %= 10LL;
        while( n && 0LL == A[n] ) --n;
        for(int i=n;i>=0;--i)printf("%I64d",A[i]);
        putchar('\n');
    }
    return 0;
}
