#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define FOR(i,a,b) for(int i = (a); i < (b); i++)

int main() {
	cin.sync_with_stdio(0);
	srand(42);

	int n, e, b;
	cin >> n >> e >> b;
	vector<int> broken;
	string res(n, '0');

	broken.pb(0);
	if(e % 2) {
		res[0] = '1';
		broken.pb(1);
		e--;
	}

	FOR(i,0,b) {
		int x;
		cin >> x;
		x--;
		if(x != broken.back()) {
			broken.pb(x);
		}
	}

	while(e) {
		int bidx = rand() % broken.size();
		int bit = broken[bidx];
		if(!bit) {
			continue;
		}
		bit--;
		while(e && bit != broken[bidx-1]) {
			res[bit] = '1';
			e -= 2;
			bit -= 2;
			if(bit < 1) {
				break;
			}
		}
	}

	cout << res << endl;
}
