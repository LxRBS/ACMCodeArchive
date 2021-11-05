// [NWERC'14] Euclidean TSP, by Jan Kuipers

#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

double n,p,s,v;

double f(double c) {
  return n * pow(log2(n), c*sqrt(2.0)) / (p*1e9) + (1+1/c) * s / v;
}

int main() {
  cin >> n >> p >> s >> v;
  double lo = 0, hi = 1;
  while (f(hi) < f(hi/2)) hi *= 2;
  for (int i=0; i<100; i++) {
    double a = (2*lo+hi)/3;
    double b = (lo+2*hi)/3;
    if (f(a) < f(b)) {
      hi = b;
    } else {
      lo = a;
    }
  }
  cout << setprecision(10) << f(lo) << " " << lo << endl;    
  return 0;
}
