// Only considers elements from cycles in the increasing sequence,

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <set>
#include <vector>
#define MAXN 3000
#define MYINF 1000000000000000000LL

using namespace std;

struct node {
	long long s_i, s_l;
	long long l[MAXN];
};

static char g[MAXN][MAXN];
long long N;

long long DFS(long long point, char b[MAXN]) {
	long long mx = point;
	for (long long i = 0; i <= N; i++) {
		if ((g[point][i]) && (b[i] != 2)) {
			mx = max(mx, DFS(i, b));
		}
	}
	return mx;
}

int main() {
	scanf("%lli",&N);

	vector< pair<long long, vector<long long> > > a;

	memset(g,0,sizeof(g));

	static node data[MAXN];
	long long i, j;
	data[0].s_i = 0; data[0].s_l = 0; g[0][0] = 1;
	for (j = 0; j <= N; j++) data[0].l[j] = 0;
	for (i = 1; i <= N; i++) {
		scanf("%lli %lli",&data[i].s_i,&data[i].s_l);
		g[data[i].s_i][i] = 1;
		for (j = 0; j <= N; j++) {
			scanf("%lli",&data[i].l[j]);
		}
	}

	static char b[MAXN];
	memset(b,0,sizeof(b));

	for (i = 0; i <= N; i++) {
		if (!b[i]) {
			vector<long long> c;
			c.push_back(i);
			int cc = 1;
			b[i] = 1;
			j = data[i].s_i;
			while (!b[j]) {
				c.push_back(j);
				cc++;
				b[j] = 1;
				j = data[j].s_i;
			}
			if (j != i) {
				continue;
			}
			vector<long long> c2;
			long long mx = j;
			c2.push_back(j);
			b[j] = 2;
			long long pos = cc-1;
			while (c[pos] != j) {
				mx = max(mx, c[pos]);
				c2.push_back(c[pos]);
				b[c[pos]] = 2;
				pos--;
			}
			for (vector<long long>::iterator it = c2.begin(); it < c2.end(); it++) {
				mx = max(mx, DFS(*it, b));
			}
			a.push_back(make_pair(mx, c2));
		}
	}

	sort(a.begin(), a.end());

	long long M = a.size();
	static long long dp[MAXN][MAXN];

	long long added = 0LL;
	for (i = 0; i <= N; i++) {
		if (b[i] != 2) {
			added += data[i].s_l;
		}
	}

	for (i = 0; i <= M; i++) {
		for (j = 0; j <= M; j++) {
			dp[i][j] = MYINF;
		}
	}
	dp[0][0] = 0;

	for (i = 0; i < M; i++) {
		for (j = 0; j <= M; j++) {
			if (dp[i][j] != MYINF) {
				// Pick cycle i
				long long curItem = 0;
				if (j) {
					curItem = a[j-1].first;
				}
				long long minCost = MYINF;
				long long sum = 0LL;
				for (vector<long long>::iterator it = a[i].second.begin(); it < a[i].second.end(); it++) {
					sum += data[*it].s_l;
				}
				for (vector<long long>::iterator it = a[i].second.begin(); it < a[i].second.end(); it++) {
					minCost = min(minCost, sum - data[*it].s_l + data[*it].l[curItem]);
				}
				dp[i+1][i+1] = min(dp[i+1][i+1], dp[i][j] + minCost);
				// Don't pick cycle i
				if (i != M-1) {
					long long curItem = N;
					long long minCost = MYINF;
					long long sum = 0LL;
					for (vector<long long>::iterator it = a[i].second.begin(); it < a[i].second.end(); it++) {
						sum += data[*it].s_l;
					}
					for (vector<long long>::iterator it = a[i].second.begin(); it < a[i].second.end(); it++) {
						minCost = min(minCost, sum - data[*it].s_l + data[*it].l[curItem]);
					}
					dp[i+1][j] = min(dp[i+1][j], dp[i][j] + minCost);
				}
			}
		}
	}

	printf("%lli\n",dp[M][M] + added);
	
	return 0;
}
