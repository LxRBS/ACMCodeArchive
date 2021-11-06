#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = (int)5e3;
const int MAX_K = 10;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, MAX_N, "n");
    inf.readSpace();
    int k = inf.readInt(1, MAX_K, "k");
    inf.readEoln();

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = inf.readInt(1, k, format("a[%d]", i + 1));
        if (i + 1 < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    vector<int> p(n);
    iota(p.begin(), p.end(), 0);

    function<int(int)> get = [&](int x) {
        return p[x] == x ? x : p[x] = get(p[x]);
    };
    auto uni = [&](int u, int v) {
        u = get(u);
        v = get(v);
        if (u == v) return false;
        p[v] = u;
        return true;
    };

    for (int i = 0; i < n - 1; i++) {
        int u = inf.readInt(1, n, format("u[%d]", i + 1)) - 1;
        inf.readSpace();
        int v = inf.readInt(1, n, format("v[%d]", i + 1)) - 1;
        inf.readEoln();
        ensuref(uni(u, v), "%d-th edge makes cycle with previous edges", i + 1);
    }
    inf.readEof();
}