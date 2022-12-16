/**
 * 字符串S，做如下操作变成T
 * 假设当前字母是字母表的前9个字母之一，则将写序号
 * 否则除了写序号还要在后再写一个0
 * 给定T，要求还原出S
 * 倒着扫描即可
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
int const SIZE = 2E5+10;
#endif

using llt = long long;
using vi = vector<int>;
using si = set<int>;
using vvi = vector<vi>;
using msi = map<int, si>;

int N;
string S;

string proc(){
	string ans;
    int k = N - 1;
	while(k >= 0){
		if(S[k] == '0'){
			int tmp = (S[k-2] - '0') * 10 + S[k-1] - '0' - 1;
            ans += (char)('a' + tmp);
			k -= 3;
		}else{
            ans += (char)('a' + S[k] - '0' - 1);
			k -= 1;
		}
	}
	return string(ans.rbegin(), ans.rend());
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
	while(nofkase--){
        cin >> N >> S;
		cout << proc() << endl;
	}

    return 0;
}


