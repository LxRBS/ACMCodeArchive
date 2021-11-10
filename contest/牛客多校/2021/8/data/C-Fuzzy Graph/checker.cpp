#include <bits/stdc++.h>
#include "testlib.h"

const int N = 1e6 + 5;

int n, m, cntr, cntg, cntb, anc[N], eu[N], ev[N];

int find(int u) {
    return anc[u] == u ? u : anc[u] = find(anc[u]);
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int T = inf.readInt();
    //setTestCase(T);
    for (; T; T--) {
        n = inf.readInt(); m = inf.readInt();
        for (int i = 0; i < m; i++) {
            eu[i] = inf.readInt(); ev[i] = inf.readInt();
        }
        std::string pa = ouf.readToken("[A-Z!]{1,300000}");
        if (pa == "CHEAT!") { quitf(_wa, "Sorry, we're SINCERE!"); return 0; }
        if (T != 1) { ouf.readEoln(); }
        if ((int) pa.size() != n) { quitf(_wa, "wa: unknown string"); return 0; }
        pa = " " + pa;
        cntr = cntg = cntb = 0;
        for (int u = 1; u <= n; u++) {
            anc[u] = u;
            if (pa[u] != 'R' && pa[u] != 'G' && pa[u] != 'B') {
                quitf(_wa, "wa: unknown string"); return 0;
            }
            if (pa[u] == 'R') { cntr++; }
            if (pa[u] == 'G') { cntg++; }
            if (pa[u] == 'B') { cntb++; }
        }
        bool edgr, edgg, edgb;
        edgr = edgg = edgb = false;
        for (int i = 0; i < m; i++) {
            if (pa[eu[i]] != pa[ev[i]]) {
                if (find(eu[i]) != find(ev[i])) {
                    anc[find(eu[i])] = find(ev[i]);
                }
            } else {
                if (pa[eu[i]] == 'R') { edgr = true; }
                if (pa[eu[i]] == 'G') { edgg = true; }
                if (pa[eu[i]] == 'B') { edgb = true; }
            }
        }
        for (int u = 2; u <= n; u++) {
            if (find(1) != find(u)) {
                quitf(_wa, "wa: invalid coloring"); return 0;
            }
        }
        bool ocd = cntr == n / 3 && cntg == n / 3 && cntb == n / 3;
        bool did = false;
        if (cntr >= cntg && cntr >= cntb && !edgr) { did = true; }
        if (cntg >= cntr && cntg >= cntb && !edgg) { did = true; }
        if (cntb >= cntr && cntb >= cntg && !edgb) { did = true; }
        if (ocd || did) { continue; }
        quitf(_wa, "wa: no awards"); return 0;
    }
    quitf(_ok, "ac: good job");
    return 0;
}
