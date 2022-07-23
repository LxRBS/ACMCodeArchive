#include <bits/stdc++.h>
using namespace std;

typedef double lf;

struct vec {
    lf x, y, z;
    vec(){} vec(lf x, lf y, lf z): x(x), y(y), z(z) {}
    vec operator-(vec b) { return vec(x - b.x, y - b.y, z - b.z); }
    vec operator+(vec b) { return vec(x + b.x, y + b.y, z + b.z); }
    vec operator*(lf k) { return vec(k * x, k * y, k * z); }
    lf sqr() { return x * x + y * y + z * z; }
    lf len() { return sqrt(x * x + y * y + z * z); }
    vec trunc(lf k = 1) { return *this * (k / len()); }
    friend vec cross(vec a, vec b) {
        return vec(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }
    friend lf dot(vec a, vec b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }
    void scan() {
        scanf("%lf%lf%lf", &x, &y, &z);
    }
};

void inter_ff(vec p1, vec dir1, vec p2, vec dir2, vec &res1, vec &res2) {
	vec e = cross(dir1, dir2), v = cross(dir1, e);
	lf d = dot(dir2, v); if (abs(d) < 1e-9) return;
	vec q = p1 + v * (dot(dir2, p2 - p1) / d);
    res1 = q;
    res2 = q + e;
}

lf dist_pp(vec p1, vec p2) {
    return (p2 - p1).len();
}

lf dist_pl(vec p, vec l1, vec l2) {
    return cross(l2 - l1, p - l1).len() / (l2 - l1).len();
}

vec perpendicular_pl(vec p, vec l1, vec l2) {
    return l1 + (l2 - l1) * (dot(l2 - l1, p - l1) / (l2 - l1).sqr());
}

void solve() {
    vec p1, d1, p2, d2;
    lf r1, r2;

    p1.scan();
    d1.scan();
    scanf("%lf", &r1);
    p2.scan();
    d2.scan();
    scanf("%lf", &r2);

    vec dir = cross(d1, d2);
    if (dir.sqr() < 0.1) {
        puts("No");
        return;
    }

    vec l1, l2;
    inter_ff(p1, d1, p2, d2, l1, l2);
    lf dis = dist_pl(p2, l1, l2);
    if (dis > r2) {
        puts("No");
        return;
    }
    vec delta = (l2 - l1).trunc(sqrt(r2 * r2 - dis * dis));
    vec mid = perpendicular_pl(p2, l1, l2);
    vec a = mid + delta;
    vec b = mid - delta;
    if ((dist_pp(a, p1) < r1) ^ (dist_pp(b, p1) < r1)) {
        puts("Yes");
    } else {
        puts("No");
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}