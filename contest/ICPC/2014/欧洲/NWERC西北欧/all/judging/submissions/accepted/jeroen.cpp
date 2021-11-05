/*
 * NWERC'14 - Solution by Jeroen Bransen
 */

#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
	int N;
	cin >> N;
	
	// Count number of times each result
	// appears for DomJudge
	map<string,int> cnt;
	for(int i = 0; i < N; i++) {
		string s;
		cin >> s;
		cnt[s]++;
	}
	
	// For each of Kattis' results, see
	// if we can match with one of the
	// results of DomJudge
	int ans = 0;
	for(int i = 0; i < N; i++) {
		string s;
		cin >> s;
		if(cnt[s] > 0) {
			cnt[s]--;
			ans++;
		}
	}
	
	cout << ans << endl;
	
	return 0;
}
