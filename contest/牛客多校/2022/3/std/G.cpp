#include <bits/stdc++.h>
using namespace std;

#define cp const point&
#define cl const line&

typedef long long ll;
typedef long double ld;

const int N = 100005;
const ld eps = 1e-10;

int sgn(ld x) {return (x > eps) - (x < -eps);}

struct point {
    ld x, y;
    point operator+(cp o) const {return {x + o.x, y + o.y};}
    point operator-(cp o) const {return {x - o.x, y - o.y};}
    point operator*(ld k) const {return {x * k, y * k};}
    point operator/(ld k) const {return {x / k, y / k};}
    point operator-() const {return {-x, -y};}
    ld len() const {
        return sqrtl(norm2());
    }
    ld norm2() const {
        return x * x + y * y;
    }
    bool operator<(cp o) const {
        if (sgn(x - o.x)) return sgn(x - o.x) < 0;
        return sgn(y - o.y) < 0;
    }
    bool operator>(cp o) const {
        return o < *this;
    }
};
ld det(cp a, cp b) {return a.x * b.y - a.y * b.x;}
ld dot(cp a, cp b) {return a.x * b.x + a.y * b.y;}

struct line {
    point s, t;
};

ld proj_to_line(cp a, cl b) { // the point is b.s + (b.t - b.s) * (#RET_VALUE / (b.t - b.s).norm2())
    return dot(a - b.s, b.t - b.s);
}

ld det_to_line(cp a, cl b) {
    return det(b.t - b.s, a - b.s);
}

struct ConvexWork {
    int n;
    point p[N];

    void read() {
        cin >> n;
        for (int i = 0, x, y; i < n; i++) {
            cin >> x >> y;
            p[i].x = x, p[i].y = y;
        }
    }

    set<pair<point, int>> upper, lower;
    point co[N];
    line l;
    void init(cl pline) {
        l = pline;
        point mi = {4e18, 4e18}, ma = {-4e18, -4e18};
        int min_id = -1, max_id = -1;
        
        for (int i = 0; i < n; i++) {
            co[i] = {proj_to_line(p[i], l), det_to_line(p[i], l)};
            if (co[i] < mi) mi = co[i], min_id = i;
            if (co[i] > ma) ma = co[i], max_id = i;
        }

        for (int i = min_id; i != max_id; i = (i + 1) % n) {
            upper.insert({co[i], i});
        }
        upper.insert({co[max_id], max_id});

        for (int i = max_id; i != min_id; i = (i + 1) % n) {
            lower.insert({co[i], i});
        }
        lower.insert({co[min_id], min_id});
    }

    ld query_one_set(cp s, cp v, const set<pair<point, int>>& shell) {
        point tmp = {proj_to_line(s, l), det_to_line(s, l)};
        auto it = shell.lower_bound({tmp, -1});
        if (it == shell.begin()) {
            tmp.y = shell.begin()->first.y;
            it = shell.lower_bound({tmp, INT_MAX});
            if (it == shell.begin())
                return 1e10;
        } else if (it == shell.end()) {
            tmp.y = shell.rbegin()->first.y;
            it = shell.lower_bound({tmp, -1});
            if (it == shell.end())
                return 1e10;
        }
        int id2 = it->second;
        int id1 = (--it)->second;
        if (sgn(det(p[id2] - p[id1], v)) == 0) {
            assert(sgn(det(p[id1] - s, v)) == 0);
            assert(sgn(det(p[id2] - s, v)) == 0);

            if (sgn(dot(p[id1] - s, p[id2] - s)) <= 0) return 0;
            ld dot1 = dot(v, p[id1] - s);
            ld dot2 = dot(v, p[id2] - s);
            if (dot1 > 0) {
                assert(dot2 > 0);
                ld dis = 0;
                if (dot1 < dot2) dis = (p[id1] - s).len();
                else dis = (p[id2] - s).len();
                return dis / v.len();
            } else {
                assert(dot2 < 0);
                ld dis = 0;
                if (dot1 > dot2) dis = (p[id1] - s).len();
                else dis = (p[id2] - s).len();
                return -dis / v.len();
            }
        } else {
            point t = s + v;
            ld s1 = det(p[id2] - p[id1], s - p[id1]);
            ld s2 = det(p[id2] - p[id1], t - p[id1]);
            return s1 / (s1 - s2);
        }
    }

    ld query(point s, point v) {
        ld a = query_one_set(s, v, upper);
        ld b = query_one_set(s, v, lower);
        if (sgn(a) < 0 && sgn(b) < 0) return 1e10;
        if (a == 1e10) {
            return sgn(b) < 0 ? 1e10 : max(b, 0.L);
        }
        if (b == 1e10) {
            return sgn(a) < 0 ? 1e10 : max(a, 0.L);
        }
        if (sgn(a) * sgn(b) <= 0) return 0;
        return min(a, b);
    }
} a, b;
point v;

int main() {
    a.read(); b.read();
    int x1, x2, y1, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    v.x = x2 - x1, v.y = y2 - y1;

    bool zero = false;
    if (v.x == 0 && v.y == 0) {
        zero = true;
        v.y = 1;
    }

    a.init({{0, 0}, {v.y, -v.x}});
    b.init({{0, 0}, {-v.y, v.x}});

    ld ans = 1e10;
    for (int i = 0; i < b.n; i++) {
        ans = min(ans, a.query(b.p[i], v));
    }
    for (int i = 0; i < a.n; i++) {
        ans = min(ans, b.query(a.p[i], -v));
    }
    if (zero) {
        if (sgn(ans) == 0) cout << 0;
        else cout << -1;
    } else {
        if (ans < 1e10) cout << setiosflags(ios::fixed) << setprecision(8) << ans;
        else cout << -1;
    }
}