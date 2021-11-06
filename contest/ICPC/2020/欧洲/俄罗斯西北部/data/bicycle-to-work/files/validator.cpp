#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int MAX = 100;
int MAX_T = 1440;

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);
  inf.readInt(0, MAX, "a");
  inf.readEoln();
  inf.readInt(0, MAX, "x");
  inf.readEoln();
  inf.readInt(0, MAX, "b");
  inf.readEoln();
  inf.readInt(0, MAX, "y");
  inf.readEoln();
  inf.readInt(1, MAX_T, "T");
  inf.readEoln();
  inf.readEof();
}