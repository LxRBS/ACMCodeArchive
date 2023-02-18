/**
 * 给定一个数组，取若干子串，要求每个子串和大于等于0
 * 问所有子串长度加起来最大是多少
 * 令Di为到i为止的最大，则，假设i是最后一个子串的结尾，且该子串从j+1开头，有
 * Di = max{Dj + i - j, j+1到i的区间和大于等于0}
 * 如果i不是结尾，显然Di = D[i-1]
 * 因此： Di = max(D[i-1], {Dj+i-j, j+1到i的区间和大于等于0})
 * 直接DP显然是平方的，需要优化。
 * 很明显要计算一个前缀和，于是条件等价于 Si >= Sj
 * 于是考虑使用权值线段树,离散化前缀和。
 * 对每一个i，假设其前缀和的离散化为Wi，查询[1, Wi]上的最大值记作tmp，
 * 求出 D[i] = max(D[i-1], i + tmp)
 * 在将线段树上Wi位置的值修改为 Di - i。
 * 这样可以保证每次查出来的tmp必然是所有前缀和比i小的j中最大的Dj-j。
 * O(NlogN)
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

char getChar(){
	char ch = __hv007();
	while( ch != 'o' && ch != 'x' ) ch = __hv007();
	return ch;
}

#ifndef ONLINE_JUDGE
int const SIZE = 21;
#else
int const SIZE = 2e5+5;
#endif

using llt = long long;
using vi = vector<int>;
using vll =vector<llt>;
using edge_t = tuple<int, int, int, int>;
using ve = vector<edge_t>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

llt const MOD = 998244353LL;

llt St[SIZE<<2];
inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t) | 1;}

inline void _update(int t, llt d){
	St[t] = d;
}

inline void _pushUp(int t){
	St[t] = max(St[lson(t)], St[rson(t)]);
}

void build(int t, int s, int e){
	St[t] = - MOD;
	if(s == e) return;
	int mid = (s + e) >> 1;
	build(lson(t), s, mid);
	build(rson(t), mid + 1, e);
}

void modify(int t, int s, int e, int pos, llt d){
	if(s == e){
		_update(t, d);
		return;
	}
	int mid = (s + e) >> 1;
	if(pos <= mid) modify(lson(t), s, mid, pos, d);
	else modify(rson(t), mid + 1, e, pos, d);
	_pushUp(t);
}

llt query(int t, int s, int e, int a, int b){
	if(a <= s && e <= b){
		return St[t];
	}
	int mid = (s + e) >> 1;
	llt ans = -MOD;
	if(a <= mid) ans = max(ans, query(lson(t), s, mid, a, b));
	if(mid < b) ans = max(ans, query(rson(t), mid + 1, e, a, b));
	return ans;
}

vll A, S, W;
int N;
vll D;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // int nofkase = getInt();
	// int nofkase; cin >> nofkase;
    N = getInt();
	A.assign(N + 1, 0LL);
	S.assign(N + 1, 0LL);
    W.assign(N + 1, 0LL);
	for(int i=1;i<=N;++i) W[i] = S[i] = S[i - 1] + (A[i] = getInt());

	sort(S.begin(), S.end());
	S.erase(unique(S.begin(), S.end()), S.end());
	int m = S.size();
    build(1, 1, m);
	auto z = lower_bound(S.begin(), S.end(), 0LL) - S.begin() + 1; 
	modify(1, 1, m, z, 0);
	
	D.assign(N + 1, 0);
	for(int i=1;i<=N;++i){
        auto pos = lower_bound(S.begin(), S.end(), W[i]) - S.begin() + 1;
		auto tmp = query(1, 1, m, 1, pos);
        D[i] = max(D[i - 1], i + tmp);
		modify(1, 1, m, pos, D[i] - i);
	}

	cout << D[N] << endl;
	return 0; 
}