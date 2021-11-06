#include <bits/stdc++.h>

#ifdef GG
#include <sys/resource.h>
#endif

#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
#define mp make_pair

using namespace std;

using ll = long long;
using li = long long;
using ld = long double;
using pii = pair<int, int>;

inline int nxt() {
    int x;
    cin >> x;
    return x;
}

void solve(bool);

//#define PROB ""

int main() {
#ifdef GG
    //    assert(PROB != string(""));
    assert(freopen("/home/golovanov/CLionProjects/godnotent/input.txt", "r", stdin));
    clock_t start = clock();

//    struct rlimit rl;
//    const rlim_t kStackSize = 512L * 1024L * 1024L;
//    assert(!getrlimit(RLIMIT_STACK, &rl));
//    rl.rlim_cur = kStackSize;
//    assert(!setrlimit(RLIMIT_STACK, &rl));
#else
//    assert(freopen("input.txt", "r", stdin));
//    assert(freopen("output.txt", "w", stdout));
//    assert(freopen(PROB".in", "r", stdin));
//    assert(freopen(PROB".out", "w", stdout));
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << setprecision(10) << fixed;

    solve(true);

#ifdef GG
    cerr << "\n\nTime elapsed: " << (clock() - start) / 1.0 / CLOCKS_PER_SEC << " s\n";
#endif
    return 0;
}

// -----------------------------------------------------

const int maxn = 26;

vector <pair <pii, int> > r;
vector <int> ed[26];

const int base = (int)1e9;

struct BigInt {
    vector <int> v;
};

bool isInf(const BigInt &a) {
    return (int)a.v.empty();
}

bool operator <(const BigInt &a, const BigInt &b) {
    if (isInf(a)) {
        return false;
    }

    if (isInf(b)) {
        return true;
    }

    if (a.v.size() != b.v.size()) {
        return a.v.size() < b.v.size();
    }

    int n = (int)a.v.size();

    for (int i = n - 1; i >= 0; i--) {
        if (a.v[i] != b.v[i]) {
            return a.v[i] < b.v[i];
        }
    }

    return false;
}

BigInt operator +(BigInt a, BigInt b) {
    if (a.v.size() < b.v.size()) {
        swap(a, b);
    }

    for (int i = 0; i < (int)a.v.size(); i++) {
        if (i < (int)b.v.size()) {
            a.v[i] += b.v[i];
        }

        if (a.v[i] >= base) {
            if (i + 1 == (int)a.v.size()) {
                a.v.push_back(0);
            }

            a.v[i + 1]++;
            a.v[i] -= base;
        }
    }

    return a;
}

BigInt dst[maxn][maxn][maxn];

void solve(bool __attribute__((unused)) read = true) {
    int p;
    cin >> p;

    //r.resize(p);
    string hh;
    getline(cin, hh);

    for (int i = 0; i < p; i++) {
        string s;
        getline(cin, s);
        int x = s[0] - 'A';

        if ('a' <= s[5] && s[5] <= 'z') {
            int y = s[5] - 'a';
            ed[y].push_back(x);
        } else {
            int y = s[5] - 'A';
            int z = s[6] - 'A';
            r.push_back(mp(mp(y, z), x));
        }
    }

    int n, m, s, t;
    cin >> n >> m >> s >> t;
    s--;
    t--;

    set <pair <BigInt, pair <pii, int> > > q;

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        char cc;
        cin >> cc;
        int c = cc - 'a';
        for (int f : ed[c]) {
            if (isInf(dst[x][y][f])) {
                dst[x][y][f].v.push_back(1);
                q.insert(mp(dst[x][y][f], mp(mp(x, y), f)));
            }
        }
    }

    while (!q.empty()) {
        int x = q.begin()->second.first.first;
        int y = q.begin()->second.first.second;
        int f = q.begin()->second.second;
        q.erase(q.begin());

        for (int i = 0; i < n; i++) {
            for (auto rule : r) {
                /*if (rule.first.first == f &&
                    dst[y][i][rule.first.second] != inf &&
                    dst[x][y][f] + dst[y][i][rule.first.second] > inf) {
                    throw 1;
                }

                if (rule.first.second == f &&
                    dst[i][x][rule.first.first] != inf &&
                    dst[x][y][f] + dst[i][x][rule.first.first] > inf) {
                    throw 1;
                }*/

                if (rule.first.first == f && !isInf(dst[y][i][rule.first.second]) &&
                    dst[x][y][f] + dst[y][i][rule.first.second] < dst[x][i][rule.second]) {
                    q.erase(mp(dst[x][i][rule.second], mp(mp(x, i), rule.second)));
                    dst[x][i][rule.second] = dst[x][y][f] + dst[y][i][rule.first.second];
                    q.insert(mp(dst[x][i][rule.second], mp(mp(x, i), rule.second)));
                }

                if (rule.first.second == f && !isInf(dst[i][x][rule.first.first]) &&
                    dst[x][y][f] + dst[i][x][rule.first.first] < dst[i][y][rule.second]) {
                    q.erase(mp(dst[i][y][rule.second], mp(mp(i, y), rule.second)));
                    dst[i][y][rule.second] = dst[x][y][f] + dst[i][x][rule.first.first];
                    q.insert(mp(dst[i][y][rule.second], mp(mp(i, y), rule.second)));
                }
            }
        }
    }

    if (isInf(dst[s][t]['S' - 'A'])) {
        cout << "NO\n";
    } else {
        auto ans = dst[s][t]['S' - 'A'];
        cout << ans.v.back();

        for (int i = (int)ans.v.size() - 2; i >= 0; i--) {
            cout << setw(9) << setfill('0') << ans.v[i];
        }

        cout << '\n';
    }
}
