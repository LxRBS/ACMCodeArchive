/**
 * 给定H*W的方格，从左上走到右下，每一步只能向右或者向下。
 * 另外，方格的左下角有A*B的子区域是不准走的，问一共有多少种不同的走法
 * 假设没有障碍物的矩形区域为(x+1)*(y+1)，整个走法会有x步向下，y步向右
 * 很容易观察到所有可能的走法就是一个组合数，C(x+y, x)。
 * 再考虑有障碍物的情况，很明显将整个过程分为两大步即可，每一大步都是走一个矩形
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
llt const MOD = 1E9+7;

llt power(llt a, llt n){
	a %= MOD;
	llt ans = 1;
	while(n){
		if(n & 1) (ans *= a) %= MOD;
		(a *= a) %= MOD;
		n >>= 1;
	}
	return ans;
}

llt Fac[SIZE] = {1, 1}, IFac[SIZE] = {1, 1};

void init(){
    for(int i=2;i<SIZE;++i) Fac[i] = Fac[i-1] * i % MOD;
    IFac[SIZE-1] = power(Fac[SIZE-1], MOD-2);
	for(int i=SIZE-2;i>1;--i) IFac[i] = IFac[i+1] * (i+1) % MOD;
}

llt C(llt n, llt m){
	return Fac[n] * IFac[n-m] % MOD * IFac[m] % MOD;
}

llt f(llt x, llt y){
	return C(x+y, x);
}

llt H, W, A, B;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    init();
    ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> H >> W >> A >> B;
    llt ans = 0;
    for(int i=B+1;i<=W;++i){
        (ans += f(H-A-1, i-1) * f(W-i, A-1) % MOD) %= MOD;
	}
	cout << ans << endl;
    return 0;
}
