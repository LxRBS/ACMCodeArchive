#include "testlib.h"

using namespace std;

bool exists(const string &s) {
  int cnt_lower = 0, cnt_upper = 0;

  for (char c : s) {
    if ('a' <= c && c <= 'z') {
      cnt_lower++;
    } else if ('A' <= c && c <= 'Z') {
      cnt_upper++;
    }
  }

  if (s.size() % 2 == 0) {
    return cnt_lower % 2 == 0 && cnt_upper % 2 == 0;
  } 
  return (cnt_lower + cnt_upper) % 2 == 0;
}

int main(int argc, char** argv) {
  registerGen(argc, argv, 1);

  int p = opt<int>("p");
  int minl = opt<int>("minl");
  int maxl = opt<int>("maxl");
  bool yes = opt<bool>("yes");
  bool digits_only = opt<bool>("digits");
  bool letters_only = opt<bool>("letters");
  bool lower_only = opt<bool>("lower");
  bool upper_only = opt<bool>("upper");

  string regex;
  if (digits_only) {
    regex = "[0-9]";
  } else if (letters_only) {
    regex = "[a-zA-Z]";
  } else if (lower_only) {
    regex = "[a-z]";
  } else if (upper_only) {
    regex = "[A-Z]";
  } else {
    regex = "[a-zA-Z0-9]";
  }


  printf("%d\n", p);
  for (int i = 0; i < p; i++) {
    string s;
    do {
      s = rnd.next(regex + "{" + to_string(minl) + "," + to_string(maxl) + "}");
    } while (yes && !exists(s));
    printf("%s\n", s.c_str());
  }
}
