/**
 * 给定N，问能否分解成 a*b+a+b 的格式，ab都是正数
 * 由于 N + 1 = (a + 1)(b + 1)
 * 因此就是问 N + 1 是不是合数。
 * O(sqrt(N))
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

bool proc(){
    llt n = N + 1;
	for(llt i=2;i*i<=n;++i){
		if(0 == n % i) return true;
	}
	return false;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; cin >> nofkase;
    N = getInt();
	puts(proc()?"Yes":"No");
    return 0; 
}