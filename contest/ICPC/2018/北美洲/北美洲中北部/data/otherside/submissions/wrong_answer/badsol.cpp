#include <iostream>
#include <cmath>

using namespace std;

int n,l,t,k;
string solve() {
  if (l < k) return "YES";
  if (n + t < k) return "YES";
  if (n + t == k && l <= 2 * k) return "YES";
  if (l == k && max(n, t) <= k) return "YES";
  return "NO";
}

int main() {
  cin >> n >> l >> t >> k;
  cout << solve() << endl;
  return 0;
}
