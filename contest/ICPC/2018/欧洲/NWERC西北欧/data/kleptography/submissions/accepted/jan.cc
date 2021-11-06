// [NWERC'18] Auto Key, by Jan Kuipers

#include <iostream>
#include <string>

using namespace std;

int main() {
  int n,m;
  string k,s;
  cin >> n >> m >> k >> s;
  for (int i=0; i<n; i++) {
    char next = k[n-1-i];
    for (int j=m-1-i; j>=0; j-=n) {
      char tmp = 'a' + (26+s[j]-next)%26;
      s[j] = next;
      next = tmp;
    }
  }
  cout << s << endl;
  return 0;
}
