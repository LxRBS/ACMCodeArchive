/**
 * 由于是单点更新，因此可以使用权值树状数组进行优化
 * 注意求最值的树状数组与求和的树状数组的区别。
 * 树状数组比线段树快
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

struct bit_t{

static int lowbit(int x){return x & -x;}

int n;
vll c;
void init(int nn){c.assign((n=nn)+1, -MOD);}
llt query(int pos){llt ans=-MOD;for(int i=pos;i;i-=lowbit(i))ans=max(ans, c[i]);return ans;}
void modify(int pos, llt d){for(int i=pos;i<=n;i+=lowbit(i))c[i]=max(c[i], d);}


}B;

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
    int m = S.end() - S.begin();
    B.init(m);
	auto z = lower_bound(S.begin(), S.end(), 0LL) - S.begin() + 1;
	B.modify(z, 0);
	
	D.assign(N + 1, 0);
	for(int i=1;i<=N;++i){
        auto pos = lower_bound(S.begin(), S.end(), W[i]) - S.begin() + 1;
		auto tmp = B.query(pos);
        D[i] = max(D[i - 1], i + tmp);
		B.modify(pos, D[i] - i);
	}

	cout << D[N] << endl;
	return 0; 
}