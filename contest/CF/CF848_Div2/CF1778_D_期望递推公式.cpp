/**
 * 给定两个长度均为N的01字符串a和b，每次等概率的将a中的一位翻转。问将a变成b的期望次数是多少
 * 令D[i]为有i位不相同时，变得一样的期望，显然 D[0] = 0
 * 从两个方向递推可以分别设 D[i] = Ai + Bi * D[i + 1]
 * D[i] = Ci + Di * D[i - 1]
 * 解出递推系数即可。
 * 这里有一个直接的递推公式： D[0] = 0, D[1] = 2^N - 1
 *         N * D[i - 1] - (i - 1) * D[i - 2] - N
 * D[i] = ---------------------------------------
 *                     N - i + 1
 *  
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

string S, T;
int N, M;
vll D;
vll Inv;

void init(){
    Inv.assign(1000000+1, 0LL);
	Inv[1] = 1LL;
	for(int i=2,n=Inv.size();i<n;++i){
		Inv[i] = mul(MOD - MOD / i, Inv[MOD % i]);
	}
	return;
}

llt proc(){
	D.assign(N + 1, 0LL);
	D[1] = (qpow(2, N) - 1 + MOD) % MOD;
	for(int i=2;i<=N;++i){
		// llt x = mul(i - 1, Inv[N]);
		// D[i] = mul(mul(N, (D[i - 1] - mul(x, D[i - 2]) - 1) % MOD), Inv[N - i + 1]);
        D[i] = mul((mul(N, D[i - 1]) - mul(i - 1, D[i - 2]) - N) % MOD, Inv[N - i + 1]);
	}
	if(D[M] < 0) D[M] += MOD;
	return D[M];
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	init();
    int nofkase; cin >> nofkase;
	while(nofkase--){
		cin >> N >> S >> T;
		M = 0;
		for(int i=0;i<N;++i){
            if(S[i] != T[i]) ++M;
		}
		cout << proc() << endl;
	}
    return 0; 
}