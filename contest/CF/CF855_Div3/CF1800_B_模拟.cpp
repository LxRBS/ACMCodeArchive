/**
 * 给定一个字符串，每一对大小字母算作一对
 * 最多可以做K次操作，每次操作改变一个字母的大小写。
 * 问最多可以拿到多少对
 * 统计一下大小写字母的数量，做一个贪心即可。 
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

inline int ABS(int x){return x>=0?x:-x;}

int N, K;
string S;

int proc(){
	vi flag(256, 0);
	for(char ch : S) ++flag[ch];

    int ans = 0;
	for(int i='a';i<='z';++i){
		auto u = flag[i];
		auto v = flag[i-32];
        ans += min(u, v);
		
		auto tmp = ABS(u - v);
        tmp = tmp / 2;
		tmp = min(tmp, K);
		K -= tmp;
		ans += tmp;
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
        cin >> N >> K >> S;
		cout << proc() << endl;
	}
    return 0; 
}