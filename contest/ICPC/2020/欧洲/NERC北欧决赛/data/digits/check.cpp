#include <bits/stdc++.h>
#include "testlib.h"

typedef long long ll;
using namespace std;
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


int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int D = inf.readInt();

    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = inf.readInt();

    int pa = ouf.readInt();
    if (pa == -1) {
        int ja = ans.readInt();
        if (ja == -1) {
            quitf(_ok, "impossible");
        } else {
            quitf(_wa, "not impossible");
        }
    }
    ouf.reset();
    ans.reset();

    int nb = ouf.readInt(1, n);
    vector<int> b(nb);
    for (int i = 0; i < nb; i++) b[i] = ouf.readInt();
    int nc = ans.readInt(1, n);
    vector<int> c(nc);
    for (int i = 0; i < nc; i++) c[i] = ans.readInt();

    int s = 1;
    for (int x : b) {
        s = (s * x) % 10;
    }
    if (s != D) {
        quitf(_wa, "last digit is %d instead of %d", s, D);
    }

    if (D % 2 != 0) {
        vector<int> aa;
        for (int x : a) {
            if (x % 2 != 0) aa.push_back(x);
        }
        a = aa;
    }
    if (D % 5 != 0) {
        vector<int> aa;
        for (int x : a) {
            if (x % 5 != 0) aa.push_back(x);
        }
        a = aa;
    }
    n = a.size();

    map<int, int> cntb;
    map<int, int> cntc;
    for (int x : a) {
        cntb[x]++;
        cntc[x]++;
    }
    for (int x : b) {
        if (cntb[x] == 0) quitf(_wa, "no such number in array: %d", x);
        cntb[x]--;
    }
    for (int x : c) {
        cntc[x]--;
    }

    infint sb = 1;
    for (auto p : cntb) {
        for (int i = 0; i < p.second; i++) {
            sb *= p.first;
        }
    }
    infint sc = 1;
    for (auto p : cntc) {
        for (int i = 0; i < p.second; i++) {
            sc *= p.first;
        }
    }

    if (sc == INFTY) {
        quitf(_fail, "infinity in jury answer");
    }
    if (sb < sc) {
        quitf(_fail, "participant answer is better");
    }
    if (sb > sc) {
        quitf(_wa, "jury answer is better");
    }

    quitf(_ok, "");
}