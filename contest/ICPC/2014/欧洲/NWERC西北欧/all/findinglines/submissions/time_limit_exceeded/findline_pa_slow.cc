/* Sample solution to findline from NWERC'14.
 *
 * Bad Algorithm: standard O(n^2) algorithm for finding largest
 * #colinear points, somewhat optimized
 *
 * Author: Per Austrin
 */
#include <cstdio>
#include <cstdlib>
#include <unordered_map>
#include <algorithm>
using namespace std;
typedef long long ll;

struct point {
	int x, y;
	point(int x=0, int y=0): x(x), y(y) {}
};

typedef pair<int, int> pii;
int n, p;
point P[1<<20];

bool check() {
	int target = (p*n-1)/100, maxseen = 0;
	random_shuffle(P, P+n);
	for (int b = 0; b < n; ++b) {
		unordered_map<ll,int> cnt;
		for (int i = b+1; i < n && maxseen + n - i >= target; ++i) {
			int dx = P[i].x-P[b].x, dy = P[i].y-P[b].y;
			int d = __gcd(dx, dy);
			dx /= d; dy /= d;
			if (dx < 0 || dx == 0 && dy < 0) dx = -dx, dy = -dy;
			int val = ++cnt[((ll)dx<<30)|dy];
			if (val >= target) return true;
			if (val > maxseen) maxseen = val;
			// Heuristic: if at the rate things are currently going we
			// seem to be ending up with less than half the needed
			// points, give up
			if (n > 1000 && 2*maxseen*(n-b-1) < target*(i+1-b)) break;
		}
	}
	return false;
}

int main(void) {
	scanf("%d%d", &n, &p);
	for (int i = 0; i < n; ++i) scanf("%d%d", &P[i].x, &P[i].y);
	printf("%spossible\n", check() ? "" : "im");
	return 0;
}
