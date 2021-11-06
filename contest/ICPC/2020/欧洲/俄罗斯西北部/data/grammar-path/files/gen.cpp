#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

#define MULTITEST_ENABLED 0

const int MAX_N = 2e5;

struct rule {
  char from;
  string to;
};

struct edge {
  int from, to;
  char c;
  bool operator< (const edge &ed) const {
    if (from != ed.from) return from < ed.from;
    if (to != ed.to) return to < ed.to;
    return c < ed.c;
  }
  bool operator== (const edge &ed) const {
    return from == ed.from && to == ed.to && c == ed.c;
  }
};


struct Test {
  vector<rule> rules;
  vector<edge> graph;
  int s{-1};
  int t{-1};

  int get_n() const {
    int n = 0;
    for (auto o : graph) {
      n = max(n, o.from + 1);
      n = max(n, o.to + 1);
    }
    return n;
  }

  void fix() {
    if (s == -1) s = 0;
    if (t == -1) t = get_n() - 1;
    sort(graph.begin(), graph.end());
    graph.resize(unique(graph.begin(), graph.end()) - graph.begin());
  }

  void shuffle_() {
    fix();

    int n = get_n();
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    shuffle(p.begin(), p.end());

    s = p[s];
    t = p[t];
    for (auto &e : graph) {
      e.from = p[e.from];
      e.to = p[e.to];
    }
    shuffle(graph.begin(), graph.end());
    shuffle(rules.begin(), rules.end());
  }

  void print() {
    fix();
    //shuffle_();
    cout << rules.size() << endl;
    for (auto o : rules) {
      cout << o.from << " -> " << o.to << endl;
    }
    cout << get_n() << " " << graph.size() << " " << s + 1 << " " << t + 1 << endl;
    for (auto o : graph) {
      cout << o.from + 1 << " " << o.to + 1 << " " << o.c << endl;
    }
  }
};

struct Multitest {
  vector<Test> tests;

  void print() {
    if (MULTITEST_ENABLED) {
      cout << tests.size() << endl;
      for (auto &t : tests) {
        t.print();
      }
    } else {
      assert(tests.size() == 1);
      tests[0].print();
    }
  }
};

template<typename T>
T opt_default(string name, T def) {
  return __testlib_opts.count(name) ? opt<T>(name) : def;
}

auto gens = [](){
  map<string, function<Multitest()>> res;

  res["brackets"] = [&](){
    int n = opt<int>("n");
    int b = opt<int>("b");
    
    vector<rule> r;
    r.push_back({'A', "a"});
    r.push_back({'B', "b"});
    r.push_back({'S', "CB"});
    r.push_back({'C', "AS"});
    r.push_back({'S', "SS"});
    r.push_back({'S', "AB"});

    vector<edge> e;
    for (int i = 1; i < n - 1; i++) {
      int any = 0;
      for (int j = min(i, b); j >= 1; j--) {
        int t = rnd.next(3);
        if (t == 1 || !any && j == 1 && b > 1) {
          e.push_back({i - j, i, 'a'});
          any = 1;
        } else 
        if (t == 2) {
          e.push_back({i - j, i, 'b'});
        }
      }
    }
    e.push_back({n - 2, n - 2, 'b'});
    int f = rnd.next(2);
    e.push_back({n - 2, n - 1, 'a' + f});
    if (!f) e.push_back({n - 1, n - 1, 'b'});
    for (int i = 0; i < n - 1; i++) e.push_back({n - 1, i, 'a' + rnd.next(2)});

    Test res{r, e, -1, -1};
    Multitest nres;
    nres.tests.push_back(res);
    return nres;
  };


  return res;
}();

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  string type = opt<string>("type");
  if (gens.count(type)) {
    gens[type]().print();
  } else {
    cerr << "unexpected test type = " << type << endl;
    return 1;
  }
}
