#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <vector>

int prod_mod_10(const std::vector<int> &res) {
  int prod = 1;
  for (int x : res) {
    prod *= x;
    prod %= 10;
  }
  return prod;
}

void print_result(int d, const std::vector<int> &res) {
  if (res.empty() || prod_mod_10(res) != d) {
    std::cout << -1 << '\n';
  } else {
    std::cout << res.size() << '\n';
    for (int x : res) {
      std::cout << x << ' ';
    }
    std::cout << '\n';
  }
}

int main() {
  std::ios::sync_with_stdio(false);

  int n, d;
  std::cin >> n >> d;

  std::vector<int> a(n);
  for (int &x : a) {
    std::cin >> x;
  }

  for (int p : {2, 5}) {
    if (d % p != 0) {
      auto end = std::partition(a.begin(), a.end(), [p](int x) {
        return x % p != 0;
      });
      a.erase(end, a.end());
    }
  }

  if (d % 5 == 0) {
    print_result(d, a);
    return 0;
  }

  std::map<int, std::vector<int>> buckets;
  for (int x : a) {
    buckets[x % 10].push_back(x);
  }

  std::vector<int> maybe_throw;
  std::vector<int> take;

  for (auto &bc : buckets) {
    auto &nums = bc.second;
    std::sort(nums.begin(), nums.end());

    auto mid = nums.begin() + std::min<size_t>(4, nums.size());

    maybe_throw.insert(maybe_throw.end(), nums.begin(), mid);
    take.insert(take.end(), mid, nums.end());
  }

  const int k = maybe_throw.size();
  const int init_take_prod = prod_mod_10(take);

  using item_t = std::pair<long long, int>;
  const item_t NONE = {std::numeric_limits<long long>::max() / 11, -1};

  std::vector<std::vector<item_t>> dp(k + 1, std::vector<item_t>(10, NONE));
  dp[0][init_take_prod] = {1, -1};

  for (int i = 0; i < k; i++) {
    auto &prev = dp[i];
    auto &next = dp[i + 1];
    auto num = maybe_throw[i];

    for (int p = 0; p < 10; p++) {
      if (prev[p] != NONE) {
        next[p] = std::min(next[p], item_t{prev[p].first * num, p});

        int q = p * num % 10;
        next[q] = std::min(next[q], item_t{prev[p].first, p});
      }
    }
  }

  if (dp[k][d] == NONE) {
    print_result(d, {});
    return 0;
  }

  int p = d;
  for (int i = k; i > 0; i--) {
    int q = dp[i][p].second;
    if (dp[i][p].first == dp[i - 1][q].first) {
      take.push_back(maybe_throw[i - 1]);
    }
    p = q;
  }
  assert(p == init_take_prod);

  assert(prod_mod_10(take) == d);
  print_result(d, take);
}
