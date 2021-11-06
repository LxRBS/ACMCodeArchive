#pragma GCC optimize("Ofast", "unroll-loops", "no-stack-protector")
  
#include <bits/stdc++.h>
  
using namespace std;
 
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a).size()
 
using ll = long long;
using ld = long double; 
// using ld = __float128;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using uint = unsigned int;
using ull = unsigned long long;
 
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
// default_random_engine generator;
 
void solve();
 
int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout); 
#endif 
 
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << setprecision(10) << fixed;
    cerr << setprecision(10) << fixed;
 
    int tests = 1;
    // cin >> tests;
 
    for (int test = 1; test <= tests; ++test) {
        // cout << "Case #" << test << ": ";
        solve();
    }
 
#ifdef LOCAL
    cerr << "Time: " << double(clock()) / CLOCKS_PER_SEC << endl;
#endif
}
 
// ----------------------------------------------------------------- 
 
const ld EPS = 1e-9;
const int OPS = 60;
 
bool eq(ld a, ld b) {
    return abs(a - b) < EPS;
}
 
bool leq(ld a, ld b) {
    return a < b + EPS;
}
 
bool geq(ld a, ld b) {
    return a + EPS > b;
}
 
bool gt(ld a, ld b) {
    return a > b + EPS;
}
 
bool lt(ld a, ld b) {
    return a + EPS < b;
}
 
struct Point {
    Point() {}
    Point(ld x, ld y) : x(x), y(y) {}
 
    ld x, y;
 
    Point operator+=(const Point &other) {
        x += other.x;
        y += other.y;
        return *this;
    }
 
    Point operator-=(const Point &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
};
 
Point operator+(const Point &a, const Point &b) {
    return {a.x + b.x, a.y + b.y};
}
 
Point operator-(const Point &a, const Point &b) {
    return {a.x - b.x, a.y - b.y};
}
 
Point operator*(const Point &a, ld c) {
    return {a.x * c, a.y * c};
}
 
Point operator/(const Point &a, ld c) {
    return {a.x / c, a.y / c};
}
 
istream &operator>>(istream &stream, Point &a) {
    stream >> a.x >> a.y;
    return stream;
}
 
ostream &operator<<(ostream &stream, const Point &a) {
    stream << a.x << " " << a.y;
    return stream;
}
 
bool operator<(const Point &a, const Point &b) {
    return tie(a.x, a.y) < tie(b.x, b.y);
}
 
bool operator>(const Point &a, const Point &b) {
    return tie(a.x, a.y) > tie(b.x, b.y);
}
 
bool operator==(const Point &a, const Point &b) {
    return tie(a.x, a.y) == tie(b.x, b.y);
}
 
ld dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
} 
 
ld cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}
 
ld dist(const Point &a) {
    return hypotl(a.x, a.y);
}
 
Point intersect(const Point &a, const Point &u, const Point &b, const Point &v) {
    // [a + alpha u - b, v] = 0
    ld alpha = cross(b - a, v) / cross(u, v);
    return a + u * alpha;
}
 
const ld PI = acosl(-1);
 
ld getArea(const Point &f, const Point &g, ld l, const Point &u, const Point &v) {
    // cout << f << " " << g << " " << u << " " << v << " " << l << endl;
    ld a = l / 2;
    ld d = dist(f - g);
    ld b = sqrtl(l * l - d * d) / 2;
 
 
    Point cen = (f + g) / 2;
    assert(l > 0);
    assert(cross(f - cen, u - cen) > 0);
    assert(cross(f - cen, v - cen) > 0);
 
    auto getAngle = [&](const Point &w) {
        ld x = dot(f - cen, w - cen) / dist(f - cen);
        ld y = cross(f - cen, w - cen) / dist(f - cen);
        return atan2(a * y, b * x);
    };
 
    ld alpha = getAngle(u);
    ld beta = getAngle(v);
    // cout << alpha << " " << beta << endl;
 
    ld area = (a * b * (beta - alpha) - cross(u - cen, v - cen)) / 2;
    // cout << area << endl;
    return area;
}
 
