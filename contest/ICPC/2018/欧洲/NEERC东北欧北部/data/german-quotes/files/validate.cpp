#include "testlib.h"

int main(int argc, char **argv) {
  registerValidation(argc, argv);
  std::string s = inf.readToken("[<>]{1,254}");
  ensure(s.size() % 2 == 0);
  for (int i = 0; i < (int)s.size(); i += 2) {
    ensure(s[i] == s[i+1]);
  }
  inf.readEoln();
  inf.readEof();
}
