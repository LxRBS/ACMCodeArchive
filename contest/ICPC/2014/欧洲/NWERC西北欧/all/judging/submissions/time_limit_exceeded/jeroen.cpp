#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	int N;
	cin >> N;
	
	vector<string> dj;
	for(int i = 0; i < N; i++) {
		string s;
		cin >> s;
		dj.push_back(s);
	}

	vector<bool> used = vector<bool>(N, false);
	int ans = 0;
	for(int i = 0; i < N; i++) {
		string s;
		cin >> s;
		for(int j = 0; j < N; j++) {
			if(!used[j] && s == dj[j]) {
				used[j] = true;
				ans++;
				break;
			}
		}
	}

	cout << ans << endl;
	
	return 0;
}
