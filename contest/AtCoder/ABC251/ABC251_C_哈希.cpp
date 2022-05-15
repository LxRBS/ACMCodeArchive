/**
  给定若干对(S,T)，S表示字符串，T表示得分
  问在所有第一次出现的S中，最大的T是多少
  S长度为10，一共1E5对，用map即可
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
 
	llt ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;
}
 
#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 100+5;
#endif

using Real = long double;
using vi = vector<int>;
using pii = pair<int, int>;
using map_t = unordered_map<string, int>;

int N;
map_t Map;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>N;
	string s;
	int ans = 0;
	int score = -1;
	for(int t,i=1;i<=N;++i){
		cin>>s>>t;
		auto it = Map.find(s);
		if(it == Map.end()){
			it = Map.insert(it, {s, t});
			if(t > score){
				score = t;
				ans = i;
			}
		}
	}
	cout<<ans<<endl;
    return 0;
}
