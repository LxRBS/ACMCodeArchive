/**
 * 一个数字字符串，问其中有多少个子串满足其内所有字符出现的次数均为偶数
 * 令Di记录从[0,i]之间的字符出现次数的奇偶情况，显然Di是一个10位二进制向量。
 * 如果存在 Di == Dj，则[i+1, j]是满足条件的子串。
 * 因此求出所有Di，再使用map将其归类，最后数一下即可。
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_cxx;
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
int const SIZE = 2E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using ull = unsigned long long;
// using i128 = __int128_t;
using Real = long double;

Real const EPS = 1E-14;
inline int sgn(Real x) {return x > EPS ? 1 : (x < -EPS ? -1 : 0);}
inline bool is0(Real x) {return 0 == sgn(x);}


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    string s ; cin >> s;
	vi d(s.length(), 0);
	map<int, vi> pos;
	pos[d[0] = 1 << (s[0] - '0')].push_back(0);
	for(int i=1,n=d.size();i<n;++i){
		pos[d[i] = (1 << (s[i] - '0')) ^ d[i - 1]].push_back(i);
	}
	llt ans = 0;
	for(const auto & p : pos){
		auto n = p.second.size();
		if(p.first) ans += (n - 1LL) * n / 2LL;
		else ans += (n + 1LL) * n / 2LL;
	}
	cout << ans << endl;
    return 0; 
}


