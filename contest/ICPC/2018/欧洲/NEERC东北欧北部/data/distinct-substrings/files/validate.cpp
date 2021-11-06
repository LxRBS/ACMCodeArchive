#include "testlib.h"

int main(int argc, char **argv) {
  registerValidation(argc, argv);
  std::string p = inf.readToken("[a-z]{1,1000}");
  inf.readEoln();
  inf.readInt(p.size(), 1000000000, "n");
  inf.readEoln();
  inf.readEof();
}
