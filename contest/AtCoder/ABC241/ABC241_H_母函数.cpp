/**
 * 一共有N种牌，N在16以内。
 * 第i种牌一共有Bi张，每张牌上面写了一个数，记作Ai。
 * 现在要求一共抽出M张牌。这M张牌的数字乘积作为这个抽法的分数。
 * 要求求出所有M抽法的分数总和。
 * 对于第i种牌，其母函数为 (1+Aix+(Aix)^2+...+(Aix)^Bi)
 * 因此所有牌的母函数为:
 *            (1 - (A1x)^(B1+1)) ... (1 - (ANx)^(Bn+1))
 *   f(x) = ---------------------------------------------  
 *                     (1 - A1x) ... (1 - ANx)
 * 只要求出 x^M 的系数即可。
 * 虽然N只有16，但是M非常大，因此不可能直接做多项式的乘法。
 * 考虑分式拆分，令 f(x) 的分母记作 g(x)，则
 *                     1                   c1                cN
 *   g(x) = ------------------------- = --------- + ... + ---------  
 *           (1 - A1x) ... (1 - ANx)     1 - A1x           1 - ANx
 *  两边同时乘以g(x)的分母，有
 *  1 = c1(1-A2x)...(1-ANx) + ... + cN(1-A1x)...(1-A[N-1]x)
 *  令 x = A1^(-1)，可以发现后面的 N-1 项全为领，于是可以求出 c1 = 1 / PI{1 - A1^(-1) * Ai, i=2,3,...,N}
 *  同理可以求出所有的 ci。
 *  求出ci以后，将f(x)的分子记作h(x)，则母函数就能写成
 *  f(x) = h(x) * SIGMA{ci(1+A1x+...)}
 * 注意到 h(x) 是可以求出来的，因为N只有16，所以可以使用二进制，在 2^N 内就出每个可能的 x 的幂次即系数，
 * 假设记作 cx^k，则再在后面的求和式中，求出 SIGMA{ci*Ai^(M-k)}即可。二者相乘即答案。
 */
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)
 
using llt = long long; 
llt getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (llt)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;
}



#ifndef ONLINE_JUDGE
int const SIZE = 21;
#else
int const SIZE = 2e5+5;
#endif


using vi = vector<int>;
using vll =vector<llt>;
using edge_t = tuple<int, int, int, int>;
using ve = vector<edge_t>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 998244353LL;

inline llt add(llt a, llt b){return (a + b) % MOD;}
inline llt mul(llt a, llt b){return a * b % MOD;}

llt qpow(llt a, llt n){
	llt ret = 1;
	while(n){
		if(n & 1) ret = ret * a % MOD;
        a = a * a %  MOD;
		n >>= 1;
	}
	return ret; 
}

inline llt inv(llt a){return qpow(a, MOD-2LL);}

int N;
llt M;
vll A, B;
vll InvA;
vll C;

llt calcC(int pos){
	llt ans = 1LL;
	for(int i=0;i<N;++i)if(pos!=i){
        ans = mul(ans, add(MOD, 1 - mul(A[i], InvA[pos])));
	}
	ans = inv(ans);
	return ans;
}

llt f(int st){
	llt k = 0;
	llt c = 1;
	for(int i=0;i<N;++i){
		if((1 << i) & st){
            k += B[i] + 1;
			c = mul(c, MOD - qpow(A[i], B[i]+1)); 
		}
	}
	if(M < k) return 0;
	llt ans = 0;
    for(int i=0;i<N;++i){
		ans = add(ans, mul(C[i], qpow(A[i], M-k)));
	}
	ans = mul(ans, c);
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    N = getInt(); M = getInt();
	A.assign(N, 0LL); B.assign(N, 0); InvA.assign(N, 0LL);
	for(int i=0;i<N;++i) InvA[i] = inv(A[i] = getInt()), B[i] = getInt();

	C.assign(N, 0LL);
	for(int i=0;i<N;++i) C[i] = calcC(i);
    
	llt ans = 0;
	for(int i=0,n=1<<N;i<n;++i){
		llt tmp = f(i);
		ans = add(ans, tmp);
	}
	if(ans < 0) ans += MOD;
	cout << ans << endl;
    return 0; 
}