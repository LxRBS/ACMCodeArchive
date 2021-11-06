#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>
#include <set>
#include <fstream>
#include <sstream>
#include <unordered_set>

using namespace std;

void fail(const char* msg = NULL) {
  if (msg) {
    cout << "fail: " << msg << endl;
  } else {
    cout << "fail" << endl;
  }
  exit(1);
}

void fassert(bool cond, const char* msg = NULL) {
  if (!cond) {
    fail(msg);
  }
}

struct input {
  input(FILE* f) : uch(-2), fin(f), sin(NULL) {
  }
  input(istream& in) : uch(-2), fin(NULL), sin(&in) {
  }

  int get() {
    if (uch != -2) {
      int ch = uch;
      uch = -2;
      return ch;
    } else if (fin) {
      return fgetc(fin);
    }
    return sin->get();
  }

  void unget(int ch) {
    uch = ch;
  }

  char get_char() {
    int ch = get();
    if (ch == -1) {
      fail("expected char");
    } else if (ch != '\n' && (ch < 32 || 126 < ch)) {
      fail("expected printable ascii");
    }
    return ch;
  }

  void get_eof() {
    fassert(get() == -1, "expected eof");
    exit(42);
  }

 void get_eol() {
    fassert(get() == '\n', "expected eol");
  }

  void get_space() {
    fassert(get() == ' ', "expected space");
  }

  void get_spaces() {
    int ch;
    get_space();
    for (ch = get(); ch == ' '; ch = get());
    unget(ch);
  }

 string get_token() {
    int ch;
    string res;
    for (ch = get(); ch != -1 && ch != '\n' && ch != ' '; ch = get()) {
      res += (char)ch;
    }
    fassert(!res.empty(), "expected token");
    unget(ch);
    return res;
  }

 long long get_int(long long min, long long max) {
    string tok = get_token();
    long long res = atoll(tok.c_str());
    fassert(tok == to_string(res), "expected int");
    fassert(min <= res && res <= max, "int out of range");
    return res;
  }

  long double get_float(long double min, long double max, int prec) {
    string tok = get_token();
    long double ret = strtold(tok.c_str(), NULL);
    fassert(min <= ret && ret <= max, "float out of range");
    // if prec is zero, don't do any check
    if(prec == 0) return ret;
    fassert(prec > 0, "precision must be positive");
    long double t = ret;
    while(prec--) {
      t *= 10;
    }
    t = abs(t);
    const long double EPS = 1e-9;
    fassert(t - (long long)t <= EPS || (long long)t - t <= EPS, "wrong precision");
    return ret;
  }

  string get_line(int min_length, int max_length) {
    int ch;
    string res;
    for (ch = get(); ch != -1 && ch != '\n'; ch = get()) {
      res += (char)ch;
      fassert(res.size() <= max_length, "line too long");
    }
    fassert(min_length <= res.size(), "line too short");
    unget(ch);
    return res;
  }

  int uch;
  FILE* fin;
  istream* sin;
};

int main(int argc, char** argv) {
  input in(cin);
  int n = in.get_int(1, 100000);
  in.get_eol();
  while(n--) {
    long double a = in.get_float(0, 1000, 6);
    fassert(a > 0, "a must be positive");
    in.get_space();
    long double b = in.get_float(0, 100, 6);
    in.get_space();
    long double c = in.get_float(0, 6.2831853071795862, 6);
    in.get_eol();
  }
  in.get_eof();
  fassert(false, "did not do EOF check");
}
