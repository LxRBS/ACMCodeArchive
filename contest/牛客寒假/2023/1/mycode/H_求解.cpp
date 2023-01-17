/**
 * 有N*N的拼图，每一小块的4边，有可能是平的，有可能是凸出一个小半圆，也有可能是凹进一个小半圆
 * 保证凹凸是对应的。现在从中拿走一块，再把剩下的打乱次序给出（但每一块的朝向还是保证原样）
 * 图块的分数为 10-凹数量+凸数量
 * 问拿走的那块的分数
 * 由于题目保证是完整的，因此只需把剩下的拼图遍历一遍，统计一下上下左右的凹凸数量，就可以知道缺的那块上下左右的凹凸数量了。
 */
#include <bits/stdc++.h>
using namespace std;
 
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
 
#ifndef ONLINE_JUDGE
int const SIZE = 23;
#else
int const SIZE = 450;
#endif

using Real = long double;
using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using prr = pair<Real, Real>;
using mvi = map<int, vi>;

int Cnt[3][4];
int N;

int proc(int a, int b){
    return b - a;
}

int proc(){
    int ans = 0;
    ans += proc(Cnt[2][0], Cnt[1][2]);
    ans += proc(Cnt[2][3], Cnt[1][1]);
    ans += proc(Cnt[2][1], Cnt[1][3]);
    ans += proc(Cnt[2][2], Cnt[1][0]);
    return 10 + ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int nofkase; cin >> nofkase;
    while(nofkase--){
        cin >> N;
        memset(Cnt, 0, sizeof(Cnt));
        for(int i=1,n=N*N;i<n;++i){
            string s; cin >> s;
            for(int j=0;j<4;++j){
                ++Cnt[s[j] - '0'][j];
            }            
        } 
        cout << proc() << endl;
    }

    return 0;
}


