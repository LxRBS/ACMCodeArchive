#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

char regex[1000];
int ptr;

void add_cols(vector<string>& v, int left, int right) {
  for (auto &x : v) {
    x.insert(x.begin(), left, ' ');
    x.insert(x.end(), right, ' ');
  }
}

void set(string& s, string_view prefix, string_view suffix) {
  std::copy(prefix.begin(), prefix.end(), s.begin());
  std::copy(suffix.rbegin(), suffix.rend(), s.rbegin());
}

vector<string> get_expr();

vector<string> get_atom_base() {
  if (regex[ptr] == '(') {
    ptr++;
    auto res = get_expr();
    assert(regex[ptr] == ')');
    ptr++;
    return res;
  }
  string lets;
  while (isalpha(regex[ptr])) {
    lets += regex[ptr];
    ptr++;
  }
  if (lets.size() != 1 && (regex[ptr] == '+' || regex[ptr] == '?' || regex[ptr] == '*')) {
    lets.pop_back();
    ptr--;
  }
  vector<string> res(3);
  res[0] = "+" + string(lets.size() + 2, '-') + "+";
  res[1] = "+ " + lets + " +";
  res[2] = "+" + string(lets.size() + 2, '-') + "+";
  return res;
}

vector<string> get_atom() {
  vector<string> res = get_atom_base();

  while (regex[ptr] == '+' || regex[ptr] == '*' || regex[ptr] == '?') {
    add_cols(res, 3, 3);
    set(res[1], "+->", "->+");
    if (regex[ptr] == '+' || regex[ptr] == '*') {
      for (int i = 2; i < (int) res.size(); i++) {
        set(res[i], "|  ", "  |");
      }
      res.emplace_back(string("| ") + string(res[0].size() - 3, ' ') + "|");
      res.emplace_back(string("+<") + string(res[0].size() - 3, '-') + "+");
    }
    if (regex[ptr] == '?' || regex[ptr] == '*') {
      set(res[0], "|", "|");
      res.insert(res.begin(), string("|") + string(res[0].size() - 3, ' ') + " |");
      res.insert(res.begin(), string("+") + string(res[0].size() - 3, '-') + ">+");
      res.insert(res.begin(), string(res[0].size(), ' '));
    }
    ptr++;
  }
  return res;
}

vector<string> get_term() {
  vector<string> res;
  while (regex[ptr] == '(' || isalpha(regex[ptr])) {
    auto atom = get_atom();
    if (!res.empty()) {
      while (res.size() < atom.size()) {
        res.emplace_back(res[0].size(), ' ');
      }
      add_cols(res, 0, 2);
      set(res[1], "", "->");
      for (int i = 0; i < (int) atom.size(); i++) {
        res[i] += atom[i];
      }
      for (int i = atom.size(); i < (int) res.size(); i++) {
        res[i].insert(res[i].end(), atom[0].size(), ' ');
      }
    } else {
      res = std::move(atom);
    }
  }
  return res;
}

vector<string> get_expr() {
  vector<vector<string>> terms;
  terms.push_back(get_term());
  while (regex[ptr] == '|') {
    ptr++;
    terms.push_back(get_term());
  }
  if (terms.size() == 1) {
    return std::move(terms[0]);
  }
  int length = 0;
  for (const auto &x : terms) {
    length = max(length, (int)x[0].size());
  }
  vector<string> res;
  for (int i = 0; i < (int)terms.size(); i++) {
    if (!res.empty()) {
      res.emplace_back("|" + string(res[0].size()-2, ' ') + "|");
    }
    auto &x = terms[i];
    int os = x[0].size();
    add_cols(x, 3, length - (int) x[0].size() + 3);
    fill(x[1].begin() + os + 3, x[1].end(), '-');
    set(x[1], "+->", "->+");
    if (i != 0) {
      set(x[0], "|", "|");
    }
    if (i != (int)terms.size() - 1) {
      for (int row = 2; row < (int) x.size(); row++) {
        set(x[row], "|", "|");
      }
    }
    for (auto &s : x) {
      res.emplace_back(std::move(s));
    }
  }
  return res;
}

vector<string> get_input() {
  auto res = get_expr();
  add_cols(res, 3, 3);
  set(res[1], "S->", "->F");
  return res;
}

int main() {
  while (scanf("%s", regex) == 1) {
    ptr = 0;
    auto result = get_input();
    fprintf(stderr, "not done = |%s|", regex + ptr);
    assert(regex[ptr] == '\0');
    printf("%d %d\n", (int)result.size(), (int)result[0].size());
    for (const auto& x : result) {
      printf("%s\n", x.c_str());
    }
  }
}
