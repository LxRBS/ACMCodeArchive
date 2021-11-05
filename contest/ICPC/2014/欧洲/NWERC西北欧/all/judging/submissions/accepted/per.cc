/* Sample solution to Judging Troubles from NWERC'14.
 *
 * Algorithm: trivial
 *
 * Author: Per Austrin
 */
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

int main(void) {
	int N;
	cin >> N;
	vector<string> W(N);
	map<string, int> C;
	for (auto w: W) cin >> w, ++C[w];
	for (auto w: W) cin >> w, --C[w];
	for (auto p: C) N -= p.second*(p.second > 0);
	cout << N;
	return 0;
}
