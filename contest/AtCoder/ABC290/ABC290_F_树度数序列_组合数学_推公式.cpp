/**
 * 对一个N长度的数组，令Ai刚好是第i个节点的度数，
 * 如果这N个节点可以构成一棵树，且该树的直径是所有这种度数序列中的树的最大直径
 * 则该树称为good tree，求所有good tree的最大直径之和
 * 首先能构成树必有 SIGMA{Ai} = 2N - 2，因为一条边贡献2个度数，树有N-1条边
 * 其次，假设序列中有k个叶子，则最大直径必然是N-k+1，因为直径上有N-k+2个点
 * 于是，总和为2N-2且其中有k个1的数组一共有多少个，首先选出k个元素做1，有C(N, k)
 * 让后将 2N-2-k 分配给 N-k，且均要大于1，也就是将 (2N-2-k)-(N-k) 分配给 N-k，且均要大于0
 * 即将N-2分配给N-k，且要大于0。用隔板法，即C(N-3,N-k-1)
 * 所以答案为 SIGMA{C(N, K)*C(N-3, N-k-1)*(N-k+1),k=2,3,...,N-1}
 * 由于 N-k+1 = N-k-1+2, 于是求和项写成了 cc*(N-k-1) + cc*2
 * 后一项直接利用范德蒙卷积即得 C(2n-3,n-1)*2
 * 前一项做个变形，将N-k-1乘进组合数，得到 C(N,K)*C(N-4,N-k-2)*(N-3)，同样用范德蒙卷积得到 C(2N-4,N-2)*(N-3)
 * 所以答案为 C(2n-3,n-1)*2 + C(2N-4,N-2)*(N-3)
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)
 

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}



#ifndef ONLINE_JUDGE
int const SIZE = 21;
#else
int const SIZE = 2e5+5;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 998244353LL;

llt qpow(llt a, llt n){
	llt ret = 1;
	while(n){
		if(n & 1) ret = ret * a % MOD;
		a = a * a % MOD;
		n >>= 1;
	}
	return ret;
}

inline llt inv(llt a){return qpow(a, MOD-2LL);}

vll Fac;
vll IFac;

void init(){
	int const sz = 1000000*2+1;
    Fac.assign(sz, 0LL);
	IFac.assign(sz, 0LL);
	
	Fac[0] = Fac[1] = 1LL;
	for(int i=2;i<sz;++i) Fac[i] = Fac[i - 1] * i % MOD;

    IFac[sz-1] = inv(Fac[sz-1]);
	for(int i=sz-2;i>=0;--i) IFac[i] = IFac[i + 1] * (i + 1) % MOD;
	assert(IFac[0] == 1LL && IFac[1] == 1LL);
	return;
}

llt C(int n, int m){
	if(m < 0 || m > n) return 0LL;
	return Fac[n] * IFac[m] % MOD * IFac[n - m] % MOD;
}

llt proc(llt n){
    return ((n - 3) * C(n + n - 4, n - 2) % MOD + 2 * C(n + n - 3, n - 1) % MOD) % MOD;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; cin >> nofkase;
	init();
    int nofkase = getInt();
	while(nofkase--){
		printf("%lld\n", proc(getInt()));
	}
    return 0; 
}