#include "bits/stdc++.h"

using namespace std;
using db = long double;
const db PI = acosl(-1.0);
const int N = 1e4 + 50;

struct point {
    db x, y;

    point() = default;

    point(db x, db y) : x(x), y(y) {}

    point operator+(const point &a) const { return point(x + a.x, y + a.y); }

    point operator-(const point &a) const { return point(x - a.x, y - a.y); }

    db operator*(const point &a) const { return x * a.x + y * a.y; }

    db operator^(const point &a) const { return x * a.y - y * a.x; }

    point operator*(const db &a) const { return point(a * x, a * y); }

    point operator/(const db &a) const { return point(x / a, y / a); }

    db len() const { return sqrtl(x * x + y * y); }
};

using vp = vector<point>;

db get_angle(point a, point b) {
    db angb = atan2l(b.y, b.x), anga = atan2l(a.y, a.x);
    db ret = angb - anga;
    while (ret >= PI) ret -= 2 * PI;
    while (ret < 0) ret += 2 * PI;
    if (ret > PI) ret = 2 * PI - ret;
    return ret;
}

int n, r1, r2, a[N];
vp tp, pp;

db secl(db a) { return 1.0l / cosl(a); }

db cal(db beta) {
    db ret = 0;
    ret += 0.5l * (1.0l * r1 * r1 * r2 * r2 + 0.5l * r2 * r2 * r2 * r2) * beta;
    ret -= 1.0l / 12.0l * (1.0l * r1 * r1 * r1 * r1 * secl(beta) * secl(beta) * tanl(beta));
    ret -= 2.0l / 3.0l * r1 * r2 * r2 * r2 * sinl(beta);
    return ret;
}

void solve() {
    db ans = 0, sum = 0;
    tp.clear(), pp.clear();
    scanf("%d%d%d", &n, &r1, &r2);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]), tp.emplace_back(r1 * cosl(a[i] * PI / 10000.0), r1 * sinl(a[i] * PI / 10000.0));
    tp.push_back(tp.front());
    reverse(tp.begin(), tp.end());
    tp.emplace_back(r1 * cosl(a[n] * PI / 10000.0), r1 * sinl(a[n] * PI / 10000.0));
    reverse(tp.begin(), tp.end());
    for (int i = 1; i <= n; ++i) {
        db beta = get_angle(tp[i], (tp[i] + tp[i - 1]) / 2);
        db ret = cal(beta);
        ans += ret;

        beta = get_angle(tp[i], (tp[i + 1] + tp[i]) / 2);
        ret = cal(beta);
        ans += ret;

        point midp = (tp[i] + tp[i + 1]) / 2;
        midp = midp / midp.len() * r1 * secl(beta);
        pp.push_back(midp);
    }
    sum += abs(pp[0] ^ pp.back());
    for (int i = 1; i < n; ++i)
        sum += abs(pp[i] ^ pp[i - 1]);
    sum /= 2;
    ans /= PI * 1.0 * r2 * r2 - sum;
    cout << fixed << setprecision(12) << ans << "\n";
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--)
        solve();
    return 0;
}