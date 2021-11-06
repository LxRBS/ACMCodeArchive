#include <bits/stdc++.h>

#define mp make_pair
#define mt make_tuple
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define for1(i, n) for (int i = 1; i <= (int)(n); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define fore(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)

using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpi;
typedef vector<vi> vvi;
typedef long long i64;
typedef vector<i64> vi64;
typedef vector<vi64> vvi64;
typedef pair<i64, i64> pi64;
typedef double ld;

template<class T> bool uin(T &a, T b) { return a > b ? (a = b, true) : false; }
template<class T> bool uax(T &a, T b) { return a < b ? (a = b, true) : false; }

typedef vi64 vlong;

const i64 P = 1000000000;

void norm(vlong &a) {
    a.pb(0);
    forn(i, a.size() - 1) {
        a[i + 1] += a[i] / P;
        a[i] %= P;
    }
    while (!a.empty() && !a.back()) a.pop_back();
}

vlong operator+(const vlong &a, const vlong &b) {
    vlong c(max(a.size(), b.size()) + 1);
    forn(i, c.size()) {
        if (i < a.size()) c[i] += a[i];
        if (i < b.size()) c[i] += b[i];
    }
    norm(c);
    return c;
}

bool cmp(const vlong &a, const vlong &b) {
    if (a.size() != b.size()) return a.size() < b.size();
    ford(i, a.size()) if (a[i] != b[i]) return a[i] < b[i];
    return false;
}

const int maxp = 110;
vi nonT[26];
pii pr[maxp];
int pl[maxp];
vi occT[26][2];

const int maxn = 30;
vlong dist[maxn][maxn][26];
int vis[maxn][maxn][26];

struct TTriple {
    int u, v, c;

    auto key() const {
        return(mt(u, v, c));
    }

    bool operator<(const TTriple &r) const {
        return key() < r.key();
    }
};

typedef pair<vlong, TTriple> TItem;

TItem item(TTriple t) {
    return mp(dist[t.u][t.v][t.c], t);
}

auto pcmp = [](const TItem &a, const TItem &b) {
    if (cmp(a.fi, b.fi)) return true;
    if (cmp(b.fi, a.fi)) return false;
    return a.se < b.se;
};

void print(vlong x) {
    cout << x.back();
    ford(i, x.size() - 1) cout << setfill('0') << setw(9) << x[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);
    cout << fixed;
#ifdef LOCAL_DEFINE
    freopen("input.txt", "rt", stdin);
#endif

    int p;
    cin >> p;
    forn(i, p) {
        char c;
        string trash, t;
        cin >> c >> trash >> t;
        if (t.size() == 1) nonT[t[0] - 'a'].pb(c - 'A');
        else {
            pl[i] = c - 'A';
            pr[i] = {t[0] - 'A', t[1] - 'A'};
            occT[pr[i].fi][0].pb(i);
            occT[pr[i].se][1].pb(i);
        }
    }

    int n, m, s, t;
    cin >> n >> m >> s >> t;
    --s; --t;
    forn(i, m) {
        int u, v;
        char c;
        cin >> u >> v >> c;
        --u; --v;
        for (int t: nonT[c - 'a']) {
            dist[u][v][t] = {1};
            vis[u][v][t] = 1;
        }
    }

    set<TItem, decltype(pcmp)> q(pcmp);
    forn(i, n) forn(j, n) forn(c, 26) if (vis[i][j][c]) q.insert(item({i, j, c}));

    while (!q.empty()) {
        TTriple t = q.begin()->se;
        q.erase(item(t));
        vlong D = dist[t.u][t.v][t.c];
        assert(vis[t.u][t.v][t.c]);
//        cerr << t.u << ' ' << t.v << ' ' << (char)(t.c + 'A') << ' ' << D[0] <<  '\n';
        for (int rule: occT[t.c][0]) forn(v, n) {
            if (!vis[t.v][v][pr[rule].se]) continue;
            vlong nd = D + dist[t.v][v][pr[rule].se];
            if (!vis[t.u][v][pl[rule]] || cmp(nd, dist[t.u][v][pl[rule]])) {
                TTriple nT = {t.u, v, pl[rule]};
                q.erase(item(nT));
                dist[t.u][v][pl[rule]] = nd;
                vis[t.u][v][pl[rule]] = 1;
                q.insert(item(nT));
            }
        }
        for (int rule: occT[t.c][1]) forn(v, n) {
            if (!vis[v][t.u][pr[rule].fi]) continue;
            vlong nd = D + dist[v][t.u][pr[rule].fi];
            if (!vis[v][t.v][pl[rule]] || cmp(nd, dist[v][t.v][pl[rule]])) {
                TTriple nT = {v, t.v, pl[rule]};
                q.erase(item(nT));
                dist[v][t.v][pl[rule]] = nd;
                vis[v][t.v][pl[rule]] = 1;
                q.insert(item(nT));
            }
        }
    }

    if (!vis[s][t]['S' - 'A']) cout << "NO\n";
    else print(dist[s][t]['S' - 'A']), cout << '\n';

#ifdef LOCAL_DEFINE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}