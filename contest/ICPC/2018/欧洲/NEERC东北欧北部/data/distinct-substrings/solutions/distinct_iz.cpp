#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll cnt(string s) {
    int n = s.length();
    s += "$";
    vector<vector<int>> lcp(n + 1, vector<int>(n + 1));
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            if (s[i] == s[j]) lcp[i][j] = lcp[i + 1][j + 1] + 1;
            else lcp[i][j] = 0;
            lcp[j][i] = lcp[i][j];
        }
    }
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    sort(p.begin(), p.end(), [&](int i, int j) {
        return s[i + lcp[i][j]] < s[j + lcp[i][j]];
    });
    ll ans = 1LL * n * (n + 1) / 2;
    for (int i = 1; i < n; i++) ans -= lcp[p[i - 1]][p[i]];
    return ans;
}

ll solve(string s, int k) {
    int n = s.length();
    for (int i = 1; i < n; i++) if (n % i == 0 && s.substr(0, n - i) == s.substr(i)) return solve(s.substr(0, i), k);
    string t = s + s;
    if (k <= 2 * n) t = t.substr(0, k);
    return cnt(t) + 1LL * (k - t.length()) * n;
}

int main() {
    string s;
    int k;
    while (cin >> s >> k) {
        cout << solve(s, k) << endl;
    }
}