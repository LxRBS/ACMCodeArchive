// Author Alexander Rass + TCR of FAU
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define sz(c) int((c).size())
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define pb push_back

const int oo = 0x3f3f3f3f;
const int MAXN = 4024;

int N, R;    // Knotenanzahl und Nummer der Wurzel
vector<pii> from[2*MAXN];    // für jeden Knoten Liste von (Vorgänger, Kosten)
int pred[2*MAXN], label[2*MAXN];
bool del[2*MAXN];
 
bool cycle(int n, int p) {
  if (label[n] == 2) return false;
  if (label[n] == 1) {
    label[n] = -1;
    return true;
  }
  label[n] = 1;
  if (cycle(pred[n], n)) {
    if (label[n] == 1) {
      label[n] = -1;
    } else if (p != -1) {
      label[p] = 2;
    }
    return true;
  } else {
    label[n] = 2;
    return false;
  }
}
int64_t rek() {
  int64_t res = 0;
  pred[R] = -1;
  FOR(i, 0, N) {
    if (i == R || del[i]) continue;
    int m = oo;
    FOR(j, 0, sz(from[i])) if(from[i][j].first != i) m = min(m, from[i][j].second);
    res += m;
    FOR(j, 0, sz(from[i])) if(from[i][j].first != i){
      from[i][j].second -= m;
      if (from[i][j].second == 0) pred[i] = from[i][j].first;
    }
  }
  FOR(i, 0, N) label[i] = 0;
  label[R] = 2;
  FOR(i, 0, N) {
    if (del[i] || label[i] == 2) continue;
    if (cycle(i, -1)) {
      FOR(j, 0, N) {
        if (del[j]) continue;
        if (label[j] == -1) {
          FOR(k, 0, sz(from[j])) if (label[from[j][k].first] != -1)
            from[N].pb(from[j][k]);
          if(sz(from[N]) > N){
              vector<pii> tmp;
              sort(from[N].begin(), from[N].end());
              for(auto it: from[N]){
                  if(!tmp.empty() && tmp[sz(tmp)-1].first == it.first)continue;
                  tmp.pb(it);
              }
              from[N] = tmp;
          }
          from[j].clear();
          del[j] = true;
        } else {
          FOR(k, 0, sz(from[j])) if (label[from[j][k].first] == -1)
            from[j][k].first = N;
        }
      }
      del[N++] = false;
      return res + rek();
    }
  }
  return res;
}
// Berechnet Wert einer minimalen Arboreszenz von R, unter der Annahme Existenz
int64_t min_arbor() { // N, R und from setzten. Algo ändert N und from!!
  FOR(i, 0, N) del[i] = false;
  return rek();
}

int main(){
    cin >> N;
    for(int i = 0; i < MAXN; i++)from[i].clear();
    for(int i = 1; i <= N; i++){
        int fast_time;
        int fast_pred;
        cin >> fast_pred >> fast_time;
        from[i].push_back(make_pair(fast_pred, fast_time));
        for(int j = 0; j <= N; j++){
            int t;
            cin >> t;
            from[i].push_back(make_pair(j,t));
        }
    }
    ++N;
    R = 0;
    cout << min_arbor() << endl;
	return 0;
}
