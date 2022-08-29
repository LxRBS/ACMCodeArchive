#include "testlib.h"
#include <iostream>
#include <functional>
using namespace std;
using LL = long long;
struct P{
    LL x, y;
    P operator - (const P& p) const {
        return {x - p.x, y - p.y};
    }
    LL cross(const P& p) const {
        return x * p.y - y * p.x;
    }
    LL dot(const P& p) const {
        return x * p.x + y * p.y;
    }
    bool operator < (const P& p) const {
        return x == p.x ? y < p.y : x < p.x;
    }
};
int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    registerTestlibCmd(argc, argv);
    int T = inf.readInt(1, 1000, "T");
    for (int ti = 1; ti <= T; ti += 1) {
        int n = inf.readInt(1, 1000, "n");
        vector<pair<int, int>> e(n - 1);
        for (auto& [x, y] : e) {
            x = inf.readInt(1, n, "x");
            y = inf.readInt(1, n, "y");
        }
        auto upper = [&](string s) {
            for (char& c : s)
                if (islower(c))
                    c = c - 'a' + 'A';
            return s;
        };
        auto readAndCheckAnswer = [&] (InStream& in) {
            auto ok = upper(in.readWord("[a-zA-Z]+", "ok"));
            if (ok != "YES" and ok != "NO")
                quitf(_pe, "YES or NO expected");
            if (ok == "NO") return 0;
            vector<P> p(n + 1);
            for (int i = 1; i <= n; i += 1) {
                auto& [x, y] = p[i];
                x = in.readInt(-n, n, "x");
                y = in.readInt(-n, n, "y");
            }
            LL a = in.readInt(-n, n, "a");
            LL b = in.readInt(-n, n, "b");
            LL c = in.readInt(-n, n, "c");
            if (a == 0 and b == 0)
                quitf(_wa, "Invalid line.");
            vector<int> f(n + 1);
            map<pair<int, int>, int> mp;
            for (int i = 1; i <= n; i += 1) {
                if (mp.count({p[i].x, p[i].y}))
                    quitf(_wa, "Two points coincide.");
                mp[{p[i].x, p[i].y}] = i;
            }
            for (int i = 1; i <= n; i += 1) {
                LL q = a * a + b * b;
                auto [x, y] = p[i];
                LL x_ = 2 * a * (a * x + b * y + c);
                if (x_ % q)
                    quitf(_wa, "Points are not symmetric.");
                x_ = x - x_ / q;
                LL y_ = 2 * b * (a * x + b * y + c);
                if (y_ % q)
                    quitf(_wa, "Points are not symmetric.");
                y_ = y - y_ / q;
                if (not mp.count({x_, y_}))
                    quitf(_wa, "Points are not symmetric.");
                f[i] = mp[{x_, y_}];
            }
            set<pair<int, int>> sp;
            for (auto p : e) sp.insert(p);
            for (auto [x, y] : e)
                if (not sp.count({f[x], f[y]}) and not sp.count({f[y], f[x]}))
                    quitf(_wa, "Segments are not symmetric.");
            for (int i = 0; i < e.size(); i += 1)
                for (int j = i + 1; j < e.size(); j += 1) {
                    P A = p[e[i].first], B = p[e[i].second];
                    P C = p[e[j].first], D = p[e[j].second];
                    int wa = 0;
                    if ((B - A).cross(D - C) == 0) {
                        if ((B - A).cross(D - A)) continue;
                        if ((D - A).dot(C - A) < 0 or (D - B).dot(C - B) < 0 or (A - C).dot(B - C) < 0 or (A - D).dot(B - D) < 0)
                            wa = 1;
                    }
                    else {
                        LL x = (B - A).cross(D - C), y =  (C - A).cross(D - C), z = (C - B).cross(B - A);
                        if (x < 0) x = -x, y = -y, z = -z;
                        if (y < 0 or y > x or z < 0 or z > x) continue;
                        if ((y > 0 and y < x) or (z > 0 and z < x)) wa = 1;
                    }
                    if (wa) {
                        //for (auto [x, y] : e) cout << x << " " << y << endl;
                        quitf(_wa, "(%lld, %lld)-(%lld, %lld) and (%lld, %lld)-(%lld, %lld) intersects", A.x, A.y, B.x, B.y, C.x, C.y, D.x, D.y);
                    }
                }
            return 1;
        };
        auto ansf = readAndCheckAnswer(ans);
        auto outf = readAndCheckAnswer(ouf);
        if (ansf != outf)
            quitf(_wa, "Diffrent from jury.");
    }
    quitf(_ok, "%d test cases", T);
}
