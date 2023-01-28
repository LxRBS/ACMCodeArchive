#include <bits/stdc++.h>
using namespace std;

namespace IO{

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

using llt = long long;

llt getLL(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}
 
	llt ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10LL + (llt)(ch-'0');
	return sgn ? ret : -ret;    
}

char getChar(function<bool(char)> ok){
    char ch = __hv007();
    while(!ok(ch)) ch = __hv007();
    return ch;
}

}

namespace ZIFUCHUAN{

/// Duval算法实现Lyndon分解
/// 每个字符串都可以唯一分解成若干个Lyndon字符串
/// 返回Lyndon串的数量，ans保存右端点的位置，从0开始编号
template<typename IT>
int Duaval(IT begin, int n, vector<int> & ans){
	ans.clear();
	auto end = begin + n;
	for(auto i=begin;i<end;){ 
        auto j = i;
		auto k = i + 1;
		while(k < end && *j <= *k){
			if(*j < *k) j = i;
			else ++j;
			++k;
		}
		while(i <= j){
			ans.emplace_back(i + (k - j - 1) - begin);
			i += k - j;
		}
	}
	return ans.size();
}

}

#ifndef ONLINE_JUDGE
int const SZ = 33;
#else
int const SZ = 5E6+10;
#endif

char S[SZ];

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); 
    // cin.tie(0); cout.tie(0);	

	scanf("%s", S);
	vector<int> vec;
	int n = ZIFUCHUAN::Duaval<char *>(S, strlen(S), vec);
	auto ans = 0;
	for(auto i : vec) ans ^= i + 1;
	printf("%d\n", ans);
	return 0;
}