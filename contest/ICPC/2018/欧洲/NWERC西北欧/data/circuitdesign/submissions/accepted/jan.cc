// [NWERC'18] Circuit Board Design, by Jan Kuipers

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> sizes;
vector<vector<int>> conn;
vector<double> x, y;

int calc_size(int i, int prev) {
  sizes[i] = 1;
  for (int j : conn[i]) {
    if (j != prev) {
      sizes[i] += calc_size(j, i);
    }
  }
  return sizes[i];
}

void create(int i, int prev, double fr, double to) {
  double next_fr = fr;
  for (int j : conn[i]) {
    if (j != prev) {
      double next_to = next_fr + 1.0*sizes[j]/(sizes[i]-1) * (to-fr);
      x[j] = x[i] + cos(next_fr);
      y[j] = y[i] + sin(next_fr);
      create(j, i, next_fr, next_to);
      next_fr = next_to;
    }
  }
}

int main() {
  int n;
  cin >> n;
  conn = vector<vector<int>>(n);
  for(int i=0; i<n-1; i++) {
    int a,b;
    cin >> a >> b;
    a--; b--;
    conn[a].push_back(b);
    conn[b].push_back(a);
  }
  
  sizes = vector<int>(n);
  calc_size(0, -1);

  x = y = vector<double>(n);
  create(0, -1, 0.0, M_PI);
  for (int i=0; i<n; i++) {
    cout << setprecision(20) << x[i] << " " << y[i] << endl;
  }

  return 0;
}
