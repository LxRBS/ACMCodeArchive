#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m; cin >> n >> m;
	string suf, enc; cin >> suf >> enc;
	
	string dec(m-n,' ');
	dec += suf;
	for (int i = m-n-1; i >= 0; i--) {
		dec[i] = 'a' + (enc[i+n]-dec[i+n]+26)%26;
	}
	cout << dec << endl;
}
