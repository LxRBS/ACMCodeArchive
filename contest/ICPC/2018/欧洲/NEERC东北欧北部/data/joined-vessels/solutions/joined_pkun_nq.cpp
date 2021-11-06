#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;


long long solve(vector<int> h, int a, int b) {
  int n = h.size() + 1;
  if (a > b) {
    reverse(h.begin(), h.end());
    a = n - a - 1;
    b = n - b - 1;
  }
  int cur = 0;
  long long ans = 0;
  for (int x = b - 1; x >= a; x--) {
    cur = max(cur, h[x]);
    ans += cur;
  }
  for (int x = a - 1; x >= 0 && h[x] <= cur; x--) {
    ans += cur;
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

