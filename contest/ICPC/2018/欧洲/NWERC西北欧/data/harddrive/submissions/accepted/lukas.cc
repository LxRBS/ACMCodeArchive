//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <cstdio>

#define rep(i,a,b) for(__typeof(b) i=(a); (i)<(b); ++(i))

int main() {
  int n, c, b;
  scanf("%d %d %d", &n, &c, &b);
  std::vector<int> z(b + 1);
  rep(i,0,b) {
    scanf("%d", &z[i + 1]);
    --z[i + 1];
  }
  z[0] = -1;

  std::string res(n, '0');
  for (int cur = b; cur >= 1; --cur) {
    for (int pos = z[cur] - 1; c >= 2 && pos > z[cur - 1]; pos -= 2) {
      res[pos] = '1';
      c -= 2;
    }
  }

  if (c == 1) {
    res[0] = '1';
  }
  std::cout << res << std::endl;
}
