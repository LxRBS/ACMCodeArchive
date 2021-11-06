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

const int maxn = 110000;
i64 dp[maxn][2][10];
array<int, 3> prv[maxn][2][10];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);
    cout << fixed;
#ifdef LOCAL_DEFINE
    freopen("input.txt", "rt", stdin);
#endif

    int n, d;
    cin >> n >> d;
    vi64 a;
    forn(i, n) {
        int x;
        cin >> x;
        if (x % 2 == 0 && d % 2) continue;
        if (x % 5 == 0 && d % 5) continue;
        a.pb(x);
    }

    n = a.size();

    forn(i, n + 1) forn(z, 2) forn(m, 10) dp[i][z][m] = 1e18;
    dp[0][0][1] = 1;
    forn(i, n) forn(z, 2) forn(m, 10) {
        if (dp[i][z][m] > 1e14) continue;
//        cerr << i << ' ' << z << ' ' << m << ' ' << dp[i][z][m] << '\n';
        if (uin(dp[i + 1][z][m], dp[i][z][m] * a[i])) prv[i + 1][z][m] = {i, z, m};
        if (uin(dp[i + 1][1][m * a[i] % 10], dp[i][z][m])) prv[i + 1][1][m * a[i] % 10] = {i, z, m};
    }

    if (dp[n][1][d] > 1e15) cout << -1 << '\n';
    else {
        int i = n, z = 1, m = d;
        vi ans;
        while (i) {
            int pi, pz, pm;
            auto w = prv[i][z][m];
            pi = w[0], pz = w[1], pm = w[2];
            if (dp[i][z][m] == dp[pi][pz][pm]) ans.pb(a[pi]);
            tie(i, z, m) = tie(pi, pz, pm);
        }
        cout << ans.size() << '\n';
        sort(all(ans));
        for (int x: ans) cout << x << ' ';
        cout << '\n';
    }

#ifdef LOCAL_DEFINE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
            