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

const int maxn = 210000;
int s[maxn][2];
int dp[maxn][2][2], bj[maxn][2][2], ans[maxn][2];
vi e[maxn];

int get_dp(int i, int l, int r) {
//    cerr << i << ' ' << l << ' ' << r << '\n';
    if (dp[i][l][r] >= 0) return dp[i][l][r];
    int ch = e[i].size();
    if (!ch) return dp[i][l][r] = s[i][1] - s[i][0];
    vi ls(ch), rs(ch);
    int extra = 0;
    if (l) ls[0] = 1, extra += s[e[i][0]][0] - s[i][0];
    if (r) rs[ch - 1] = 1, extra += s[i][1] - s[e[i][ch - 1]][1];
    int base = 0;
    forn(j, ch) base += get_dp(e[i][j], ls[j], rs[j]);
    forn(j, ch + 1) {
        int lp = 1, rp = 1;
        int el = 0;
        if (j == 0) {if (!l) el = s[e[i][0]][0] - s[i][0];}
        else if (j == ch) {if (!r) el = s[i][1] - s[e[i][ch - 1]][1];}
        else el = s[e[i][j]][0] - s[e[i][j - 1]][1];

        int res = extra + base + el;
        
        if (j) {
            res -= get_dp(e[i][j - 1], ls[j - 1], rs[j - 1]);
            swap(rs[j - 1], rp);
            res += get_dp(e[i][j - 1], ls[j - 1], rs[j - 1]);
            swap(rs[j - 1], rp);
        }
        if (j < ch) {
            res -= get_dp(e[i][j], ls[j], rs[j]);
            swap(ls[j], lp);
            res += get_dp(e[i][j], ls[j], rs[j]);
            swap(ls[j], lp);
        }
        if (uax(dp[i][l][r], res)) bj[i][l][r] = j;
    }
//    cerr << i << ' ' << l << ' ' << r << ' ' << dp[i][l][r] << '\n';
    return dp[i][l][r];
}

void restore(int i, int *lp, int *rp) {
    int ch = e[i].size();
    int l = lp != NULL;
    int r = rp != NULL;
    if (!ch) {
        ans[i][0] = s[i][0];
        ans[i][1] = s[i][1];
        if (l) *lp = ans[i][0];
        if (r) *rp = ans[i][1];
        return;
    }
    vector<int *> lps(ch, NULL), rps(ch, NULL);
    lps[0] = lp;
    rps[ch - 1] = rp;
    int j = bj[i][l][r];
    if (j == 0) {
        ans[i][0] = s[i][0];
        lps[0] = &ans[i][1];
        if (l) *lp = ans[i][0];
    } else rps[j - 1] = &ans[i][0];
    if (j == ch) {
        ans[i][1] = s[i][1];
        rps[ch - 1] = &ans[i][0];
        if (r) *rp = ans[i][1];
    } else lps[j] = &ans[i][1];
    forn(j, ch) restore(e[i][j], lps[j], rps[j]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);
    cout << fixed;
#ifdef LOCAL_DEFINE
    freopen("input.txt", "rt", stdin);
#endif

    int n;
    cin >> n;
    forn(i, n) forn(j, 2) cin >> s[i][j];
    vector<pii> p(2 * n);
    forn(i, 2 * n) p[i] = {i / 2, i % 2};
    sort(all(p), [&](pii a, pii b){return s[a.fi][a.se] < s[b.fi][b.se];});

    vi st;
    vi roots;
    for (auto [i, j]: p) {
//        cerr << i << ' ' << j << ' ' << st.size() << '\n';
        if (j == 0) st.pb(i);
        else {
            st.pop_back();
            if (!st.empty()) e[st.back()].pb(i);
            else roots.pb(i);
        }
    }

    forn(i, n) forn(l, 2) forn(r, 2) dp[i][l][r] = -1;
    int total = 0;
    for (int i: roots) total += get_dp(i, 0, 0);
    for (int i: roots) restore(i, NULL, NULL);
    cout << total << '\n';
    forn(i, n) forn(j, 2) cout << ans[i][j] << " \n"[j];
    
#ifdef LOCAL_DEFINE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
