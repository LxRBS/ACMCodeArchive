#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

const int N = 100000 + 9;

long long t[N];

vector<pair<long long, long long>> vc[N];

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    
    int n = inf.readInt();
    int m = inf.readInt();

    long long sum = 0;
    long long maxv = 0;

    for (int i = 1; i <= n; ++i) {
        t[i] = inf.readLong();
        sum += t[i];
        maxv = max(maxv, t[i]);
    }

    long long ans_time = max((sum - 1) / m + 1, maxv);

    for (int i = 1; i <= n; ++i) {
        int k = ouf.readInt();
        if (k == 1) {
            int id = ouf.readInt(1, m, "id");
            long long l = ouf.readLong(0, 1000000000000000000LL, "l");
            long long r = ouf.readLong(0, 1000000000000000000LL, "r");
            if (!(l < r)) {
                quitf(_wa, "l must be lower than r");
            }
            if (!(r - l == t[i])) {
                quitf(_wa, "The time spent frying the i-th hamburger steak must be t_i minutes");
            }
            vc[id].push_back({l, r});
        }
        else if (k == 2) {
            int id = ouf.readInt(1, m, "id");
            long long l = ouf.readLong(0, 1000000000000000000LL, "l");
            long long r = ouf.readLong(0, 1000000000000000000LL, "r");
            if (!(l < r)) {
                quitf(_wa, "l must be lower than r");
            }
            vc[id].push_back({l, r});
            int id2 = ouf.readInt(1, m, "id");
            if (!(id != id2)) {
                quitf(_wa, "Two ids must be different");
            }
            long long l2 = ouf.readLong(0, 1000000000000000000LL, "l");
            long long r2 = ouf.readLong(0, 1000000000000000000LL, "r");
            if (!(l2 < r2)) {
                quitf(_wa, "l must be lower than r");
            }
            if (!(r <= l2)) {
                quitf(_wa, "Two intervals must be given in chronological order and not intersect");
            }
            if (!(r2 - l2 + r - l == t[i])) {
                quitf(_wa, "The time spent frying the i-th hamburger steak must be t_i minutes");
            }
            vc[id2].push_back({l2, r2});
        }
        else {
            quitf(_wa, "k must be equal 1 or 2");
        }
    }

    long long ouf_time = 0;

    for (int i = 1; i <= m; ++i) {
        sort(vc[i].begin(), vc[i].end());
        for (int j = 1, sz = vc[i].size(); j < sz; ++j) {
            if (!(vc[i][j - 1].second <= vc[i][j].first)) {
                quitf(_wa, "There must be at most one hamburger steak in a certain pan at the same time");
            }
        }
        if (!vc[i].empty()) {
            ouf_time = max(ouf_time, vc[i].back().second);
        }
    }

    if (ouf_time != ans_time) {
        quitf(_wa, "The time spent must be minimized");
    }

    quitf(_ok, "The time spent is %lld minutes", ans_time);
}
