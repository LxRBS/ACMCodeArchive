/**
 * 给定一个数组A，遍历其所有子数组，每一次改动最少的元素使得当前子数组为回文
 * 问一共要改多少个元素。注意每次改动是独立的。
 * 枚举每个子数组显然是T的，反过来考虑枚举每一对位置
 * 如果 Ai == Aj, 则该对在 min(i, N-j+1) 个子数组中就是无需改动的
 * 考虑计算出每一对位置在多少个子数组中是无需改动的
 * 令Pos[i]记录了所有元素值为i的在A中的位置，从1开始计数，以下直接记作Pos
 * 首先求一个后缀和，令 Suf[i] = SIGMA{Pos[i,...,n], n为当前Pos数组的长度}
 * 然后for Pos数组中的每个下标u，假设v位置是其分界线，即v之前的Pos[v]都满足N - Pos[v] + 1 > Pos[u]
 * 则当前位置无需更改的对数一共是 (v - u) * Pos[u] + Suf[v + 1]
 * 注意如果 v < u，则直接就是 Suf[u + 1]
 * 每个Pos数组的处理都可以在线性时间内完成，因此一共是O(N)
 * 也可以对每个u使用二分处理，应该也够。
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

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
int const SIZE = 21;
#else
int const SIZE = 2e5+5;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 998244353LL;
int const INF = 2000000000;

int N;
vi A;

llt proc(const vi & vec){
	llt ans = 0;
	vll suf(vec.size() + 1, 0LL);
	int u = 0, v = vec.size() - 1;
	int n = vec.size() - 1;
	while(u < n){
		llt t = vec[u];
        while(v > u && N + 1 <= t + vec[v]) suf[v] = suf[v + 1] + N - vec[v] + 1,  --v;
		if(v >= u) ans += (v - u) * t + suf[v + 1];
		else ans += suf[u + 1];
		++u;
	}
	return ans;
}

llt proc(){
	map<int, vi> pos;
	for(int i=0;i<N;++i) pos[A[i]].push_back(i + 1);

	llt res=0;
	for(llt i=1;i<=N;i++){
		res+=(N+1-i)*(i/2);
	}

    llt ans = 0;
	for(const auto & p : pos){
		ans += proc(p.second);
	}

	return res - ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    A.assign(N=getInt(), 0);
	for(int & i : A) i = getInt();
	cout << proc() << endl;
	return 0;
}