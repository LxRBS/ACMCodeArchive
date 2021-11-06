#include "testlib.h"

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);
  for (int i = 1; i < argc; i++) {
    printf(argv[i]);
    if (i + 1 < argc) {
      putchar(' ');
    } else {
      puts("");
    }
  }
}