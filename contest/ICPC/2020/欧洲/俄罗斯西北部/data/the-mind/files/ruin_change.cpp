#include "testlib.h"
#include <unordered_set>
using namespace std;

int const MAXC = 1000000000;

int main(int argc, char **argv) {
	registerGen(argc, argv, 1);
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	vector<int> a(n);
	unordered_set<int> q;
	for (int &i : a) {
		cin >> i;
		q.insert(i);
	}
	int count = atoi(argv[1]);
	int maxc = atoi(argv[2]);
	for (int i = 0; i < count; i++) {
		while (true) {
			int pos = rnd.next(0, n - 1);
			int value = rnd.next(1, maxc);
			q.erase(a[pos]);
			int old = a[pos];
			a[pos] = value;
			if (q.find(a[pos]) != q.end() || a[pos] <= 0 || a[pos] > MAXC) {
				a[pos] = old;
				q.insert(a[pos]);
				continue;
			}
			q.insert(a[pos]);
			break;
		}
	}
	cout << n << '\n';
	for (int i = 0; i < n; i++) {
		if (i > 0) cout << ' ';
		cout << a[i];
	}
	cout << '\n';
}
