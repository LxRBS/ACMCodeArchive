#include <iostream>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;

pii pts[100005], dif[100005], cmp;
int npts, pct, possible, cnt;

int gcd(int a, int b) { return (b == 0) ? a : gcd(b, a%b); }

pii d(pii a) {
	pii ret = make_pair(a.first - cmp.first, a.second - cmp.second);
	if (a == cmp) return ret;
	if (ret.first < 0) ret.first *= -1, ret.second *= -1;
	int ggt = gcd(ret.first, ret.second);
	return make_pair(ret.first / ggt, ret.second / ggt);
}

int main() {
	cin >> npts >> pct;
	for (int i = 0; i < npts; i++) cin >> pts[i].first >> pts[i].second;
	for (int i = 0; !possible && i < 50; i++) {
		cmp = pts[rand() % npts];
		for (int j = 0; j < npts; j++) dif[j] = d(pts[j]);
		sort(dif, dif + npts);
		int same = 0;
		while (dif[same] == dif[0]) same++;
		if (same > ceil(npts*pct/100.)) possible = true;
		for (int j = same; !possible && j < npts; j += cnt + 1) {
			cnt = 0;
			for (int k = j + 1; k < npts; k++, cnt++) if (dif[j] != dif[k]) break;
			if (cnt+same+1 >= ceil(npts*pct/100.)) possible = true;
		}
	}
	cout << (possible ? "possible" : "impossible") << endl;
	return 0;
}
