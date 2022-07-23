#include<bits/stdc++.h>

using ll = long long;
using ld = long double;

namespace GTI
{
	char gc(void)
   	{
		const int S = 1 << 16;
		static char buf[S], *s = buf, *t = buf;
		if (s == t) t = buf + fread(s = buf, 1, S, stdin);
		if (s == t) return EOF;
		return *s++;
	}
	ll gti(void)
   	{
		ll a = 0, b = 1, c = gc();
		for (; !isdigit(c); c = gc()) b ^= (c == '-');
		for (; isdigit(c); c = gc()) a = a * 10 + c - '0';
		return b ? a : -a;
	}
	int gts(char *s)
   	{
		int len = 0, c = gc();
		for (; isspace(c); c = gc());
		for (; c != EOF && !isspace(c); c = gc()) s[len++] = c;
		s[len] = 0;
		return len;
	}
	int gtl(char *s)
   	{
		int len = 0, c = gc();
		for (; isspace(c); c = gc());
		for (; c != EOF && c != '\n'; c = gc()) s[len++] = c;
		s[len] = 0;
		return len;
	}
}
using GTI::gti;
using GTI::gts;
using GTI::gtl;

const int N = 1 << 20 | 1, M = 998244353, G = 3;
int qpw(int a, int b)
{
	a %= M;
	if (a == 0) return (b == 0);
	b %= M - 1;
	if (b < 0) b += M - 1;
	int c = 1;
	for (; b; b >>= 1, a = 1ll * a * a % M)
		if (b & 1)
			c = 1ll * c * a % M;
	return c;
}
int mod(int val)
{
	return (val < 0) ? (val + M) : ((val >= M) ? (val - M) : val);
}

namespace Poly
{
	std::vector<int> g[2][20];
	int getgl(int len, int tag)
	{
		return qpw(G, (M - 1) / len * tag);
	}
	void precalc(void)
	{
		for (int l = 1, x = 0; l < (1 << 20); l <<= 1, ++x)
		{
			int gl[2] = {getgl(l << 1, 1), getgl(l << 1, -1)}, gx[2] = {1, 1};
			g[0][x].resize(l), g[1][x].resize(l);
			for (int i = 0; i < l; i++)
				for (int t = 0; t < 2; t++)
				{
					g[t][x][i] = gx[t];
					gx[t] = 1ll * gx[t] * gl[t] % M;
				}
		}
	}
	int id[N];
	int init(int n)
	{
		int k = 0, len = 1;
		while (len < n) len <<= 1, ++k;
		for (int i = 0; i < len; i++)
			id[i] = id[i >> 1] >> 1 | ((i & 1) << (k - 1));
		return len;
	}
	void ireverse(int *a, int len)
	{
		for (int i = 0; i < len; i++)
			if (id[i] > i)
				std::swap(a[id[i]], a[i]);
	}
	void ntt(int *a, int len, int tag = 1)
	{
		tag = (tag < 0) ? 1 : 0;
		ireverse(a, len);
		for (int l = 1, x = 0; l < len; l <<= 1, ++x)
			for (int st = 0; st < len; st += (l << 1))
				for (int i = st; i < st + l; i++)
				{
					int tmp = 1ll * a[i + l] * g[tag][x][i - st] % M;
					a[i + l] = mod(a[i] - tmp);
					a[i] = mod(a[i] + tmp);
				}
		if (tag)
		{
			int rev = qpw(len, -1);
			for (int i = 0; i < len; i++)
				a[i] = mod(1ll * a[i] * rev % M);
		}
	}
}

int fct[N], ifc[N];
void init(int n)
{
	fct[0] = 1;
	for (int i = 1; i <= n; i++)
		fct[i] = 1ll * fct[i - 1] * i % M;
	ifc[n] = qpw(fct[n], -1);
	for (int i = n - 1; i >= 0; i--)
		ifc[i] = ifc[i + 1] * (i + 1ll) % M;
}
int C(int n, int m)
{
	if (m < 0 || n - m < 0) return 0;
	return 1ll * fct[n] * ifc[m] % M * ifc[n - m] % M;
}

int f[N], g[N];
int main(void)
{
	int n = gti(), m = n / 3;
	init(n), Poly::precalc();
	for (int i = 0; i <= m; i++)
		f[i] = 1ll * C(n - i * 2, i) * qpw(26, n - i * 3) % M;
	for (int i = 0, sgn = 1; i <= m; i++, sgn = -sgn)
	{
		f[i] = 1ll * f[i] * fct[i] % M;
		g[m - i] = sgn * ifc[i];
	}

	int len = Poly::init(m * 2 + 1);
	Poly::ntt(f, len), Poly::ntt(g, len);
	for (int i = 0; i < len; i++)
		f[i] = 1ll * f[i] * g[i] % M;
	Poly::ntt(f, len, -1);

	for (int i = 0; i <= m; i++)
		f[i + m] = 1ll * f[i + m] * ifc[i] % M;
	for (int i = 0; i <= m; i++)
		printf("%d%c", f[m + i], " \n"[i == n]);
	for (int i = m + 1; i <= n; i++)
	    printf("%d%c", 0, " \n"[i == n]);
	return 0;
}
