/**
 * 给定A,X,M，求 SIGMA{A^i, i=0,...,X-1} % M
 * 令 f(k) = SIGMA{A^i, i=0,...,k} % M
 * 则 fk = A * f(k-1) + 1
 * 写成矩阵形式有
 *  (fk, 1)^T = | A  1 | * (f[k-1], 1)^T
 *              | 0  1 |
 *  所以做一个矩阵快速幂即可
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

using matrix_t = array<array<llt, 2>, 2>;

matrix_t operator * (const matrix_t & a, const matrix_t & b){
	matrix_t c{};
	for(int i=0;i<2;++i)for(int k=0;k<2;++k){
		auto aik = a[i][k];
		auto & bk = b[k];
        for(int j=0;j<2;++j){
            (c[i][j] += aik * bk[j] % M) %= M;
		}
	}
	return c;
}

matrix_t qpow(matrix_t a, llt n){
	matrix_t ret = {array<llt, 2>({1, 0}), array<llt, 2>({0, 1})};
	while(n){
		if(n & 1) ret = ret * a;
		a = a * a;
		n >>= 1;
	}
	return ret;
}

llt proc(){
	matrix_t a = {array<llt, 2>({A, 1LL}), array<llt, 2>({0LL, 1LL})};
	a = qpow(a, X);
	// cout << a[0][0] << endl;
	// cout << (a[0][0] + a[0][1]) % M << endl;
	return a[0][1];
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


