/**
 * 给定一个字符串S，长度为N，问有多少个长度为N的字符串，满足：
 * 字典序小于S且是回文。
 * 从S0开始考虑，假设S0是D，则S0可以选ABC三种，然后后面的每个位置显然是26种可能，
 * 一共到一半，注意分奇偶
 * 再考虑S1，只需比之前少乘一个26即可，直到一半的位置
 * 最后单独判断一下前一半作为回文串是否小于源串，决定是否加1
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

#ifndef ONLINE_JUDGE
int const SIZE = 33;
#else
int const SIZE = 1000001;
#endif

typedef long long llt;
llt const MOD = 998244353LL;

llt power(llt a, llt n){
	llt ret = 1LL; a %= MOD;
	while(n){
		if(n&1) (ret *= a) %= MOD;
		n >>= 1;
		(a *= a) %= MOD;
	}
	return ret;
}

int N;
char A[SIZE];
int N2 = 0;

inline llt proc(int idx){
    // llt ans = 1LL;
	llt t = A[idx] - 'A';
    (t *= power(26LL, N2-idx)) %= MOD;
	return t;
}

bool isOK(){
	for(int i=N2+1;i<N;++i){
		if(A[i] < A[N-i-1]) return false;
		if(A[i] > A[N-i-1]) return true;
	}
	return true;
}

llt proc(){
	N2 = N / 2 - (N&1?0:1);
	llt ans = 0LL;
    for(int i=0;i<=N2;++i){
        (ans += proc(i)) %= MOD;
	}
	if(isOK()) ++ans;
	return ans % MOD;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase; scanf("%d", &nofkase);
	while(nofkase--){
        scanf("%d%s", &N, A);
		printf("%lld\n", proc());
	}
    return 0;
}