#include <bits/stdc++.h>

struct Point {
    long double x;
    long double y;
    long double atan;
} p[6005];

struct Tri {
    Point p[3];
} t[2005];

#ifdef INFINITY
#undef INFINITY
#endif
#define INFINITY __builtin_infl()

const static long double eps = 1e-8;
const static Point zero = {0, 0};

bool cmp(const Point& p1, const Point& p2) {
    return p1.atan + eps < p2.atan;
}

long double dist(const Point& p1, const Point& p2) {
    long double x = p1.x - p2.x;
    long double y = p1.y - p2.y;
    return sqrt(x * x + y * y);
}

long double line_cross(const Point& p, const Point& l1, const Point& l2, bool need_eq) {
    Point l;
    l.x = l1.x - l2.x;
    l.y = l1.y - l2.y;
    long double down = p.y * l.x - p.x * l.y;
    long double up = l2.y * p.x - l2.x * p.y;
    // printf("~** %.3Lf %.3Lf\n", up, down);
    if (fabsl(down) < 0) {
        if (fabsl(up) < 0 && need_eq) {
            return std::min(dist(zero, l1), dist(zero, l2)) / dist(zero, p);
        } else {
            return INFINITY;
        }
    }
    long double flag = (need_eq ? 1.L : -1.L);
    long double t_l = up / down;
    if (t_l <= -flag * eps || 1 + flag * eps <= t_l) {
        return INFINITY;
    }

    long double x = l1.x * t_l + l2.x * (1 - t_l);
    long double y = l1.y * t_l + l2.y * (1 - t_l);
    // printf("~@@ %.7Lf %.7Lf %.3Lf\n", x, y, t_l);
    if ((fabsl(p.x) > eps && x / p.x < -eps) || (fabsl(p.y) > eps && y / p.y < -eps)) {
        // printf("~() %.3Lf %.3Lf %.3Lf %.3Lf\n", x, p.x, y, p.y);
        return INFINITY;
    }
    return sqrt(x * x + y * y) / dist(zero, p);
}

bool get_targent(const Point& a, const Point& b, Point* res) {
    long double r = (a.x - b.x) * a.x + (a.y - b.y) * a.y;
    long double d = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    if (r <= eps)
        return false;
    else if (r >= d - eps)
        return false;
    r /= d;
    res->x = a.x + (b.x - a.x) * r;
    res->y = a.y + (b.y - a.y) * r;
    // printf("~++ %.3Lf %.3Lf\n", res->x, res->y);
    return true;
}

int main() {
    int n;
    scanf("%d", &n);
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 3; ++j) {
            int x, y;
            scanf("%d%d", &x, &y);
            p[cnt].x = x;
            p[cnt].y = y;
            t[i].p[j] = p[cnt];
            cnt++;
        }
    }
    Tri& target = t[0];
    // target point on (0,0)
    for (int i = 0; i < 3; ++i) {
        if (fabsl(target.p[i].x) < eps && fabsl(target.p[i].y) < eps) {
            printf("0\n");
            return 0;
        }
    }
    // target line on (0,0)
    for (int i = 0; i < 3; ++i) {
        int j = (i + 1) % 3;
        if (fabsl(target.p[i].x - target.p[j].x) < eps && fabsl(target.p[i].y - target.p[j].y) < eps) {
            continue;
        }
        if (fabsl(target.p[i].x * target.p[j].y - target.p[i].y * target.p[j].x) > eps) {
            continue;
        }
        long double t = target.p[j].x / (target.p[j].x - target.p[i].x);
        if (-eps < t && t < 1 + eps) {
            printf("0\n");
            return 0;
        }
    }
    // add tangent
    for (int i = 0; i < 3; ++i) {
        int j = (i + 1) % 3;
        if (get_targent(target.p[i], target.p[j], p + cnt)) {
            cnt++;
        }
    }

    for (int i = 0; i < cnt; ++i) {
        p[i].atan = atan2l(p[i].y, p[i].x);
    }
    std::sort(p, p + cnt, cmp);
    long double min_dist = INFINITY;
    Point res = zero;
    for (int i = 0; i < cnt; ++i) {
        if (i > 0 && p[i].atan  - p[i - 1].atan < eps) {
            continue;
        }
        long double tt = INFINITY;
        for (int j = 0; j < 3; ++j) {
            long double tmp_t = line_cross(p[i], target.p[j], target.p[(j + 1) % 3], true);
            // printf("~?? %.7Lf %.7Lf %.3Lf %.3Lf\n", p[i].x, p[i].y, tt, tmp_t);
            tt = std::min(tt, tmp_t);
        }
        if (std::isinf(tt)) {
            continue;
        }
        // printf("~## %.3Lf %.3Lf %.3Lf\n", p[i].x, p[i].y, tt);
        
        bool cover = false;
        for (int j = 1; j < n; ++j) {
            for (int k = 0; k < 3; ++k) {
                long double tmp_t = line_cross(p[i], t[j].p[k], t[j].p[(k + 1) % 3], false);
                if (tmp_t < tt + eps) {
                    cover = true;
                    // printf("~$$ %.3Lf %.3Lf %.3Lf %.3Lf %.3Lf\n", t[j].p[k].x, t[j].p[k].y, t[j].p[(k + 1) % 3].x, t[j].p[(k + 1) % 3].y, tmp_t);
                    break;
                }
            }
            if (cover) {
                break;
            }
        }
        if (cover) {
            continue;
        }
        long double d = tt * dist(zero, p[i]);
        // printf("~!! %.3Lf\n", d);
#ifdef CHECK
        if (min_dist > d) {
            min_dist = d;
            res.x = p[i].x * tt;
            res.y = p[i].y * tt;
        }
#else
        min_dist = std::min(min_dist, d);
#endif
    }
    if (std::isinf(min_dist)) {
        printf("-1\n");
        return 0;
    }
    printf("%.9Lf\n", min_dist);
#ifdef CHECK
    printf("%.9Lf %.9Lf\n", res.x, res.y);
#endif
    return 0;
}