void solve() { 
    int n;
    ld len;
    cin >> n >> len;
    vector<Point> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    auto nxt = [&](int k) {
        return k + 1 == n ? 0 : k + 1;
    };
    auto prv = [&](int k) {
        return k == 0 ? n - 1 : k - 1;
    };
 
    ld sign = 0;
    for (int i = 0; i < n; ++i) {   
        sign += cross(p[i], p[nxt(i)]);
    }
    if (sign < 0) {
        reverse(all(p));
    }
 
    // Point cen = (p[0] + p[2]) / 2;
 
    vector<ld> pref(n + 1);
    for (int i = 0; i < n; ++i) {
        int j = nxt(i);
        pref[i + 1] = pref[i] + dist(p[i] - p[j]);
    }
 
    auto perimeter = [&](int i, int j) {
        ld res = pref[j] - pref[i];
        return i <= j ? res : pref[n] + res;
    };
 
    function<pair<bool, Point>(int, int)> getForward = [&](int i, int k) {
        int j = nxt(i);
        int l = nxt(k);
 
        Point rg;
        if (gt(cross(p[j] - p[i], p[l] - p[k]), 0)) {
            rg = intersect(p[i], p[j] - p[i], p[l], p[k] - p[l]);
            ld s = dist(rg - p[j]) + dist(rg - p[k]) + perimeter(k, j);
            if (lt(s, len)) {
                return pair<bool, Point>{false, Point(0, 0)};
            }
        } else {
            rg = p[j] + (p[j] - p[i]) / dist(p[j] - p[i]) * len;
        }
 
        Point lf = intersect(p[i], p[j] - p[i], p[k], p[prv(k)] - p[k]);
 
        for (int op = 0; op < OPS; ++op) {
            Point q = (lf + rg) / 2;
            ld s = dist(q - p[j]) + dist(q - p[k]) + perimeter(k, j);
            if (s >= len) {
                rg = q;
            } else {
                lf = q;
            }
        }
 
        if (geq(cross(lf - p[k], p[prv(k)] - p[k]), 0) || geq(cross(lf - p[k], p[nxt(k)] - p[k]), 0)) {
            return pair<bool, Point>{false, Point(0, 0)}; 
        }
 
        return pair<bool, Point>{true, lf};
    };
 
 
    function<pair<bool, Point>(int, int)> getBackward = [&](int i, int k) {
        if (i == k) {
            return pair<bool, Point>{false, Point(0, 0)};
        }
 
        int j = nxt(i);
        int l = nxt(k);
 
        Point rg;
        if (gt(cross(p[j] - p[i], p[l] - p[k]), 0)) {
            rg = intersect(p[i], p[j] - p[i], p[l], p[k] - p[l]);
            ld s = dist(rg - p[j]) + dist(rg - p[k]) + perimeter(k, j);
            if (lt(s, len)) {
                return pair<bool, Point>{false, Point(0, 0)};
            }
        } else {
            rg = p[k] + (p[k] - p[l]) / dist(p[k] - p[l]) * len;
        }
 
        Point lf = intersect(p[j], p[j] - p[nxt(j)], p[k], p[l] - p[k]);
 
        for (int op = 0; op < OPS; ++op) {
            Point q = (lf + rg) / 2;
            ld s = dist(q - p[j]) + dist(q - p[k]) + perimeter(k, j);
            if (s >= len) {
                rg = q;
            } else {
                lf = q;
            }
        }
 
        if (leq(cross(lf - p[j], p[nxt(j)] - p[j]), 0) || leq(cross(lf - p[j], p[prv(j)] - p[j]), 0)) {
            return pair<bool, Point>{false, Point(0, 0)}; 
        }
 
        return pair<bool, Point>{true, lf};
    };
 
 
 
    int k = nxt(0);
    while (!getForward(0, k).first) {
        k = nxt(k);
    }
 
    bool state = 1;
    ld area = 0;
 
    bool start = true;
    int si = 0, sk = k, sstate = 1;
 
    vector<Point> conv;
 
    for (int i = 0; i < n; ) {
        if (i == si && k == sk && state == sstate && !start) {
            break;
        }
        start = false;
        // cerr << i << " " << k << " " << state << endl;
        int j = nxt(i);
        int l = nxt(k);
 
        if (state) {
            bool flag = false;
            Point a;
            tie(flag, a) = getForward(i, k);
            conv.push_back(a);
            assert(flag);
 
            Point b;
            tie(flag, b) = getBackward(i, k);
 
            if (flag) {
                area += getArea(p[j], p[k], len - perimeter(k, j), a, b);
                state = 0;
            } else {
                tie(flag, b) = getForward(j, k);
                assert(flag);
                area += getArea(p[j], p[k], len - perimeter(k, j), a, b);
                state = 1;
                i = nxt(i);
            }
        } else {
            bool flag = false;
            Point a;
            tie(flag, a) = getBackward(i, k);
            conv.push_back(a);
            assert(flag);
             
 
            Point b;
            tie(flag, b) = getForward(j, l);
 
            if (flag) {
                area += getArea(p[j], p[l], len - perimeter(l, j), a, b);
                state = 1;
                i = nxt(i);
                k = nxt(k);
            } else {
                tie(flag, b) = getBackward(i, l);
                assert(flag);
                area += getArea(p[j], p[l], len - perimeter(l, j), a, b);
                state = 0;
                k = nxt(k);
            }
        }
    }   
 
    // area = 0;
    for (int i = 0; i < sz(conv); ++i) {
        // cerr << conv[i] << endl;
        int j = (i + 1 == sz(conv) ? 0 : i + 1);
        area += cross(conv[i], conv[j]) / 2;
    }
 
    cout << area << endl;
    // cerr << area << endl;
}