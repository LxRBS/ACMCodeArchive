#include <algorithm>
#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

const int mod = 110119;

long long fac[mod];
long long inv[mod];
long long facinv[mod];

void init()
{
	fac[0] = fac[1] = inv[1] = facinv[0] = facinv[1] = 1;
	for(int i = 2; i < mod; ++i) {
		fac[i] = fac[i - 1] * i % mod;
		inv[i] = inv[mod % i] * (mod - mod / i) % mod;
		facinv[i] = facinv[i - 1] * inv[i] % mod;
	}
}

long long C(long long n, long long m)
{
	if(n < 0 || m < 0 || m > n)
		return 0;
	return fac[n] * facinv[m] % mod * facinv[n - m] % mod;
}

long long Lucas(long long n, long long m)
{
	if(n < 0 || m < 0 || m > n)
		return 0;
	long long res = 1;
	while(n || m) {
		res = res * C(n % mod, m % mod) % mod;
		n /= mod;
		m /= mod;
	}
	return res;
}

long long Solve(long long n, long long m) { return Lucas(n + m, n); }

int main()
{
	init();
	long long n, m;
	int r;
	int kase = 0;
	while(scanf("%lld %lld %d", &n, &m, &r) == 3) {
		vector<pair<long long, long long>> v;
		while(r--) {
			long long x, y;
			scanf("%lld %lld", &x, &y);
			v.emplace_back(x, y);
		}
		v.emplace_back(1, 1);
		v.emplace_back(n, m);
		sort(v.begin(), v.end());
		vector<long long> dp(v.size(), 0);
		dp[0] = mod - 1;
		for(int i = 1; i < v.size(); ++i)
			for(int j = 0; j < i; ++j) {
				if(v[i].first < v[j].first || v[i].second < v[j].second ||
				        (v[i].first + v[i].second - v[j].first - v[j].second) % 3)
					continue;
				long long step =
				    (v[i].first + v[i].second - v[j].first - v[j].second) / 3;
				dp[i] = (dp[i] + mod -
				         dp[j] * Solve(v[i].first - v[j].first - step,
				                       v[i].second - v[j].second - step) %
				         mod) %
				        mod;
			}
		printf("Case #%d: %d\n", ++kase, (int)dp.back());
	}
	return 0;
}
