/**
 * 给定一个有a和b构成的字符串，长度大于等于3，要求将其拆成三段满足
 * 中间的一段要么字典序最小，要么最大。注意，无需严格
 * 假设第一个字母是a，从后面找到第一个a，分三种情况
 * 没有第二个a，则将字符串分为 a bb...b b即可
 * 最后一个是a，则将字符串分为 a xx...x a即可
 * a在中间，将字符串分为 axx...x a xx.x即可
 * 对b照此办理
 */
#include <bits/stdc++.h>
using namespace std;
 
char *__abc147, *__xyz258, __ma369[1000000];
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
int const SIZE = 23;
#else
int const SIZE = 3500000;
#endif

using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;

string S;

void proca(){
	int n = S.length();
	int k = n - 1;
	while(k >= 0 && 'a' != S[k]) --k;
	if(0 == k){
		cout << "a " << S.substr(1, n - 2) << " b" << endl;
		return; 
	}
	if(k + 1 == n){
		cout << "a " << S.substr(1, n - 2) << " a" << endl;
		return;
	}
    cout << S.substr(0, k) << " a " << S.substr(k + 1) << endl;
}

void procb(){
	int n = S.length();
	int k = 1;
	while(k < n && 'b' == S[k]) ++k;
	if(k == n){
		cout << "b " << S.substr(1, n - 2) << " b" << endl;
		return;
	}
	if(k + 1 == n){
		cout << "b " << S.substr(1, n - 2) << " a" << endl;
		return;
	}
	cout << S.substr(0, k) << " a " << S.substr(k + 1) << endl;
}

void proc(){
	int n = S.length();
	if('a' == S[0]){
		return (void)proca();
	}
    procb();
} 

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int nofkase; cin >> nofkase;
	while(nofkase--){
        cin >> S;
		proc();
	}

    return 0;
}


