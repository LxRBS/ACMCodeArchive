#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int &i : a) {
		cin >> i;
	}
	sort(a.begin(), a.end());
	int maxDiff = a[0];
	for (int i = 0; i + 1 < n; i++) {
		maxDiff = max(maxDiff, a[i + 1] - a[i]);
	}
	for (int i = 1; i < n; i++) {
		int prev = i - 2 < 0 ? 0 : a[i - 2];
		if (prev + maxDiff >= a[i]) {
			cout << "0\n";
			return 0;
		}
	}
	cout << maxDiff << "\n";
}
