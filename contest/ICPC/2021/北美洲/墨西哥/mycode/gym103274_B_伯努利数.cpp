/**
 * 求zeta函数的结果的π的n次方的系数
 * 令n是偶数，则zeta(n)=SIGMA{1/i^n}
 * zeta(n)=(-1)^(n/2+1)*2^(n-1)*B[n]/n!*π^n
 * 其中Bn是第n个伯努利数，所以就是要计算伯努利数
 * 预处理有O(n^2)和O(nlogn)，这里要用对数时间
 * NTT多项式求逆即可。
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

typedef long long llt;
llt const MOD = 998244353LL;
llt const NTT_MOD = MOD;

int const SIZE_OF_OMEGA = 21;
int const SIZE = 1 << SIZE_OF_OMEGA;
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

//雷德算法，调整系数位置，n为数组长度，从0开始
void Rader(llt a[],int n){
    for(int i=1,j=n>>1,k;i<n-1;++i){
        if ( i < j ) swap(a[i],a[j]);
        k = n >> 1;
        while( j >= k ) j -= k, k >>= 1;
        if ( j < k ) j += k;
    }
}


//快速数论变换，a为输入输出参数，n为长度，必须是2的幂
void ntt(llt a[], int n, bool isInv=false){
    Rader(a,n);

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

//The extended Euclidean algorithm implemented by iteration
//returns gcd(a,b), and x, y are satisfied with ax + by = gcd
llt exEuclid(llt a,llt b,llt&x,llt&y){
    llt x0 = 1, y0 = 0;
    llt x1 = 0, y1 = 1;
    x = 0; y = 1;
    llt r = a % b;
    llt q = ( a - r ) / b;
    while( r ){
        x = x0 - q * x1;
        y = y0 - q * y1;
        x0 = x1; y0 = y1;
        x1 = x; y1 = y;
        a = b; b = r; r = a % b;
        q = ( a - r ) / b;
    }
    return b;
}

//returns the inverse of a mod p satisfied with 1 == ax%p
//it will be success only when a and p are co-prime
inline llt inv(llt a,llt p){
    llt x,y;
    llt r = exEuclid(a,p,x,y);
    if ( r != 1 ) return 0;
    x = x % p;
    if ( x < 0 ) x += p;
    return x;
}

llt TA[SIZE],TB[SIZE];//临时数组

//求多项式a的逆，n为多项式的最高次项，n+1为多项式的长度
void inv(llt const a[],int n,llt ans[]){
    if(1==n){
        ans[0] = inv(a[0],NTT_MOD);
        return;
    }

    inv(a,(++n)>>1,ans);//递归

    //求NTT的合适长度
    int limit = 1, len = 0;
    while(limit<(n<<1)) limit<<=1,++len;

    fill(TA,TA+limit+1,0);
    fill(TB,TB+limit+1,0);

    copy(a,a+n,TA);
    copy(ans,ans+n,TB);

    ntt(TA,limit);
    ntt(TB,limit);

    //计算B(2-AB)的NTT变换
    for(int i=0;i<limit;++i){
        TB[i]= TB[i] * ( (2-TA[i]*TB[i]%NTT_MOD+NTT_MOD)%NTT_MOD ) % NTT_MOD;
    }

    //对上述结果做NTT逆变换
    ntt(TB,limit,true);

    //拷贝结果
    copy(TB,TB+n,ans);
}

llt Bernoulli[SIZE];
llt IofFac[SIZE];
llt Fac[SIZE];

llt A[SIZE];

/// 求出1~n的Bernoulli数，n最好是2的幂
void initBernoulli(int n){
	initOmega();
    Bernoulli[0] = IofFac[0] = Fac[0] = 1LL;
	/// 阶乘
    for(int i=1,n2=n<<1;i<=n2;++i){
		Fac[i] = Fac[i-1] * i % MOD;
	}
	/// 阶乘的逆
	IofFac[n+n] = inv(Fac[n+n], MOD);
    for(int i=n+n-1;i;--i){
		IofFac[i] = IofFac[i+1] * (i+1) % MOD;
	}
    /// 准备多项式
	for(int i=0;i<=n;++i){
		A[i] = IofFac[i+1];
	}
	/// 多项式求逆
	inv(A, n, Bernoulli);
    /// 伯努利数
	for(int i=1;i<=n;++i){
		Bernoulli[i] = Bernoulli[i] * Fac[i] % MOD;
	}
}


int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    initBernoulli(1<<18);
    int nofkase = getUnsigned();
	while(nofkase--){
	    llt n = getUnsigned();
        llt ans = IofFac[n] * Bernoulli[n] % MOD;
		(ans *= powerMod(2, n-1)) %= MOD;
		if(!((n>>1)&1)) ans = MOD - ans;
		printf("%lld\n", ans);
	}
	return 0;
}
