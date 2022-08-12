#include <bits/stdc++.h>
using namespace std;
#define AC exit(0)
#define WA exit(1)
constexpr int N = 1e5 + 5;
int n, a[N], m;
vector<int> buc[N];
void ensure(bool judge) {if(!judge) WA;}
int main() {
  ifstream fin("input");
  ifstream fout("user_output");
  fin >> n;
  ensure(1 <= n && n <= 100000);
  for(int i = 1; i <= n; i++) {
    fin >> a[i];
    ensure(2 <= a[i] && a[i] <= 200000);
  }
  fout >> m;
  ensure(1 <= m && m <= 1000000);
  for(int i = 0, x; i < m; i++) {
    fout >> x;
    ensure(1 <= x && x <= n);
    buc[x].push_back(i);
  }
  for(int i = 1; i <= n; i++) {
    if(buc[i].empty()) WA;
    for(int j = 0; j < (int) buc[i].size(); j++) {
      int nxt = (j + 1) % buc[i].size();
      int P = buc[i][j], Q = buc[i][nxt];
      if(Q <= P) Q += m;
      if(Q - P > a[i]) WA;
    }
  }
  AC;
}
