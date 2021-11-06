#include "testlib.h"

using namespace std;

string s;
int ptr = 0;

void parse_expr();

void parse_atom_base() {
  if (s[ptr] == '(') {
    ptr++;
    parse_expr();
    ensure(s[ptr] == ')');
    ptr++;
    return;
  }
  ensure('A' <= s[ptr] && s[ptr] <= 'Z');
  ptr++;
}

void parse_atom() {
  parse_atom_base();
  while (s[ptr] == '+' || s[ptr] == '*' || s[ptr] == '?') {
    ptr++;
  }
}

void parse_term() {
  parse_atom();
  while (s[ptr] == '(' || ('A' <= s[ptr] && s[ptr] <= 'Z')) {
    parse_atom();
  }
}

void parse_expr() {
  parse_term();
  while (s[ptr] == '|') {
    ptr++;
    parse_term();
  }
}

int main(int argc, char **argv) {
  registerValidation(argc, argv);

  s = inf.readLine("[A-Z?+*()\\|]{1,100}", "regex") + '$';
  inf.readEof();

  parse_expr();
  ensure(s[ptr] == '$');
}
