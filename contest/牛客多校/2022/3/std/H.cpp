#include <bits/stdc++.h>
 
using namespace std;
typedef long long ll;
const int N = 100010;
int _w;
 
int n, m, k, v[N];
char a[N], b[N];
 
namespace SAM {
	int ch[N*2][26], len[N*2], pa[N*2], idx;
 
	void init() {
		memset(ch, 0, sizeof ch);
		memset(len, 0, sizeof len);
		memset(pa, 0, sizeof pa);
		idx = 1;
		pa[0] = -1;
	}
	int append( int p, int c ) {
		int np = idx++;
		len[np] = len[p] + 1;
		while( p != -1 && !ch[p][c] )
			ch[p][c] = np, p = pa[p];
		if( p == -1 ) pa[np] = 0;
		else {
			int q = ch[p][c];
			if( len[q] == len[p] + 1 ) pa[np] = q;
			else {
				int nq = idx++;
				memcpy(ch[nq], ch[q], sizeof ch[nq]);
				len[nq] = len[p] + 1;
				pa[nq] = pa[q];
				pa[q] = pa[np] = nq;
				while( p != -1 && ch[p][c] == q )
					ch[p][c] = nq, p = pa[p];
			}
		}
		return np;
	}
	void solve() {
		init();
		int last = 0;
		for( int i = 1; i <= n; ++i )
			last = append(last, a[i] - 'a');
	}
}
 
namespace SGT {
	ll mx[N*4], lmx[N*4], rmx[N*4], sum[N*4];
	int ql, qr;
	ll qmx, qlmx, qrmx, qsum;
 
	void _solve( int o, int L, int R ) {
		if( L == R ) {
			mx[o] = lmx[o] = rmx[o] = max(v[L], 0);
			sum[o] = v[L];
		} else {
			int M = (L+R)/2, lc = o<<1, rc = lc|1;
			_solve(lc, L, M);
			_solve(rc, M+1, R);
			sum[o] = sum[lc] + sum[rc];
			lmx[o] = max(lmx[lc], sum[lc] + lmx[rc]);
			rmx[o] = max(rmx[rc], sum[rc] + rmx[lc]);
			mx[o] = max(max(mx[lc], mx[rc]), rmx[lc] + lmx[rc]);
		}
	}
	void solve() {
		_solve(1, 1, m);
	}
 
	void _query( int o, int L, int R ) {
		if( L >= ql && R <= qr ) {
			ll mxo, lmxo, rmxo, sumo;
			ll mxlc, lmxlc, rmxlc, sumlc;
			ll mxrc, lmxrc, rmxrc, sumrc;
			mxlc = qmx;
			lmxlc = qlmx;
			rmxlc = qrmx;
			sumlc = qsum;
			mxrc = mx[o];
			lmxrc = lmx[o];
			rmxrc = rmx[o];
			sumrc = sum[o];
			sumo = sumlc + sumrc;
			lmxo = max(lmxlc, sumlc + lmxrc);
			rmxo = max(rmxrc, sumrc + rmxlc);
			mxo = max(max(mxlc, mxrc), rmxlc + lmxrc);
			qmx = mxo;
			qlmx = lmxo;
			qrmx = rmxo;
			qsum = sumo;
		} else {
			int M = (L+R)/2, lc = o<<1, rc = lc|1;
			if( ql <= M ) _query(lc, L, M);
			if( qr > M ) _query(rc, M+1, R);
		}
	}
	ll query( int l, int r ) {
		ql = l, qr = r;
		qmx = qlmx = qrmx = qsum = 0;
		_query(1, 1, m);
		return qmx;
	}
}
 
void solve() {
	using namespace SAM;
	
	ll ans = 0;
	int u = 0, l = 0;
	for( int i = 1; i <= m; ++i ) {
		int c = b[i] - 'a';
		while( u != 0 && ch[u][c] == 0 )
			u = pa[u], l = len[u];
		if( ch[u][c] ) {
			u = ch[u][c];
			++l;
		}
		if( l ) {
			ans = max(ans, SGT::query(i-l+1, i));
		}
	}
	printf( "%lld\n", ans );
}
 
int main() {
	_w = scanf( "%d%d%d", &n, &m, &k );
	_w = scanf( "%s", a+1 );
	SAM::solve();
	for( int i = 1; i <= m; ++i ) {
		_w = scanf( "%d", v+i );
	}
	SGT::solve();
	while( k-- ) {
		_w = scanf( "%s", b+1 );
		solve();
	}
	return 0;
}