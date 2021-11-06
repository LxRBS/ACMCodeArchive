#include <unordered_set>
#include <iostream>
#include <cstdint>
#include <vector>

#define assume(reason,condition) assume_((reason), bool(condition), (__LINE__))
void assume_(const char *reason, bool condition, int lineno) {
  if (!condition) {
    printf("assume failed at line %d: %s\n", lineno, reason);
    exit(1);
  }
}

int main(){
  int32_t n; assume("read number of nodes", std::cin>>n);

  std::vector<std::unordered_set<int32_t>> outgoing_edges(n);
  std::vector<uint32_t> incoming_edges(n);

  for (int32_t i = 0; i < n; i++) {
    int64_t value; assume("read weight of node", std::cin>>value);
    assume("read number of incoming edges", std::cin>>incoming_edges[i]);
    assume("number of incoming edges in bounds",
        (0 <= incoming_edges[i] and incoming_edges[i] < n));

    for (int32_t j = 0; j < incoming_edges[i]; j++) {
      int32_t from; assume("incoming edge", std::cin>>from);
      --from;
      assume("edge source inside bounds", 0 <= from and from < n);
      assume("no self-loops", i != from);
      assume("no repeated edges", not outgoing_edges[from].count(i));
      outgoing_edges[from].insert(i);
    }
  }

  std::vector<int32_t> santa;
  for (int32_t i = 0; i < n; i++) {
    if (incoming_edges[i] == 0) {
      santa.push_back(i);
    }
  }
  for (int32_t i = 0; i < santa.size(); i++) {
    int32_t x = santa[i];
    for (int32_t y : outgoing_edges[x]) {
      assume("validator managed to create a negative number of edges",
          incoming_edges[y] > 0);
      if (not --incoming_edges[y]) {
        santa.push_back(y);
      }
    }
  }

  if (santa.size() == n) {
    exit(42);
  } else {
    printf("cycle detected: only %d of %d nodes reachable\n",
        (int) santa.size(),
        (int) n);
    exit(1);
  }
}
