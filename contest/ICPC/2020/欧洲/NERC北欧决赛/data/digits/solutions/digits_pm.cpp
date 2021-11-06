#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

// @author: pashka

ll INFTY = 1000000000000000000ll;

struct infint {
    ll val;

    infint(ll v) {
        if (v >= INFTY) {
            v = INFTY;
        }
        val = v;
    }

    infint& operator +=(const infint& a) {
        if (INFTY - a.val <= val) {
            val = INFTY;
        } else {
            val += a.val;
        }
        return *this;
    }

    infint& operator *=(const infint& a) {
        if (a.val != 0 && INFTY / a.val <= val) {
            val = INFTY;
        } else {
            val *= a.val;
        }
        return *this;
    }
};

infint operator +(const infint& a, const infint& b) {
    infint res = a;
    res += b;
    return res;
}

infint operator *(const infint& a, const infint& b) {
    infint res = a;
    res *= b;
    return res;
}

bool operator <(const infint& a, const infint& b) {
    return a.val < b.val;
}

bool operator >(const infint& a, const infint& b) {
    return a.val > b.val;
}

bool operator <=(const infint& a, const infint& b) {
    return a.val <= b.val;
}

bool operator >=(const infint& a, const infint& b) {
    return a.val >= b.val;
}

bool operator ==(const infint& a, const infint& b) {
    return a.val == b.val;
}

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

    vector<vector<infint>> d(n + 1, vector<infint>(10, INFTY));
    vector<vector<int>> p(n + 1, vector<int>(10, -1));

    d[0][1] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            int jj = j;
            infint dd = d[i][j] * a[i];
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
    if (d[n][D] == INFTY) {
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
    sort(res.begin(), res.end());
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