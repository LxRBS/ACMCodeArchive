#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 998244353;

void add(int &x, ll y) {
  x = (x + y) % MOD;
}

int slow(int n, int k, vector<int> a, vector<vector<int>> e) {
  vector<int> p(n, -1);
  function<void(int, int)> dfs = [&](int v, int pr) {
    p[v] = pr;
    for (int to : e[v]) {
      if (to == pr) continue;
      dfs(to, v);
    }
  };
  dfs(0, -1);
  int ans = 0;
  for (int mask = 1; mask < (1 << n); mask++) {
    vector<int> c(n);
    for (int i = 0; i < n; i++) if (mask & (1 << i)) {
      for (int v = i; v != -1; v = p[v]) {
        c[v]++;
      }
    }
    int z = 0;
    for (int i = 1; i < n; i++) if (c[i] == c[z]) z = i;
    
    set<int> st;
    for (int i = 0; i < n; i++) if (mask & (1 << i)) {
      for (int v = i; v != p[z]; v = p[v]) {
        st.insert(a[v]);
      }
    }
    int coef = 0;
    for (int j = 0; j < (int)st.size(); j++) coef = (coef + (1 << (k - j))) % MOD;
    add(ans, coef);
  }
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
