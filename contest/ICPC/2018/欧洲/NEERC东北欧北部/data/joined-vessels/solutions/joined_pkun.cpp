#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct query {
  int l;
  long long &ans;
};

struct item {
  int upto;
  int value;
  long long prefix_sum;

  item(int upto, int value, long long int prefix_sum) : upto(upto), value(value), prefix_sum(prefix_sum) {}
};

void process(const vector<int> &h, vector <vector<query>> &qs) {
  vector<item> st;
  for (int i = 0; i < (int)qs.size(); i++) {
    while (!st.empty() && st.back().value < h[i]) {
      st.pop_back();
    }
    long long sum = 0;
    int prev = -1;
    if (!st.empty()) {
      prev = st.back().upto;
      sum = st.back().prefix_sum;
    }
    sum += h[i] * 1LL * (i - prev);
    st.emplace_back(i, h[i], sum);
    for (query &q : qs[i]) {
      auto it = lower_bound(st.begin(), st.end(), q.l, [](const item &a, int x) { return a.upto < x;});
      if (it == st.begin()) {
        q.ans = st.back().prefix_sum;
      } else {
        --it;
        q.ans = st.back().prefix_sum - it->prefix_sum;
      }
    }
  }
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
  vector<vector<query>> ltr(n);
  vector<vector<query>> rtl(n);
  vector<long long> ans(q);

  for (int i = 0; i < q; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    if (a < b) {
      ltr[b - 1].push_back({a, ans[i]});
    } else {
      rtl[n - b - 2].push_back({n - a - 1, ans[i]});
    }
  }
  process(h, ltr);
  reverse(h.begin(), h.end());
  process(h, rtl);

  for (int i = 0; i < q; i++) {
    printf("%lld\n", ans[i]);
  }
}

