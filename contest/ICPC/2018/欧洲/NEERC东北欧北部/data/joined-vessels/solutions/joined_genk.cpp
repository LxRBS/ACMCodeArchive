/**
 *    author:  tourist
 *    created: 21.10.2018 12:33:04       
**/
#include <bits/stdc++.h>

using namespace std;

const int inf = (int) 1.01e9;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> h(n);
  h[0] = inf;
  for (int i = 1; i < n; i++) {
    cin >> h[i];
  }
  int m;
  cin >> m;
  vector<int> a(m), b(m);
  for (int i = 0; i < m; i++) {
    cin >> a[i] >> b[i];
    a[i]--; b[i]--;
  }
  vector<long long> res(m, -1);
  for (int rot = 0; rot < 2; rot++) {
    vector<vector<int>> qs(n);
    for (int i = 0; i < m; i++) {
      if (a[i] < b[i]) {
        qs[b[i]].push_back(i);
      }
    }
    vector<long long> area(1, 0);
    vector<int> st(1, 0);
    for (int i = 1; i < n; i++) {
      while (h[i] > h[st.back()]) {
        area.pop_back();
        st.pop_back();
      }
      area.push_back(area.back() + (long long) h[i] * (i - st.back()));
      st.push_back(i);
      for (int id : qs[i]) {
        int j = a[id];
        int pos = (int) (upper_bound(st.begin(), st.end(), j) - st.begin());
        res[id] = area.back() - area[pos - 1];
      }
    }
    reverse(h.begin() + 1, h.end());
    for (int i = 0; i < m; i++) {
      a[i] = n - 1 - a[i];
      b[i] = n - 1 - b[i];
    }
  }
  for (int i = 0; i < m; i++) {
    cout << res[i] << '\n';
  }
  return 0;
}
