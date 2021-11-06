// [NWERC'18] Balloons, by Jan Kuipers

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> x(n);
  for (int i=0; i<n; i++) {
    cin >> x[i];
  }
  sort(x.begin(), x.end());
  double sol = 1e99;
  for (int i=0; i<n; i++) {
    if (x[i] > i+1) {
      cout << "impossible" << endl;
      return 0;
    }
    sol = min(sol, x[i] / (i+1.0));
  }
  cout << sol << endl;				    
  return 0;
}
