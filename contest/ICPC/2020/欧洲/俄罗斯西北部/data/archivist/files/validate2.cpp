#include "testlib.h"

int main(int argc, char **argv) {
  registerValidation(argc, argv);
  inf.readInt(1995, 2019, "y");
  inf.readEoln();
  inf.readEof();
}
