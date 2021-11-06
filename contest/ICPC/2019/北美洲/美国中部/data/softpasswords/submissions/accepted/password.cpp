#include <bits/stdc++.h>
using namespace std;
int main() {
	string s, p;
	cin >> s;
	cin >> p;
	if (s == p) {
		cout << "Yes" << endl;
		return 0;
	}
	for (char ch = '0'; ch <= '9'; ++ ch) {
		string c; c += ch;
		if (c + p == s || p + c == s) {
			cout << "Yes" << endl;
			return 0;
		}
	}
	for (char &c : p) {
		if (c >= 'a' && c <= 'z') {
			c = c - 'a' + 'A';
		}
		else if (c >= 'A' && c <= 'Z') {
			c = c - 'A' + 'a';
		}
	}
	if (p == s) {
		cout << "Yes" << endl;
		return 0;
	}
	cout << "No" << endl;
}

