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

vector<pair<int, int>> a[10];

void solve(bool __attribute__((unused)) read = true) {
    int n = nxt(), d = nxt();
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        int x = nxt();
        arr[i] = x;
        a[x % 10].push_back({x, i});
    }

    if (d == 0 || d == 5) {
        vector<int> ans;
        int last = 1;
        for (int i = 0; i < 10; ++i) {
            if (d == 5 && i % 2 == 0) {
                continue;
            }
            for (auto [x, id] : a[i]) {
                last = last * x % 10;
                ans.push_back(id);
            }
        }
        if (last != d) {
            cout << "-1\n";
        } else {
            cout << ans.size() << "\n";
            for (int x : ans) {
                cout << arr[x] << " ";
            }
            cout << "\n";
        }
        return;
    }

    if (d % 2) {
        for (int i = 0; i < 10; i += 2) {
            a[i].clear();
        }
    }

    vector<ld> to_remove[10];
    for (int i = 0; i < 10; ++i) {
        sort(all(a[i]));
        to_remove[i] = {0.};
        for (int j = 0; j < 4 && j < (int)a[i].size(); ++j) {
            to_remove[i].push_back(logl(a[i][j].first));
        }
//        for (int j = 1; j < (int)to_remove[i].size(); ++j) {
//            to_remove[i][j] += to_remove[i][j - 1];
//        }
    }

    int total_even = 0;
    int total = 0;
    for (int i = 2; i < 10; i += 2) {
        total_even += a[i].size();
    }
    for (int i = 1; i < 10; ++i) {
        if (i != 5) {
            total += a[i].size();
        }
    }

    int div[10][10];
    for (int i = 0; i < 10; ++i) {
        for (int j = 1; j < 10; ++j) {
            if (j == 5) {
                continue;
            }
            for (int k = 0; k < 10; ++k) {
                if (k * j % 10 == i) {
                    div[i][j] = k;
                }
            }
            for (int k = 0; k < 10; ++k) {
                if (k * j % 10 == i && k % 2 == 0) {
                    div[i][j] = k;
                }
            }
        }
    }

    pair<ld, vector<int>> ans = {1e9, {}};
    vector<int> st;
    function<void(ld, int, int, int, int)> rec = [&](ld cur, int i, int cur_even, int cur_cnt, int cur_dg) {
        if (i == 10) {
            if (cur_cnt == total) {
                return;
            }
            if (cur_even == total_even) {
                if (cur_dg % 2 == 0) {
                    cur_dg = (cur_dg + 5) % 10;
                }
            }
            if (cur_dg == d) {
                ans = min(ans, {cur, st});
            }
            return;
        }
        if (i == 5) {
            rec(cur, i + 1, cur_even, cur_cnt, cur_dg);
            return;
        }
        int need_popb = 0;
        for (int j = 0; j < (int)to_remove[i].size(); ++j) {
            rec(cur, i + 1, cur_even, cur_cnt, cur_dg);
            if (j < (int)a[i].size()) {
                need_popb += 1;
                st.push_back(a[i][j].second);
                cur += to_remove[i][j + 1];
                cur_even += (i % 2 == 0);
                cur_cnt += 1;
                cur_dg = div[cur_dg][i];
            }
        }
        while (need_popb--) {
            st.pop_back();
        }
    };
    int init_dg = 1;
    for (int i = 1; i < 10; ++i) {
        if (i == 5) {
            continue;
        }
        for (int j = 0; j < (int)a[i].size(); ++j) {
            init_dg = init_dg * i % 10;
        }
    }
    rec(0, 2, 0, 0, init_dg);
    if (ans.first > 1e8) {
        cout << "-1\n";
        return;
    }

    vector<char> need(n, false);
    for (int i = 1; i < 10; ++i) {
        if (i != 5) {
            for (auto p : a[i]) {
                need[p.second] = true;
            }
        }
    }
    for (int x : ans.second) {
        need[x] -= 1;
    }
    cout << total - ans.second.size() << "\n";
    for (int i = 0; i < n; ++i) {
        if (need[i]) {
            cout << arr[i] << " ";
        }
    }
    cout << "\n";
}
