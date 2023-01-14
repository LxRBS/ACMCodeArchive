/**
 * 给定一个数组A，元素值只在0/1/2，给定一个整数k，求
 * SIGMA{a[i1]...a[ik]}
 * 即任意k个元素的积的累加和
 * 其实考虑1和2即可，假设数组A中有a个1和b个2，则答案为
 * SIGMA{C(a, x) * C(b, k-x) * 2^(k-x), x=0...max(k,a)}
 */
#include <bits/stdc++.h>
using namespace std;

int const _SS123_ = 10;
char *__abc147, *__xyz258, __ma369[_SS123_];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,_SS123_-1,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

typedef long long llt;
llt const MOD = 998244353;


llt powerMod(llt a,llt n){
    llt ret = 1;
    a %= MOD;

    while( n ){
        if ( n & 1 ) ret = ret * a % MOD;
        n >>= 1;
        a = a * a % MOD;
    }
    return ret;
}

inline llt inv(llt a){
    return powerMod(a, MOD-2);
}

llt Cmod(llt n,llt k){
    if(k>n) return 0;
    llt fenzi = 1, fenmu = 1;
    for(int i=n-k+1;i<=n;++i)fenzi=fenzi*i%MOD;
    for(int i=1;i<=k;++i)fenmu=fenmu*i%MOD;
    return fenzi*inv(fenmu)%MOD;
}

llt Lucas(llt n,llt k){
    if(0==k) return 1;
    return Lucas(n/MOD,k/MOD) * Cmod(n%MOD,k%MOD) % MOD;
}

int N, K;
// int A[SIZE];
int C1, C2;
llt proc(){ 
    if(C1 + C2 < K) return 0;
    if(C1 + C2 == K) return powerMod(2, C2);

    llt ans = 0;
    int left = K > C2 ? K - C2 : 0;
    int right = K > C1 ? C1 : K;
    llt cc1 = Cmod(C1, left);
    llt cc2 = Cmod(C2, K-left);
    for(int i=left;i<=right;++i){
        llt tmp = cc1 * cc2 % MOD * powerMod(2, K-i) % MOD;
        ans = (ans+tmp) % MOD;
        cc1 = cc1 * inv(i+1) % MOD * (C1-i) % MOD;
        cc2 = cc2 * (K-i) % MOD * inv(C2-(K-i)+1) % MOD;
    } 

    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getUnsigned(); K = getUnsigned();
    int c[3] = {0};
    for(int i=0;i<N;++i){
        ++c[getUnsigned()];
    }
    (C1 = c[1], C2 = c[2]);
    cout<<proc()<<endl;
    return 0;
}