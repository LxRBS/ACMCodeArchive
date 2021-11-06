#include <cstdio>
#include <vector>
#include <tuple>
#include <set>

using namespace std;

struct bigint {
  vector<int> data;
  int& operator[](int x) { return data[x];}
  int operator[](int x) const { return data[x];}
  int size() const { return (int)data.size(); }
};
const int BASELEN = 9;
const int BASE = 1'000'000'000;

bool operator<(const bigint& a, const bigint &b) {
  if (a.size() != b.size()) {
    return a.size() < b.size();
  }
  for (int i = (int)a.size() - 1; i >= 0; i--) {
    if (a[i] != b[i]) {
      return a[i] < b[i];
    }
  }
  return false;
}

bigint operator+(const bigint& a, const bigint &b) {
  bigint nres;
  nres.data.reserve(max(a.size(), b.size()) + 1);
  int cur = 0;
  for (int i = 0; i < a.size() || i < b.size() || cur; i++) {
    if (i < a.size()) cur += a[i];
    if (i < b.size()) cur += b[i];
    nres.data.push_back(cur % BASE);
    cur /= BASE;
  }
  return nres;
}

void print(const bigint& a) {
  printf("%d", a[a.size() - 1]);
  for (int i = (int)a.size() - 2; i >= 0; i--) {
    printf("%0*d", BASELEN, a[i]);
  }
}

const int NTERM = 26;
const int TERM = 26;

vector<pair<int, int>> left_rule[NTERM];
vector<pair<int, int>> right_rule[NTERM];
vector<int> letter_rule[TERM];

struct item {
  int nterm;
  int from;
  int to;
};

int main() {
#ifdef LOCAL
  freopen("in", "r", stdin);
#endif
  int p;
  scanf("%d", &p);
  for (int i = 0; i < p; i++) {
    char s1[3], s2[3];
    scanf("%s -> %s", s1, s2);
    if ('A' <= s2[0] && s2[0] <= 'Z') {
      left_rule[s2[0] - 'A'].emplace_back(s2[1] - 'A', s1[0] - 'A');
      right_rule[s2[1] - 'A'].emplace_back(s2[0] - 'A', s1[0] - 'A');
    } else {
      letter_rule[s2[0] - 'a'].push_back(s1[0] - 'A');
    }
  }
  int n, m, s, t;
  scanf("%d%d%d%d", &n, &m, &s, &t);
  --s, --t;
  vector<vector<bigint>> ans[NTERM];
  for (int i = 0; i < NTERM; i++) {
    ans[i] = vector<vector<bigint>>(n, vector<bigint>(n));
  }
  auto cmp = [&](const item &a, const item &b) {
    return std::tie(ans[a.nterm][a.from][a.to], a.nterm, a.from, a.to) < std::tie(ans[b.nterm][b.from][b.to], b.nterm, b.from, b.to);
  };
  set<item, decltype(cmp)> d(cmp);
  for (int i = 0; i < m; i++) {
    int a, b; char c;
    scanf("%d %d %c", &a, &b, &c);
    --a, --b;
    for (int id : letter_rule[c - 'a']) {
      ans[id][a][b] = {{1}};
      d.insert({id, a, b});
    }
  }

  while (!d.empty()) {
    auto it = d.begin();
    auto [nt, a, b] = *it;
    if (a == s && b == t && nt == 'S' - 'A') {
      print(ans[nt][a][b]);
      printf("\n");
      return 0;
    }
    d.erase(d.begin());
    for (auto [ont, rnt] : left_rule[nt]) {
      for (int i = 0; i < n; i++) {
        if (ans[ont][b][i].size()) {
          bigint res = ans[nt][a][b] + ans[ont][b][i];
          if (!ans[rnt][a][i].size() || res < ans[rnt][a][i]) {
            d.erase({rnt, a, i});
            ans[rnt][a][i] = res;
            d.insert({rnt, a, i});
          }
        }
      }
    }
    for (auto [ont, rnt] : right_rule[nt]) {
      for (int i = 0; i < n; i++) {
        if (ans[ont][i][a].size()) {
          bigint res = ans[nt][a][b] + ans[ont][i][a];
          if (!ans[rnt][i][b].size() || res < ans[rnt][i][b]) {
            d.erase({rnt, i, b});
            ans[rnt][i][b] = res;
            d.insert({rnt, i, b});
          }
        }
      }
    }
  }
  printf("NO\n");
}
