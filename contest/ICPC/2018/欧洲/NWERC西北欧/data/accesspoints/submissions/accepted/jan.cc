// [NWERC'18] Content, by Jan Kuipers

#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct State {
  double sumx,sumx2,n;
  
  double x() { return sumx/n; }

  State operator+= (State a) {
    sumx += a.sumx;
    sumx2 += a.sumx2;
    n += a.n;
    return *this;
  }
};

double solve(vector<int> xs) {
  vector<State> s;
  for (int x : xs) {
    s.push_back((State) {1.0*x, 1.0*x*x, 1.0});
    while (s.size() >= 2 && s[s.size()-1].x() < s[s.size()-2].x()) {
      s[s.size()-2] += s[s.size()-1];
      s.pop_back();
    }
  }
  double res = 0.0;
  for (State x : s) {
    res += x.sumx2 - x.n*x.x()*x.x();
  }
  return res;
}

int main() {
  int n;
  cin >> n;
  vector<int> x(n), y(n);
  for (int i=0; i<n; i++) {
    cin >> x[i] >> y[i];
  }
  cout << setprecision(9) << solve(x) + solve(y) << endl;
  return 0;
}
