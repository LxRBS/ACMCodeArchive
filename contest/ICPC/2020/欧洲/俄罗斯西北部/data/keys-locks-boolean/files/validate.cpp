#include "testlib.h"

using namespace std;
constexpr int ALPH = 8;

string cur_token;
string line;
int pos;

void next_token() {
  if (pos == (int)line.size()) {
    cur_token = "";
  } else if (line.substr(pos, 5) == " and ") {
    cur_token = "and";
    pos += 5;
  } else if (line.substr(pos, 4) == " or ") {
    cur_token = "or";
    pos += 4;
  } else if (line.substr(pos, 4) == "not ") {
    cur_token = "not";
    pos += 4;
  } else {
    cur_token = line[pos];
    pos++;
  }
}


void read_expr();

void read_var() {
  if (cur_token == "(") {
    next_token();
    read_expr();
    if (cur_token != ")") {
      quitf(_fail, "Expected ')', found %s", cur_token.c_str());
    }
    next_token();
    return;
  }
  if (cur_token == "not") {
    next_token();
    read_var();
    return;
  }
  if (cur_token.size() != 1 || !('a' <= cur_token[0] && cur_token[0] <= 'h')) {
    quitf(_fail, "Expected variable, found %s", cur_token.c_str());
  }
  next_token();
}

void read_and() {
  read_var();
  while (cur_token == "and") {
    next_token();
    read_var();
  }
}

void read_expr() {
  read_and();
  while (cur_token == "or") {
    next_token();
    read_and();
  }
}

int main(int argc, char **argv) {
  registerValidation(argc, argv);
  line = inf.readLine("[a-z()\\ ]{1,2020}", "expr");
  if (line.size() > 2020) {
    quitf(_fail, "expression should be at most 2020 symbols");
  }
  inf.readEof();
  next_token();
  read_expr();
  if(cur_token != "" || pos != (int)line.size()) {
    quitf(_fail, "'%s' unparsed", (cur_token + line.substr(pos)).c_str());
  }
  return 0;
}
