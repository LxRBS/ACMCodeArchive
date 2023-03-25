/**
 * 给定字符串S每一次将S中的某个字母全部改成0或者1
 * 问最后的01字符串是否能够满足相邻的字母不相等
 * 只需要每一个字母的所有位置奇偶性相同即可。
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

int N;
string S;

bool proc(){
	array<vi, 26> pos;
	for(int i=0;i<N;++i){
        pos[S[i] - 'a'].push_back(i);
	}
	for(const auto & v : pos){
		if(v.size() <= 1) continue;

		bool flag = v[0] & 1;
		for(int i=1;i<v.size();++i){
			if(flag and 0 == v[i] % 2) return false;
			if(!flag and (v[i] & 1)) return false;
		}
	}
	return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// int nofkase; scanf("%d", &nofkase);
	int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N >> S;
		puts(proc()?"YES":"NO"); 
	}
    return 0; 
}


