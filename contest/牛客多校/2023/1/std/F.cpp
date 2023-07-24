#include<bits/stdc++.h>
using namespace std;

const double eps = 1e-8;
const double RBase = 1e6;
const double pi = acos(-1.0);

typedef complex<double> Comp;
struct Circle {
    Comp o;
    double r;
};

// 反演运算
Circle inv(const Circle &circ, const Circle &base) {
    auto[z, r] = circ;
    auto[o, R] = base;
    double d2 = norm(z - o);
    double a = d2 - r * r;
    return {R * (z - o) / a, R * r / abs(a)};
}

int main() {
    int n;
    cin >> n;

    vector<Circle> circ(n);
    for (int i = 0; i < n; ++i) {
        double x, y, r;
        cin >> x >> y >> r;
        circ[i] = {Comp(x, y), r};
    }
    if (n <= 3) {
        cout << n << endl;
        return 0;
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            Comp o, p;
            vector<Circle> tr(n);
            // 反演所有的圆
            {
                auto[o1, r1] = circ[i];
                auto[o2, r2] = circ[j];
                Comp A = o2 - o1, A2 = A * A;
                double An2 = norm(A);
                if (An2 >= eps) {
                    Comp B = -(o2 * o2 - o1 * o1) * An2 + (r2 * r2 - r1 * r1) * A2;
                    Comp C = (o2 * r1 * r1 - o1 * r2 * r2) * A2 + o1 * o2 * (o2 - o1) * An2;
                    o = (-B + sqrt(B * B - A * C * An2 * 4.0)) / (A * An2 * 2.0);
                    for (int k = 0; k < n; ++k) {
                        auto[z, r] = circ[k];
                        double d = abs(z - o);
                        tr[k] = inv(circ[k], {o, RBase});
                    }
                    p = (tr[i].o + tr[j].o) / 2.0;
                    for (int k = 0; k < n; ++k) tr[k].o -= p;
                }
            }

            // 计算角度然后转化到区间问题
            double Ro = max(tr[i].r, tr[j].r);
            double Ri = min(tr[i].r, tr[j].r);
            vector<pair<double, int>> seg;
            seg.reserve(n * 6);
            // 维护差分数组
            auto add2 = [&seg](double x, double y) {
                x = max(x, -pi), y = min(y, pi);
                if (x >= y) return;
                seg.emplace_back(x, 1);
                seg.emplace_back(y, -1);
            };
            // 为防止[350,10]出现，因而倍长
            auto add = [add2](double x, double y) {
                x -= eps, y += eps;
                add2(x, y);
                add2(x + 2 * pi, y + 2 * pi);
                add2(x - 2 * pi, y - 2 * pi);
            };
            for (int k = 0; k < n; ++k) {
                if (k == i || k == j) continue;
                auto[z, r] = tr[k];
                double D1 = norm(z) + Ro * Ri - r * r;
                double D2 = abs(z) * (Ro + Ri);
                double A = acos((D1 - r * (Ro - Ri)) / D2);
                double B = acos((D1 + r * (Ro - Ri)) / D2);
                double C = arg(z);
                add(C - A, C - B), add(C + B, C + A);
            }
            sort(seg.begin(), seg.end());

            int cnt = 2;
            for (auto[x, c]: seg) ans = max(ans, cnt += c);
        }
    }
    cout << ans << endl;
    return 0;
}
