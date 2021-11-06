
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

int par[100005];
int find(int x) {
  return par[x] == x ? x : (par[x] = find(par[x]));
}
void merge(int x, int y) {
  par[find(x)] = find(y);
}
int main(int argc, char** argv) {
  input in(cin);
  int n = in.get_int(2, 100000);
  in.get_space();
  int m = in.get_int(1, 100000);
  in.get_eol();
  set<pair<int,int>> s;
  for(int i = 0; i < m; i++) {
    int a = in.get_int(1, n);
    in.get_space();
    int b = in.get_int(1, n);
    in.get_eol();
    fassert(a != b, "edge cannot connect same vertex twice");
    if(a > b) swap(a, b);
    s.insert({a, b});
  }
  fassert(s.size() == m, "non-unique edge detected");
  for(int i = 1; i <= n; i++) par[i] = i;
  for(auto out: s) {
    merge(out.first, out.second);
  }
  set<int> uniquepars;
  for(int i = 1; i <= n; i++) uniquepars.insert(find(i));
  fassert(uniquepars.size() == 1, "graph is not connected");
  in.get_eof();
  fassert(false, "did not do EOF check");
}
