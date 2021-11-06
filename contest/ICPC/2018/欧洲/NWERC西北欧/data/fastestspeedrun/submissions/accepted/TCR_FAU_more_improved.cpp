// Author Alexander Rass + TCR of FAU
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define sz(c) int((c).size())
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define pb push_back

const int oo = 0x3f3f3f3f;
const int MAXN = 4024;

int N, R;    // Number of nodeds and id of root
vector<pii> from[MAXN];    // for each node a list of pairs (predecessor, cost)
int pred[MAXN], label[MAXN], node[MAXN];
int helper[MAXN];
int get_node(int n){
  return ((node[n] == n)?n:(node[n]=get_node(node[n])));
}
int update_node(int n){
    int m = oo;
    for(auto ed: from[n]) m = min(m, ed.second);
    FOR(j, 0, sz(from[n])) {
        from[n][j].second -= m;
        if (from[n][j].second == 0) pred[n] = from[n][j].first;
    }
    return m;
}
int64_t cycle(vector<int> & active, int n, int& cycleend) {
  n = get_node(n);
  if (label[n] == 1) return false;
  if (label[n] == 2) {
    cycleend = n;
    return 0;
  }
  active.push_back(n);
  label[n] = 2;
  auto res = cycle(active, pred[n], cycleend);
  if(cycleend == n){
    int F = find(active.begin(), active.end(), n) - active.begin();
    vector<int> todo(active.begin() + F, active.end());
    active.resize(F);
    vector<pair<int, int> > newfrom;
    for(auto i: todo) node[i] = n;
    for(auto i: todo)for(auto& ed: from[i])helper[ed.first = get_node(ed.first)] = ed.second;
    for(auto i: todo)for(auto ed: from[i])helper[ed.first] = min(ed.second, helper[ed.first]);
    for(auto i: todo)for(auto ed: from[i]){
        if(helper[ed.first] != oo && ed.first != n){
            newfrom.push_back(make_pair(ed.first,helper[ed.first]));
            helper[ed.first] = oo;
        }
    }
    from[n] = newfrom;
    res += update_node(n);
    label[n] = 0;
    cycleend = -1;
    return cycle(active,n,cycleend) + res;
  }
  if(cycleend == -1){
    active.pop_back();
    label[n] = 1;
  }
  return res;
}
// Calculates value of minimal arborescence from R, assuming it exists
int64_t min_arbor() { // N, R und from has to be initialized. Algo changes from!!
  int64_t res = 0;
  FOR(i, 0, N) {
    node[i] = i;
    if (i != R) res += update_node(i);
  }
  FOR(i, 0, N) label[i] = (i==R);
  FOR(i, 0, N) {
    if (label[i] == 1 || get_node(i) != i) continue;
    vector<int> active;
    int cycleend = -1;
    res += cycle(active, i, cycleend);
  }
  return res;
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
