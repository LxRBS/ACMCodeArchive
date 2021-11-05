#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MAX_X = 1000000;
const int MAX_N = 1000;
const int MAX_V = 1000;

int testcase_num;
int v_walk, v_metro;
int x_min, y_min, x_max, y_max;
int x_start, y_start;
int x_end, y_end;
vector<int> x_metro, y_metro;

void save(string testcase_id) {
  char filename[100];
  sprintf(filename, "data/secret/%02d_%s.in", testcase_num, testcase_id.c_str());
  cout << "saving: " << filename << endl;
  testcase_num++;
  ofstream out(filename);
  out << v_walk << " " << v_metro << endl;
  out << x_min << " " << y_min << " " << x_max << " " << y_max << endl;
  out << x_start << " " << y_start << endl;
  out << x_end << " " << y_end << endl;
  out << x_metro.size() << endl;
  for (int i=0; i<x_metro.size(); i++) {
    out << x_metro[i] << " " << y_metro[i] << endl;
  }
  out.close();
}

void set_speeds(int v_walk_, int v_metro_) {
  v_walk = v_walk_;
  v_metro = v_metro_;
}

void set_bounds(int x_min_, int y_min_, int x_max_, int y_max_) {
  x_min = x_min_;
  y_min = y_min_;
  x_max = x_max_;
  y_max = y_max_;
}

void set_start_end(int x_start_, int y_start_, int x_end_, int y_end_) {
  x_start = x_start_;
  y_start = y_start_;
  x_end = x_end_;
  y_end = y_end_;
}

void clear_metro() {
  x_metro.clear();
  y_metro.clear();
}

void add_metro(int x, int y) {
  x_metro.push_back(x);
  y_metro.push_back(y);
}

void testcase_no_stations_walk_directly() {
  set_speeds(2, 10);
  set_bounds(-10, -10, 10, 10);
  set_start_end(0, 0, 3, 4);
  clear_metro();
  save("no_stations_walk_directly");
}

void testcase_no_stations_on_boundary() {
  set_speeds(1, 2);
  set_bounds(100, 100, 200, 123);
  set_start_end(100, 100, 200, 100);
  clear_metro();
  save("no_stations_on_boundary");
}

void testcase_no_stations_walk_to_boundary() {
  set_speeds(1, 2);
  set_bounds(-200, -200, -100, -100);
  set_start_end(-199, -199, -199, -101);
  clear_metro();
  save("no_stations_walk_to_boundary");
}

void testcase_no_stations_two_adjacent_boundaries() {
  set_speeds(3, 10);
  set_bounds(-100, -100, 100, 100);
  clear_metro();
  set_start_end(-99, 0, 0, +99);
  save("no_stations_north_west_boundaries");
  set_start_end(-99, 0, 0, -99);
  save("no_stations_south_west_boundaries");
  set_start_end(+99, 0, 0, +99);
  save("no_stations_north_east_boundaries");
  set_start_end(+99, 0, 0, -99);
  save("no_stations_south_east_boundaries");
}

void testcase_no_stations_two_opposite_boundaries() {
  set_speeds(1, 10);
  set_bounds(-50, -50, 50, 50);
  clear_metro();
  set_start_end(-40, 1, 40, -1);
  save("no_stations_east_west_boundaries");
  set_start_end(1, 40, -1, -40);
  save("no_stations_north_south_boundaries");
}

void testcase_via_stations() {
  set_speeds(2, 7);
  set_bounds(-1000, -1000, 1000, 1000);
  set_start_end(0, 0, 0, 70);
  clear_metro();
  add_metro(10, 0);
  add_metro(10, 70);
  save("via_two_stations");
}

void testcase_via_station_and_boundary() {
  set_speeds(10, 100);
  set_bounds(0, 1000, 10000, 2000);
  set_start_end(500, 1500, 9000, 1300);
  clear_metro();
  add_metro(600, 1400);
  save("via_station_and_boundary");
  swap(x_start, x_end);
  swap(y_start, y_end);
  save("via_boundary_and_station");
}

void testcase_start_equals_end() {
  set_speeds(10, 100);
  set_bounds(-12, -34, 56, 78);
  set_start_end(42, 42, 42, 42);
  clear_metro();
  save("no_stations_start_equals_end");
  for (int i=0; i<10; i++) {
    add_metro(random()%10, random()%10);
  }
  save("start_equals_end");
}

