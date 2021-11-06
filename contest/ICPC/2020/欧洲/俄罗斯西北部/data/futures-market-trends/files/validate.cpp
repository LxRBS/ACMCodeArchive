#include "testlib.h"

int main(int argc, char **argv) {
  registerValidation(argc, argv);
  int n = inf.readInt(3, 3000, "d");
  inf.readSpace();
  inf.readStrictDouble(0.001, 1000, 0, 9, "P");
  inf.readEoln();
  inf.readInts(n, -1000, 1000, "c");
  inf.readEoln();
  inf.readEof();
}
