// [NWERC'18] Hard Drive entropy, by Jan Kuipers

#include <iostream>
#include <set>
#include <string>

using namespace std;

int main() {
  int n,c,b;
  cin >> n >> c >> b;
  set<int> zs;
  for (int i=0; i<b; i++) {
    int z;
    cin >> z;
    z--;
    zs.insert(z);
  }
  string res(n, '0');
  if (c%2 == 1) {
    res[0] = '1';
    c--;
  }
  for (int i=1; c>0; i++) {
    if (res[i-1]=='0' && !zs.count(i)) {
      res[i]='1';
      c-=2;
    }
  }
  cout << res << endl;
  return 0;
}
