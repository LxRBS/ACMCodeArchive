// Solution by lukasP (Lukáš Poláček)
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

template <int reverse>
int collect(const std::string& s, int start, bool append, std::vector<int>& res) {
  if (s[start] == '[') {
    int end = s.find(']', start + 1);
    for (int cur = start + 1; cur < (int)end; ++cur) {
      int integer = 0;
      while (std::isdigit(s[cur])) {
        integer = integer * 10 + (s[cur] - '0');
        ++cur;
      }
      // Too slow: sscanf(s.c_str() + cur, "%d%n", &integer, &read);
      res.push_back(integer);
    }
    return end + 1;
  }
  if (s[start] == 'c') {
    int end = collect<reverse>(s, start + 7, append, res);
    return collect<reverse>(s, end + 1, append, res) + 1;
  }

  int cnt = 7 + (s[start + 1] == 'h');
  if (append) {
    return collect<reverse>(s, start + cnt, true, res) + 1;
  }

  int pos = res.size();
  int end = collect<reverse>(s, start + cnt, true, res);
  if (s[start + 1] == 'o' || reverse == 0) {
    std::sort(res.begin() + pos, res.end(), std::less<int>());
  } else {
    std::sort(res.begin() + pos, res.end(), std::greater<int>());
  }
  return end + 1;
}

std::vector<int> eval(const std::string& s, bool reverse) {
  std::vector<int> res;
  if (reverse) {
    collect<1>(s, 0, false, res);
  } else {
    collect<0>(s, 0, false, res);
  }
  return res;
}

int main() {
  char xa[1000001];
  char xb[1000001];
  scanf("%s %s", xa, xb);
  std::string a(xa), b(xb);

  bool ok = eval(a, true) == eval(b, true);
  if (ok) ok = eval(a, false) == eval(b, false);

  printf("%sequal\n", ok ? "" : "not ");
}
