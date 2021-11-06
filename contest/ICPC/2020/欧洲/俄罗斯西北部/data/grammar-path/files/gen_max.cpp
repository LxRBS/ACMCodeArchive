#include "testlib.h"
#include <cstdio>
using namespace std;

template<typename T>
T opt_default(string name, T def) {
  return __testlib_opts.count(name) ? opt<T>(name) : def;
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int new_rule = opt_default<int>("last_rule", 0);
  
  if (new_rule) printf("50\n");
  else printf("49\n");
  printf("A -> x\n");
  printf("B -> y\n");
  printf("C -> z\n");
  printf("S -> DD\n");
  for (char c = 'D'; c < 'R'; c++) {
    printf("%c -> %c%c\n", c, c+1, c+1);
  }
  printf("R -> TT\n");
  printf("T -> UV\n");
  printf("T -> XY\n");
  printf("U -> ZB\n");
  printf("V -> SW\n");
  printf("W -> CZ\n");
  printf("X -> AB\n");
  printf("Y -> CA\n");
  for (char c = 'a'; c < 'x'; c++) {
    printf("Z -> %c\n", c);
  }
  if (new_rule) printf("T -> y\n");
  
  printf("24 69 1 1\n");
  for (int i = 1; i <= 23; i++) {
    printf("%d %d %c\n", i, i, i + 'a');
    printf("%d %d %c\n", i, i + 1, 'y');
    printf("%d %d %c\n", i + 1, i, 'z');
  }
}
