/**
 * 初始价格x，每卖出k个就涨价y，现有N个客户
 * 第i个客户购买N+1-i个物品。
 * 问卖到T元，要接待多少个客户。
 * 注意到客户只有10000个，直接循环模拟即可
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

llt X, Y, K, N, T;

llt proc(){
    llt total = 0;
    llt left = 0;
    for(int p=N,i=1;i<=N;++i,--p){
        total += X * p;
        if(total >= T) return i;
        auto c = (left + p) / K;
        X += c * Y;
        left = (left + p) % K;
    }
    return -1;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> X >> Y >> K >> N >> T;
    cout << proc() << endl;
    return 0;
}