#include <unordered_set>
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>

#define assume(reason,condition) assume_((reason), bool(condition), (__LINE__))
void assume_(const char *reason, bool condition, int lineno) {
  if (!condition) {
    printf("assume failed at line %d: %s\n", lineno, reason);
    exit(1);
  }
}

int main(){
  int32_t n; assume("read number of nodes", std::cin>>n);

  std::vector<std::unordered_set<int32_t>> incoming_edges(n);
  std::vector<uint32_t> cardinality(n);

  for (int32_t i = 0; i < n; i++) {
    int64_t value; assume("read weight of node", std::cin>>value);
    assume("read number of incoming edges", std::cin>>cardinality[i]);
    assume("number of incoming edges in bounds",
        (0 <= cardinality[i] and cardinality[i] < n));

    for (int32_t j = 0; j < cardinality[i]; j++) {
      int32_t from; assume("incoming edge", std::cin>>from);
      --from;
      assume("edge source inside bounds", 0 <= from and from < n);
      assume("no self-loops", i != from);
      assume("no repeated edges", not incoming_edges[i].count(from));
      incoming_edges[i].insert(from);
    }
  }

  std::vector<bool> visited(n),in_stack(n);
  for (int32_t i = 0; i < n; i++) {
    if (visited[i]) {
      continue;
    } else {
      visited[i] = true;
    }

    std::stack<int32_t> active;
    active.push(i);
    while (not active.empty()) {
      int32_t x = active.top(); active.pop();
      if (x >= 0) {
        active.push(~x);
        in_stack[x] = true;
        for (int32_t y : incoming_edges[x]) {
          assume("cycles are not allowed", not in_stack[y]);
          if (not visited[y]) {
            visited[y] = true;
            active.push(y);
          }
        }
      } else {
        x = ~x;
        in_stack[x] = false;
      }
    }
  }

  exit(42);
}
