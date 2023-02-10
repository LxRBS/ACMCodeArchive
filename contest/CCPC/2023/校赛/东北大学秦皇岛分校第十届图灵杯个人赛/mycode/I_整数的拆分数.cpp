/**
 * 整数的拆分数模板题。N在5000，因此如果使用平方做法，最好滚动优化。
 * 也可以看作完全背包。同样也是平方做法。
 * 这里使用了线性做法。五边形数。
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
int const SIZE = 133;
#else
int const SIZE = 1E6+10;
#endif

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

llt const MOD = 998244353LL;

int N;
vector<llt> D;
 
void init(int sz){
    D.assign(sz * 3, 0);
    for(int i = 0; i <= sz; i++){
        D[2 * i] = i * (i * 3 - 1) / 2;
        D[2 * i + 1] = i * (i * 3 + 1) / 2;
    }
}

llt f(int n){
    vi d(n + 1, 0);
    d[1] = 1;
    d[2] = 2;
    d[0] = 1;
    for (int i = 3; i <= n; i++)    {
        int k = 0;
        int flags;
        d[i] = 0;
        for (int j = 2; D[j] <= i; j++)        {
            flags = k & 2;
            if (!flags)
                d[i] = (d[i] + d[i - D[j]] + MOD) % MOD;
            else
                d[i] = (d[i] - d[i - D[j]] + MOD) % MOD;
            k++;
            k %= 8;
        }
    }
    return d[n];
}
 
int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    cin >> N;
    init(N);
    cout << f(N) << endl;
    return 0;
}