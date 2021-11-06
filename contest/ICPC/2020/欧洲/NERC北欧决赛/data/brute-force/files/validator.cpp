#include "testlib.h"

using namespace std;

int const MAX_D = 10;

int main(int argc, char **argv) {
  registerValidation(argc, argv);
  int d = inf.readInt(1, MAX_D, "d");
  inf.readSpace();
  int n = inf.readInt(1, (1 << d) - 1, "n");
  inf.readEoln();

  map<string, int> passwords;
  for (int i = 0; i < n; i++) {
    string password = inf.readLine(format("[01]{%d}", d), format("s[%d]", i));
    bool hasOne = false;
    for (int j = 0; j < d; j++) {
      hasOne |= password[j] == '1';
    }
    ensuref(hasOne, "Password %d consists of all zeros", i);
    ensuref(passwords.find(password) == passwords.end(), "Password %s appears the second time at %d", password.c_str(), i);
    passwords[password] = i;
  }
  inf.readEof();
  return 0;
}
