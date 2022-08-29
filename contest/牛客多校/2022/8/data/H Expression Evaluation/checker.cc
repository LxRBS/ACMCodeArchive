#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
using LL = long long;
int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int seed = inf.readLong(0LL, (1LL << 32) - 1, "seed");
    rnd.setSeed(seed);
    string s;
    while (s.size() == 0) {
        int n = 100000;
        string ch = "0123456789+-*";
        string t;
        for (int i = 0; i < n; i += 1)
            t += ch[rnd.next(0, 12)];
        for (char c : t) {
            if (isdigit(c)) s.push_back(c);
            else if (not s.empty() and isdigit(s.back()))
                s.push_back(c);
        }
        while (not s.empty() and isdigit(s.back()))
            s.pop_back();
    }
    auto f = [&](string& s) {
        unsigned pm[2] = {0, 0}, p = 1, cur = 0;
        int sg = 0;
        for (char c : s) {
            if (c == '+') {
                p *= cur;
                cur = 0;
                pm[sg] += p;
                p = 1;
                sg = 0;
            }
            else if (c == '-') {
                p *= cur;
                cur = 0;
                pm[sg] += p;
                p = 1;
                sg = 1;
            }
            else if (c == '*') {
                p *= cur;
                cur = 0;
            }
            else {
                cur = cur * 10 + c - '0';
            }
        }
        p *= cur;
        pm[sg] += cur;
        return pm[0] - pm[1];
    };
    auto ans = f(s);
    int m = 1024;
    vector<unsigned> r(m);
    for (int i = 0; i < m; i += 1)
        r[i] = ouf.readLong(0, (1LL << 32) - 1, "ri");
    int si = 0;
    for (int i = 0; i < 100'000'000; i += 1) {
        auto pc = r[0] % m;
        auto t = r[pc];
        auto c = t % m; t /= m;
        auto b = t % m; t /= m;
        auto a = t % m; t /= m;
        if (t == 0) {
            if (r[a] == ans)
                quitf(_ok, "answer is %lld and execution time is %d", (long long)ans, i + 1);
            else quitf(_wa, "answer is %lld, but particant is %lld", (long long)ans, (long long)r[a]);
        }
        if (t == 1) {
            if (si == s.size()) {
                r[0] = r[c];
            }
            else {
                r[a] = s[si ++];
                r[0] = r[b];
            }
        }
        if (t == 2) {
            r[a] = r[a] + r[b];
            r[0] = r[c];
        }
        if (t == 3) {
            if (r[a]) r[0] = r[c];
            else r[0] = r[b];
        }
    }
    quitf(_wa, "time limit exceed");
}