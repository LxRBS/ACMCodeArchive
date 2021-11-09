#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

typedef pair<int, int> pii;

bool check(int n, vector<pii> a, vector<pii> b) {
    vector<int> s(n + 1, 0), t(n + 1, 0);
    for (pii p : a) {
        int l = p.first, r = p.second;
        l--;
        if (l < r) s[l]++, s[r]--;
        else s[0]++, s[r]--, s[l]++, s[n]--;
    }
    for (int i = 0; i < n; ++i)
        s[i + 1] += s[i];
    for (pii p : b) {
        int l = p.first, r = p.second;
        l--;
        if (l < r) t[l]++, t[r]--;
        else t[0]++, t[r]--, t[l]++, t[n]--;
    }
    for (int i = 0; i < n; ++i)
        t[i + 1] += t[i];
    for (int i = 0; i < n; ++i) {
        bool f1 = (s[i] == 1), f2 = (t[i] == (int)b.size());
        if (f1 != f2)
            return false;
    }
    return true;
}

vector<pii> readScheme(InStream& f, const char* name, int n) {
    int m = f.readInt();
    f.readEoln();
    if (m < 0 || m > 2000)
        f.quitf(_wa, "%s output invalid scheme. m should lie in range [0, 2000], instead of %d\n", name, m);
    vector<pii> a(m);
    for (int i = 0; i < m; ++i) {
        int l = f.readInt();
        f.readSpace();
        int r = f.readInt();
        f.readEoln();
        if (l <= 0 || l > n || r <= 0 || r > n)
            f.quitf(_wa, "%s output invalid scheme. [l, r] should be a valid range, instead of [%d, %d]\n", name, l, r);
        a[i] = { l, r };
    }
    return a;
}

int main(int argc, char** argv) {
    registerTestlibCmd(argc, argv);
    int T = inf.readInt();
    for (int t = 1; t <= T; ++t) {
        //setTestCase(t);
        int n = inf.readInt();
        int m = inf.readInt();
        vector<pii> a(m);
        for (int i = 0; i < m; ++i) {
            a[i].first = inf.readInt();
            a[i].second = inf.readInt();
        }
        const char* nj = "Judge";
        const char* np = "Participant";
        vector<pii> bp = readScheme(ouf, np, n);
        if (!check(n, a, bp))
            ouf.quitf(_wa, "%s output a wrong scheme\n", np);
        vector<pii> bj = readScheme(ans, nj, n);
        ensuref(check(n, a, bj), "%s output wrong scheme or the checker is wrong.", nj);
    }
    quitf(_ok, "Passed");
    return 0;
}