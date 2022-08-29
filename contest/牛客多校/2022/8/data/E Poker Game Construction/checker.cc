#include "testlib.h"
#include <iostream>
#include <functional>
using namespace std;
using LL = long long;
int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    registerTestlibCmd(argc, argv);
    string ranks = "0123456789TJQKA";
    string suits = "SHCD";
    auto rank = [&](LL h) -> int {
        int res = 0;
        vector<int> r, s;
        while (h) {
            int t = __builtin_ctzll(h);
            r.push_back(t / 4);
            s.push_back(t % 4);
            h ^= 1LL << t;
        }
        int straight = 1;
        for (int i = 0; i < 3; i += 1) if (r[i]  + 1 != r[i + 1]) straight = 0;
        if ((r[3] + 1 != r[4]) and (r[3] != 5 or r[4] != 14)) straight = 0;
        int flush = 1;
        for (int i = 0; i < 4; i += 1) if (s[i] != s[i + 1]) flush = 0;
        if (straight and flush) {
            if (r[3] + 1 == r[4])  return res = (9 << 20) | r[4];
            return res = (9LL << 20) | r[3];
        }
        if (r[0] == r[3]) return res = (8 << 20) | r[0];
        if (r[1] == r[4]) return res = (8 << 20) | r[1];
        if (r[0] == r[2] and r[3] == r[4]) return res = (7 << 20) | r[0];
        if (r[0] == r[1] and r[2] == r[4]) return res = (7 << 20) | r[2];
        if (flush) return (6 << 20) | (r[4] << 16) | (r[3] << 12) | (r[2] << 8) | (r[1] << 4) | r[0];
        if (straight) {
            if (r[3] + 1 == r[4])  return (5 << 20) | r[4];
            return (5 << 20) | r[3];
        }
        if (r[0] == r[2]) return (4 << 20) | r[0];
        if (r[1] == r[3]) return (4 << 20) | r[1];
        if (r[2] == r[4]) return (4 << 20) | r[2];
        if (r[0] == r[1] and r[2] == r[3]) return (3 << 20) | (r[2] << 8) | (r[0] << 4) | r[4];
        if (r[0] == r[1] and r[3] == r[4]) return (3 << 20) | (r[3] << 8) | (r[0] << 4) | r[2];
        if (r[1] == r[2] and r[3] == r[4]) return (3 << 20) | (r[3] << 8) | (r[1] << 4) | r[0];
        if (r[0] == r[1]) return (2 << 20) | (r[0] << 12) | (r[4] << 8) | (r[3] << 4) | r[2];
        if (r[1] == r[2]) return (2 << 20) | (r[1] << 12) | (r[4] << 8) | (r[3] << 4) | r[0];
        if (r[2] == r[3]) return (2 << 20) | (r[2] << 12) | (r[4] << 8) | (r[1] << 4) | r[0];
        if (r[3] == r[4]) return (2 << 20) | (r[3] << 12) | (r[2] << 8) | (r[1] << 4) | r[0];
        return (1 << 20) | (r[4] << 16) | (r[3] << 12) | (r[2] << 8) | (r[1] << 4) | r[0];
    };
    vector f(64, vector<int>(64));
    vector g(64, vector<int>(64, INT_MAX));
    vector<int> sci;
    vector ci(1 << 6, vector<int>());
    vector<LL> sc(1 << 6);
    for (int i = 0; i < (1 << 6); i += 1) {
        if (__builtin_popcount(i) == 3)
            sci.push_back(i);
        for (int j = 0; j < 6; j += 1)
            if ((i >> j) & 1)
                ci[i].push_back(j);
    }
    int TT = 0;
    auto F = [&](LL A, LL B, vector<int> c) {
        TT += 1;
        for (int i : sci) {
            sc[i] = 0;
            for (int j : ci[i]) sc[i] |= 1LL << c[j];
        }
        function<int(int a, int b, int c)> DFS = [&](int a, int b, int c) -> int {
            if (g[a][b] == TT) return f[a][b];
            g[a][b] = TT;
            int& res = f[a][b];
            if (c == 0) {
                auto rA = rank(A | sc[a]), rB = rank(B | sc[b]);
                if (rA > rB) return res = 1;
                if (rA == rB) return res = 0;
                return res = -1;
            }
            if (__builtin_parity(c)) {
                res = 1;
                for (int i : ci[c]) {
                    int pres = DFS(a, b ^ (1 << i), c ^ (1 << i));
                    res = min(res, pres);
                    if (res == -1) return res;
                }
                return res;
            }
            res = -1;
            for (int i : ci[c]) {
                int pres = DFS(a ^ (1 << i), b, c ^ (1 << i));
                res = max(res, pres);
                if (res == 1) return res;
            }
            return res;
        };
        return DFS(0, 0, 63);
    };
    auto readCard = [&](InStream& in) {
        auto s = in.readToken("[23456789TJQKA][SHCD]", "s");
        return (find(ranks.begin(), ranks.end(), s[0]) - ranks.begin()) * 4
            + (find(suits.begin(), suits.end(), s[1]) - suits.begin());
    };
    auto check = [&](LL A, LL B, InStream& in, int res) {
        auto s = in.readToken("[a-zA-Z]{2,3}", "s");
        for (char& si : s) if (si >= 'a' and si <= 'z') si = si - 'a' + 'A';
        if (s == "NO") return 0;
        if (s != "YES")
            quitf(_pe, "Yes or no is not found.");
        vector<int> c(6);
        LL X = A | B;
        for (int& ci : c) {
            ci = readCard(in);
            X |= 1LL << ci;
        }
        if (__builtin_popcountll(X) != 10)
            quitf(_wa, "Rpeated cards.");
        //cout << F(A, B, c) << endl;
        if (F(A, B, c) != res)
            quitf(_wa, "The construction is wrong.");
        return 1;
    };
    int T = inf.readInt(1, 100'000, "T");
    int bug = 0;
    for (int ti = 1; ti <= T; ti += 1) {
        LL A = (1LL << readCard(inf)) | (1LL << readCard(inf));
        LL B = (1LL << readCard(inf)) | (1LL << readCard(inf));
        for (int res : {1, -1, 0}) {
            int p = check(A, B, ouf, res);
            int j = check(A, B, ans, res);
            if (j and not p)
                quitf(_wa, "Jury find answer but partcitant not.");
            if (p and not j)
                bug = 1;
        }
    }
    if (bug) quitf(_ok, "There is bug.");
    else quitf(_ok, "%d test cases", T);
}