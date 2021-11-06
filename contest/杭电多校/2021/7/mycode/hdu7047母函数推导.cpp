/**
   本质上是两组桶A和B，从1到N
   只能从Ai中取出i的倍数，只能从Bi中取出最多i
   问恰好取出M的方案总数
   对Ai而言，易知其母函数为(1-x^i)^(-1)
   对Bi而言，易知其母函数为(1+x+...+x^i) = (1-x^(i+1))/(1-x)
   所以整个的母函数为
   (1-x^(N+1))/(1-x)^(N+1)
   求这个多项式的x^M的系数
   假设N+1>M，则只需考虑分母即可
   令f(x) = 1+x+x^2+x^3+... = 1/(1-x)
   令fn(x)为f的n阶导，易知fn(x) = n! / (1-x)^(n+1)
   所以只需考虑 x^(N+M) 求N阶导的系数再除以N!即可
   因此答案是 (N+M)...(N+1) / N! = C(N+M, N);
   再考虑N+1<=M的情况，此时需要减掉x^(M-N-1)的系数，即C(M-1, N);
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
