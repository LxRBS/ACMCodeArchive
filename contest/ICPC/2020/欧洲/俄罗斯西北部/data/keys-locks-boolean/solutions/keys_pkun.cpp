#include <iostream>
#include <functional>
#include <string>
#include <cassert>

using namespace std;
constexpr int ALPH = 8;

string cur_token;
string line;
int pos;

void next_token() {
  while (pos < (int)line.size() && line[pos] == ' ') {
    pos++;
  }
  if (pos == (int)line.size()) {
    cur_token = "";
  } else if (line[pos] == '(' || line[pos] == ')') {
    cur_token = line[pos];
    pos++;
  } else {
    cur_token = "";
    while (pos < (int)line.size() && isalpha(line[pos])) {
      cur_token += line[pos++];
    }
  }
}


std::function<bool(int)> read_expr();

std::function<bool(int)> read_var() {
  if (cur_token == "(") {
    next_token();
    auto res = read_expr();
    assert(cur_token == ")");
    next_token();
    return res;
  }
  if (cur_token == "not") {
    next_token();
    auto res = read_var();
    return [=](int x) {
      return !res(x);
    };
  }
  assert(cur_token.size() == 1);
  assert('a' <= cur_token[0] && cur_token[0] <= 'z');
  int id = cur_token[0] - 'a';
  next_token();
  return [=](int x) {
    return (x & (1 << id)) != 0;
  };
}

std::function<bool(int)> read_and() {
  auto res = read_var();
  while (cur_token == "and") {
    next_token();
    auto res2 = read_var();
    res = [=](int x) {
      return res(x) && res2(x);
    };
  }
  return res;
}

std::function<bool(int)> read_expr() {
  auto res = read_and();
  while (cur_token == "or") {
    next_token();
    auto res2 = read_and();
    res = [=](int x) {
      return res(x) || res2(x);
    };
  }
  return res;
}

int main() {
  getline(cin, line);
  next_token();
  auto fun = read_expr();
  assert(pos == (int)line.size());
  vector<bool> result(1 << ALPH);
  for (int i = 0; i < (int)result.size(); i++) {
    result[i] = fun(i);
  }
  vector<string> v;
  v.push_back("+" + string(ALPH, ' ') + "+");
  for (int i = 0; i < (int)result.size(); i++) {
    if (result[i]) {
      for (int j = 0; j < ALPH; j++) {
        if (!result[i | (1 << j)]) {
          printf("IMPOSSIBLE\n");
          return 0;
        }
      }
    } else {
      bool skip = false;
      for (int j = 0; j < ALPH; j++) {
        if (!(i & (1 << j)) && !result[i | (1 << j)]) {
          skip = true;
        }
      }
      if (skip) {
        continue;
      }
      string res;
      for (int j = 0; j < ALPH; j++) {
        if (i & (1 << j)) {
          res += '-';
        } else {
          res += 'a' + j;
        }
      }
      res = "+" + res + "+";
      v.push_back("|" + string(ALPH, ' ') + "|");
      v.push_back(res);
    }
  }

  for (const string& a : v) {
    printf("%s\n", a.c_str());
  }
}
