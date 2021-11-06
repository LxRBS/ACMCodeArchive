#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, c, b;
	cin >> n >> c >> b;
	set<int> dont;
	for(int i = 0; i < b; i++) {
		int x;
		cin >> x;
		dont.insert(x-1);
	}

	string res(n, '0');
	int idx = 1;
	if(c % 2) {
		res[0] = '1';
		idx++;
	}
	c /= 2;

	for(; idx < n; idx += 2) {
		if(dont.count(idx)) {
			continue;
		}
		res[idx] = '1';
		c--;
		if(!c) {
			break;
		}
	}

	cout << res << endl;
}
