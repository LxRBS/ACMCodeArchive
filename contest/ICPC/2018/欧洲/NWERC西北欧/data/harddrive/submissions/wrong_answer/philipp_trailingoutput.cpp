#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i < (b); i++)

int main() {
	cin.sync_with_stdio(0);

	int n, e, b;
	cin >> n >> e >> b;

	string res(n, '0');
	if(e % 2) {
		res[0] = '1';
		e--;
	}
	set<int> dont;
	dont.insert(0);
	queue<int> qu;
	FOR(i,0,b) {
		int x;
		cin >> x;
		x--;
		dont.insert(x);
		qu.push(x-1);
	}

	while(e) {
		int idx = qu.front(); qu.pop();
		if(dont.count(idx) || res[idx-1] == '1') {
			continue;
		}
		if(res[idx+1] == '0') {
			res[idx] = '1';
			e -= 2;
		}
		qu.push(idx-1);
	}

	cout << res << endl;
	cout << '.' << endl;
}
