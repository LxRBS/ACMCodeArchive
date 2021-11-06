#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);
  int start = atoi(argv[1]);

  auto GenRandom = [&](int n, int limit, int min_d, int max_d) {
    startTest(start++);
    limit = max(limit, 2 * n - 1);
    set<int> xs;
    while ((int) xs.size() < 2 * n) {
      xs.insert(rnd.next(0, limit));
    }
    vector<int> xs_v(xs.begin(), xs.end());
    vector<int> pr(n);
    vector<vector<int>> g(n);
    for (int i = 0; i < n; i++) {
      pr[i] = (min_d == -1 ? rnd.next(-1, min(i - 1, max_d - 2)) : i - rnd.next(min(min_d, i + 1), min(max_d, i + 1)));
      if (pr[i] != -1) {
        g[pr[i]].push_back(i);
      }
    }
    int T = 0;
    vector<pair<int, int>> segs(n);
    function<void(int)> Dfs = [&](int i) {
      segs[i].first = xs_v[T++];
      for (int j : g[i]) {
        Dfs(j);
      }
      segs[i].second = xs_v[T++];
    };
    for (int i = 0; i < n; i++) {
      if (pr[i] == -1) {
        Dfs(i);
      }
    }
    assert(T == 2 * n);
    shuffle(segs.begin(), segs.end());
    cout << n << '\n';
    for (auto& s : segs) {
      cout << s.first << " " << s.second << '\n';
    }
  };
  
  auto GenSpecial = [&](int id, int n, int max_x) {
    startTest(start++);
    if (id == 1) {
      cout << n << '\n';
      for (int i = 0; i < n; i++) {
        cout << i << " " << max_x - i << '\n';
      }
    }
    if (id == 2) {
      cout << n << '\n';
      int step = max_x / (2 * n);
      for (int i = 0; i < n; i++) {
        cout << i * step << " " << max_x - i * step << '\n';
      }
    }
    if (id == 3) {
      cout << n << '\n';
      set<int> s;
      while ((int) s.size() < 2 * n) {
        s.insert(rnd.next(0, max_x));
      }
      vector<int> a(s.begin(), s.end());
      for (int i = 0; i < n; i++) {
        cout << a[2 * i] << " " << a[2 * i + 1] << '\n';
      }
    }
    if (id == 4) {
      cout << n << '\n';
      set<int> s;
      while ((int) s.size() < n) {
        s.insert(rnd.next(n / 2, max_x - n / 2));
      }
      vector<int> a(s.begin(), s.end());
      for (int i = 0; i < n / 2; i++) {
        cout << i << " " << max_x - i << '\n';
      }
      for (int i = 0; i < n / 2; i++) {
        cout << a[2 * i] << " " << a[2 * i + 1] << '\n';
      }
    }
    if (id == 5) {
      cout << n << '\n';
      set<int> s;
      while ((int) s.size() < n) {
        s.insert(rnd.next(n / 2, max_x - n / 2));
      }
      vector<int> a(s.begin(), s.end());
      for (int i = 0; i < n / 2; i++) {
        cout << i << " " << max_x - i << '\n';
      }
      for (int i = 0; i < n / 4; i++) {
        cout << a[4 * i] << " " << a[4 * i + 3] << '\n';
        cout << a[4 * i + 1] << " " << a[4 * i + 2] << '\n';
      }
    }
    if (id == 6) {
      cout << n << '\n';
      set<int> s;
      while ((int) s.size() < n) {
        s.insert(rnd.next(n / 2, max_x - n / 2));
      }
      vector<int> a(s.begin(), s.end());
      for (int i = 0; i < n / 2; i++) {
        cout << i << " " << max_x - i << '\n';
      }
      for (int i = 0; i < n / 4; i++) {
        cout << a[4 * i] << " " << a[4 * i + 3] << '\n';
        cout << a[4 * i + 1] << " " << a[4 * i + 2] << '\n';
      }
    }
    if (id == 7) {
      cout << n << '\n';
      set<int> s;
      while ((int) s.size() < 2 * n) {
        s.insert(rnd.next(0, max_x));
      }
      vector<int> a(s.begin(), s.end());
      for (int i = 0; i < n / 2; i++) {
        cout << a[i] << " " << a[n - 1 - i] << '\n';
      }
      for (int i = n / 2; i < n; i++) {
        cout << a[2 * i] << " " << a[2 * i + 1] << '\n';
      }
    }
    if (id == 8) {
      cout << n << '\n';
      for (int i = 0; i < 2 * n; i += 2) {
        cout << i << " " << i + 1 << '\n';
      }
    }
    if (id == 9) {
      cout << n << '\n';
      for (int i = 0; i < n; i++) {
        cout << i << " " << 2 * n - 1 - i << '\n';
      }
    }
    if (id == 10) {
      cout << n << '\n';
      for (int i = 0; i < 2 * n; i += 2) {
        cout << max_x - 2 * n + i << " " << max_x - 2 * n + i + 1 << '\n';
      }
    }
    if (id == 11) {
      cout << n << '\n';
      for (int i = 0; i < n; i++) {
        cout << max_x - 2 * n + i << " " << max_x - 2 * n + 2 * n - 1 - i << '\n';
      }
    }
    if (id == 12) {
      cout << n << '\n';
      int ptr = 0;
      for (int i = 0; i < n / 2; i++) {
        cout << ptr << " " << ptr + 1 << '\n';
        cout << ptr + 2 << " " << max_x - ptr << '\n';
        ptr += 3;
      }
    }
    if (id == 13) {
      cout << n << '\n';
      set<int> s;
      while ((int) s.size() < 2 * n) {
        s.insert(rnd.next(0, max_x));
      }
      vector<int> a(s.begin(), s.end());
      int ptr = 0;
      for (int i = 0; i < n / 2; i++) {
        cout << a[ptr] << " " << a[ptr + 1] << '\n';
        cout << a[ptr + 2] << " " << a[2 * n - 1 - i] << '\n';
        ptr += 3;
      }
    }
    if (id == 14) {
      cout << n << '\n';
      set<int> s;
      while ((int) s.size() < 2 * n) {
        s.insert(rnd.next(0, max_x));
      }
      vector<int> a(s.begin(), s.end());
      int ptr = 0;
      for (int i = 0; i < n / 4; i++) {
        cout << a[ptr] << " " << a[ptr + 5] << '\n';
        cout << a[ptr + 1] << " " << a[ptr + 2] << '\n';
        cout << a[ptr + 3] << " " << a[ptr + 4] << '\n';
        cout << a[ptr + 6] << " " << a[2 * n - 1 - i] << '\n';
        ptr += 7;
      }
    }
  };
  
  auto GenExp = [&](int n, int limit, int max_d) {
    startTest(start++);
    limit = max(limit, 2 * n - 1);
    vector<int> xs_v(1, 0);
    while ((int) xs_v.size() < 2 * n) {
      int last = xs_v.back();
      last += (int) exp(rnd.next(0.0, log(limit / (2 * n))));
      xs_v.push_back(last);
    }
    vector<int> pr(n);
    vector<vector<int>> g(n);
    pr[0] = -1;
    for (int i = 1; i < n; i++) {
      pr[i] = i - rnd.next(1, min(max_d, i));
      if (pr[i] != -1) {
        g[pr[i]].push_back(i);
      }
    }
    int T = 0;
    vector<pair<int, int>> segs(n);
    function<void(int)> Dfs = [&](int i) {
      segs[i].first = xs_v[T++];
      for (int j : g[i]) {
        Dfs(j);
      }
      segs[i].second = xs_v[T++];
    };
    for (int i = 0; i < n; i++) {
      if (pr[i] == -1) {
        Dfs(i);
      }
    }
    assert(T == 2 * n);
    shuffle(segs.begin(), segs.end());
    cout << n << '\n';
    for (auto& s : segs) {
      cout << s.first << " " << s.second << '\n';
    }
  };

  auto GenDeepRandom = [&](int n, int limit, int depth, int max_d) {
    startTest(start++);
    limit = max(limit, 2 * n - 1);
    set<int> xs;
    while ((int) xs.size() < 2 * n) {
      xs.insert(rnd.next(0, limit));
    }
    vector<int> xs_v(xs.begin(), xs.end());
    vector<int> pr(n);
    vector<vector<int>> g(n);
    for (int i = 0; i < n; i++) {
      pr[i] = (i <= depth ? i - 1 : i - rnd.next(1, min(max_d, i - depth)));
      if (pr[i] != -1) {
        g[pr[i]].push_back(i);
      }
    }
    int T = 0;
    vector<pair<int, int>> segs(n);
    function<void(int)> Dfs = [&](int i) {
      segs[i].first = xs_v[T++];
      for (int j : g[i]) {
        Dfs(j);
      }
      segs[i].second = xs_v[T++];
    };
    for (int i = 0; i < n; i++) {
      if (pr[i] == -1) {
        Dfs(i);
      }
    }
    assert(T == 2 * n);
    shuffle(segs.begin(), segs.end());
    cout << n << '\n';
    for (auto& s : segs) {
      cout << s.first << " " << s.second << '\n';
    }
  };

  auto GenDeepUndeep = [&](int n, int limit, int depth, int coeff) {
    startTest(start++);
    limit = max(limit, 2 * n - 1);
    set<int> xs;
    while ((int) xs.size() < 2 * n) {
      xs.insert(rnd.next(0, limit));
    }
    vector<int> xs_v(xs.begin(), xs.end());
    vector<int> pr(n);
    vector<vector<int>> g(n);
    int ptr = 0;
    for (int i = 0; i < n; i++) {
      if (i <= depth) {
        pr[i] = i - 1;
        ptr = i;
      } else {
        if (rnd.next(0, 10) < coeff) {
          pr[i] = depth;
          ptr = i;
        } else {
          pr[i] = i - rnd.next(1, i - ptr);
        }
      }
      if (pr[i] != -1) {
        g[pr[i]].push_back(i);
      }
    }
    int T = 0;
    vector<pair<int, int>> segs(n);
    function<void(int)> Dfs = [&](int i) {
      segs[i].first = xs_v[T++];
      for (int j : g[i]) {
        Dfs(j);
      }
      segs[i].second = xs_v[T++];
    };
    for (int i = 0; i < n; i++) {
      if (pr[i] == -1) {
        Dfs(i);
      }
    }
    assert(T == 2 * n);
    shuffle(segs.begin(), segs.end());
    cout << n << '\n';
    for (auto& s : segs) {
      cout << s.first << " " << s.second << '\n';
    }
  };

  int maxn = atoi(argv[2]);
  int maxx = atoi(argv[3]);

  set<int> ns;
  for (int i = 1; i <= 10; i++) {
    ns.insert(i);
  }
  int x = 10;
  while (x < maxn) {
    for (int i = 0; i < 5; i++) {
      ns.insert(rnd.next(x + 1, min(maxn, 10 * x)));
    }
    x *= 10;
  }
  ns.insert(maxn);
  
  for (int n : ns) {
    GenRandom(n, n <= 10 ? 100 : (n <= 100 ? 10000 : maxx), 1, n);
  }

  for (int max_d = 1; max_d < maxn; max_d *= 5) {
    GenRandom(maxn, maxx, 1, max_d);
  }

  for (int min_d = 1; min_d < maxn; min_d *= 5) {
    GenRandom(maxn, maxx, min_d, maxn);
  }

  for (int limit = 1; limit < maxn; limit *= 2) {
    GenRandom(maxn, maxx, -1, limit);
  }

  for (int id = 1; id <= 14; id++) {
    GenSpecial(id, maxn, maxx);
  }

  for (int max_d = 1; max_d < 2 * maxn; max_d *= 2) {
    GenExp(maxn, maxx, max_d);
  }

  for (int max_d = 1; max_d < 2 * maxn; max_d *= 2) {
    GenDeepRandom(maxn, maxx, maxn / 2, max_d);
    for (int it = 0; it < 3; it++) {
      GenDeepRandom(maxn, maxx, rnd.next(1, maxn - 1), max_d);
    }
  }

  for (int coeff = 1; coeff <= 10; coeff++) {
    GenDeepUndeep(maxn, maxx, maxn / 2 + rnd.next(-maxn / 10, maxn / 10), coeff);
  }

  return 0;
}
