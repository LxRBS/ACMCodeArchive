// [NWERC'18] Brexit Negotiations, by Jan Kuipers

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> len(n);
  vector<int> dep(n);
  vector<vector<int>> conn(n);
  for (int i=0; i<n; i++) {
    int m;
    cin >> len[i] >> m;
    for (int j=0; j<m; j++) {
      int x;
      cin >> x;
      conn[i].push_back(x-1);
      dep[x-1]++;
    }
  }
  priority_queue<pair<int,int>> pq;
  for (int i=0; i<n; i++) {
    if (dep[i] == 0) {
      pq.push(make_pair(-len[i], i));
    }
  }
  int add = n;
  int sol = 0;
  while (!pq.empty()) {
    add--;
    sol = max(sol, -pq.top().first + add);
    int i = pq.top().second;
    pq.pop();
    for (int j : conn[i]) {
      dep[j]--;
      if (dep[j] == 0) {
	pq.push(make_pair(-len[j], j));
      }
    }      
  }
  cout << sol << endl;
  return 0;
}
