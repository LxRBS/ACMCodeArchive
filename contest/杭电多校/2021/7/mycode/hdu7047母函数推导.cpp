/**
   ������������ͰA��B����1��N
   ֻ�ܴ�Ai��ȡ��i�ı�����ֻ�ܴ�Bi��ȡ�����i
   ��ǡ��ȡ��M�ķ�������
   ��Ai���ԣ���֪��ĸ����Ϊ(1-x^i)^(-1)
   ��Bi���ԣ���֪��ĸ����Ϊ(1+x+...+x^i) = (1-x^(i+1))/(1-x)
   ����������ĸ����Ϊ
   (1-x^(N+1))/(1-x)^(N+1)
   ���������ʽ��x^M��ϵ��
   ����N+1>M����ֻ�迼�Ƿ�ĸ����
   ��f(x) = 1+x+x^2+x^3+... = 1/(1-x)
   ��fn(x)Ϊf��n�׵�����֪fn(x) = n! / (1-x)^(n+1)
   ����ֻ�迼�� x^(N+M) ��N�׵���ϵ���ٳ���N!����
   ��˴��� (N+M)...(N+1) / N! = C(N+M, N);
   �ٿ���N+1<=M���������ʱ��Ҫ����x^(M-N-1)��ϵ������C(M-1, N);
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

int const SIZE = 2000001;
typedef long long llt;
llt const MOD = 1000000007;

llt InvFac[SIZE] = {1LL, 1LL};
llt Fac[SIZE] = {1LL, 1LL};
llt Inv[SIZE] = {1LL, 1LL};
void initFac(){
    for(int i=2;i<SIZE;++i){
        Inv[i] = (MOD-MOD/i) * Inv[MOD%i] % MOD;
        Fac[i] = Fac[i-1] * i % MOD;
        InvFac[i] = InvFac[i-1] * Inv[i] % MOD;
    }
}

llt C(int n, int m){
    return Fac[n] * InvFac[m] % MOD * InvFac[n-m] % MOD;
}

int N, M;

int main(){
    //freopen("1.txt","r",stdin);
    initFac();
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        M = getUnsigned();
        if(M<N+1){
            printf("%lld\n", C(N+M, N));
        }else{
            printf("%lld\n", (C(N+M, N)-C(M-1, N)+MOD)%MOD);
        }
    }
    return 0;
}
