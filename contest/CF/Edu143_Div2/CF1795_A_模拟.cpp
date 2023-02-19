/**
 * 两个字符串S和T表示两个塔，每一块是两种颜色之一。
 * 每次操作可以从一个塔顶选择一块移动到另一个塔顶。
 * 问能否通过操作使得两个塔均没有连续的相同颜色的块
 * 显然不需要反复横跳的操作，又由于参数很小，直接模拟即可。
 * 即把S都移到T，判断一遍，再把T都移到S判断一遍。
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

char getChar(){
	char ch = __hv007();
	while( ch != 'o' && ch != 'x' ) ch = __hv007();
	return ch;
}

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using edge_t = tuple<int, int, int, int>;
using ve = vector<edge_t>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 1E9+7LL;

int N, M;
string S, T;

bool check(const string & s){
	for(int i=0,n=s.length();i+1<n;++i){
		if(s[i] == s[i + 1]) return false;
	}
	return true;
}

bool proc(string a, string b){
	if(check(a) && check(b)) return true;
	for(int i=a.length()-1;i>=1;--i){
		b += a.substr(a.length() - 1, 1);
		a.pop_back(); 
		if(check(a) && check(b)) return true;
	}
	return false;
}

bool proc(){
    bool b = proc(S, T);
	if(b) return true;
	b = proc(T, S);
	return b;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // int nofkase = getInt();
	int nofkase; cin >> nofkase;
	for(int kase=1;kase<=nofkase;++kase){
        cin >> N >> M >> S >> T;
	    cout << (proc() ? "YES" : "NO") << endl;
	}
	return 0; 
}