/* Sample solution to findline from NWERC'14.
 *
 * Bad Algorithm: search for line with floor(p*N/100) pts
 *
 * Author: Per Austrin
 */
#include <cstdio>
#include <cstdlib>
using namespace std;
typedef long long ll;

struct point {
	ll x, y;
	point(ll x=0, ll y=0): x(x), y(y) {}
	point operator-(const point &p) const {return point(x-p.x, y-p.y); }
	ll cross(const point &p) const { return x*p.y - y*p.x; }
};

int n, p;
point P[1<<20];

bool check() {
	if (n < 3) return true;
	for (int i = 0; i < 250; ++i) {
		int a = random() % n, b = random() % n, c = 0;
		if (a == b) continue;
		for (int j = 0; j < n; ++j)
			c += !(P[j]-P[a]).cross(P[b]-P[a]);
		if (c >= p*n/100) return true;
	}
	return false;
}

int main(void) {
	scanf("%d%d", &n, &p);
	for (int i = 0; i < n; ++i) scanf("%d%d", &P[i].x, &P[i].y);
	printf("%spossible\n", check() ? "" : "im");
	return 0;
}
