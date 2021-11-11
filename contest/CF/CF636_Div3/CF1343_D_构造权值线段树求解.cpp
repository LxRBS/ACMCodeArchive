/**
 * 给定一个数组A，做若干次替换操作，每次操作可以将ai换成[1, k]之间的某个数
 * 用最少的操作满足：
 * 1 所有的ai都不超过k
 * 2 a1+an==a2+a[n-1]==...==x
 * N/K都在2E5
 * 考虑任意目标值x，最多修改2次就能改好。
 * 对于给定的Ai和A[N-i+1]，如果x在[min+1, max+K]范围内，修改1次即可
 * 如果x刚好就是和，修改0次
 * 初始化一个线段树[1, 2K]，每个端点都是N
 * for i从1到N/2：
 *   对[min+1, max+K]范围做成段修改减一
 *   对和再减一
 * 求[1, 2K]的最小值即可，复杂度O(Nlog(2K))
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
int const SIZE = 22;
#else
int const SIZE = 200100<<1;
#endif

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}

int St[SIZE<<2];
int Lazy[SIZE<<2];

inline void _pushUp(int t){
	St[t] = St[lson(t)] + St[rson(t)];
}

inline void _pushDown(int t, int s, int e){
	if(0 == Lazy[t]) return;

	int &lazy = Lazy[t];
	int mid = (s+e) >> 1;
    int son = lson(t);
	Lazy[son] += lazy;
	St[son] += lazy * (mid - s + 1);
	son = rson(t);
	Lazy[son] += lazy;
	St[son] += lazy * (e - mid);
	lazy = 0;
}

void modify(int t, int s, int e, int a, int b, int delta){
	if(a<=s&&e<=b){
		St[t] += delta;
		Lazy[t] += delta;
		return;
	}

	_pushDown(t, s, e);
	int mid = (s+e) >> 1;
	if(a<=mid) modify(lson(t), s, mid, a, b, delta);
	if(mid<b) modify(rson(t), mid+1, e, a, b, delta);
	_pushUp(t);
}

int query(int t, int s, int e, int a, int b){
	if(a<=s&&e<=b){
		return St[t];
	}

	_pushDown(t, s , e);
	int mid = (s+e) >> 1;
	int ans = 0;
	if(a<=mid) ans += query(lson(t), s, mid, a, b);
	if(mid<b) ans += query(rson(t), mid+1, e, a, b);
	return ans;
}

int N, K;
int A[SIZE];

void build(int t, int s, int e){
	Lazy[t] = 0;
	if(s==e){
        St[t] = N;
		return;
	}
	int mid = (s+e) >> 1;
	build(lson(t), s, mid);
	build(rson(t), mid+1, e);
	_pushUp(t);
}

int proc(){
    build(1, 1, K+K);
	for(int left, right, i=1;i<=N/2;++i){
        left = min(A[i], A[N-i+1]) + 1;
		right = max(A[i], A[N-i+1]) + K;
		modify(1, 1, K+K, left, right, -1);
		modify(1, 1, K+K, A[i]+A[N-i+1], A[i]+A[N-i+1], -1);
	}
	int ans = 0x3F3F3F3F;
	for(int i=2;i<=K+K;++i){
		ans = min(ans, query(1, 1, K+K, i, i));
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    int nofkase = getInt();
    while(nofkase--){
        N = getInt(); K = getInt();
        for(int i=1;i<=N;++i) A[i] = getInt();
		printf("%d\n", proc());
	}
    return 0;
}

