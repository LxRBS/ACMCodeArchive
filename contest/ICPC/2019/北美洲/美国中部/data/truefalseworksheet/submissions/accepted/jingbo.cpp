#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

const int MAXN = 5000;
const int MAXM = 1000000;

const int MOD = 1000000007;

// int f[MAXN + 1][MAXN + 1];
int f[2][MAXN + 1];

struct Constraint
{
    int x, l, r;
    Constraint() {}
    Constraint(int x, int l, int r) : x(x), l(l), r(r) {}
};

vector<Constraint> constraints[MAXN + 1];

int main()
{
    int n, m;
    assert(scanf("%d%d", &n, &m) == 2);
    assert(1 <= n && n <= MAXN);
    assert(1 <= m && m <= MAXM);
    for (int i = 0; i < m; ++ i) {
        int x, l, r;
        std::string s;
        std::cin >> l >> r >> s;
        (s == "same") ? (x=1) : (x=2);
        assert(x == 1 || x == 2);
        assert(1 <= l && l <= r && r <= n);
        constraints[r].push_back(Constraint(x, l, r));
    }
    int now = 0, old = 1;
    f[0][0] = 1;
    for (int i = 0; i <= n; ++ i) {
        now = 1 - now;
        old = 1 - old;
        memset(f[now], 0, sizeof(f[now]));
        for (int j = 0; j <= i; ++ j) {
            bool valid = true;
            for (const Constraint& constraint : constraints[i]) {
                if (constraint.x == 1) {
                    if (constraint.l <= j) {
                        valid = false;
                        break;
                    }
                } else {
                    if (constraint.l > j) {
                        valid = false;
                        break;
                    }
                }
            }
            if (!valid) {
                f[old][j] = 0;
            }

            if (f[old][j]) {
                // if a[i + 1] == a[j]
                f[now][i] += f[old][j];
                f[now][i] %= MOD;

                // if a[i + 1] != a[j]
                f[now][j] += f[old][j];
                f[now][j] %= MOD;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= n; ++ i) {
        ans += f[old][i];
        ans %= MOD;
    }
    printf("%d\n", ans);
    return 0;
}

