#include "testlib.h"

int main(int argc, char **argv) {
  registerValidation(argc, argv);
  int P = inf.readInt(1, 50, "P");
  inf.readEoln();
  for (int i = 0; i < P; i++) {
    inf.readLine("[a-zA-Z0-9]{10,50}", "s");
  }
  inf.readEof();
}
