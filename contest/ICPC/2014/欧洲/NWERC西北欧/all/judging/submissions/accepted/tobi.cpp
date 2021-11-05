#include <iostream>
#include <map>
#include <string>

using namespace std;
int N, C;
string s;
map<string,int> m;

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> s;
		m[s]++;
	}
	for (int i = 0; i < N; i++) {
		cin >> s;
		if (m[s] > 0) {
			m[s]--;
			C++;
		}
	}
	cout << C << endl;
	return 0;
}
