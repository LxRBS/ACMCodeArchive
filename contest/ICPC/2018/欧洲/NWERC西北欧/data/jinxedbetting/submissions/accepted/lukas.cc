// Solution by lukasP (Lukáš Poláček)
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

#define rep(i, a, b) for (__typeof(b) i = (a); (i) < (b); ++(i))

int log2(int n) {
  int res = 0;
  for (int bits = 16; bits > 0; bits >>= 1) {
    if ((n >> bits) > 0) {
      res |= bits;
      n >>= bits;
    }
  }
  return res + 1;
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int64_t> p(n);
  rep(i, 0, n) {
    scanf("%ld", &p[i]);
  }
  int64_t jeff = p[0];
  std::sort(p.begin(), p.end());
  p.pop_back();

  int64_t lead = jeff - p.back();
  unsigned grp_size = 1;
  int64_t matches = 0;
  while (p.size() >= 2) {
    int64_t gap = p.back() - p[p.size() - 2];
    unsigned cycle_length = log2(grp_size);
    if (cycle_length >= 2 && lead <= gap * (cycle_length - 1)) {
      break;
    }

    matches += gap * cycle_length;
    lead -= gap * (cycle_length - 1);

    p.pop_back();
    ++grp_size;
  }

  unsigned cycle_length = log2(grp_size);
  int64_t whole = lead / (cycle_length - 1);
  lead -= whole * (cycle_length - 1);
  matches += whole * cycle_length + lead;

  std::cout << matches << std::endl;
}
