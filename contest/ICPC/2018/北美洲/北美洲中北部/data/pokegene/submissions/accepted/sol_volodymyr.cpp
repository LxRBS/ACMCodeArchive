#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string.h>
#include <utility>
#include <queue>
#include <stack>
#include <iomanip>
#include <ctype.h>
#include <map>
#include <set>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <sstream>
#include <math.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <tuple>
#include <cmath>
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>
#include <fstream>

using namespace std;

typedef long long LL;

#define FOR(i,n) for(int i = 0;i < n;i++)
#define MP make_pair
#define PB push_back
#define ALL(a) (a).begin(),(a).end()
#define PII pair<int, int>
#define PLL pair<long long, long long>
#define CLEAR(a) memset(a, 0, sizeof(a))
#define INF 2000000007
#define y1 uu1
#define y2 uu2
#define hash mash
const double EPS = 1E-12;
const double PI = acos(-1.0);
const LL mod = 1000000007;

using namespace std;

int n, q, k, l, idx, gi = 0;
string s;
pair<string, int> words[200005];
vector<int> tree[200005];
unordered_map<int, int> p2p;

struct node {
  node* nxt[26];
  int id;

  node() {
    FOR(i, 26) nxt[i] = NULL;
    id = gi;
    gi++;
  }
};
node * root = new node();

void add(int index) {
  node * cur = root;
  FOR(i, words[index].first.length()) {
    int to = words[index].first[i] - 'a';
    if (cur->nxt[to] == NULL) {
      cur->nxt[to] = new node();
    }
    tree[index].push_back(cur->id);
    cur = cur->nxt[to];
  }
  tree[index].push_back(cur->id);
}

int getcommon(int i1, int i2) {
  int l = 0, r = min(tree[i1].size(), tree[i2].size()) - 1;
  while (r > l) {
    int mid = (l + r + 1) / 2;
    if (tree[i1][mid] == tree[i2][mid]) {
      l = mid;
    } else {
      r = mid - 1;
    }
  }
  return l;
}

void solve() {
  vector<int> widx;
  FOR(i, k) {
    cin >> idx;
    idx--;
    widx.push_back(p2p[idx]);
  }
  sort(ALL(widx));
  int ans = 0;

  for (int idx = 0; idx <= k - l; idx++) {
    //cerr << "DBG " << words[widx[idx]].first << ' ' << words[widx[idx + l - 1]].first << endl;
    int c = getcommon(widx[idx], widx[idx + l - 1]);
    int c1, c2;
    if (idx > 0)
      c1 = getcommon(widx[idx], widx[idx - 1]);
    else
      c1 = 0;
    if (idx + l < k)
      c2 = getcommon(widx[idx], widx[idx + l]);
    else
      c2 = 0;
    int other = min(c, max(c1, c2));
    ans += (c - other);
  }

  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);

  cin >> n >> q;
  FOR(i, n) {
    cin >> words[i].first;
    words[i].second = i;
  }
  sort(words, words + n);
  FOR(i, n) {
    p2p[words[i].second] = i;
    add(i);
  }

  FOR(qq, q) {
    cin >> k >> l;
    assert(l > 0);
    solve();
  }

  return 0;
}
