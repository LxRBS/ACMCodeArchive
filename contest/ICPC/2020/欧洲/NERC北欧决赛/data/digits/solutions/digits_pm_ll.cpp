#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

// @author: pashka

const ll INF = (ll)1e12;

int main() {
    ios::sync_with_stdio(false);

    int n, D;
    cin >> n >> D;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    if (D % 2 != 0) {
        vector<int> aa;
        for (int x : a) {
            if (x % 2 != 0) aa.push_back(x);
        }
        a = aa; n = a.size();
    }
    if (D % 5 != 0) {
        vector<int> aa;
        for (int x : a) {
            if (x % 5 != 0) aa.push_back(x);
        }
        a = aa; n = a.size();
    }

    vector<vector<ll>> d(n + 1, vector<ll>(10, INF));
    vector<vector<int>> p(n + 1, vector<int>(10, -1));

    d[0][1] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            int jj = j;
            ll dd = d[i][j] * a[i];
            if (d[i + 1][jj] > dd) {
                d[i + 1][jj] = dd;
                p[i + 1][jj] = j;
            }
            jj = (j * a[i]) % 10;
            dd = d[i][j];
            if (d[i + 1][jj] > dd) {
                d[i + 1][jj] = dd;
                p[i + 1][jj] = j;
            }
        }
    }
    if (d[n][D] == INF) {
        cout << -1 << "\n";
        return 0;
    }
    vector<int> res;
    int j = D;
    for (int i = n - 1; i >= 0; i--) {
        int jj = p[i + 1][j];
        if (d[i][jj] == d[i + 1][j]) {
            res.push_back(a[i]);
        }
        j = jj;
    }
    if (res.empty()) {
        cout << -1 << "\n";
        return 0;
    }
    cout << res.size() << "\n";
    int s = 1;
    for (int x : res) {
        cout << x << " ";
        s *= x;
        s %= 10;
    }
    cout << "\n";
    assert(s == D);

    return 0;
}