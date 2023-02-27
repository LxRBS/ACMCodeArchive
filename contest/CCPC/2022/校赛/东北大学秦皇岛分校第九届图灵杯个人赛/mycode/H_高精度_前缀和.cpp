/**
 * 对于一个大数，依次将其右移一位加上，求最后的和。
 * 例如： 1234，要计算
 * 1234
 *  123
 *   12
 *    1
 * 的累加和。长度在10万，直接算是O(N^2)的
 * 使用前缀和优化一下，变成O(N)。
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
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 998244353LL;

int N;
string S;
vi A, B;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; cin >> nofkase;
    cin >> S;
    N = S.length();
	A.assign(N + 1, 0);
	for(int i=1;i<=N;++i){
		A[i] = A[i - 1] + (S[i - 1] - '0');
	}

    B.reserve(N + 2);
	int carry = 0;
	for(int i=N;i>=1;--i){
		B.push_back(A[i]);
		B.back() += carry;
		carry = B.back() / 10;
		B.back() %= 10;
	}
	assert(carry < 10);
	if(carry) B.push_back(carry);
	for(auto it=B.rbegin(),et=B.rend();it!=et;++it) printf("%d", *it);
	printf("\n");
    return 0; 
}