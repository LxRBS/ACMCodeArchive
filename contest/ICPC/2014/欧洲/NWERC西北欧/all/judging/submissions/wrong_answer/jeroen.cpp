#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	int N;
	cin >> N;

	vector<string> dj, kattis;
	for(int i = 0; i < N; i++) {
		string s;
		cin >> s;
		dj.push_back(s);
	}
	for(int i = 0; i < N; i++) {
		string s;
		cin >> s;
		kattis.push_back(s);
	}

	sort(dj.begin(), dj.end());
	sort(kattis.begin(), kattis.end());
	
	int ans = 0;
	for(int i = 0; i < N; i++)
		if(dj[i] == kattis[i])
			ans++;
	cout << ans << endl;
	
	return 0;
}
