/**
 * 给定A和B，然后进行N步。
 * 第1步，令每个Bi的得分是min(Ai, Bi)，且Ai要减去此得分，然后将B左移一格(此时B1就移出去了)
 * 第2步，令每个Bi的得分是min(A[i-1], Bi)，且A[i-1]要减去此得分，然后B左移一格
 * 第k步，令得分是min(A[i-k+1], Bi)，且A[i-k+1]要减去此得分，然后B左移一格
 * 问，每个Bi的得分是多少。
 * 考虑每个Ai能够向后支持多少B。求出B的前缀和S，就可以利用二分确定这一点。
 * 假设Ai可以向后支持到j，则B[i,...,j]都要可以加1个完整的次，B[j+1]则要加上Ai还剩下的值
 * 最后每个每个Bi的得分就是 完整次数 * Bi + 累积剩下的
 * 中间需要成段更新单点求值，直接使用了线段树。
 * 也可以变形一下，利用差分数组，由于中间没有查询，只需要最后查询一次，因此修改时只需头尾加减一即可，可以做到O(1)
 * 最后查询，正好随着循环做一个累加和，也是O(1)的。
 * 总时间O(NlogN)
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

llt const MOD = 1E9+7LL;

struct _t{
    llt sum;
	llt lazy;
}St[SIZE<<2];

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t) | 1;}

void _pushUp(int t){
	St[t].sum = St[lson(t)].sum + St[rson(t)].sum;
}

void _pusDown(int t, int s, int e){
	auto & lazy = St[t].lazy;
	if(0 == lazy) return;
    int mid = (s + e) >> 1;  
	int son = lson(t);
    St[son].sum += lazy * (mid - s + 1);
	St[son].lazy += lazy;

	son = rson(t);
	St[son].sum += (e - mid) * lazy;
    St[son].lazy += lazy;

	lazy = 0;
}

void build(int t, int s, int e){
	St[t].lazy = 0;
	if(s == e){
		St[t].sum = 0;
		return;
	}
	int mid = (s + e) >> 1;
	build(lson(t), s, mid);
	build(rson(t), mid + 1, e);
	_pushUp(t);
}

void modify(int t, int s, int e, int a, int b, llt d){
	if(a <= s && e <= b){
		St[t].sum += (e - s + 1) * d;
		St[t].lazy += d;
		return;
	}
	_pusDown(t, s, e);
	int mid = (s + e) >> 1;
	if(a <= mid) modify(lson(t), s, mid, a, b, d);
	if(mid < b) modify(rson(t), mid + 1, e, a, b, d);
	_pushUp(t);
}

llt query(int t, int s, int e, int a, int b){
	if(a <= s && e <= b){
		return St[t].sum;
	}
	_pusDown(t, s, e);
	int mid = (s + e) >> 1;
	llt ans = 0;
	if(a <= mid) ans += query(lson(t), s, mid, a, b);
	if(mid < b) ans += query(rson(t), mid + 1, e, a, b);
	return ans;
}

int N;
vll A, B;

void proc(){
	vll s(N + 1, 0LL);
	for(int i=1;i<=N;++i) s[i] = s[i - 1] + B[i];
	
    build(1, 1, N);

	vll ans(N + 1, 0LL);	
	for(int i=1;i<=N;++i){
		llt level = A[i] + s[i - 1];
        int pos = lower_bound(s.begin(), s.end(), level) - s.begin();
		if(pos == N + 1){
            modify(1, 1, N, i, N, 1);
		}else if(s[pos] == level){
            modify(1, 1, N, i, pos, 1);    
		}else{
			assert(level < s[pos]);
			if(pos > i) modify(1, 1, N, i, pos - 1, 1);
			ans[pos] += level - s[pos - 1];
		}
	}
	for(int i=1;i<=N;++i){
		ans[i] += B[i] * query(1, 1, N, i, i);
	}
	for(int i=1;i<=N;++i)printf("%lld ", ans[i]);
	printf("\n");
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nofkase = getInt();
	// int nofkase; cin >> nofkase;
	for(int kase=1;kase<=nofkase;++kase){
		// printf("kase = %d\n", kase);
        N = getInt();
		A.assign(N + 1, 0);
		B.assign(N + 1, 0);
		for(int i=1;i<=N;++i) A[i] = getInt();
        for(int i=1;i<=N;++i) B[i] = getInt();
		proc();
	}
	return 0; 
}