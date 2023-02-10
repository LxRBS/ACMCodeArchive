/**
 * 给定多行字符串，统计指定单词的数量以及将指定单词替换成指定内容。
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
 
#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 1E6+1;
#endif

vector<string> V;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	string s;
	while(getline(cin, s)){
		if("#" == s) break;
		V.emplace_back(s);		
	}

    auto f = [](const string & s, int pos){
		if(pos && s[pos-1] != ' ') return 0;
		if(pos + 4 != s.length() && s[pos+4] != ' ') return 0;
		if(s[pos] == 'N' && s[pos+1] == 'E' && s[pos+2] == 'U' && s[pos+3] == 'Q'){
			return 2;
		}
		if((s[pos] == 'N' || 'n' == s[pos]) && (s[pos+1] == 'E' || 'e' == s[pos+1]) && (s[pos+2] == 'U' || 'u' == s[pos+2]) && (s[pos+3] == 'Q' || 'q' == s[pos+3])){
			return 1;
		}
		return 0;
	};

    const string RE = "WOW NEUQ";
    int ans = 0;
	for(auto & s : V){
		int k = 0, n = s.length();
		while(k + 3 < n){
            auto tmp = f(s, k);
			if(1 == tmp) {
				++ans;
				k += 5;
			}else if(2 == tmp){
				s.replace(k, 4, RE);
				k += 5 + 4;
				n += 4;
			}else{
				++k;
			}
		}
	}
	cout << ans << endl;
	for(const auto & s : V) cout << s << endl;
    return 0;
}