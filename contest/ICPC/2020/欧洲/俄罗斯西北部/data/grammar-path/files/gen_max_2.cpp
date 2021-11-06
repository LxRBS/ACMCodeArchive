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
  
  if (new_rule) printf("28\n");
  else printf("27\n");
  printf("A -> x\n");
  printf("B -> y\n");
  printf("C -> z\n");
  printf("S -> DD\n");
  for (char c = 'D'; c < 'R'; c++) {
    printf("%c -> %c%c\n", c, c+1, c+1);
  }
  printf("R -> TT\n");
  for (char c = 'T'; c < 'W'; c++) {
    printf("%c -> %c%c\n", c, c+1, c+1);
  }

  printf("W -> XC\n");
  printf("W -> YZ\n");
  printf("X -> BS\n");
  printf("Y -> AB\n");
  printf("Z -> CA\n");
  if (new_rule) printf("W -> y\n");
  
  printf("26 75 1 1\n");
  for (int i = 1; i <= 25; i++) {
    printf("%d %d %c\n", i, i, i - 1 + 'a');
    printf("%d %d %c\n", i, i + 1, 'y');
    printf("%d %d %c\n", i + 1, i, 'z');
  }
}
