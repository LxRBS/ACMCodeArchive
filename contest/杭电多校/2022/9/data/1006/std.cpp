#include "bits/stdc++.h"
#define rep(i, a, n) for (auto i = a; i <= (n); ++i)
#define revrep(i, a, n) for (auto i = n; i >= (a); --i)
#define all(a) a.begin(), a.end()
#define sz(a) (int)(a).size()
template<class T> inline bool chmax(T &a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T &a, T b) { if (b < a) { a = b; return 1; } return 0; }
using namespace std;

template<class A, class B> string to_string(pair<A, B> p);
string to_string(const string &s) { return '"' + s + '"'; }
string to_string(const char *s) { return to_string((string) s); }
string to_string(char c) { return "'" + string(1, c) + "'"; }
string to_string(bool x) { return x ? "true" : "false"; }
template<class A> string to_string(A v) {
    bool first = 1;
    string res = "{";
    for (const auto &x: v) {
        if (!first) res += ", ";
        first = 0;
        res += to_string(x);
    }
    res += "}";
    return res;
}
template<class A, class B> string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }

void debug_out() { cerr << endl; }
template<class Head, class... Tail> void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}
#ifndef ONLINE_JUDGE
    #define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
    #define debug(...) if(0) puts("No effect.")
#endif

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;


int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    int cas; cin >> cas; while (cas--) {
        int n, q; cin >> n >> q;
        vi as(n);
        for (auto &x: as) cin >> x;
        int bsz = sqrt(n) + 0.5, btot = n / bsz + 1;
        vi ls(btot, n), rs(btot, 0);
        rep(i, 0, n - 1) {
            int bid = i / bsz;
            chmin(ls[bid], i);
            chmax(rs[bid], i);
        }
        vvi pres(btot);
        rep(bid, 0, btot - 1) {
            int S = 0;
            rep(i, ls[bid], rs[bid]) if (as[i] < 0) S -= as[i];
            vi &pre = pres[bid];
            pre.resize(S + 1);
            rep(x, 0, S) {
                int now = x;
                rep(i, ls[bid], rs[bid]) {
                    int a = as[i];
                    if (now + a >= 0) now += a;
                }
                pre[x] = now;
            }
        }
        while (q--) {
            int ql, qr, x; cin >> ql >> qr >> x;
            qr--;
            int L = ql / bsz, R = qr / bsz;
            rep(bid, L, R) {
                if (ql <= ls[bid] && rs[bid] <= qr) {
                    auto &pre = pres[bid];
                    int S = sz(pre) - 1;
                    if (x <= S) x = pre[x];
                    else x = pre[S] + x - S;
                } else {
                    rep(i, max(ql, ls[bid]), min(qr, rs[bid])) {
                        if (x + as[i] >= 0) x += as[i];
                    }
                }
            }
            printf("%d\n", x);
        }
    }
    return 0;
}