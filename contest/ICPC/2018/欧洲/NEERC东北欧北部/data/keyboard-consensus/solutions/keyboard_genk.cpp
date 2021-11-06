/**
 *    author:  tourist
 *    created: 25.10.2018 20:18:40       
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n), b(n), a_pos(n), b_pos(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    a[i]--;
    a_pos[a[i]] = i;
  }
  for (int i = 0; i < n; i++) {
    cin >> b[i];
    b[i]--;
    b_pos[b[i]] = i;
  }
  auto removeA = [&](vector<int> &alive) {
    for (int i = n - 1; i >= 0; i--) {
      if (alive[a[i]] == 1) {
        alive[a[i]] = 0;
        break;
      }
    }
  };
  auto removeB = [&](vector<int> &alive) {
    for (int i = n - 1; i >= 0; i--) {
      if (alive[b[i]] == 1) {
        alive[b[i]] = 0;
        break;
      }
    }
  };
  auto calcA = [&](vector<int> alive) {
    int cc = accumulate(alive.begin(), alive.end(), 0);
    for (int i = 0; i < cc - 1; i++) {
      if (i % 2 == 0) {
        removeA(alive);
      } else {
        removeB(alive);
      }
    }
    for (int i = 0; i < n; i++) {
      if (alive[i]) {
        return i;
      }
    }
    assert(false);
    return -1;
  };
  auto calcB = [&](vector<int> alive) {
    int cc = accumulate(alive.begin(), alive.end(), 0);
    if (cc > 1 && cc % 2 == 1) {
      int best = b[n - 1];
      for (int i = 0; i < n; i++) {
        if (alive[i]) {
          alive[i] = 0;
          int cur = calcA(alive);
          if (b_pos[cur] < b_pos[best]) {
            best = cur;
          }
          alive[i] = 1;
        }
      }
      return best;
    }
    for (int i = 0; i < cc - 1; i++) {
      if (i % 2 == 0) {
        removeB(alive);
      } else {
        removeA(alive);
      }
    }
    for (int i = 0; i < n; i++) {
      if (alive[i]) {
        return i;
      }
    }
    assert(false);
    return -1;
  };
  int best = a[n - 1];
  vector<int> ways;
  for (int i = 0; i < n; i++) {
    vector<int> alive(n, 1);
    alive[i] = 0;
    int cur = calcB(alive);
    if (a_pos[cur] < a_pos[best]) {
      best = cur;
      ways.clear();
    }
    if (a_pos[cur] == a_pos[best]) {
      ways.push_back(i);
    }
  }
  cout << best + 1 << '\n';
  cout << (int) ways.size() << '\n';
  for (int i = 0; i < (int) ways.size(); i++) {
    if (i > 0) {
      cout << " ";
    }
    cout << ways[i] + 1;
  }
  cout << '\n';
  return 0;
}
