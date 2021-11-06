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

struct vt {
    int sumx;
    int sumy;
    string s;
};

const int maxc = 20 * 20 * 20 * 20;
int cnt[maxc];

vector <vt> buf;

void my_sort(vector<vt> &a, int tp) {
    memset(cnt, 0, sizeof cnt);
    for (vt &f : a) {
        cnt[f.sumy]++;
    }

    for (int i = 1; i < maxc; i++) {
        cnt[i] += cnt[i - 1];
    }

    buf.resize(a.size());
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        vt f = a[i];
        buf[--cnt[f.sumy]] = f;
    }

    memset(cnt, 0, sizeof cnt);
    for (vt &f : buf) {
        cnt[maxc * tp - f.sumx * (tp == 1 ? 1 : -1)]++;
    }

    for (int i = 1; i < maxc; i++) {
        cnt[i] += cnt[i - 1];
    }

    for (int i = (int)buf.size() - 1; i >= 0; i--) {
        vt f = buf[i];
        a[--cnt[maxc * tp - f.sumx * (tp == 1 ? 1 : -1)]] = f;
    }
}

const int maxmass = 19 * 19 * 6;

vector <vt> v[2][19][maxmass];

string cur;

void gen(int pos, int len, int bal, int mass, int sumx, int sumy) {
    if (bal < 0) {
        return;
    }

    if (pos == len) {
        v[0][bal][mass].push_back({sumx, sumy, cur});
        return;
    }

    cur.push_back('(');
    int d = 1;
    gen(pos + 1, len, bal + 1, mass + (2 * bal + d) * 3, sumx + (6 * pos + 3) * bal + (3 * pos + 2) * d,
        sumy + 3 * bal * bal + (3 * bal + 1) * d);
    cur.pop_back();
    cur.push_back(')');
    d = -1;
    gen(pos + 1, len, bal - 1, mass + (2 * bal + d) * 3, sumx + (6 * pos + 3) * bal + (3 * pos + 2) * d,
        sumy + 3 * bal * bal + (3 * bal + d) * d);
    cur.pop_back();
}

void solve(bool __attribute__((unused)) read = true) {
    int n;
    cin >> n;
    gen(0, n / 2, 0, 0, 0, 0);
    ld x, y;
    cin >> x >> y;

    for (int b = 0; b <= n / 2; b++) {
        for (int m1 = 0; m1 < maxmass; m1++) {
            if (v[0][b][m1].empty()) {
                continue;
            }

            my_sort(v[0][b][m1], 0);
            v[1][b][m1] = v[0][b][m1];
            my_sort(v[1][b][m1], 1);
        }
    }

    const ld eps = 1e-7;

    for (int b = 0; b <= n / 2; b++) {
        for (int m1 = 0; m1 < maxmass; m1++) {
            if (v[0][b][m1].empty()) {
                continue;
            }

            for (int m2 = 0; m2 < maxmass; m2++) {
                if (v[1][b][m2].empty()) {
                    continue;
                }

                int x1 = round(x * (m1 + m2));
                int y1 = round(y * (m1 + m2));

                if (fabs(x1 - x * (m1 + m2)) > eps) {
                    continue;
                }

                if (fabs(y1 - y * (m1 + m2)) > eps) {
                    continue;
                }

                int pos = 0;
                for (vt &a : v[0][b][m1]) {
                    while (pos < (int)v[1][b][m2].size() &&
                            mp(a.sumx + -v[1][b][m2][pos].sumx + n * m2, a.sumy + v[1][b][m2][pos].sumy) > mp(x1, y1)) {
                        pos--;
                    }

                    if (pos != (int)v[1][b][m2].size() &&
                        mp(a.sumx + -v[1][b][m2][pos].sumx + n * m2, a.sumy + v[1][b][m2][pos].sumy) == mp(x1, y1)) {
                        cout << a.s;
                        reverse(all(v[1][b][m2][pos].s));
                        for (char c : v[1][b][m2][pos].s) {
                            if (c == ')') {
                                cout << '(';
                            } else {
                                cout << ')';
                            }
                        }
                        exit(0);
                    }
                }
            }
        }
    }
}
