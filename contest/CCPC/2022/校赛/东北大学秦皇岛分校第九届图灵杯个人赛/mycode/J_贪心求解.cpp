/**
 * 给定偶数长度的01串，有3种操作
 * 1 删除01对，代价a
 * 2 删除00或者11，代价b
 * 3 将一个位置翻转，代价c
 * 问删除所有字母的最小代价
 * 分情况讨论即可。
 * 当 c + a <= b时，就不会用b操作
 * 当 c + b <= a时，就不会用a操作
 * 到此以下就不会用c操作。然后再看看a、b哪个优先。
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

int A, B, C;
string S;

llt procA(){
	int c0 = 0, c1 = 0;
	for(char ch : S){
		if('0' == ch) ++c0;
		else ++c1;
	}
	if(c0 <= c1){
		return c0 * 1LL * A + (c1 - c0) / 2LL * B;
	}
	return c1 * 1LL * A + (c0 - c1) / 2LL * B;
}

llt procBC(){
	int c0 = 0, c1 = 0;
	for(char ch : S){
		if('0' == ch) ++c0;
		else ++c1;
	}
	llt ans = (c0 / 2LL + c1 / 2LL) * B;
	if(c0 & 1) ans += C + B;
	return ans;	
}

llt procAC(){
	int c0 = 0, c1 = 0;
	for(char ch : S){
		if('0' == ch) ++c0;
		else ++c1;
	}
	int t = c0 - c1;
	if(t < 0) t = -t;
	llt ans = t / 2LL * C;
	ans += S.length() / 2LL * A;
	return ans;	
}

llt proc(){    
	if(C + A <= B) return procAC();
	if(C + B <= A) return procBC();
	if(A <= B) return procA();

	int c0 = 0, c1 = 0;
	for(char ch : S){
		if('0' == ch) ++c0;
		else ++c1;
	}
	llt ans = (c0 / 2LL + c1 / 2LL) * B;
	if(c0 & 1) ans += A;
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; cin >> nofkase;
    cin >> S >> A >> B >> C;
    cout << proc() << endl;
    return 0; 
}