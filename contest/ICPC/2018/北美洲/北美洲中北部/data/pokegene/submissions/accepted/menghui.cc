#include <algorithm>
#include <deque>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

int max_prefix_length(const string& a, const string& b) {
  int ans = 0;
  while (a.length() > ans && b.length() > ans && a[ans] == b[ans]) ++ans;
  return ans;
}

int log2(int x) {
  int ans = 0, t = 1;
  while (t * 2 <= x) {
    t *= 2;
    ++ans;
  }
  return ans;
}

struct RMQ {
  explicit RMQ(const std::vector<int>& a) {
    int n = a.size();
    query = vvi(log2(a.size()) + 1, vi(n));
    query[0] = a;
    for (int k = 1; k < query.size(); ++k) {
      for (int i = 0; i < n; ++i) {
        query[k][i] = query[k - 1][i];
        int gap = 1 << (k - 1);
        if (i + gap < n) {
          query[k][i] = std::min(query[k][i], query[k - 1][i + gap]);
        }
      }
    }
  }

  int range_min(int left, int right) {
    int k = log2(right - left + 1);
    int gap = 1 << k;
    if (gap == right - left + 1) {
      return query[k][left];
    } else {
      return std::min(query[k][left], query[k][right - gap + 1]);
    }
  }

  const static int kRMQQueryTableDepth = 19;
  vector<vector<int>> query;
};

struct MonotonicQueue {
  void push(int x) {
    while (!queue.empty() && queue.back().second >= x) {
      queue.pop_back();
    }
    queue.emplace_back(rear++, x);
  }

  void pop() {
    if (queue.front().first == front) {
      queue.pop_front();
    }
    ++front;
  }

  int min() {
    return queue.front().second;
  }

  int front = 0;
  int rear = 0;
  std::deque<std::pair<int /* position */, int /* value */>> queue;
};

int main() {
  ios_base::sync_with_stdio(false);
  int n, q;
  cin >> n >> q;
  vector<string> genes(n);
  vi sorted_gene_indexes;
  for (int i = 0; i < n; ++i) {
    cin >> genes[i];
    sorted_gene_indexes.push_back(i);
  }
  sort(sorted_gene_indexes.begin(), sorted_gene_indexes.end(),
       [&genes](int i, int j) { return genes[i] < genes[j]; });
  vi rank_to_gene_lengths;
  for (int i = 0; i < n; ++i) {
    rank_to_gene_lengths.push_back(genes[sorted_gene_indexes[i]].length());
  }

  vector<int> index_to_rank(n);
  for (int i = 0; i < n; ++i) {
    index_to_rank[sorted_gene_indexes[i]] = i;
  }

  vector<int> common_prefix_length;
  common_prefix_length.push_back(0);
  for (int i = 0; i + 1 < n; ++i) {
    common_prefix_length.push_back(max_prefix_length(
        genes[sorted_gene_indexes[i]], genes[sorted_gene_indexes[i + 1]]));
  }

  RMQ rmq(common_prefix_length);
  for (int ii = 0; ii < q; ++ii) {
    int k, l;
    cin >> k >> l;
    vi pokes;
    for (int j = 0; j < k; ++j) {
      int t;
      cin >> t;
      --t;
      pokes.push_back(index_to_rank[t]);
    }
    std::sort(pokes.begin(), pokes.end());

    vi new_common_prefix;
    new_common_prefix.push_back(0);
    for (int i = 0; i + 1 < pokes.size(); ++i) {
      new_common_prefix.push_back(rmq.range_min(pokes[i] + 1, pokes[i + 1]));
    }

    long long ans = 0;
    MonotonicQueue window;
    int window_start = 0, window_end = 0;
    while (window_end + 1 < l) {
      if (window_end >= 1) {
        window.push(new_common_prefix[window_end]);
      }
      ++window_end;
    }
    for (; window_end < k; ++window_start, ++window_end) {
      if (l == 1) {
        window.push(rank_to_gene_lengths[pokes[window_start]]);
      } else {
        window.push(new_common_prefix[window_end]);
      }
      int base = new_common_prefix[window_start];
      if (window_end + 1 < k) {
        base = std::max(base, new_common_prefix[window_end + 1]);
      }
      int upper = window.min();
      if (upper > base) {
        ans += upper - base;
      }
      window.pop();
    }
    cout << ans << endl;
  }

  return 0;
}
