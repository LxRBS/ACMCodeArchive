#include <bits/stdc++.h>

using namespace std;

#define N 1000005

int a[N], b[N], c[N], d[N], n, k;

long long ans;

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int i = 1; i <= n; ++i) scanf("%d", &b[i]);
	if (n == 2)
	{
		if (k & 1) swap(a[1], a[2]);
		ans += abs(a[1] - b[1]);
		ans += abs(a[2] - b[2]);
	}
	else
	{
		for (int i = 1; i <= n; ++i) c[i] = max(a[i], b[i]), d[i] = min(a[i], b[i]), ans += abs(a[i] - b[i]);
		sort(c + 1, c + n + 1); sort(d + 1, d + n + 1);
		for (int i = 1; i <= min(n, k); ++i) ans += max(0ll, 2ll * d[n - i + 1] - 2ll * c[i]);
	}
	printf("%lld\n" ,ans);
}