void testcase_start_end_on_stations() {
  set_speeds(10, 100);
  set_bounds(-11, -11, 11, 11);
  set_start_end(-10, -10, 10, 10);
  clear_metro();
  add_metro(-10, -10);
  save("start_on_station");
  clear_metro();
  add_metro(10, 10);
  save("end_on_station");
  add_metro(-10, -10);
  save("start_end_on_stations");    
}

void testcase_big_answer() {
  set_speeds(1, 2);
  set_bounds(-MAX_X, -MAX_X, MAX_X, MAX_X);
  int X = MAX_X * 3 / 4;
  set_start_end(-X, X, X, -X);
  clear_metro();
  save("big_answer");
}

int rnd(int X) {
  return random() % (2*X+1) - X;
}

void testcase_many_stations() {
  set_speeds(1, 10);
  set_bounds(-MAX_X, -MAX_X, MAX_X, MAX_X);
  int X = MAX_X / 10;
  set_start_end(-X, -X, X, X);
  clear_metro();
  for (int i=0; i<MAX_N / 2; i++) {
    add_metro(-X + rnd(X), -X + rnd(X));
    add_metro(+X + rnd(X), +X + rnd(X));    
  }
  save("many_stations");
}

void testcase_random_centered() {
  for (int times=0; times<10; times++) {
    set_speeds(1 + random() % 10, 11 + random() % (MAX_V - 10));
    set_bounds(-MAX_X, -MAX_X, MAX_X, MAX_X);
    int X = MAX_X / 10;
    set_start_end(rnd(X), rnd(X), rnd(X), rnd(X));
    clear_metro();
    int n = random() % MAX_N;
    for (int i=0; i<n; i++) {
      add_metro(rnd(X), rnd(X));
    }
    char name[100];
    sprintf(name, "random_centered_n%d", n);
    save(name);
  }
}

void testcase_random_one_boundary() {
  for (int times=0; times<10; times++) {
    set_speeds(1 + random() % 10, 11 + random() % (MAX_V - 10));
    set_bounds(-MAX_X, -MAX_X, MAX_X, MAX_X);
    set_start_end(rnd(MAX_X), rnd(MAX_X), rnd(MAX_X), rnd(MAX_X));
    int close = MAX_X - random() % 100;
    if (random()%2==0) close*=-1;
    int boundary = random() % 4;
    if (boundary == 0) x_start = close;
    if (boundary == 1) x_start = close;
    if (boundary == 2) x_end = close;
    if (boundary == 3) x_end = close;
    clear_metro();
    int n = random() % MAX_N;
    for (int i=0; i<n; i++) {
      add_metro(rnd(MAX_X), rnd(MAX_X));
    }
    char name[100];
    sprintf(name, "random_one_boundary_n%d", n);
    save(name);
  }    
}

void testcase_random_two_boundaries() {
  for (int times=0; times<10; times++) {
    set_speeds(1 + random() % 10, 11 + random() % (MAX_V - 10));
    set_bounds(-MAX_X, -MAX_X, MAX_X, MAX_X);
    set_start_end(rnd(MAX_X), rnd(MAX_X), rnd(MAX_X), rnd(MAX_X));
    int close = MAX_X - random() % 100;
    if (random()%2==0) close*=-1;
    if (random()%2==0) x_start=close; else y_start=close;
    close = MAX_X - random() % 100;
    if (random()%2==0) close*=-1;
    if (random()%2==0) x_end=close; else y_end=close;
    clear_metro();
    int n = random() % MAX_N;
    for (int i=0; i<n; i++) {
      add_metro(rnd(MAX_X), rnd(MAX_X));
    }
    char name[100];
    sprintf(name, "random_two_boundaries_n%d", n);
    save(name);
  }    
}

int main() {
  testcase_no_stations_walk_directly();
  testcase_no_stations_on_boundary();
  testcase_no_stations_walk_to_boundary();
  testcase_no_stations_two_adjacent_boundaries();
  testcase_no_stations_two_opposite_boundaries();
  testcase_via_stations();
  testcase_via_station_and_boundary();
  testcase_start_equals_end();    
  testcase_start_end_on_stations();
  testcase_big_answer();
  testcase_many_stations();
  testcase_random_centered();
  testcase_random_one_boundary();
  testcase_random_two_boundaries();
  return 0;
}
