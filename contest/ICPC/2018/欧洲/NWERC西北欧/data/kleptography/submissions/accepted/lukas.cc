//Solution by lukasP (Lukáš Poláček)
#include <cstdio>

int main() {
  char cypher[101];
  char text[101];
  int n, m;
  scanf("%d %d", &n, &m);
  scanf("%s %s", &text[m - n], cypher);
  text[m] = 0;

  for (int i = m - 1; i >= n; --i) {
    text[i - n] = (cypher[i] - text[i] + 26) % 26 + 'a';
  }
  printf("%s\n", text);
}
