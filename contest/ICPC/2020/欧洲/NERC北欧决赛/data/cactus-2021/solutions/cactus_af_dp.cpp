#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

void relax(pair<int, int> &a, pair<int, int> b) {
    if (a > b)
        a = b;
}

struct Problem {
    vector<vector<vector<pair<int, int>>>> dp;
    vector<vector<vector<vector<pair<int, int>>>>> vdp;
    vector<vector<int>> gr;
    set<pair<int, int>> removed;
    vector<int> used;
    vector<int> path;

    void remove_cycles(int v, int p) {
        used[v] = 1;
        path.push_back(v);
        for (int i = 0; i < gr[v].size(); i++) {
            int u = gr[v][i];
            if (p == u) continue;
            if (used[u] == 1) {
                for (int i = path.size() - 2; i >= 0; i--) {
                    removed.insert({path[i], path[i + 1]});
                    removed.insert({path[i + 1], path[i]});
                    if (path[i] == u) break;
                }
                removed.insert({u, v});
                removed.insert({v, u});
            } else if (used[u] == 0) {
                remove_cycles(u, v);
            }
        }
        path.pop_back();
        used[v] = 2;
    }

    void calc_dp(int v, int p, int root) {
        used[v] = true;
        for (int i = 0; i < gr[v].size(); i++)
            if (gr[v][i] == p) {
                swap(gr[v][i], gr[v].back());
                gr[v].pop_back();
            }
        for (int u : gr[v])
            calc_dp(u, v, root);
        vdp[v].resize(gr[v].size() + 1, vector<vector<pair<int, int>>>(2, vector<pair<int, int>>(2, make_pair(INF, 0))));
        vdp[v][0][0][0] = make_pair(0, 0);
        for (int i = 0; i < gr[v].size(); i++) {
            int u = gr[v][i];
            for (int was_vert = 0; was_vert < 2; was_vert++)
                for (int was_without = 0; was_without < 2; was_without++) {
                    for (int child_is_vert = was_without; child_is_vert < 2; child_is_vert++)
                        for (int started_here = 0; started_here < 2; started_here++) {
                            int is_vert = child_is_vert ^ was_vert;
                            int is_without = !child_is_vert || was_without;
                            relax(vdp[v][i + 1][is_vert][is_without],
                                  make_pair(
                                          vdp[v][i][was_vert][was_without].first + dp[u][child_is_vert][started_here].first,
                                          vdp[v][i][was_vert][was_without].second + dp[u][child_is_vert][started_here].second
                                  )
                            );
                        }
                }
        }
        for (int creates_new = 0; creates_new < 2; creates_new++) {
            for (int is_vert = 0; is_vert < 2; is_vert++)
                for (int was_without = 0; was_without < 2; was_without++) {
                    int is_vert_0 = is_vert ^ creates_new;
                    if (!is_vert_0 && v != root && was_without) continue; // prohibited state
                    int started_here = creates_new & is_vert_0;
                    relax(dp[v][is_vert_0][started_here],
                          make_pair(vdp[v][gr[v].size()][is_vert][was_without].first + creates_new, vdp[v][gr[v].size()][is_vert][was_without].second - is_vert_0));
                }
        }
    }

    int recover_dp(int v, int should_be_vert, int should_start_here, vector<pair<int, int>> &edges, int root) {
        if (dp[v][should_be_vert][should_start_here].first == 0) return -1;
        for (int creates_new = 0; creates_new < 2; creates_new++) {
            for (int is_vert = 0; is_vert < 2; is_vert++)
                for (int was_without = 0; was_without < 2; was_without++) {
                    int is_vert_0 = is_vert ^ creates_new;
                    if (!is_vert_0 && v != root && was_without) continue; // prohibited state
                    int started_here = creates_new & is_vert_0;
                    if (is_vert_0 != should_be_vert || started_here != should_start_here) continue;
                    if (dp[v][is_vert_0][started_here] == make_pair(
                            vdp[v][gr[v].size()][is_vert][was_without].first + creates_new,
                            vdp[v][gr[v].size()][is_vert][was_without].second - is_vert_0)
                    ) {
                        int u = recover_vdp(v, gr[v].size(), is_vert, was_without, edges, root);
                        if (u != -1 && !should_be_vert) edges.emplace_back(u, v);
                        if (should_start_here) return v;
                        if (should_be_vert) return u;
                        return -1;
                    }
                }
        }
        assert(false);
    }

    int recover_vdp(int v, int child, int should_be_vert, int should_be_without, vector<pair<int, int>> &edges, int root) {
        if (child == 0) return -1;
        int i = child - 1;
        int u = gr[v][i];
        for (int was_vert = 0; was_vert < 2; was_vert++)
            for (int was_without = 0; was_without < 2; was_without++) {
                for (int child_is_vert = was_without; child_is_vert < 2; child_is_vert++)
                    for (int started_here = 0; started_here < 2; started_here++) {
                        int is_vert = child_is_vert ^ was_vert;
                        int is_without = !child_is_vert || was_without;
                        if (is_vert != should_be_vert || is_without != should_be_without) continue;
                        if (vdp[v][i + 1][is_vert][is_without] == make_pair(
                                vdp[v][i][was_vert][was_without].first + dp[u][child_is_vert][started_here].first,
                                vdp[v][i][was_vert][was_without].second + dp[u][child_is_vert][started_here].second
                        )) {
                            int w1 = recover_vdp(v, i, was_vert, was_without, edges, root);
                            int w2 = recover_dp(u, child_is_vert, started_here, edges, root);
                            if (w1 != -1 && w2 != -1) {
                                edges.emplace_back(w1, w2);
                                return -1;
                            } else if (w1 != -1) {
                                return w1;
                            } else if (w2 != -1) {
                                return w2;
                            } else {
                                return -1;
                            }
                        }
                    }
            }
        assert(false);
    }

    bool solve() {
        int n, m;
        cin >> n >> m;
        if (n == 0) return false;
        gr.resize(n);
        used.resize(n, 0);
        for (int j = 0; j < m; j++) {
            int s;
            cin >> s;
            vector<int> v;
            while (s --> 0) {
                int u;
                cin >> u;
                u--;
                v.push_back(u);
            }
            for (int i = 0; i + 1 < v.size(); i++) {
                gr[v[i]].push_back(v[i + 1]);
                gr[v[i + 1]].push_back(v[i]);
            }
        }
        remove_cycles(0, -1);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < gr[i].size(); j++)
                if (removed.count(make_pair(i, gr[i][j]))) {
                    swap(gr[i][j], gr[i].back());
                    gr[i].pop_back();
                    j--;
                }
        dp.resize(n, vector<vector<pair<int, int>>>(2, vector<pair<int, int>>(2, make_pair(INF, 0))));
        vdp.resize(n);
        fill(used.begin(), used.end(), 0);
        int result = 0;
        vector<pair<int, int>> ans;
        for (int v = 0; v < n; v++) {
            if (!used[v]) {
                calc_dp(v, -1, v);
                recover_dp(v, 0, 0, ans, v);
                result += dp[v][0][0].first;
            }
        }
        cout << result / 2 << "\n";
        for (auto p : ans) {
            cout << p.first + 1 << " " << p.second + 1 << "\n";
        }
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    while (Problem().solve());
}