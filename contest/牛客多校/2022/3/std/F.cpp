#include<bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, m, q, q_u[N], q_v[N];

int dfn[N], low[N], bcc_cnt, tim;
int stk[N], tot;
vector<int> G[N], T[N];
void tarjan(int x, int fa) {
    dfn[x] = low[x] = ++tim;
    stk[++tot] = x;
    for (int y : G[x])
        if (y != fa) {
            if (!dfn[y]) {
                tarjan(y, x);
                low[x] = min(low[x], low[y]);
                if (low[y] >= dfn[x]){
                    bcc_cnt++;
                    while (stk[tot] != y) {
                        int u = n + bcc_cnt, v = stk[tot--];
                        T[u].push_back(v), T[v].push_back(u);
                    }
                    int u = n + bcc_cnt, v = stk[tot--];
                    T[u].push_back(v), T[v].push_back(u);
                    T[x].push_back(u), T[u].push_back(x);
                }
            }
            else
                low[x] = min(low[x], dfn[y]);
        }
}
void prt_bad() {
    for (int i = 1; i <= q; i++) cout << "NO" << endl;
}
int main() {
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        G[u].push_back(v), G[v].push_back(u);
    }
    
    cin >> q;
    for (int i = 1; i <= q; i++) cin >> q_u[i] >> q_v[i];
    if (n == 2) {
        for (int i = 1; i <= q; i++) cout << "YES" << endl;
        return 0;
    }
    bool is_first = true, bad = false;
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            if (is_first) {
                is_first = false;
                tarjan(i, 0);
            } else {
                bad = true;
                break;
            }
        }
    }
    cerr << "hello?\n";
    if (bad) {
        prt_bad();
        return 0;
    }
    if (bcc_cnt == 1) {
        for (int i = 1; i <= q; i++) cout << "YES" << endl;
        return 0;
    }
    
    vector<int> cnt(bcc_cnt + 1);
    for (int i = 1; i <= n; i++) {
        assert(T[i].size());
        if (T[i].size() > 2) {
            bad = true;
            break;
        }
        if (T[i].size() == 1) continue;
        for (int u : T[i]) {
            assert(u > n);
            cnt[u - n]++;
        }
    }
    vector<int> good_bcc;
    for (int i = 1; i <= bcc_cnt; i++) {
        if (cnt[i] > 2) {
            bad = true;
            break;
        }
        if (cnt[i] == 1) good_bcc.push_back(i);
    }
    if (bad) {
        prt_bad();
        return 0;
    }
    
    assert(good_bcc.size() == 2);
    vector<int> tag(n + 1);
    for (int i = 1; i <= n; i++) {
        tag[i] = 0;
        if (T[i].size() == 1) {
            int x = T[i].front() - n;
            if (x == good_bcc[0]) tag[i] = 1;
            if (x == good_bcc[1]) tag[i] = 2;
        }
    }
    for (int i = 1; i <= q; i++) {
        int a = tag[q_u[i]], b = tag[q_v[i]];
        if (a && b && a != b) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}