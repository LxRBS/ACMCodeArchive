#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class TIn, class TOut = null_type>
using order_tree = tree<TIn, TOut, less<TIn>, rb_tree_tag,
	tree_order_statistics_node_update>;

constexpr int INF = 2000000010;
constexpr ll LLINF = 9000000000000000010LL;

struct pt { int x, y; };

bool hor(char c) { return c == 'L' || c == 'R'; }
bool ver(char c) { return c == 'U' || c == 'D'; }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	string s;
	cin >> s;

	if (s.length() > 2) {
		if (hor(s.end()[-3]) && hor(s.end()[-2]) && hor(s.end()[-1])) {
			cout << "impossible" << endl;
			return 0;
		}
		if (ver(s.end()[-3]) && ver(s.end()[-2]) && ver(s.end()[-1])) {
			cout << "impossible" << endl;
			return 0;
		}	
	}

	vector<pt> blocks;
	pt b{0, 0};
	int M = 0;
	for (size_t i = 0; i < s.length(); ++i) {
		if (i + 1 < s.length() &&
				((hor(s[i+1]) && hor(s[i]))
					|| (ver(s[i+1]) && ver(s[i]))))
			continue;
		if (hor(s[i])) {
			blocks.push_back(pt{-M-2, b.y});
			blocks.push_back(pt{+M+2, b.y});
			if (s[i] == 'L') b.x = -M-1;
			if (s[i] == 'R') b.x = +M+1;
		} else {
			blocks.push_back(pt{b.x, -M-2});
			blocks.push_back(pt{b.x, +M+2});
			if (s[i] == 'D') b.y = -M-1;
			if (s[i] == 'U') b.y = +M+1;
		}
		M += 2;
	}

	cout << -b.x << ' ' << -b.y << endl;
	cout << blocks.size() << endl;
	for (size_t i = 0; i < blocks.size(); ++i)
		cout << blocks[i].x-b.x << ' ' << blocks[i].y-b.y << endl;
	
	
	return 0;
}
