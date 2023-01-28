/**
 * 给一个长度为N的字符串S作为目标，初始字符串为空，2种操作
 * 1 在尾部添加任意一个字母
 * 2 在尾部添加一个已有的子串
 * 问能否在少于N次的操作中得到S
 * 显然，只用1操作，可以在N次得到S。因此只要看能否用到一次2操作添加大于1的子串即可
 * 不需要讨论更长的字符串，只需要讨论长度为2的子串即可
 * 如果任何一个长度为2的子串出现过2次，就能使用2操作。
 * 长度2为2的子串分两类，一类是ab各不相同，用计数器统计即可。
 * 一种是aa，用计数器，如果是3个a只能统计一次。
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
char S[SIZE];
vvi Cnt;


bool proc(){
	if(N <= 3) return false;
    Cnt.assign(256, vi(256, 0));
	for(int i=0;i<N-1;++i){
		if(S[i] == S[i+1]) continue;
		if(++Cnt[S[i]][S[i+1]] > 1) return true;
	}

	vi cnt(256, 0);
	int k = 0;
	while(1){
		int tmp = 0;
		while(k + tmp < N && S[k] == S[k+tmp]) ++tmp;
		if(tmp >= 4) return true;
		if(tmp > 1){
			if(++cnt[S[k]] > 1) return true;
		}
		if((k += tmp) == N) break;
	}
	return false;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif

    int nofkase; scanf("%d", &nofkase);
	while(nofkase--){
	    scanf("%d%s", &N, S);
		puts(proc()?"YES":"NO");
	}

    return 0;
}