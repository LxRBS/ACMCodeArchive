#include <iostream>
#include <vector>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

int main() {
  int k, n, m;
  cin >> k >> n >> m;

  vvi supply(k, vi(n, 0));
  vvi demand(k, vi(n, 0));
  for (int i = 0; i < m; ++i) {
    int from, to, day, cap;
    cin >> from >> to >> day >> cap;
    --from;
    --to;
    --day;
    demand[from][day] += cap;
    if (day + 1 < n) {
      supply[to][day + 1] += cap;
    }
  }
  for (int i = 0; i < k * n; ++i) {
    int airport, day, num_people;
    cin >> airport >> day >> num_people;
    --airport;
    --day;
    supply[airport][day] += num_people;
  }
  bool optimal = true;
  for (int i = 0; i < k; ++i) {
    int net = 0;
    for (int j = 0; j < n; ++j) {
      net += supply[i][j];
      if (net < demand[i][j]) {
        optimal = false;
      }
      net -= demand[i][j];
    }
  }
  cout << (optimal ? "optimal" : "suboptimal") << endl;
  return 0;
}
