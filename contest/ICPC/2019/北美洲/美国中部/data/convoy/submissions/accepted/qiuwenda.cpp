#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int t[N];
int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; ++ i) scanf("%d", &t[i]);
	sort(t, t + n);
	long long l = 0, r = 1e12, ans = r;
	while (l <= r) {
		long long mid = (l + r) / 2;
		long long cnt = 0;
		for (int i = 0; i < min(n, k) && t[i] <= mid; ++ i) {
			cnt += 1 + (mid / t[i] + 1) / 2 * 4;
			if (cnt >= n) break;
		}
		if (cnt >= n) {
			ans = mid;
			r = mid - 1;
		}
		else {
			l = mid + 1;
		}
	}
	printf("%lld\n", ans);
}

