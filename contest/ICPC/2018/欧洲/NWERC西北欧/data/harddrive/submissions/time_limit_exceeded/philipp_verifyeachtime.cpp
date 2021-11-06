#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.sync_with_stdio(0);

	int n, c, b;
	cin >> n >> c >> b;

	vector<bool> isbroken(n, false);
	while(b--) {
		int idx;
		cin >> idx;
		idx--;
		isbroken[idx] = true;
	}

	string res(n, '0');
	int ne = 1;
	if(c % 2 == 1) {
		res[0] = '1';
		ne = 2;
	}

	while(true) {
		int changes = 0;
		for(int i = 1; i < n; i++) {
			if(res[i] != res[i-1]) {
				changes++;
			}
		}
		if(changes == c) {
			cout << res << endl;
			return 0;
		}
		while(isbroken[ne]) {
			ne++;
		}
		res[ne] = '1';
		ne += 2;
	}
}
