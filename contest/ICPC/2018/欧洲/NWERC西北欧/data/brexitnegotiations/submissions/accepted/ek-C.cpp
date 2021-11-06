#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <set>
#include <vector>
#define MAXN 2000005

using namespace std;

int main() {
	int N;
	scanf("%d",&N);

	static vector< vector<int> > g;
	int i;
	for (i = 0; i < N; i++) {
		vector<int> s;
		g.push_back(s);
	}

	static int l[MAXN];

	static int o[MAXN];
	memset(o, 0, sizeof(o));

	for (i = 0; i < N; i++) {
		scanf("%d",&l[i]);
		int d;
		scanf("%d",&d);
		for (int dd = 0; dd < d; dd++) {
			int z;
			scanf("%d",&z);
			z--;
			o[z]++;
			g[i].push_back(z);
		}
	}

	int res = 0;
	int sz = N-1;

	static set< pair< pair<int, int>, int > > a;
	for (i = 0; i < N; i++) {
		a.insert(make_pair(make_pair(o[i], l[i]), i));
	}

	while (!a.empty()) {
		pair< pair<int, int>, int > cur = *(a.begin());
		a.erase(cur);
		for (vector<int>::iterator it = g[cur.second].begin(); it < g[cur.second].end(); it++) {
			int edge = *it;
			a.erase(make_pair(make_pair(o[edge], l[edge]), edge));
			o[edge]--;
			a.insert(make_pair(make_pair(o[edge], l[edge]), edge));
		}
		res = max(res, sz + cur.first.second);
		sz--;
	}

	printf("%d\n",res);
	
	return 0;
}
