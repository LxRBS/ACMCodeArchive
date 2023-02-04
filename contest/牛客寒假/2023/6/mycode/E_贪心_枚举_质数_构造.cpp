/**
 * N个节点的完全图，如果 j - i <= K，则ij边的边权是lcm(i, j)，否则就是gcd(i, j)，问最小生成数的权值和是多少
 * 显然要尽量取gcd。其次，如果取lcm显然最好和1取，取gcd未必和1取，只需要互质即可。
 * 首先考虑N<=K的情况， 此时只能取lcm，无法取gcd。显然所有点与1取lcm即可。
 * 其次考虑N>K，则[K+2, N]的节点都可以和1取gcd，肯定是最小的。
 * 再考虑范围内的点2E5内最大的质数间距在100多。因此对每一个u，对[u+K+1, N]范围内枚举gcd(u, i)即可
 * 2E5以内质数最大间隔为(155921, 156007)，差为86， 因此复杂度最多是O(86N)。
 * 加上筛法，总共为O(NlogN+86N)
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
int const SIZE = 1E6+10;
#endif

using llt = long long;
using vi = vector<int>;
using vvi = vector<vi>;

int N, K;

llt proc(int val){
    int ans = val;
    for(int i=val+K+1;i<=N;++i){
        auto t = __gcd(val, i);
        if(1 == (ans = min(ans, t))) break;
    }
    return ans;
}

llt proc(){
    if(N <= K){
        return (N + 2LL) * (N - 1LL) / 2;
    }
    llt ans = N - K - 1;
    for(int i=2;i<=K+1;++i){
        ans += proc(i);
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> K;
    cout << proc() << endl;
    return 0;
}