/**
 * 给定若干个三角形，每条边有权值。每个定点染两种颜色。
 * 只有端点颜色不同的边权才会累加，问使得边权和最大的染色方案一共有多少个，还需使得两种颜色的端点数量相等。
 * 首先显然三角形不可能三点同色，必然是 1-2 分布。所以首先计算C(N, N/2)，其中N表示三角形的数量
 * 即选出这些染 1R2B，剩下的自然是 2R1B 染色。
 * 再考虑每个三角形，此时颜色种类已经确定，对于权值结构为 大中小 和 大大小 结构的三角形，只有一种染色方案，才能使得权值和最大
 * 对于 大小小 有2种方案，对于 大大大 结构有3种方案。乘法原理即可。
 */
#include <bits/stdc++.h>
using namespace std;

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

char getChar(){
	char ch = __hv007();
	while( ch != 'o' && ch != 'x' ) ch = __hv007();
	return ch;
}

#ifndef ONLINE_JUDGE
int const SIZE = 21;
#else
int const SIZE = 2e5+5;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using edge_t = tuple<int, int, int, int>;
using ve = vector<edge_t>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 998244353LL;

llt qpow(llt a, llt n){
	a %= MOD;
	llt ret = 1;
	while(n){
		if(n & 1) ret = ret * a % MOD;
		a = a * a % MOD;
		n >>= 1;
	}
	return ret;
}

inline llt inv(llt a){return qpow(a, MOD - 2LL);}

vll Fac, IFac;
void init(int sz){
	Fac.assign(sz + 1, 0LL);
	IFac.assign(sz + 1, 0LL);
	Fac[0] = IFac[0] = 1LL;
	for(int i=1;i<=sz;++i) Fac[i] = Fac[i - 1] * i % MOD;
	IFac[sz] = inv(Fac[sz]);
	for(int i=sz-1;i>=1;--i)IFac[i] = IFac[i + 1] * (i + 1) % MOD;
	assert(IFac[1] == 1LL && Fac[1] == 1LL);
	return;
}

inline llt C(int n, int m){
	if(n < m) return 0;
	return Fac[n] * IFac[m] % MOD * IFac[n - m] % MOD;
}

vector<vll> A;
int N;

llt proc(){
    int n = N / 3;
    assert(n % 2 == 0);
	llt ans = C(n, n / 2);
	for(auto & a : A){
		sort(a.begin(), a.end());
		if(a[0] == a[1]){
			if(a[1] == a[2]) ans = ans * 3 % MOD;
			else ans = ans * 2 % MOD;
		}
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	init(100000);
    // int nofkase = getInt();
	// int nofkase; cin >> nofkase;
	int nofkase = 1;
	for(int kase=1;kase<=nofkase;++kase){
		// printf("kase = %d\n", kase);
        N = getInt();
		A.clear(); A.reserve(N / 3);
        for(int i=0;i<N;i+=3){
			llt a = getInt();
			llt b = getInt();
			llt c = getInt();
			A.push_back(vll({a, b, c}));
		}
		printf("%lld\n", proc());
	}
	return 0; 
}