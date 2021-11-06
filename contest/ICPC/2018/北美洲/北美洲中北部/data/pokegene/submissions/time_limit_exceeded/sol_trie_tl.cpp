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

int n, q, k, l, idx;
string s;
vector<string> words;

struct node {
  node* nxt[26];

  node() {
    FOR(i, 26) nxt[i] = NULL;
  }
};
node * root = new node();

void add() {
  node * cur = root;
  FOR(i, s.length()) {
    int to = s[i] - 'a';
    if (cur->nxt[to] == NULL) {
      cur->nxt[to] = new node();
    }
    cur = cur->nxt[to];
  }
}

void solve() {
  unordered_map<node*, vector<int> > a;
  FOR(i, k) {
    cin >> idx;
    idx--;
    a[root].push_back(idx);
  }

  int ans = 0;
  int step = 0;
  //cerr << "looping " << endl;
  while(a.size() > 0) {
    //cerr << "s1 " << endl;
    unordered_map<node*, vector<int> > na;
    for (auto it : a) {
      for (auto idx : it.second) {
        if (words[idx].length() <= step) {
          continue;
        }
        int to = words[idx][step] - 'a';
        if (it.first->nxt[to] != NULL) {
          na[it.first->nxt[to]].push_back(idx);
        }
      }
    }
    //cerr << "s2 " << endl;

    a = na;
    vector<node*> er;
    for (auto it : a) {
      if (it.second.size() < l) {
        er.push_back(it.first);
      } else if (it.second.size() == l) {
        ans++;
      }
    }
    //cerr << "s3 " << endl;
    for(auto e : er) {
      a.erase(e);
    }
    step++;
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);

  cin >> n >> q;
  FOR(i, n) {
    cin >> s;
    words.push_back(s);
    add();
  }

  FOR(qq, q) {
    cin >> k >> l;
    assert(l > 0);
    solve();
  }

  return 0;
}
