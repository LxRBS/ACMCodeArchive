#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	vector<int> a(n);
	for (int &x: a) cin >> x;
	sort(begin(a),end(a));
	
	double res = 1;
	for (int i = 0; i < n; i++) {
		if (a[i] > i+1) {
			cout << "impossible" << endl;
			return 0;
		}
		res = min(res,a[i]/(i+1.0));
	}
	cout << fixed << setprecision(20) << res << endl;
}
