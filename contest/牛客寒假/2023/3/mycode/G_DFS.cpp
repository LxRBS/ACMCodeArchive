/**
 * 给一个字符串，格式如
 * 数 ? 数 ? 数 = 数
 * 其中数不超过1E9的非负整数，问号不超过12个。字符串格式保证正确，没有什么奇怪的可能。
 * 问号可以替换为加号、减号和井号，其中 a#b = a^a % b
 * 问能否填入合法运算符使得等式成立。
 * 所有运算符均为左结合，特别的井号的运算数必须是正的。
 * 首先做个字符串处理，将数和问号的位置还有右边的结果处理出来，然后直接深搜即可。
 * 一开始用STLstring，re了很多次，不知道哪里有问题。
 * 改成char[]输入，一次AC
 * 注意到问号一共只有12个，因此所有方案数是3^12，50w+，也可以直接状压枚举
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
int const SIZE = 26;
#else
int const SIZE = 2800;
#endif
 
using llt = long long;
using Real = long double;
using vi = vector<int>; 

llt powerMod(llt a,llt n,llt mod){
    llt ret = 1;
    a %= mod;

    while( n ){
        if ( n & 1 ) ret = ret * a % mod;
        n >>= 1;
        a = a * a % mod;
    }
    return ret;
}

int N;
char S[SIZE];
vector<llt> Vec;
vector<int> Fu;
llt Right;

bool dfs(int pos, llt cur){
	if(pos == Fu.size()){
		if(cur == Right) return true;
		return false;
	}

	auto t = Fu[pos];
	auto nxt = Vec[pos + 1];

	S[t] = '+';
	auto b = dfs(pos + 1, cur + nxt);
	if(b) return true;

	S[t] = '-';
	b = dfs(pos + 1, cur - nxt);
	if(b) return true;

	if(cur > 0 && nxt > 0){
		S[t] = '#';
		b = dfs(pos + 1, powerMod(cur, cur, nxt));
		if(b) return true;
	}

	return false;
}

void proc(){
	N = 0;
	while(S[N]){
		if(isdigit(S[N])){
			llt v = 0;
			while(isdigit(S[N])){
				v = v * 10 + S[N] - '0', ++N;
			}
            Vec.push_back(v);
		}else if('=' == S[N]){
			++N;
		}else if('?' == S[N]){
			Fu.push_back(N); ++ N;
		}else if(S[N] = '\n'){
			break;
		}else{
			assert(0);
		}
	}
	S[N] = '\0';

    Right = Vec.back();
	if(dfs(0, Vec[0])){
		puts(S); return;
	}
	puts("-1");
	return;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0);
	// cin.tie(0); cout.tie(0);
    fgets(S, SIZE - 1, stdin);
	proc();
    return 0;
}