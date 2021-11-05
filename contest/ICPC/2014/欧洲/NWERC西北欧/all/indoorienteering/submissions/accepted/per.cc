/* Sample solution to Exact Orienteering from NWERC'14.
 *
 * Algorithm: guess midpoint, use meet in the middle to reduce to
 * 2-sum
 *
 * Author: Per Austrin
 */
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<long long> vi;
int N;
long long L, d[20][20];

vi genpartial(int s, int M, long long t) {
	vi W, R;
	W.push_back(s);
	for (int i = 0; (1<<i) <= M; ++i)
		if (M & (1<<i))	W.push_back(i);
	W.push_back(t);
	do {
		long long l = 0;
		int p = s;
		for (auto v: W)	{
			l += d[p][v];
			p = v;
			if (l > L) break;
		}
		R.push_back(l);
	} while (next_permutation(W.begin()+1, W.end()-1));
	sort(R.begin(), R.end());
	return R;
}

bool hastour() {
	int all = (1<<(N-1))-1;
	for (int S = 1; S <= all; ++S) {
		int w = 0;
		for (int i = 0; i < N-1; ++i) if (S & (1<<i)) ++w;
		if (w == N/2)
			for (int mid = 0; mid < N-1; ++mid)
				if (S & (1<<mid)) {
					vi A = genpartial(N-1, S^(1<<mid), mid);
					vi B = genpartial(mid, S^all, N-1);
					int a = 0, b = B.size()-1;
					while (a < A.size() && b >= 0) {
						if (A[a]+B[b] == L) return true;
						if (A[a]+B[b] < L) ++a;
						else if (A[a]+B[b] > L) --b;
					}
				}
	}
	return false;
}

int main(void) {
	scanf("%d%lld", &N, &L);
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			scanf("%lld", d[i]+j);
	printf("%s\n", hastour() ? "possible" : "impossible");
	return 0;
}
