#include <bits/stdc++.h>
using std::vector;
using ll = long long;

int solve(ll s0, vector<std::pair<ll, int>>& lvl) {
    std::sort(lvl.begin(), lvl.end());
    for (auto& li : lvl) {
        auto &s = li.first;
        auto &d = li.second;
        s -= s0, s0 += d;
    }
    std::multiset<int> ds;
    ll pre = 0;
    int id = 0;
    for (int i = (int)lvl.size() - 1; i >= 0; i--) {
        if (pre >= lvl[i].first) {
            ds.insert(lvl[i].second);
        } else if (ds.empty()) {
            pre += lvl[i].second, ++id;
        } else {
            ll scn = pre + *(--ds.end());
            if (scn <= pre + lvl[i].second) {
                pre += lvl[i].second, ++id;
            } else {
                pre = scn, ++id;
                ds.erase(--ds.end());
                ds.insert(lvl[i].second);
            }
        }
    }
    return (int)lvl.size() - id;
}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        int n;
        ll s0, sum = 0;
        std::cin >> n >> s0;
        vector<std::pair<ll, int>> lp, lm;
        lp.reserve(n), lm.reserve(n);
        for (int i = 0; i < n; i++) {
            int d;
            ll s;
            std::cin >> d >> s;
            sum += d;
            if (d < 0) {
                lm.push_back({s, -d});
            } else {
                lp.push_back({s - d, d});
            }
        }
        printf("%d\n", solve(s0, lp) + solve(s0 + sum, lm));
    }
    return 0;
}
