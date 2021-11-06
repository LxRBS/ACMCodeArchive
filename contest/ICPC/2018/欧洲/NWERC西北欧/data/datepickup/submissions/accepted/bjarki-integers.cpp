#include <bits/stdc++.h>
using namespace std;
template <class T> int size(const T &x) { return x.size(); }
#define rep(i,a,b) for (auto i=(a); i<(b); ++i)
#define iter(it,c) for (auto it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef long long ll;
const int INF = 2147483647;
const ll DINF = 1000000000000000000LL;

ll *dist;
struct cmp {
    bool operator()(int a, int b) {
        return dist[a] != dist[b] ? dist[a] < dist[b] : a < b;
    }
};
ll* dijkstra(int n, int s, const vector<vii> &adj) {
    dist = new ll[n];
    rep(i,0,n) dist[i] = DINF;
    set<int, cmp> pq;
    dist[s] = 0;
    pq.insert(s);
    while (!pq.empty()) {
        int cur = *pq.begin();
        pq.erase(pq.begin());
        rep(i,0,size(adj[cur])) {
            int nxt = adj[cur][i].first;
            ll ndist = dist[cur] + adj[cur][i].second;
            if (ndist < dist[nxt]) {
                pq.erase(nxt);
                dist[nxt] = ndist;
                pq.insert(nxt);
            }
        }
    }
    return dist;
}

void tsort_dfs(int cur, vector<char> &color, const vector<vector<pair<int,ll> > >& adj, stack<int>& res, bool& cyc) {
  color[cur] = 1;
  rep(i,0,size(adj[cur])) {
    int nxt = adj[cur][i].first;
    if (color[nxt] == 0)
      tsort_dfs(nxt, color, adj, res, cyc);
    else if (color[nxt] == 1)
      cyc = true;
    if (cyc) return;
  }
  color[cur] = 2;
  res.push(cur);
}

int main() {
    ll a, b;
    cin >> a >> b;
    int n, m;
    cin >> n >> m;

    vector<vii> adj(n), radj(n);
    rep(i,0,m) {
        int u, v, t;
        cin >> u >> v >> t;
        u--, v--;
        adj[u].push_back(ii(v,t));
        radj[v].push_back(ii(u,t));
    }

    ll *to = dijkstra(n, 0, adj);
    ll *rem = dijkstra(n, n-1, radj);
    ll lo = 0, hi = 1000000000000, ans;
    while (lo <= hi) {
        vi start;
        ll resp = (lo+hi)/2;
        vector<vector<pair<int, ll> > > nadj;
        map<int,int> new_id, old_id;
        rep(i,0,n) {
            if (rem[i] <= resp) {
                int v = size(nadj);
                new_id[i] = v;
                old_id[v] = i;
                nadj.push_back(vector<pair<int, ll> >());
                if (to[i] <= a) {
                    start.push_back(v);
                }
            }
        }
        rep(i,0,n) {
            iter(it,adj[i]) {
                if (rem[it->first] <= resp) {
                    if (it->second + rem[it->first] <= resp) {
                        assert(new_id.find(i) != new_id.end());
                        assert(new_id.find(it->first) != new_id.end());
                        int u = new_id[i],
                            v = new_id[it->first];
                        nadj[u].push_back(make_pair(v, it->second));
                    } else {
                        int u = size(nadj);
                        nadj.push_back(vector<pair<int, ll> >());
                        assert(new_id.find(it->first) != new_id.end());
                        int v = new_id[it->first];
                        ll k = resp - rem[it->first];
                        assert(k <= it->second);
                        nadj[u].push_back(make_pair(v, k));
                        if (to[i] + it->second - k <= a) {
                            start.push_back(u);
                        }
                    }
                }
            }
        }

        set<int> in_start(start.begin(), start.end());

        bool cyc = false;
        stack<int> S;
        vi ord;
        vector<char> color(size(nadj));
        iter(it,start) {
            if (!color[*it]) {
                tsort_dfs(*it, color, nadj, S, cyc);
                if (cyc) break;
            }
        }
        while (!S.empty()) {
            ord.push_back(S.top());
            S.pop();
        }

        if (new_id.find(0) != new_id.end()) {
            cyc = true;
        }

        bool ok = false;
        if (cyc) {
            ok = true;
        } else {
            vector<ll> res(size(nadj));
            vector<bool> path(size(nadj));
            path[new_id[n-1]] = true;
            ll mx = -1;
            for (int i = size(ord)-2; i >= 0; i--) {
                iter(it,nadj[ord[i]]) {
                    if (path[it->first]) {
                        res[ord[i]] = max(res[ord[i]], it->second + res[it->first]);
                        path[ord[i]] = true;
                    }
                }
                if (path[ord[i]] && in_start.find(ord[i]) != in_start.end()) {
                    mx = max(mx, res[ord[i]]);
                }
            }
            if (mx >= b - a) {
                ok = true;
            }
        }

        if (ok) {
            ans = resp;
            hi = resp - 1;
        } else {
            lo = resp + 1;
        }
    }

    cout << ans << endl;
    // cout << setprecision(12) << lo << endl;

    return 0;
}

