#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 998244353;

void add(int &x, ll y) {
  x = (x + y) % MOD;
}

int slow(int n, int k, vector<int> a, vector<vector<int>> e) {
  vector<int> par(n, -1), vis(n), q;
  q.push_back(0);
  vis[0] = 1;
  for (int i = 0; i < n; i++) {
    for (int to : e[q[i]]) {
      if (!vis[to]) {
        q.push_back(to);
        vis[to] = 1;
        par[to] = q[i];
      }
    }
  }

  int ans = 0;
  vector<int> used(n);
  vector<vector<int>> comps;
  function<void()> rec = [&]() {
    int cur = 0;
    while (cur < n && used[cur]) cur++;
    if (cur == n) {
      for (auto c : comps) {
        vector<int> cnt(n);
        for (int v : c) for (int x = v; x != -1; x = par[x]) cnt[x]++;
        int r = 0;
        for (int v : q) if (cnt[v] == cnt[r]) r = v;
        set<int> st;
        for (int v : c) for (int x = v; x != r; x = par[x]) st.insert(a[x]);
        st.insert(a[r]);
        for (int i = 0; i < (int)st.size(); i++) add(ans, 1 << (k - i));
      }
    } else {
      vector<int> vct;
      for (int i = cur + 1; i < n; i++) if (!used[i]) vct.push_back(i);
      for (int mask = 0; mask < (1 << (int)vct.size()); mask++) {
        vector<int> b(1, cur);
        for (int i = 0; i < (int)vct.size(); i++) if (mask & (1 << i)) b.push_back(vct[i]);
        comps.push_back(b);
        for (int x : b) used[x] = 1;
        rec();
        for (int x : b) used[x] = 0;
        comps.pop_back();
      }
    }
  };
  rec();
  return ans;
}

int main() {
#ifdef HOME
  freopen("in", "r", stdin);
#endif
  int n, k;
  scanf("%d%d", &n, &k);
  vector<int> a(n, -1);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]), a[i]--;
  vector<vector<int>> e(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  cout << slow(n, k, a, e) << endl;
}

