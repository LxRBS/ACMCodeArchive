/**
 * N个人，每次下达一个指令x，每x个人组成一团，没有成团的人淘汰
 * 可以下达任意指令。问最少几次指令使得剩下的人最少。
 * 观察样例，考虑折半即可。
 * N是偶数，令x=N/2+1，则留下x人
 * N是奇数，令x=N/2+1，还是留下x人
 * 直到2。这样是最少次数。
 * 注意特判 
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

llt N;
int M;
int Q;
vi A;
vll S;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    if(N <= 2) {
        cout << 0 << endl;
        return 0;
    }
    int cnt = 0;
    while(N != 2){
        if(N & 1) N = N - N / 2;
        else N = N / 2 + 1;
        ++cnt;
    }
    cout << cnt << endl;
    return 0;
}