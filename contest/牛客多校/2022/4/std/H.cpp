#pragma comment(linker, "/STACK:1024000000,1024000000")
/*
    Author: elfness@UESTC
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>

using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
#define PB push_back
#define fi first
#define se second
#define MP make_pair
const int oo = 1000000000;
const int P = 1000000007;
const int V = 110;
int cur[1100];

vector<PII> ans[V];
bool check(int n, int h, int w) {
	for (int i = 0; i < h; ++i) cur[i] = 0;
	for (int i = n; i > 0; --i) {
		ans[i].clear();
		int cnt = n - i + 1;
		for (int j = 0; j < cnt; ++j) {
			bool fd = false;
			for (int k = 0; k < h; ++k) {
				if (cur[k] + i <= w) {
					ans[i].PB({k, cur[k]});
					cur[k] += i;
					fd = true;
					break;
				}
			}
			if (!fd) return false;
		}
	}
	printf("%d\n",h+h+w+w);
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < n - i + 1; ++j) {
			printf("%d %d %d %d\n", ans[i][j].se, ans[i][j].fi, ans[i][j].se + i, ans[i][j].fi + 1);
		}
	}
	return true;
}

int _, ca, n;
int main() {
	scanf("%d", &_);
	for (int ca = 1; ca <= _; ++ca) {
		scanf("%d", &n);
		int s = 0;
		for (int i = 1; i <= n; ++i) s += (n - i + 1) * i;
		vector<int> fac;
		for (int i = 1; i * i <= s; ++i) {
			if (s % i != 0) continue;
			fac.PB(i);
		}
// 		printf("Case #%d:\n", ca);
		for (int i = fac.size() - 1; i >= 0; --i) {
			if (check(n, fac[i], s / fac[i])) break;
		}
	}
    return 0;
}

/*
4
1
2
3
4
*/
