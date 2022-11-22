/**
 * 给N个长度不超过10的字符串，两个人轮流走棋，每一步：
 * 选择一个字符串且该字符串的开头与上一个字符串的结尾相同。
 * 不能选者告负。问先手的胜负。
 * 由于N不超过16，显然是一个状压博弈论DP
 * 令Dis为上一个字符串是i、已选字符串为s时，先手的胜负
 * 其中s用二进制位表示N个字符串的选取与否
 * 则下一个局面显然是 D[j][s|(1<<j)]，其中j是的开头字母与i的结尾字母相等。
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
int const SIZE = 17;
#else
int const SIZE = 17;
#endif

using si = unordered_set<int>;
using msi = unordered_map<int, si>;
using llt = long long;

int N;
string S[SIZE];
int D[16][1<<16];

int dfs(int st, int last){
    if(D[last][st] != -1) return D[last][st];

    for(int i=0;i<N;++i){
        if((1<<i)&st) continue;
        if(S[i][0] != S[last].back()) continue;

        bool b = dfs(st|(1<<i), i);
        if(!b) return D[last][st] = 1;
    }
    return D[last][st] = 0;
}

bool proc(){
    for(int i=0;i<N;++i){
        bool b = dfs(1<<i, i);
        if(!b) return true;
    }
    return false;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r" ,stdin);
#endif
    memset(D, -1, sizeof(D));
    cin >> N;
    for(int i=0;i<N;++i) D[i][(1<<N)-1] = 0;
    for(int i=0;i<N;++i) cin >> S[i];
    puts(proc()?"First":"Second");
    return 0;
}
