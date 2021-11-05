#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int max_switches = 500000;
const long long max_balls = 1000000000000000000LL;

int testcase_num;
long long balls;
int switches;
string state;
vector<int> left_switch, right_switch;

void save(string testcase_id) {
  char filename[100];
  sprintf(filename, "data/secret/%02d_%s.in", testcase_num, testcase_id.c_str());
  cout << "saving: " << filename << endl;
  testcase_num++;
  ofstream out(filename);
  out << balls << " " << switches << endl;
  for (int i=0; i<switches; i++) {
    out << state[i] << " " << left_switch[i] << " " << right_switch[i] << endl;
  }
  out.close();
}

void set_size(long long _balls, int _switches) {
  balls = _balls;
  switches = _switches;
  state = string(switches, '?');
  left_switch = right_switch = vector<int>(switches, -1);
}

void update(vector<int> perm) {
  string new_state = state;
  vector<int> new_left_switch = left_switch;
  vector<int> new_right_switch = right_switch;
  for (int i=0; i<switches; i++) {
    new_state[perm[i]] = state[i];
    new_left_switch[perm[i]] =
      (left_switch[i] == 0 ? 0 : perm[left_switch[i] - 1] + 1);
    new_right_switch[perm[i]] =
      (right_switch[i] == 0 ? 0 : perm[right_switch[i] - 1] + 1);
  }
  state = new_state;
  left_switch = new_left_switch;
  right_switch = new_right_switch;
}

void shuffle() {
  vector<int> perm;
  for (int i=0; i<switches; i++) {
    perm.push_back(i);
  }
  random_shuffle(perm.begin() + 1, perm.end()); // fixate 0 (entrance)
  update(perm);
}

void reverse() {
  vector<int> perm;
  for (int i=0; i<switches; i++) {
    perm.push_back(i);
  }
  reverse(perm.begin() + 1, perm.end()); // fixate 0 (entrance)
  update(perm);
}

void testcase_left_first() {
  set_size(4, 3);
  state = "LLL";
  left_switch[0] = 2; right_switch[0] = 3;
  left_switch[1] = 3; right_switch[1] = 0;
  left_switch[2] = 0; right_switch[2] = 0;
  save("left_first");
}

void testcase_right_first() {
  set_size(4, 3);
  state = "LLL";
  left_switch[0] = 3; right_switch[0] = 2;
  left_switch[1] = 3; right_switch[1] = 0;
  left_switch[2] = 0; right_switch[2] = 0;
  save("right_first");
}

void testcase_multi_start() {
  set_size(1, 3);
  state = "LLL";
  left_switch[0] = 3; right_switch[0] = 0;
  left_switch[1] = 3; right_switch[1] = 0;
  left_switch[2] = 0; right_switch[2] = 0;
  save("multi_start");
}

void create_line(long long balls, int switches) {
  set_size(balls, switches);
  for (int i=0; i<switches; i++) {
    state[i] = (random()%2 ? 'L' : 'R');
    left_switch[i] = (i+2 <= switches ? i+2 : 0);
    right_switch[i] = left_switch[i];
  }
}

void testcase_small_lines() {
  create_line(91, 25);
  save("small_lines_ordered");
  reverse();
  save("small_lines_reversed");
  shuffle();
  save("small_lines_shuffled");
}

void testcase_big_lines() {
  create_line(max_balls - 11, max_switches);
  save("big_lines_ordered");
  reverse();
  save("big_lines_reversed");
  shuffle();
  save("big_lines_shuffled");
}

void create_ladder(long long balls, int switches) {
  set_size(balls, switches);
  for (int i=0; i<switches; i++) {
    state[i] = (random()%2 ? 'L' : 'R');
    left_switch[i] = (i+2 <= switches ? i+2 : 0);
    right_switch[i] = (i+3 <= switches ? i+3 : 0);
  }
}

void testcase_small_ladders() {
  create_ladder(42, 10);
  save("small_ladder_ordered");
  reverse();
  save("small_ladder_reversed");
  shuffle();
  save("small_ladder_shuffled");
}

