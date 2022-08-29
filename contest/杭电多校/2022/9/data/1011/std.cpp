#include<bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int sid = 2000500;

#define rep(io, st, ed) for(int io = st; io <= ed; io ++)
#define drep(io, ed, st) for(int io = ed; io >= st; io --)

inline void inc(int &a, int b) { a += b; if(a >= mod) a -= mod; }
inline void dec(int &a, int b) { a -= b; if(a < 0) a += mod; }
inline int Inc(int a, int b) { return (a + b >= mod) ? a + b - mod : a + b; }
inline int Dec(int a, int b) { return (a - b < 0) ? a - b + mod : a - b; }
inline int mul(int a, int b) { return 1ll * a * b % mod; }
inline int fp(int a, int k) {
	int ret = 1;
	while(k) {
		if(k & 1) ret = mul(ret, a);
		a = mul(a, a); k >>= 1;
	}
	return ret;
}

int fac[sid], inv[sid], pw[sid];
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int N, rev[sid], G[sid], f[sid], g[sid], h[sid];
void pre(int M) {
	int lg = 0;
	for(N = 1; N <= M; N <<= 1) lg ++;
	for(int i = 0; i < N; i ++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (lg - 1));
	G[0] = 1; int g = fp(3, (mod - 1) / N);
	for(int i = 1; i < N; i ++) G[i] = mul(G[i - 1], g);
}

void NTT(int *y, int dft) {
	for(int i = 0; i < N; i ++) if(i < rev[i]) swap(y[i], y[rev[i]]);
	for(int i = 1; i < N; i <<= 1) {
		for(int j = 0, kj = N / (i << 1); j < N; j += (i << 1))
		for(int k = 0, kp = 0; k < i; k ++, kp += kj) {
			int y0 = y[j + k], y1 = mul(G[kp], y[j + k + i]);
			y[j + k] = Inc(y0, y1); y[j + k + i] = Dec(y0, y1);
		}
	}
	if(dft == -1) {
		reverse(y + 1, y + N);
		int iv = fp(N, mod - 2);
		for(int i = 0; i < N; i ++) y[i] = mul(y[i], iv);
	}
}


inline int up2(int x) { return x ? ((x - 1) >> 1) + 1 : 0; }
int C(int n, int m) {
	if(n < 0 || m < 0 || n < m) return 0;
	assert(n >= 0); assert(m >= 0); assert(n >= m);
	return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;
}
void solve() {
	int p, c, n, o = 1;
	scanf("%d%d%d", &p, &c, &n);
	assert(c >= 1);
	int cg = c; while(cg != 1) cg = 1ll * cg * c % p, o ++;
	int k = (p - 1) / o, l = o;
	//if(p >= 400000) cerr << "order of " << c << " is " << o << endl;
	// solve f
	int l2 = up2(l);
	rep(i, 0, l2) f[i] = 1ll * pw[i] * Inc(C(l - i, i), C(l - i - 1, i - 1)) % mod;
	if(l & 1) inc(f[up2(l)], 1);
	else dec(f[up2(l)], 1);
	// solve ans
	rep(i, 0, N) g[i] = 0;
	rep(i, 0, l2) g[i] = f[i];
	pre(p + 5); 
	NTT(g, 1); rep(i, 0, N) g[i] = fp(g[i], k); NTT(g, - 1);
	int ans = 0;
	rep(i, 0, min(p, n)) {
		//printf("%d ", g[i]);
		inc(ans, g[i]);
		if(i) inc(ans, g[i - 1]);
	}
	if(n == 1) dec(ans, 1);
	printf("%d\n", ans);
}

int main() {
	fac[0] = inv[0] = pw[0] = 1;
	rep(i, 1, 500000) fac[i] = mul(fac[i - 1], i), inv[i] = fp(fac[i], mod - 2), pw[i] = mul(pw[i - 1], 2);
	int T;
	scanf("%d", &T);
	while(T --) solve();
	return 0;
}