/**
 * 给定A,X,M，求 SIGMA{A^i, i=0,...,X-1} % M
 * 由于逆可能不存在，不能求逆。使用递归。
 * 令 f(a, k) = SIGMA{a^i, i=0,...,k}
 * 如果k是奇数，则一共有偶数项，将其分为两半，有 f(a, k) = f(a, k/2) * (1 + a ^ (k/2+1))
 * 如果k是偶数，则一共有奇数项，简单的将其写作 f(a, k) = 1 + a * f(a, k - 1)
 * 递归一下即可，对数复杂度
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
	while(ch != 'R' and ch != 'B') ch = __hv007();
	return ch;
}



#ifndef ONLINE_JUDGE
int const SIZE = 21;
#else
int const SIZE = 66;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using ull = unsigned long long;

llt A, X, M;

llt qpow(llt a, llt n){
	a %= M;
	llt ret = 1;
	while(n){
		if(n & 1) ret = ret * a % M;
		a = a * a % M;
		n >>= 1;
	}
	return ret;
}

llt f(llt a, llt k){
	if(0 == k) return 1;
	if(k & 1) return f(a, k/2) * (1 + qpow(a, k/2+1)) % M;
	return (1 + a * f(a, k - 1) % M) % M;
}

inline llt proc(){
	if(1 == M) return 0;
	if(1 == A) return X % M;
    return f(A, X - 1);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; scanf("%d", &nofkase);
    cin >> A >> X >> M;
	cout << proc() << endl;
    return 0; 
}


