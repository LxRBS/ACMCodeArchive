#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <unordered_set>
#include <vector>

// correct but too slow O(n^4)

class Point {
    public:
        Point(double _x, double _y) : x(_x), y(_y) {}

        double x, y;

        double dot(Point const &other) const { return x * other.x + y * other.y; }
        Point operator-(Point const &other) const { return Point(x - other.x, y - other.y); }
        Point operator+(Point const &other) const { return Point(x + other.x, y + other.y); }
        Point operator*(double d) const { return Point(x * d, y * d); }
        Point operator/(double d) const { return Point(x / d, y / d); }

        bool operator==(Point const &other) const { return x == other.x && y == other.y; }
};

class PointHash {
    public:
        size_t operator()(Point const &p) const {
            auto x = std::hash<double>()(p.x);
            auto y = std::hash<double>()(p.y);
            return x * y;
        }
};

// three distinct points define a circle
//   a, b, c
//
//   <a-p,a-p> - r^2 = 0 (1)
//   <b-p,b-p> - r^2 = 0 (2)
//   <c-p,c-p> - r^2 = 0 (3)
//
//   Taking (2) - (1) eliminates terms leading to:
//       <b,b> - <a,a> - 2<p,b-a> = 0
//   Taking (3) - (1) eliminates terms leading to:
//       <c,c> - <a,a> - 2<p,c-a> = 0
//   
//   Solving each of these for p.x and setting them equal to each other gives
//       <b,b> - <a,a> - 2p.y(b.y-a.y)   <c,c> - <a,a> - 2p.y(c.y-a.y)
//       ----------------------------- = -----------------------------
//             2(b.x-a.x)                      2(c.x-a.x)
//
//   Let B = <b,b> - <a,a>               C = <c,c> - <a,a>
//       D = 2(b.y-a.y)                  E = 2(c.y-a.y)
//       F = 2(b.x-a.x)                  G = 2(c.x-a.x)
//   
//   Gives (B - p.y * D) / F = (C - p.y * E) / G
//
//   and p.y = (F*C - G*B) / (F*E - G*D)
//
//   Then plug in p.y to get p.x, and then both to get r^2


double min_diameter_circle(std::vector<Point> const &points) {
    double eps = 1e-7;

    // find a bound on the minimum radius needed to exclude some options
    double required_r2 = 0;
    for (auto a = points.begin(); a != points.end(); ++a) {
        for (auto b = a + 1; b != points.end(); ++b) {
            auto p = (*a + *b) / 2;
            auto ap = p - *a;
            required_r2 = std::max(required_r2, ap.dot(ap));
        }
    }

    double min_r2 = 1e100;
    // smallest circle defined by two points
    for (auto a = points.begin(); a != points.end(); ++a) {
        for (auto b = a + 1; b != points.end(); ++b) {
            auto p = (*a + *b) / 2;
            auto r2 = (*a - p).dot(*a - p);
            if (required_r2 <= r2) {
                auto broke_early = false;
                for (auto const &d : points) {
                    auto dp = p - d;
                    if (r2 + eps < dp.dot(dp)) {
                        broke_early = true;
                        break;
                    }
                }

                if (not broke_early)
                    min_r2 = std::min(min_r2, r2);
            }
        }
    }

    // smallest circle defined by three points
    for (auto a = points.begin(); a != points.end(); ++a) {
        auto a_dot_a = a->dot(*a);
        for (auto b = a + 1; b != points.end(); ++b) {
            auto b_dot_b = b->dot(*b);

            auto B = b_dot_b - a_dot_a;
            auto D = 2 * (b->y - a->y);
            auto F = 2 * (b->x - a->x);

            for (auto c = b + 1; c != points.end(); ++c) {
                auto C = c->dot(*c) - a_dot_a;
                auto E = 2 * (c->y - a->y);
                auto G = 2 * (c->x - a->x);

                auto denom = F * E - G * D;
                if (denom == 0)
                    // a, b, c are collinear
                    continue;
                auto num = F * C - G * B;

                // now we have the center
                auto py = num / denom;
                auto px = (F != 0) ? (B - py * D) / F : (C - py * E) / G;
                Point p(px, py);
                // and the radius^2
                auto ap = p - *a;
                auto r2 = ap.dot(ap);

                // sanity check that the center is equidistant from the three points
                assert(abs(1 - (p - *a).dot(p - *a) / (p - *b).dot(p - *b)) < 1e-3);
                assert(abs(1 - (p - *a).dot(p - *a) / (p - *c).dot(p - *c)) < 1e-3);

                if (min_r2 <= r2)
                    // don't bother checking, we already have a smaller radius^2
                    continue;

                if (r2 < required_r2)
                    // cannot capture all the points
                    continue;

                auto broke_early = false;
                for (auto const &d : points) {
                    auto dp = p - d;
                    if (r2 + eps < dp.dot(dp)) {
                        broke_early = true;
                        break;
                    }
                }

                if (not broke_early)
                    min_r2 = std::min(min_r2, r2);
            }
        }
    }

    return sqrt(min_r2) * 2;
}

int main(int argc, char **argv) {
    int n;
    std::cin >> n;

    std::vector<double> x(n), y(n), z(n);
    std::unordered_set<Point, PointHash> uxy, uxz, uyz;
    for (int i = 0; i < n; ++i) {
        std::cin >> x[i] >> y[i] >> z[i];
        uxy.insert(Point(x[i], y[i]));
        uxz.insert(Point(x[i], z[i]));
        uyz.insert(Point(y[i], z[i]));
    }

    std::vector<Point> xy(uxy.begin(), uxy.end());
    std::vector<Point> xz(uxz.begin(), uxz.end());
    std::vector<Point> yz(uyz.begin(), uyz.end());

    double smallest = 1e100;
    for (auto const &pts : {xy, xz, yz})
        smallest = std::min(smallest, min_diameter_circle(pts));

    std::cout << std::fixed << std::setprecision(10) << smallest << std::endl;
}

