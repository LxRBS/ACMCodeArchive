#include <iostream>
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdio>
#include <map>
#include <random>

using namespace std;

using ull = unsigned long long;

minstd_rand rnd(239239);
pair<long long, string> gen_random_expr();

// expr = summand ['+' summand]*
// summand = multiplier ['*' multipler]*
// multiplier = '(' expr ')' | int

pair<long long, string> gen_random_mutipliler() {
  int type = std::bernoulli_distribution(0.1)(rnd);
  if (type == 1) {
    auto [value, res] = gen_random_expr();
    int id = uniform_int_distribution<int>(0, 2)(rnd);
    return {value, "([{"[id] + res + ")]}"[id]};
  }
  int x = std::poisson_distribution<int>(8)(rnd);
  return {x, to_string(x)};
}

pair<long long, string> gen_random_summand() {
  auto [value, res] = gen_random_mutipliler();
  int count = std::poisson_distribution<int>(1)(rnd);
  for (int i = 0; i < count; i++) {
    auto [value2, res2] = gen_random_mutipliler();
    value *= value2;
    res += '*';
    res += res2;
  }
  return {value, res};
}

pair<long long, string> gen_random_expr() {
  auto [value, res] = gen_random_summand();
  int count = std::poisson_distribution<int>(2)(rnd);
  for (int i = 0; i < count; i++) {
    auto [value2, res2] = gen_random_summand();
    value += value2;
    res += '+';
    res += res2;
  }
  return {value, res};
}

struct my_bitset {
  static constexpr int BITS = sizeof(ull) * 8;
  static constexpr ull onebit(int id) {
    return ull(1) << id;
  }
  vector<ull> bits;
  explicit my_bitset(int size) : bits((size + BITS - 1) / BITS) {}
  explicit my_bitset(const string& s) : bits((s.size() * 8 + BITS - 1) / BITS){
    int id = 0;
    for (char c : s) {
      for (int i = 0; i < 8; i++) {
        if ((((unsigned char) c) & (1 << i)) != 0) {
          bits[id / BITS] |= onebit(id % BITS);
        }
        id++;
      }
    }
  }
  my_bitset& operator^=(const my_bitset& other) {
    assert(bits.size() == other.bits.size());
    for (int i = 0; i < (int)bits.size(); i++) {
      bits[i] ^= other.bits[i];
    }
    return *this;
  }
  bool operator[](int id) const {
    assert(0 <= id && id < (int)bits.size() * BITS);
    return bits[id / BITS] & onebit(id % BITS);
  }
  void set(int id) {
    assert(0 <= id && id < (int)bits.size() * BITS);
    bits[id / BITS] |= onebit(id % BITS);
  }
  int any_bit() const {
    for (int i = 0; i < (int)bits.size(); i++) {
      if (bits[i] != 0) {
        return BITS * i + __builtin_ctzll(bits[i]);
      }
    }
    return -1;
  }
};

struct Basis {
  vector<my_bitset> basis;
  vector<my_bitset> repr;
  vector<int> basis_bit;
  vector<string> expr;
  int len;
  void add(const string &s) {
    assert(len == (int)s.size());
    my_bitset v(s);
    my_bitset r(8 * len);
    for (int i = 0; i < (int) basis.size(); i++) {
      if (v[basis_bit[i]]) {
        v ^= basis[i];
        r ^= repr[i];
      }
    }
    int bit = v.any_bit();
    if (bit == -1) {
      return;
    }
    assert((int)basis.size() < 8 * len);
    r.set(basis.size());
    for (int j = 0; j < (int) basis.size(); j++)
      if (basis[j][bit]) {
        basis[j] ^= v;
        repr[j] ^= r;
      }
    expr.push_back(s);
    basis.push_back(v);
    basis_bit.push_back(bit);
    repr.push_back(r);
  }
  bool ready() const {
    if (len % 2 == 0) {
      return (int)basis.size() == len * 7 - 2;
    } else {
      return (int)basis.size() == len * 7 - 1;
    }
  }

  vector<string> represent(const string& x) {
    assert(len == (int)x.size());
    my_bitset s(x);
    my_bitset r(8 * len);
    for (int i = 0; i < (int)basis.size(); i++) {
      if (s[basis_bit[i]]) {
        s ^= basis[i];
        r ^= repr[i];
      }
    }
    if (s.any_bit() != -1) {
      return {};
    }
    vector<string> ans;
    for (int i = 0; i < 8*len; i++) {
      if (r[i]) {
        ans.push_back(expr[i]);
      }
    }
    return ans;
  }
};


int main() {
#ifdef LOCAL
  freopen("in", "r", stdin);
  freopen("out", "w", stdout);
#endif
  const int MIN_LEN = 10;
  const int MAX_LEN = 50;
  vector<Basis> bs(MAX_LEN + 1);

  for (int len = MIN_LEN; len <= MAX_LEN; len++) {
    bs[len].len = len;
    if (len % 2 == 1) {
      bs[len].add(string((len - 3) / 2, '(') + "0" + string((len - 3) / 2, ')') + "=0");
      bs[len].add(string((len - 3) / 2, '{') + "0" + string((len - 3) / 2, '}') + "=0");
      bs[len].add(string((len - 3) / 2, '[') + "0" + string((len - 3) / 2, ']') + "=0");
      bs[len].add("0=" + string((len - 3) / 2, '(') + "0" + string((len - 3) / 2, ')'));
      bs[len].add("0=" + string((len - 3) / 2, '{') + "0" + string((len - 3) / 2, '}'));
      bs[len].add("0=" + string((len - 3) / 2, '[') + "0" + string((len - 3) / 2, ']'));
    } else {
      bs[len].add(string((len - 6) / 2, '(') + "10*0" + string((len - 6) / 2, ')') + "=0");
      bs[len].add(string((len - 6) / 2, '{') + "10*0" + string((len - 6) / 2, '}') + "=0");
      bs[len].add(string((len - 6) / 2, '[') + "10*0" + string((len - 6) / 2, ']') + "=0");
      bs[len].add("0=" + string((len - 6) / 2, '(') + "10*0" + string((len - 6) / 2, ')'));
      bs[len].add("0=" + string((len - 6) / 2, '{') + "10*0" + string((len - 6) / 2, '}'));
      bs[len].add("0=" + string((len - 6) / 2, '[') + "10*0" + string((len - 6) / 2, ']'));
    }
  }

  map<int, vector<string>> strs;
  for (int i = 0; i < 10000; i++) {
    strs[i].emplace_back(to_string(i));
  }
  int not_ready = MAX_LEN - MIN_LEN + 1;
  while (not_ready) {
    auto [val, s] = gen_random_expr();
    if ((int) s.size() > MAX_LEN) continue;
    strs[val].emplace_back(s);
    for (const auto &x : strs[val]) {
      int f_len = x.size() + s.size() + 1;
      if (MIN_LEN <= f_len && f_len <= MAX_LEN && !bs[f_len].ready()) {
        bs[f_len].add(x + '=' + s);
        bs[f_len].add(s + '=' + x);
        if (bs[f_len].ready()) {
          not_ready--;
        }
      }
    }
  }

  int tcnt;
  scanf("%d", &tcnt);
  for (int test = 0; test < tcnt; test++) {
    string s;
    cin >> s;
    vector<string> r = bs[s.size()].represent(s);
    if (r.empty()) {
      printf("NO\n");
    } else {
      printf("YES\n");
      printf("%d\n", (int) r.size());
      for (const auto &x : r) {
        printf("%s\n", x.c_str());
      }
    }
  }
}
