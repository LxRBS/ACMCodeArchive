#include <bits/stdc++.h>

#define N 5005
#define Mo 998244353

using namespace std;

int p[N], n, f[N][N], g[N][N], Count[N][N], inv[N];

int power(int x, int y)
{
	int s = 1;
	for ( ; y; y >>= 1)
	{
		if (y & 1) s = 1ll * s * x % Mo;
		x = 1ll * x * x % Mo;
	}
	return s;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &p[i]);
	for (int i = n; i >= 1; --i)
	{
		for (int j = 1; j <= n; ++j) Count[i][j] = Count[i + 1][j];
		for (int j = 1; j <= p[i]; ++j) Count[i][j]++;
	}
	for (int i = 1; i <= n; ++i) inv[i] = power(i, Mo - 2);
	for (int i = 1; i <= n; ++i) g[i][1] = 1ll * inv[n] * inv[Count[1][p[i] + 1]] % Mo;
	int ans = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
		{
			if (p[j] > p[i]) (ans += g[i][j]) %= Mo, (f[i][j] += 1ll * g[i][j] * inv[Count[i][p[j] + 1]] % Mo) %= Mo;
			if (p[i] > p[j]) (ans += f[i][j]) %= Mo, (g[i][j] += 1ll * f[i][j] * inv[Count[j][p[i] + 1]] % Mo) %= Mo;
			(g[i][j + 1] += g[i][j]) %= Mo; 
			(f[i + 1][j] += f[i][j]) %= Mo;
		}
	printf("%d\n", ans);
}
