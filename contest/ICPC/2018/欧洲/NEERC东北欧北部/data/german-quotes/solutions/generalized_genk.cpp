/**
 *    author:  tourist
 *    created: 19.10.2018 16:21:42       
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string s;
  cin >> s;
  int len = (int) s.size();
  string res(len / 2, '.');
  vector<int> st;
  for (int i = 0; i < len; i += 2) {
    if (st.empty()) {
      st.push_back(i);
      continue;
    }
    if (s[i] == s[st.back()]) {
      st.push_back(i);
    } else {
      res[st.back() / 2] = '[';
      res[i / 2] = ']';
      st.pop_back();
    }
  }
  if (!st.empty()) {
    cout << "Keine Loesung" << '\n';
    return 0;
  }
  cout << res << '\n';
  return 0;
}
