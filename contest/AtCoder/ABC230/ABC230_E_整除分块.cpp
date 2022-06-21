/**
 *  给定N，求SIGMA{N/i}，裸整除分块
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
int const SIZE = 13;
#else
int const SIZE = 2E5+5;
#endif

using llt = long long int;
llt const MOD = 998244353LL;
llt const INV2 = (MOD+1)/2;

llt N;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> N;
	llt ans = 0;
	for(llt r,i=1;i<=N;i=r+1){
        r = N / (N / i);
		ans += (r - i + 1) * (N / i);
	}
	cout<<ans<<endl;
    return 0;
}
