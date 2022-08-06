#include <bits/stdc++.h>
using namespace std;

const int N = 100000 + 9;

char s[N];
int ans[N];

template <int N, int Sigma>
struct Palindromic_Tree {
    int tot, top, L, R, pre, suf, s[N * 2];
    struct Node {
        int nxt[Sigma], quick[Sigma], fail, len;
    } node[N * 2];
    struct OP { int p, x; } sk[N * 2];
    void init(int op = 0, int M = N) {
        if (!op) memset(s, -1, sizeof(s));
        else memset(s + L, -1, (R - L + 1) * sizeof(*s));
        memset(node, 0, (tot + 1) * sizeof(Node));
        tot = 1; top = 0; L = M + 1; R = M; pre = suf = 0;
        node[0].fail = node[1].fail = 1; node[1].len = -1;
        fill_n(node[0].quick, Sigma, 1);
        fill_n(node[1].quick, Sigma, 1);
    }
    void push_front(int c) {
        // cout << " push_front: " << c << endl;
        s[--L] = c; OP op =
            {s[L + node[pre].len + 1] == s[L] ? pre : node[pre].quick[c], -pre};
        Node &_p = node[op.p];
        if (_p.nxt[c] == 0) {
            Node &_o = node[++tot];
            op.p = ~op.p; _o.len = _p.len + 2;
            Node &_f = node[_o.fail = node[_p.quick[c]].nxt[c]];
            memcpy(_o.quick, _f.quick, sizeof(_f.quick));
            _o.quick[s[L + _f.len]] = _o.fail;
            _p.nxt[c] = tot;
        }
        Node &_o = node[pre = _p.nxt[c]];
        if (_o.len == R - L + 1) suf = pre;
        sk[++top] = op;
    }
    void push_back(int c) {
        // cout << " push_back: " << c << endl;
        s[++R] = c; OP op =
            {s[R - node[suf].len - 1] == s[R] ? suf : node[suf].quick[c], suf};
        Node &_p = node[op.p];
        if (_p.nxt[c] == 0) {
            Node &_o = node[++tot];
            op.p = ~op.p; _o.len = _p.len + 2;
            Node &_f = node[_o.fail = node[_p.quick[c]].nxt[c]];
            memcpy(_o.quick, _f.quick, sizeof(_f.quick));
            _o.quick[s[R - _f.len]] = _o.fail;
            _p.nxt[c] = tot;
        }
        Node &_o = node[suf = _p.nxt[c]];
        if (_o.len == R - L + 1) pre = suf;
        sk[++top] = op;
    }
    void undo() {
        // cout << " undo: " << endl;
        OP &op = sk[top--];
        if (op.x < 0) {
            Node &_o = node[pre]; pre = -op.x;
            if (_o.len == R - L + 1) suf = _o.fail;
            if (op.p < 0) {
                node[~op.p].nxt[s[L]] = 0; --tot;
                memset(&_o, 0, sizeof(Node));
            }
            s[L++] = -1;
        } else {
            Node &_o = node[suf]; suf = op.x;
            if (_o.len == R - L + 1) pre = _o.fail;
            if (op.p < 0) {
                node[~op.p].nxt[s[R]] = 0; --tot;
                memset(&_o, 0, sizeof(Node));
            }
            s[R--] = -1;
        }
    }
};

Palindromic_Tree<N, 2> pam;

template <int Nv, int Ne> struct Graph {  // "Ne * 2" if edges are undirected.
    int tot, hd[Nv], nxt[Ne], to[Ne];
    void init(int n) { tot = -1; memset(hd, -1, (n + 5) * sizeof(*hd)); }
    void addedge(int u, int v) { nxt[++tot] = hd[u]; to[hd[u] = tot] = v; }
    void addedge2(int u, int v) { addedge(u, v); addedge(v, u); }
};

Graph<N, N * 2> G;

