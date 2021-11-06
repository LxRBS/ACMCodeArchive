#include <bits/stdc++.h>
#include "validate.h"
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
#define xx first
#define yy second
#define mp make_pair

const ll BORDER = 1000 * 1000 * 1000;
const ll MAX_N = 10 * 1000;

ll read_id = 0;
set<pll> walls_hsort;
set<pll> walls_vsort;

inline ll sign(ll num) {
  return (0 < num) - (num < 0);
}

long long safe_parse(const string& to_parse) {
  try {
    size_t idx;
    ll a = stoll(to_parse, &idx, 10);
    if(idx != to_parse.size())
      wrong_answer("String contains non-digit characters (%lld).\n", read_id);
    return a;
  } catch(const invalid_argument& ia) {
      wrong_answer("String contains non-digit characters (%lld).\n", read_id);
  } catch(const out_of_range& oor) {
      wrong_answer("Integer is out of range (%lld).\n", read_id);
  }
  judge_error("Something went wrong when parsing (%lld): %s.\n", read_id, to_parse);
}

long long safe_author_read_ll() {
  read_id++;
  string to_conv;
  if(!(author_out >> to_conv))
    wrong_answer("Less output than expected (%lld).\n", read_id);
  return safe_parse(to_conv);
}

string safe_author_read_str() {
  read_id++;
  string str;
  if(!(author_out >> str))
    wrong_answer("Less output than expected (%lld).\n", read_id);
  transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str;
}

pll next_hor(pll cur) {
  swap(cur.xx, cur.yy);
  auto it = upper_bound(walls_vsort.begin(), walls_vsort.end(), cur);
  if(it == walls_vsort.end() || (*it).xx != cur.xx)  return mp(BORDER, cur.xx);
  return mp((*it).yy - 1, cur.xx);
}

pll next_roh(pll cur) {
  swap(cur.xx, cur.yy);
  auto it = lower_bound(walls_vsort.begin(), walls_vsort.end(), cur);
  if(it == walls_vsort.begin())
    return mp(-BORDER, cur.xx);
  it--;
  if((*it).xx != cur.xx)  return mp(-BORDER, cur.xx);
  return mp((*it).yy + 1, cur.xx);
}

pll next_ver(pll cur) {
  auto it = upper_bound(walls_hsort.begin(), walls_hsort.end(), cur);
  if(it == walls_hsort.end()|| (*it).xx != cur.xx)  return mp(cur.xx, BORDER);
  return mp(cur.xx, (*it).yy - 1);
}

pll next_rev(pll cur) {
  auto it = lower_bound(walls_hsort.begin(), walls_hsort.end(), cur);
  if(it == walls_hsort.begin())
    return mp(cur.xx, -BORDER);
  it--;
  if((*it).xx != cur.xx)  return mp(cur.xx, -BORDER);
  return mp(cur.xx, (*it).yy + 1);
}

int main(int argc, char **argv) {
  init_io(argc,argv);
  
  string movement, first_auth, first_judge;
  judge_in >> movement;
  judge_ans >> first_judge;
 
  bool differs = false;
  first_auth = safe_author_read_str();
  if(first_judge == "impossible") {
    if(first_auth == first_judge) {
      char foo;
      if(author_out >> foo)
        wrong_answer("More output than expected.\n");
      accept();
    }
    differs = true;
  }
  else if(first_auth == "impossible") {
    wrong_answer("Claimed impossible but judge has a solution.\n");
  }

  ll start_x = safe_parse(first_auth), start_y = safe_author_read_ll();
  if(start_x < -BORDER || BORDER < start_x || start_y < -BORDER || BORDER < start_y)
    wrong_answer("Start out of bounds.\n");
  if(start_x == 0 && start_y == 0)
    wrong_answer("Start on goal.\n");

  ll n = safe_author_read_ll();
  if(n < 0 || MAX_N < n)
    wrong_answer("Invalid number of blocks.\n");
  while(n--) {
    ll x = safe_author_read_ll(), y = safe_author_read_ll();
    if(start_x == x && start_y == y)
      wrong_answer("Block at start space.\n");
    if(x == 0 && y == 0)
      wrong_answer("Block at goal space.\n");
    if(x < -BORDER || BORDER < x || y < -BORDER || BORDER < y)
      wrong_answer("Block out of bounds.\n");
    if(walls_hsort.count(mp(x,y)) != 0)
      wrong_answer("Block at (%lld / %lld) appears more than once.\n", x, y);
    walls_hsort.insert(mp(x,y));
    walls_vsort.insert(mp(y,x));
  }
  char foo;
  if(author_out >> foo)
    wrong_answer("More than expected output.\n");

  pll cur_pos = mp(start_x, start_y);
  pll next_pos;
  for(size_t i = 0; i < movement.size(); i++) {
    char move = movement[i];
    switch(move) {
      case('U'):
      next_pos = next_ver(cur_pos);
      break;
      case('D'):
      next_pos = next_rev(cur_pos);
      break;
      case('L'):
      next_pos = next_roh(cur_pos);
      break;
      case('R'):
      next_pos = next_hor(cur_pos);
      break;
    }
    bool vertical = move == 'U' || move == 'D';
    if(next_pos.xx == 0 && next_pos.yy == 0) {
      if(i == movement.size() - 1) {
        if(differs)
          judge_error("Judge answer is 'impossible' but submission gave valid answer.\n");
        accept();
      }
      wrong_answer("Landed on goal before movement was finished.\n");
    }
    if((vertical && sign(cur_pos.yy) == -sign(next_pos.yy) && next_pos.xx == 0) || (!vertical && sign(cur_pos.xx) == -sign(next_pos.xx) && next_pos.yy == 0)) {
      if(i == movement.size() - 1) {
        if(differs)
          judge_error("Judge answer is 'impossible' but solution gave valid answer.\n");
        accept();
      }
      wrong_answer("Moved over goal before movement was finished.\n");
    }
    if (cur_pos == next_pos) {
      wrong_answer("Nothing happened during movement.\n");
    }
    cur_pos = next_pos;
  }
  
  wrong_answer("Never reached goal.\n");
}
