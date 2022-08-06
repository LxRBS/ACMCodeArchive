#include <bits/stdc++.h>

using namespace std;

using fuck = long long;

#define int __int128

constexpr int maxn = 5005;
constexpr int p = 862118861, q[] = {857, 997, 1009}, m[] = {1005973, 864713, 854429}, m_inv[] = {461, 435, 26};

int qpow(int a, int b, int c) {
	int ans = 1;
	
	while (b) {
		if (b & 1)
			ans = (__int128)ans * a % c;
		
		a = (__int128)a * a % c;
		b >>= 1;
	}

	return ans;
}

int crt(int a, int b, int c) {
	return ((__int128)a * (m[0] * m_inv[0]) + (__int128)b * (m[1] * m_inv[1]) + (__int128)c * (m[2] * m_inv[2])) % p;
}

struct LinearRecurrence {
	vector<int> first, trans;
	int mod;
	vector<vector<int> > bin;

	vector<int> multi(const vector<int> &a, const vector<int> &b) {
		int n = (int)a.size() - 1;

		vector<int> c(n * 2 + 1);

		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= n; j++)
				c[i + j] = (c[i + j] + a[i] * b[j]) % mod;
		
		for (int i = n * 2; i > n; i--) {
			for (int j = 0; j < n; j++)
				c[i - 1 - j] = (c[i - 1 - j] + c[i] * trans[j]) % mod;
			
			c[i] = 0;
		}

		c.resize(n + 1);
		return c;
	}

	LinearRecurrence(vector<int> &first, vector<int> &trans, int mod) :
			first(first), trans(trans), mod(mod) {
		int n = (int)first.size();

		vector<int> a(n + 1);
		a[1] = 1;
		bin.push_back(a);

		for (int i = 1; i < 64; i++)
			bin.push_back(multi(bin[i - 1], bin[i - 1]));
	}

	int calc(__int128 k) {
		int n = (int)first.size();

		vector<int> a(n + 1);
		a[0] = 1;

		for (int i = 0; i < 64; i++)
			if (k >> i & 1)
				a = multi(a, bin[i]);
		
		int ans = 0;
		for (int i = 0; i < n; i++)
			ans = (ans + a[i + 1] * first[i]) % mod;
		
		return ans;
	}
};

int st[maxn], bell[maxn];

void prework(int n) {
	st[1] = bell[1] = 1;

	for (int i = 2; i <= n; i++)
		for (int j = i; j; j--) {
			st[j] = (st[j - 1] + (__int128)st[j] * j) % p;
			bell[i] = (bell[i] + st[j]) % p;
		}
}

int calc_bell(__int128 n) {
	int ans[3];

	for (int k = 0; k < 3; k++) {
		int mod = q[k];
		vector<int> first(mod), trans(mod);

		for (int i = 1; i <= mod; i++)
			first[i - 1] = bell[i] % mod;
		
		trans[mod - 1] = trans[mod - 2] = 1;

		LinearRecurrence line_rec(first, trans, mod);

		ans[k] = line_rec.calc(n);
	}

	return crt(ans[0], ans[1], ans[2]);
}

int fac[3][maxn * 2], fac_inv[3][maxn * 2];

int choose(__int128 n, __int128 k, int i) {
	if (n < k)
		return 0;
	
	if (n >= q[i] || k >= q[i])
		return choose(n % q[i], k % q[i], i) * choose(n / q[i], k / q[i], i) % q[i];
	
	return (__int128)fac[i][n] * fac_inv[i][k] % q[i] * fac_inv[i][n - k] % q[i];
}

int C(__int128 n, __int128 k) {
	if (n < k)
		return 0;
	
	int tmp = crt(choose(n, k, 0), choose(n, k, 1), choose(n, k, 2));
	// printf("C(%lld, %d) = %d\n", n, k, tmp);
	return tmp;
}

int f[maxn][maxn];

signed main() {
	
	prework(1010);

	// __int128 n, k;
	// scanf("%lld%lld", &n, &k);

	fuck n, k;
	cin >> n >> k;

	int ans = calc_bell(k);

	if (k > n) {
		int m = k - n;

		f[0][0] = 1;
		for (int i = 1; i <= m; i++)
			for (int j = 0; j <= i; j++) {
				f[i][j] = (__int128)f[i - 1][j] * (j + 1) % p;

				if (j)
					f[i][j] = (f[i][j] + (__int128)(2 * i - j - 1) * f[i - 1][j - 1]) % p;
			}
		
		for (int t = 0; t < 3; t++) {
			int *a = fac[t], *b = fac_inv[t];

			a[0] = b[0] = 1;
			for (int i = 1; i < q[t]; i++) {
				a[i] = (__int128)a[i - 1] * i % q[t];
				// printf("fac[%d] = %d\n", i, a[i]);
			}
			
			b[q[t] - 1] = qpow(a[q[t] - 1], q[t] - 2, q[t]);
			for (int i = q[t] - 2; i; i--) {
				b[i] = (__int128)b[i + 1] * (i + 1) % q[t];
				assert(a[i] * b[i] % q[t] == 1);
			}
		}

		int tmp = 0;
		for (int i = 0; i < m; i++) {
			int res = 0;
			for (int j = 0; j <= i; j++)
				res = (res + (__int128)f[i][j] * C(k + i - j - 1, 2 * i)) % p;
			
			tmp = (tmp + res) % p;
		}

		ans = (ans - tmp + p) % p;
	}

	printf("%lld\n", (fuck)ans);

	return 0;
}
/*
1000000000000000000
1000000000000005000
*/