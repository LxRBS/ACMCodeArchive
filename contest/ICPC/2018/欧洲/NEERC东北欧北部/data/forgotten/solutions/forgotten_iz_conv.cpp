#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 998244353;

void add(int &x, ll y) {
    x = (x + y) % MOD;
}

void oft(vector<int> &a, int inv) {
    int n = a.size();
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                int u = a[i + j], v = a[i + k + j];
                if (!inv) {
                    a[i + k + j] = (u + v) % MOD;
                } else {
                    a[i + k + j] = (v - u + MOD) % MOD;
                }
            }
        }
    }
}

vector<int> mul(vector<int> a, vector<int> b) {
    oft(a, 0);
    oft(b, 0);
    for (int i = 0; i < (int)a.size(); i++) a[i] = 1LL * a[i] * b[i] % MOD;
    oft(a, 1);
    return a;
}

vector<int> sum(vector<int> a, vector<int> b) {
    for (int i = 0; i < (int)a.size(); i++) {
        add(a[i], b[i]);
    }
    return a;
}

vector<int> sub(vector<int> a, vector<int> b) {
    for (int i = 0; i < (int)a.size(); i++) {
        add(a[i], MOD - b[i]);
    }
    return a;
}

int solve(int n, int k, vector<int> a, vector<vector<int>> e) {
    struct item {
        vector<int> res, pref;
    };
    function<item(int, int)> dfs = [&](int v, int pr) {
        item cur;
        cur.res = cur.pref = vector<int>(1 << k, 0);
        cur.pref[0] = 1;
        auto tmp = cur.res;
        for (int to : e[v]) {
            if (to == pr) continue;
            auto nw = dfs(to, v);
            cur.pref = mul(cur.pref, nw.pref);
            cur.res = sum(cur.res, nw.res);
            tmp = sum(tmp, nw.pref);
            add(tmp[0], MOD - 1);
        }
        vector<int> t2(1 << k, 0);
        t2[1 << a[v]] = 2;
        cur.pref = mul(cur.pref, t2);
        t2[1 << a[v]] = 1;
        tmp = mul(tmp, t2);

        add(cur.pref[0], 1);
        add(cur.pref[1 << a[v]], MOD - 1);
        cur.res = sum(cur.res, sub(cur.pref, tmp));
        return cur;
    };
    auto cur = dfs(0, -1);
    int ans = 0;
    for (int i = 0; i < (1 << k); i++) {
        int coef = 0;
        for (int j = 0; j < __builtin_popcount(i); j++) coef = (coef + (1 << (k - j))) % MOD;
        add(ans, (ll)cur.res[i] * coef);
    }
    return ans;
}

int main() {
#ifdef HOME
    freopen("in", "r", stdin);
#endif
    int n, k;
    scanf("%d%d", &n, &k);
    vector<int> a(n, -1);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]), a[i]--;
    vector<vector<int>> e(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    cout << solve(n, k, a, e) << endl;
}
