#include "testlib.h"

int main(int argc, char **argv) {
  registerValidation(argc, argv);
  inf.readInt(1, 1000, "s");
  inf.readEoln();
  inf.readEof();
}
