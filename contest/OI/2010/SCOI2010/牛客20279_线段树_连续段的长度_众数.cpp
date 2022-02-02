/**
 * 线段树区间操作，只有01的数组，5种操作
 * 0 a b: [a, b]区间全变为0
 * 1 a b: [a, b]区间全变为1
 * 2 a b: [a, b]区间取反
 * 3 a b: [a, b]区间1的数量
 * 4 a b: [a, b]区间中最长连续1的数量
 * 两种类型的延迟，设置和取反，注意操作的顺序
 * 需要记录1的总数量，还要分别记录0和1的最长连续的数量，左端连续的数量和右端连续的数量
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

void getString(char *p){
	char ch = __hv007();
	while(!isalpha(ch)) ch = __hv007();

	*p++ = ch;
	while(isalpha(ch = __hv007())) *p++ = ch;
	*p++ = '\0';
}

typedef long long llt;

#ifndef ONLINE_JUDGE
int const SIZE = 12;
#else
int const SIZE = 100110;
#endif

int const ONE = 1;
int const ZER = 2;
int const XOR = 4;

int N;
int M;

inline int lson(int t){return t<<1;}
inline int rson(int t){return lson(t)|1;}
inline int max(int a,int b, int c){return max(a, max(b, c));}

int Front[2][SIZE<<2];// 前端连续
int Back[2][SIZE<<2]; // 后端连续
int Long[2][SIZE<<2]; // 最长连续
int St[SIZE<<2];      // 总数量
char Lazy[SIZE<<2];

inline void _pushUp(int t, int s, int e){
	int mid = (s + e) >> 1;
	int c[2] = {mid - s + 1, e - mid};
    int a = lson(t), b = rson(t);
	St[t] = St[a] + St[b];
	for(int i=0;i<2;++i){ // 0和1分别pushUp
        Front[i][t] = Front[i][a] == c[0] ? c[0] + Front[i][b] : Front[i][a];
		Back[i][t] = Back[i][b] == c[1] ? c[1] + Back[i][a] : Back[i][b];
		Long[i][t] = max(Long[i][a], Long[i][b], Back[i][a]+Front[i][b]);
	}
}

inline void _pushDown(int t, int s, int e){
	char &lazy = Lazy[t];
	if(0 == lazy) return;

	int mid = (s + e) >> 1;
	int c[2] = {mid - s + 1, e - mid};
	int a = lson(t), b = rson(t);	

    /// 先设置再取反
	int k = -1, ok = -1;
	if(lazy & ONE) k = 1, ok = 0; 
	else if(lazy & ZER) k = 0, ok = 1;

	if(-1 == k) goto L;

	/// 先设置	
	Front[k][a] = Back[k][a] = Long[k][a] = c[0];
	Front[k][b] = Back[k][b] = Long[k][b] = c[1];

	Front[ok][a] = Back[ok][a] = Long[ok][a] = 0;
	Front[ok][b] = Back[ok][b] = Long[ok][b] = 0;

	St[a] = k == 1 ? c[0] : 0;
	St[b] = k == 1 ? c[1] : 0;

L:
    /// 再取反
	if(lazy & XOR){
        swap(Front[0][a], Front[1][a]);
		swap(Back[0][a], Back[1][a]);
		swap(Long[0][a], Long[1][a]);

		swap(Front[0][b], Front[1][b]);
		swap(Back[0][b], Back[1][b]);
		swap(Long[0][b], Long[1][b]);

		St[a] = c[0] - St[a];
		St[b] = c[1] - St[b];
	}

	/// 延迟标记往下传
	if(-1 == k){ // 说明只有取反延迟
        Lazy[a] ^= XOR; Lazy[b] ^= XOR;
	}else{ // 说明有设置
        Lazy[a] = Lazy[b] = lazy;
	}

	lazy = 0;
}

void modify(int t, int s, int e, int a, int b, int op){
    if(a<=s && e<=b){
		if(0 == op){ // 全0
            St[t] = 0;
			Front[0][t] = Back[0][t] = Long[0][t] = e - s + 1;
			Front[1][t] = Back[1][t] = Long[1][t] = 0;
			Lazy[t] = ZER;
		}else if(1 == op){
			St[t] = e - s + 1;
			Front[0][t] = Back[0][t] = Long[0][t] = 0;
			Front[1][t] = Back[1][t] = Long[1][t] = e - s + 1;
			Lazy[t] = ONE;
		}else if(2 == op){ // 取反
            St[t] = e - s + 1 - St[t];
			swap(Front[0][t], Front[1][t]);
			swap(Back[0][t], Back[1][t]);
			swap(Long[0][t], Long[1][t]);
			Lazy[t] ^= XOR;
		}else{
			throw runtime_error("XX");
		}
		return;
	}

    _pushDown(t, s, e);
	int mid = (s + e) >> 1;
	if(a<=mid) modify(lson(t), s, mid, a, b, op);
	if(mid<b) modify(rson(t), mid+1, e, a, b, op);
	_pushUp(t, s, e);	
}

int qSum(int t, int s, int e, int a, int b){
	if(a<=s && e<=b){
		return St[t];
	}
	_pushDown(t, s, e);
	int mid = (s + e) >> 1;
	int ans = 0;
	if(a<=mid) ans += qSum(lson(t), s, mid, a, b);
	if(mid<b) ans += qSum(rson(t), mid+1, e, a, b);
	return ans;
}

typedef tuple<int, int, int, int> t4t;
t4t merge(const t4t &a, const t4t &b){
    int za = get<0>(a), zb = get<0>(b);
	if(-1 == za) return b;
	if(-1 == zb) return a;

    int na = get<3>(a), nb = get<3>(b); // 长度
	int la = get<1>(a), lb = get<1>(b); // 左
	int ra = get<2>(a), rb = get<2>(b);
	

	int ll = la == na ? na + lb : la;
	int rr = rb == nb ? nb + ra : rb;
	int nn = na + nb;
	int zz = max(za, zb, ra+lb);

	return {zz, ll, rr, nn};
}

t4t query(int t, int s, int e, int a, int b){
	if(a<=s && e<=b){
		return {Long[1][t], Front[1][t], Back[1][t], e-s+1};
	}

    _pushDown(t, s, e);
    int mid = (s + e) >> 1;
    t4t lans = {-1, -1, -1, -1}, rans = {-1, -1, -1, -1};
	if(a <= mid) lans = query(lson(t), s, mid, a, b);
	if(mid < b) rans = query(rson(t), mid+1, e, a, b);
	return merge(lans, rans);
}

void build(int t, int s, int e){
	if(s == e){
		int x = getInt();
		Front[x][t] = Back[x][t] = Long[x][t] = 1;
		Front[x^1][t] = Back[x^1][t] = Long[x^1][t] = 0;
		St[t] = x;
		return;
	}

	int mid = (s + e) >> 1;
	build(lson(t), s, mid);
	build(rson(t), mid+1, e);
	_pushUp(t, s, e);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    N = getInt(); M = getInt();
	build(1, 1, N);
	for(int cmd,a,b,q=1;q<=M;++q){
        cmd = getInt(); a = getInt(); b = getInt();
		++a; ++b;
		if(cmd<=2){
			modify(1, 1, N, a, b, cmd);
		}else if(3 == cmd){
            printf("%d\n", qSum(1, 1, N, a, b));
		}else if(4 == cmd){
            printf("%d\n", get<0>(query(1, 1, N, a, b)));
		}else{
			throw runtime_error("XX");
		}
	}
	return 0;
}
