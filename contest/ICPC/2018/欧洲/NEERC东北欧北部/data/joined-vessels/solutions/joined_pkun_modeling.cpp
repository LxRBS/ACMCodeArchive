#include <cstdio>
#include <vector>
#include <algorithm>
#include <climits>
#include <cassert>
#include <list>
#include <tuple>


using namespace std;

struct segment {
  int l, r, h;

  friend bool operator==(const segment &lhs, const segment &rhs) {
    return std::tie(lhs.l, lhs.r, lhs.h) == std::tie(rhs.l, rhs.r, rhs.h);
  }
};

long long solve(vector<int> h, int a, int b) {
  int n = h.size() + 1;
  list<segment> v;
  list<segment>::iterator active;
  for (int i = 0; i < n; i++) {
    v.push_back({i, i + 1, 0});
    if (i == a) {
      active = --v.end();
    }
  }

  while (true) {
    if (active->l <= b && b < active->r) {
      break;
    }
    int next_event = INT_MAX;
    if (active->l != 0) {
      if (active->h < h[active->l - 1]) {
        next_event = min(next_event, h[active->l - 1]);
      } else {
        next_event = min(next_event, prev(active)->h);
      }
    }
    if (active->r != n) {
      if (active->h < h[active->r - 1]) {
        next_event = min(next_event, h[active->r - 1]);
      } else {
        next_event = min(next_event, next(active)->h);
      }
    }
    assert(active->h < next_event);
    active->h = next_event;

    if (next(active) != v.end()) {
      auto next_seg = next(active);
      if (next_seg->h == active->h) {
        active->r = next_seg->r;
        v.erase(next_seg);
        continue;
      }
      if (active->h == h[active->r - 1]) {
        assert(next_seg->h == 0);
        active = next_seg;
        continue;
      }
    }
    assert(active != v.begin());
    auto prev_seg = prev(active);
    if (prev_seg->h == active->h) {
      active->l = prev_seg->l;
      v.erase(prev_seg);
      continue;
    }
    if (active->h == h[active->l - 1]) {
      assert(prev_seg->h == 0);
      active = prev_seg;
      continue;
    }
    assert(0);
  }

  long long ans = 0;
  for (auto x : v) {
    ans += (x.r - x.l) * 1LL * x.h;
  }
  return ans;
}
int main() {
  int n;
  scanf("%d", &n);
  vector<int> h(n - 1);
  for (int i = 0; i < n - 1; i++) {
    scanf("%d", &h[i]);
  }
  int q;
  scanf("%d", &q);

  for (int i = 0; i < q; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    printf("%lld\n", solve(h, a, b));
  }
}

