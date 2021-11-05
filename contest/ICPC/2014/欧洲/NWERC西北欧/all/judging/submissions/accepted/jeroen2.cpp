/*
 * NWERC'14 - Solution by Jeroen Bransen
 */

#include <iostream>
#include <set>
#include <string>

using namespace std;

int main() {
	int N;
	cin >> N;
	
	multiset<string> dj;
	for(int i = 0; i < N; i++) {
		string s;
		cin >> s;
		dj.insert(s);
	}
	
	int ans = 0;
	for(int i = 0; i < N; i++) {
		string s;
		cin >> s;
		multiset<string>::iterator pos = dj.find(s);
		if(pos != dj.end()) {
			ans++;
			dj.erase(pos);
		}
	}
	
	cout << ans << endl;
	
	return 0;
}
