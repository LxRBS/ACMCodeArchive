/**
 * 数轴上有N个点，给定坐标。一旦开始行动，每个点都会查最近的点的方向移动，直到两个点相遇
 * 如果左右都是最近，则向左移动。每次选择这N个点的子集(至少包含2个点)开始行动，则会产生若干个相遇点。
 * 求所有子集的相遇点数量的总和。考虑每一个可能的相遇点对总和的共线，每一个可能的相遇点必然是两个点造成的。
 * 因此枚举两个点，记作i和j，注意中间不能有其他点，令其间距为diff，则 Xi - diff 以内的点不能选，Xj + diff 以内的点不能选
 * 因此只有形如{前面的点,i,j,后面的点}的集合能够贡献出ij的相遇点。这样的集合一共有2^m个，m是前后可行点的数量。这个数量可以用二分求出。
 * O(N^2logN)，利用单调栈可以做到O(N^2)
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

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using edge_t = tuple<int, int, int, int>;
using ve = vector<edge_t>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 1E9+7LL;

vll Pow;
vll X;
int N;

llt proc(){
    Pow.assign(N + 1, 0LL);
	Pow[0] = 1LL;
	for(int i=1;i<=N;++i) Pow[i] = Pow[i - 1] * 2 % MOD;

    llt ans = 0;
    for(int i=0;i<N;++i)for(int j=i+1;j<N;++j){
		auto diff = X[j] - X[i];
        auto tmp = X[i] - diff;
		auto pos = lower_bound(X.begin(), X.end(), tmp) - X.begin();
		auto ret = Pow[pos];
		tmp = X[j] + diff;
		pos = lower_bound(X.begin(), X.end(), tmp) - X.begin();
		ret = ret * Pow[N - pos] % MOD;
		ans = (ans + ret) % MOD; 
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    X.assign(N = getInt(), 0LL);
    for(auto & i : X) i = getInt();
	cout << proc() << endl;
    return 0; 
}