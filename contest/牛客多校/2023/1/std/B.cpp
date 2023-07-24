#include<bits/stdc++.h>

#define X first
#define Y second
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
inline pll operator-(const pll &a, const pll &b) { return {a.X - b.X, a.Y - b.Y}; }
inline ll cross(const pll &a, const pll &b) { return a.X * b.Y - a.Y * b.X; }

int main() {
    int n;
    cin >> n;
    vector<pll> ps(n);
    for (auto &[x, y]: ps) cin >> x >> y;

    auto nxt = [&](int x) { return (x + 1) % n; };
    auto pre = [&](int x) { return (x + n - 1) % n; };
    auto area = [&](int u, int v, int w) { return cross(ps[v] - ps[u], ps[w] - ps[u]); };

    int r = 0, s = 1, t = 2;
    // 固定i=1，找到一个初始的极大
    ll maxArea = -1;
    for (int j = 1, k = 2; k < n; ++k) {
        while (j + 1 != k && area(0, j + 1, k) > area(0, j, k)) ++j;
        ll S = area(0, j, k);
        if (S > maxArea) maxArea = S, s = j, t = k;
    }

    // 局部调整
    while (true) {
        auto S = area(r, s, t);
        if (area(r, s, nxt(t)) > S) t = nxt(t);
        else if (area(r, s, pre(t)) > S) t = pre(t);
        else if (area(r, nxt(s), t) > S) s = nxt(s);
        else if (area(r, pre(s), t) > S) s = pre(s);
        else if (area(nxt(r), s, t) > S) r = nxt(r);
        else if (area(pre(r), s, t) > S) r = pre(r);
        else break;
    }
    cout << r + 1 << ' ' << s + 1 << ' ' << t + 1 << endl;
    return 0;
}
