/**
 * N个石子，双方轮流取，第i个回合取出的数放到各自的第i格
 * 最后按字典序排序。小的获胜。问先手胜负。
 * 显然只能取1。所以判断一下奇偶即可。
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
int const SIZE = 810;
#endif

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vll = vector<llt>;

int N;
int M;
int Q;
vi A;
vll S;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    N = getInt();
    puts(N&1 ? "Yaya-win!" : "win-win!");
    return 0;
}