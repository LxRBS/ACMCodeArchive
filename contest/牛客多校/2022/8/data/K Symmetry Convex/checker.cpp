#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
using LL = long long;
int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int T = inf.readInt(1, 100'000, "T");
    for (int ti = 1; ti <= T; ti += 1) {
        int n = inf.readInt(1, 300'000, "n");
        for (int i = 1; i <= n; i += 1)
        {
            inf.readToken();
            inf.readToken();
        }
        constexpr LL maxn = 2'000'000'000'000'000'000LL;
        auto readAndCheckAnswer = [&] (InStream& in) {
            vector<set<vector<LL>>> v;
            for (int i = 3; i <= n; i += 1) {
                v.emplace_back();
                int k = in.readInt(0, i, "k");
                for (int j = 0; j < k; j += 1) {
                    LL a = in.readLong(-maxn, maxn, "a");
                    LL b = in.readLong(-maxn, maxn, "b");
                    LL c = in.readLong(-maxn, maxn, "c");
                    if (a == 0 and b == 0)
                        quitf(_wa, "%lld x + %lld y + %lld = 0 is not a line.", a, b, c);
                    LL d = gcd(gcd(abs(a), abs(b)), abs(c));
                    a /= d;
                    b /= d;
                    c /= d;
                    if (a < 0) {
                        a = -a;
                        b = -b;
                        c = -c;
                    }
                    else if (a == 0) {
                        if (b < 0) {
                            b = -b;
                            c = -c;
                        }
                    }
                    v.back().insert({a, b, c});
                }
            }
            return v;
        };
        auto anss = readAndCheckAnswer(ans);
        auto oufs = readAndCheckAnswer(ouf);
        if (anss != oufs)
            quitf(_wa, "the participant are greater than answer");
    }
    quitf(_ok, "%d test cases", T);
}
