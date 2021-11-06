#include <bits/stdc++.h>
using namespace std;
const long long INF = (long long) 2e5 * (long long) 1e9 + 1;
int main() {
	int n, ans = 0;
	scanf("%d", &n);
	unordered_map<long long, int> sum;
	sum[0] = 1;
	long long cur = 0;
	vector<pair<int, long long>> mul;
	for (int i = 1; i <= n; ++ i) {
		int a;
		scanf("%d", &a);
		cur += a;
		mul.push_back(make_pair(i, 1LL));
		for (auto &x : mul) {
			if (a < (INF + x.second - 1) / x.second && a * x.second <= INF) {
				x.second *= a;
			}
			else {
				x.second = -1;
			}
		}
		while ((int) mul.size() >= 2) {
			if (mul.back().second == mul[(int) mul.size() - 2].second) {
				mul.pop_back();
			}
			else if (mul[(int) mul.size() - 2].second == -1) {
				mul[(int) mul.size() - 2] = mul.back();
				mul.pop_back();
			}
			else {
				break;
			}
		}
		vector<pair<int, long long>> tmp;
		for (auto x : mul) {
			if (x.second != -1) tmp.push_back(x);
		}
		tmp.swap(mul);
		for (int j = (int) mul.size() - 1; j >= 0; -- j) {
			auto &x = mul[j];
			long long need = cur - x.second;
			if (need < 0) break;
			if (sum.count(need)) {
				int tmp = sum[need];
				if (tmp >= x.first && tmp < (j == (int) mul.size() - 1 ? i : mul[j + 1].first)) {
					ans ++;
				}
			}
		}
		/*printf("%d %d\n", i, (int) mul.size());
		for (auto x : mul) printf("<%d %lld> ", x.first, x.second); puts("");*/
		sum[cur] = i + 1;
	}
	printf("%d\n", ans);
}

