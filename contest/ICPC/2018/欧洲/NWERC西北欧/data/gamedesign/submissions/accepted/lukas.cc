// Solution by lukasP (Lukáš Poláček)
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#define rep(i, a, b) for (__typeof(b) i = (a); (i) < (b); ++(i))

int main() {
  std::string s;
  std::cin >> s;

  const int sx[] = {0, 1, 0, -1};
  const int sy[] = {1, 0, -1, 0};
  int dir[256];
  dir['U'] = 0;
  dir['R'] = 1;
  dir['D'] = 2;
  dir['L'] = 3;

  int m[] = {0, 0, 0, 0};
  int cx = 0, cy = 0;
  std::vector<std::pair<int, int>> obst;
  bool collision = false;
  for (char x : s) {
    int d = dir[static_cast<int8_t>(x)];
    collision = false;
    for (const auto& pair : obst) {
      int dx = pair.first - cx, dy = pair.second - cy;
      if (dx == 0 || dy == 0) {
        if (dx * sx[d] + dy * sy[d] > 0) {
          cx = pair.first - sx[d];
          cy = pair.second - sy[d];
          collision = true;
          continue;
        }
      }
    }
    if (collision) continue;

    if ((d & 1) == 0) {
      int f = 2 + (m[d] == cy);
      m[d] += sy[d] * f;
      cy = m[d] - sy[d];
    } else {
      int f = 2 + (m[d] == cx);
      m[d] += sx[d] * f;
      cx = m[d] - sx[d];
    }
    obst.emplace_back(cx + sx[d], cy + sy[d]);
  }
  if (collision) {
    printf("impossible\n");
    return 0;
  }

  printf("%d %d\n", -cx, -cy);
  printf("%ld\n", obst.size());
  for (const auto& pair : obst) {
    printf("%d %d\n", pair.first - cx, pair.second - cy);
  }
}
