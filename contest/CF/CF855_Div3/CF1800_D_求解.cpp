/**
 * 给定一个字符串，每次删掉相邻的两个字母，问一共能够形成多少个不同的子串
 * 假设字符串 .....xx.....yy..... 删除xx和yy所得到的子串是相等的，则显然有
 * 如果xx本身是两个不同的字母，则 xx....yy 的循环节是 xx， 且长度是偶数
 * 否则该子串长度可以是奇数。
 * 无论何种情况， 令 xx...yy 长度为n，本来可以产生 n-1 个子串，但现在只能计数为1
 * 总结而言就是对位置i，如果 S[i-1] == S[i+1]，则该位置不能计数。
 * 遍历一遍减掉即可。 
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

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

llt const MOD = 998244353LL;

int N;
string S;

int proc(){
    int ans = N - 1;
    int k = 0;
	while(1){
		int t = 0;
		while(k + t < N && S[k] == S[k + t]) ++t;
		if(t >= 3) ans -= t - 2;
		if((k += t) == N) break;
	}
	for(int i=1;i+1<N;++i){
		if(S[i - 1] != S[i] and S[i - 1] == S[i + 1]){
			--ans;
		}
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; scanf("%d", &nofkase);
    // int nofkase = getInt();
	int nofkase; cin >> nofkase;
	while(nofkase--){
        cin >> N >> S;
		printf("%d\n", proc());
	}
    return 0; 
}