template <int N, int S, typename Graph, Graph &G>
struct Mo_Algorithm_on_Trees {
    struct Query { int u, v, id; };
    vector<Query> Q[N / S + 2];
    int cntb, tot, p[N], dep[N], dfn[N], blg[N], top[N / S + 2];
    void dfs2(int u) {
        // cout << " dfs2: " << u << endl;
        blg[u] = cntb;
        // cout << u << ' ' << cntb << ' ' << p[u] << endl;
        for (int e = G.hd[u]; ~e; e = G.nxt[e]) {
            int v = G.to[e]; if (v != p[u] && !blg[v]) dfs2(v);
        }
    }
    int dfs(int u) {
        // cout << " dfs1: " << u << endl;
        int h = 0; dep[u] = dep[p[u]] + 1;
        for (int e = G.hd[u]; ~e; e = G.nxt[e]) {
            int v = G.to[e]; if (v == p[u]) continue;
            p[v] = u; h = max(h, dfs(v));
        }
        if (++h >= S) {
            dfs2(top[++cntb] = u);
            Q[cntb].clear(); h = 0;
        }
        return h;
    }
    void init(int n) {
        cntb = 0; p[1] = 0;
        memset(blg, 0, (n + 5) * sizeof(*blg));
        if (dfs(1)) dfs2(top[++cntb] = 1);
    }
    vector<int> get_chain(int u, int v) { // require blg[u] == blg[v];
        if (u == v) return {u};
        if (dep[u] > dep[v]) swap(u, v);
        vector<int> pu, pv;
        for (int t = top[blg[u]]; u != t; u = p[u]) pu.push_back(u);
        for (int t = top[blg[v]]; v != t; v = p[v]) pv.push_back(v);
        while (!pu.empty() && pu.back() == pv.back()) {
            pu.pop_back(); pv.pop_back();
        }
        pv.push_back(p[pv.back()]);
        for (; !pv.empty(); pv.pop_back()) pu.push_back(pv.back());
        return pu;
    }
    void add_query(int u, int v, int id) {
        if (blg[u] == blg[v]) {
            auto path = get_chain(u, v);
            for (int v : path) pam.push_back(s[v] - '0');
            ans[id] = pam.tot - 1;
            pam.init(1);
        }
        else {
            if (dep[top[blg[u]]] > dep[top[blg[v]]]) swap(u, v);
            Q[blg[v]].push_back({u, v, id});
        }
    }
    bool dfs3(int u, int p) {
        bool f = dfn[u] == -1; dfn[u] = ++tot;
        for (int e = G.hd[u]; ~e; e = G.nxt[e]) {
            int v = G.to[e]; if (v != p) f |= dfs3(v, u);
        }
        return (dfn[u] = f ? dfn[u] : 0);
    }
    void dfs4(int u, int p, int i) {
        // cout << " dfs4 : " << u << endl;
        pam.push_back(s[u] - '0');
        for (; !Q[i].empty() && u == Q[i].back().u; Q[i].pop_back()) {
            auto path = get_chain(top[i], Q[i].back().v);
            for (int w : path) pam.push_front(s[w] - '0');
            // cout << Q[i].back().id << ' ' << pam.tot - 1 << endl;
            ans[Q[i].back().id] = pam.tot - 1;
            for (int l = path.size(); l; --l) pam.undo();
        }
        for (int e = G.hd[u]; ~e; e = G.nxt[e]) {
            int v = G.to[e];
            if (!Q[i].empty() && v != p && dfn[v]) dfs4(v, u, i);
        }
        pam.undo();
    }
    void calc() {
        for (int i = 1; i <= cntb; ++i) if (p[top[i]]) {
            // cout << "top : " << top[i] << endl;
            for (auto &it : Q[i]) dfn[it.u] = -1;
            tot = 0; dfs3(p[top[i]], top[i]);
            sort(Q[i].begin(), Q[i].end(), [this](const Query &a, const Query &b)
                { return dfn[a.u] > dfn[b.u]; });
            pam.init(1); dfs4(p[top[i]], top[i], i);
        }
    }
};

Mo_Algorithm_on_Trees<N, 700, decltype(G), G> mo;

void solve() {
    int n, q;
    scanf("%d %d", &n, &q);
    scanf("%s", s + 1);
    G.init(n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        G.addedge2(u, v);
    }
    mo.init(n);
    for (int i = 1; i <= q; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        mo.add_query(u, v, i);
    }
    mo.calc();
    for (int i = 1; i <= q; ++i) {
        printf("%d\n", ans[i]);
    }
}

int main() {
    pam.init();
    int T; scanf("%d", &T);
    while (T--) solve();
    return 0;
}