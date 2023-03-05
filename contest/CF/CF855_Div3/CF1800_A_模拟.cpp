/**
 * 如果一个字符串可以分为四个部分，依次是
 * 连续的大写或小写的m，连续的大写或小写的e，连续的大写或小写的o，连续的大写或小写的w
 * 则称为good，给定字符串问是否good
 * 做一个unique，再判断一下即可
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
string const T = "meow";

bool proc(){
	S.erase(unique(S.begin(), S.end(), [](char a, char b){
		int sa = islower(a) ? 1 : 0;
		int sb = islower(b) ? 1 : 0;
		int st = (sb << 1) | sa;
		switch(st){
			case 0: case 3: return a == b;
			case 1: return a - 32 == b;
			case 2: return a + 32 == b;
			default: assert(0);
		}
		return false;
	}), S.end());
    if(S.size() != 4) return false;
	if(S[0] != 'm' and S[0] != 'M') return false;
	if(S[1] != 'e' and S[1] != 'E') return false;
	if(S[2] != 'o' and S[2] != 'O') return false;
	if(S[3] != 'w' and S[3] != 'W') return false;
	return true;
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
		puts(proc()?"YES":"NO");
	}
    return 0; 
}