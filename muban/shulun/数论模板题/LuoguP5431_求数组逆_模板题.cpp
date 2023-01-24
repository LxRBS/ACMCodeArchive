/**
 * 全局数组开5E6，直接报编译失败。但是题解也是这样开的却能通过。
 * 将数组改为vector就能通过。因为vector实际上用的是堆的空间。
 */
#include <bits/stdc++.h>
using namespace std;


namespace IO{

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

using llt = long long;

llt getLL(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;    
}

char getChar(function<bool(char)> ok){
    char ch = __hv007();
    while(!ok(ch)) ch = __hv007();
    return ch;
}

}


#ifndef ONLINE_JUDGE
int const SIZE = 12;
#else
int const SIZE = 5000000+4;
#endif
using llt = long long;

llt MOD;

// int A[SIZE], Pre[SIZE] = {1};
// int K[SIZE] = {1};

llt powMod(llt a, llt n){
	llt ret = 1;
	while(n){
		if(n & 1) (ret *= a) %= MOD;
		(a *= a) %= MOD;
		n >>= 1;
	}
	return ret;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); 
    // cin.tie(0); cout.tie(0);
    llt n = IO::getInt();
	MOD = IO::getInt();
	llt k = IO::getInt();

	vector<llt> A(n);
	vector<llt> Pre(n);

    int K = 1;
	Pre[0] = 1;
    for(int i=1;i<=n;++i){
		Pre[i] = (llt)Pre[i-1] * (A[i] = IO::getInt()) % MOD;		
		// K[i] = ((llt)K[i-1] * k) % MOD;
		K = (k * K) % MOD;
	}
    
	llt kni = powMod(k, MOD-2LL);
	auto ni = powMod(Pre[n], MOD-2LL);
    auto ans = 0LL;
	for(int i=n;i;--i){
        (ans += Pre[i-1] * ni % MOD * K % MOD) %= MOD;
		(ni *= A[i]) %= MOD;
		K = kni * K % MOD;
	}
	printf("%lld\n", ans);
	return 0;
}