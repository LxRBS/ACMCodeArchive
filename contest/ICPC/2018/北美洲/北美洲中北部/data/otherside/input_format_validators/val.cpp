#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <set>

using namespace std;
int n=0,l=0,t=0,k=0;

int main() {
  cin >> n >> l >> t >> k;
  if (n < 0 || n > 1000000) cout << "BAD W";
  if (l < 0 || l > 1000000) cout << "BAD S";
  if (t < 0 || t > 1000000) cout << "BAD C";
  if (k < 0 || k > 1000000) cout << "BAD K";
  if (max(t, max(n,l)) == 0) cout << "BAD max";
  return 42;
}
