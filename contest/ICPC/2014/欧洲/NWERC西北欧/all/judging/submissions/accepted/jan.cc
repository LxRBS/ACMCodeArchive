// [NWERC'14] Judging, by Jan Kuipers

#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
  int n;
  map<string, int> cnt;
  cin >> n;
  for (int i=0; i<n; i++) {
    string s;
    cin >> s;
    cnt[s]++;
  }
  int res=0;
  for (int i=0; i<n; i++) {
    string s;
    cin >> s;
    if (cnt[s] > 0) {
      cnt[s]--;
      res++;
    }
  }
  cout << res << endl;
  return 0;
}
