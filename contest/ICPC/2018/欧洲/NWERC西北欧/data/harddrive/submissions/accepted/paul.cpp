#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, e, b;
	cin >> n >> e >> b;
	
	vector<bool> zero(n);
	while (b--) {
		int i; cin >> i;
		zero[i-1] = true;
	}
	
	string res(n,'0');
	int i = 1 + e%2;
	
	if (e%2) res[0] = '1';
	e /= 2;
	
	while (e--) {
		while (zero[i]) i++;
		res[i] = '1';
		i += 2;
	}
	cout << res << endl;
}