void testcase_big_ladders() {
  create_ladder(max_balls, max_switches);
  save("big_ladder_ordered");
  reverse();
  save("big_ladder_reversed");
  shuffle();
  save("big_ladder_shuffled");
}

void create_tree(long long balls, int switches) {
  set_size(balls, switches);
  for (int i=0; i<switches; i++) {
    state[i] = (random()%2 ? 'L' : 'R');
    left_switch[i] = (2*(i+1) <= switches ? 2*(i+1) : 0);
    right_switch[i] = (2*(i+1)+1 <= switches ? 2*(i+1)+1 : 0);
  }
}

void testcase_small_trees() {
  create_tree(365, 31);
  save("small_tree_ordered");
  reverse();
  save("small_tree_reversed");
  shuffle();
  save("small_tree_shuffled");
}

void testcase_big_trees() {
  create_tree(max_balls - 17, max_switches);
  save("big_tree_ordered");
  reverse();
  save("big_tree_reversed");
  shuffle();
  save("big_tree_shuffled");
}

void testcase_disconnected() {
  create_ladder(99, 99);
  shuffle();
  left_switch[0] = right_switch[0] = 0;
  save("disconnected");
}

void testcase_all_to_one() {
  set_size(max_balls - 41, max_switches);
  for (int i=0; i<switches; i++) {
    state[i] = (random()%2 ? 'L' : 'R');
    left_switch[i] = switches;
    right_switch[i] = switches;
  }
  left_switch[switches-1] = 0;
  right_switch[switches-1] = 0;
  save("all_to_one");
}

void create_random(long long balls, int switches) {
  set_size(balls, switches);
  for (int i=0; i<switches; i++) {
    state[i] = (random()%2 ? 'L' : 'R');
    left_switch[i] = i + 2 + random() % 10;
    if (left_switch[i] > switches) left_switch[i] = 0;
    right_switch[i] = i + 2 + random() % 10;
    if (right_switch[i] > switches) right_switch[i] = 0;
  }
  shuffle();
}

void testcase_randoms() {
  int exp = 2;
  for (int switches = 100; switches <= max_switches; switches *= 10) {
    create_random(max_balls - random()%100, switches - random()%100);
    char filename[100];
    sprintf(filename, "random_1e%d", exp);
    save(filename);
    exp++;
  }
}

void testcase_zero_balls() {
  create_random(0, switches - random()%100);
  save("zero_balls");
}

void testcase_asymmetric_parts() {
  int switches = max_switches;
  set_size(max_balls - 71, switches);
  int i=0;
  while (i<switches-1) {
    int stop;
    stop = min(switches-1,i+63);
    for (; i<stop; ++i) {
      state[i] = (random()%2 ? 'L' : 'R');
      if (random()%2 == 0) {
        left_switch[i] = i+2;
        right_switch[i] = stop+1;
      } else {
        left_switch[i] = stop+1;
        right_switch[i] = i+2;
      }
    }
    stop = min(switches-1,i+5);
    for (; i<stop; ++i) {
      state[i] = (random()%2 ? 'L' : 'R');
      if (random()%2 == 0) {
        left_switch[i] = i+2;
        right_switch[i] = stop+1;
      } else {
        left_switch[i] = stop+1;
        right_switch[i] = i+2;
      }
    }
  }
  state[i] = (random()%2 ? 'L' : 'R');
  left_switch[i] = 0;
  right_switch[i] = 0;

  save("asymmetric_parts_ordered");
  reverse();
  save("asymmetric_parts_reversed");
  shuffle();
  save("asymmetric_parts_shuffled");
}

int main() {
  testcase_num = 1;
  testcase_left_first();
  testcase_right_first();
  testcase_multi_start();
  testcase_small_lines();
  testcase_small_ladders();
  testcase_small_trees();
  testcase_disconnected();
  testcase_randoms();
  testcase_all_to_one();
  testcase_big_lines();
  testcase_big_ladders();
  testcase_big_trees();
  testcase_zero_balls();
  testcase_asymmetric_parts();
  return 0;
}
