/**
 * 初始有一个字符串S，未知，将其从某个k位置断开，并且得到字符串T为
 * S[1..k]S转置S[k+1...N]
 * 现在给定T，问是否能还原S
 * 将字符串看作是一个整数，假设k位置是正确的，T记作T[1...k,转置,k+1...N]，
 * 则 T[1...k]*10^(N) + (T[N+N] - T[N+k+1]) = S * 10^N
 * 再考虑T的转置，记作 T[N...K+1,S,k...1]，所以
 * (T[N+N-1-k] - T[N-1-k]) * 10^k = S * 10^N
 * 枚举每一个i，判断是否相等即可。
 * 不应采用十进制，应该大于26，不过可以AC
 * 另外将字母a编码为1更容易发现bug
 * 标程采用了Z算法，即扩展的KMP算法。
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

using llt = long long;
using vi = vector<llt>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;

llt const BIT = 10LL;
llt const MOD = 1E9+7;

int N;
string S;

inline int tr(char ch){return ch - 'a';}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> N >> S;

    vi pw(N+N, 1);
	for(int i=1;i<N+N;++i) pw[i] = pw[i - 1] * BIT % MOD;

    vi a(N+N, 0), b(N+N, 0);

    a[0] = tr(S[0]);
	b[0] = tr(S[N+N-1]);
	bool flag = a[0] == b[0];
	for(int i=1;i<N+N;++i){
		a[i] = (a[i - 1] + tr(S[i]) * pw[i] % MOD) % MOD; 
		b[i] = (b[i - 1] + tr(S[N+N-1-i]) * pw[i] % MOD) % MOD;
		flag = flag && a[i] == b[i];
	}     

    if(flag){
		return printf("%s\n0\n", S.substr(N, N).c_str()), 0;
	}

    int ans = -1;
	for(int i=0;i<N;++i){
		llt u = (a[i] * pw[N] % MOD + (a[N+N-1] - a[N+i] + MOD) % MOD) % MOD;
		llt v = (b[N+N-2-i] - b[N-2-i] + MOD) * pw[i+1] % MOD;
		if(u == v){
			ans = i;
			break;
		}
	}    

    if(-1 == ans) return printf("-1\n"), 0;
	printf("%s%s\n%d\n", S.substr(0, ans+1).c_str(), S.substr(ans+N+1).c_str(), ans+1);
    return 0;
}


