#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <sstream>
#include <complex>
#include <ctime>
#include <cassert>
#include <functional>

using namespace std;

typedef long long ll;
typedef vector<int> VI;
typedef pair<int, int> PII;

#define REP(i,s,t) for(int i=(s);i<(t);i++)
#define FILL(x,v) memset(x,v,sizeof(x))

const int INF = (int)1e9;
#define MAXN 200005

int main() {
	int n, sum = 0, total = 0;
	cin >> n;
	map<int, int> cnt;
	REP(i, 0, n) {
		int v;
		cin >> v;
		cnt[v]++;
		total += v;
	}
	for (auto v : cnt) {
		if (2 * sum == total - v.first * v.second) return cout << v.first << endl, 0;
		sum += v.first * v.second;
		if (cnt.find(v.first + 1) == cnt.end() && 2 * sum == total) return cout << v.first + 1 << endl, 0;
	}
	return 1;
}