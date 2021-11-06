#include <iostream>
#include <vector>
#include <cmath>

class Point {
    public:
        Point(double _x=0, double _y=0) : x(_x), y(_y) {}

        double norm2() const { return x * x + y * y; }
        Point operator-(Point const &p) const { return Point(x - p.x, y - p.y); }
        Point operator+(Point const &p) const { return Point(x + p.x, y + p.y); }
        Point operator*(double d) const { return Point(x * d, y * d); }
        Point operator/(double d) const { return Point(x / d, y / d); }
        bool operator==(Point const &p) const { return x == p.x and y == p.y; }

        double x, y;
};

class Circle {
    public:
        Circle(Point const &_c, double _r2) : c(_c), r2(_r2) {}

        Point c;
        double r2;

        bool contains(Point const &p) const { return (p - c).norm2() <= r2; }

        static Circle from_points(std::vector<Point> const &points) {
            switch (points.size()) {
                case 0: return Circle(Point(0, 0), 0);
                case 1: return Circle(points[0], 0);
                case 2: return from_two_points(points[0], points[1]);
                case 3: return from_three_points(points[0], points[1], points[2]);
            }
            return Circle(Point(0, 0), 0);
        }

        static Circle from_two_points(Point const &a, Point const &b) {
            Point c = (a + b) / 2;
            double r2 = (a - c).norm2();
            return Circle(c, r2);
        }

        static Circle from_three_points(Point const &a, Point const &b, Point const &c) {
            double B = b.norm2() - a.norm2();
            double D = 2 * (b.y - a.y);
            double F = 2 * (b.x - a.x);

            double C = c.norm2() - a.norm2();
            double E = 2 * (c.y - a.y);
            double G = 2 * (c.x - a.x);

            double denom = F * E - G * D;
            if (denom == 0) {
                double ab = (a - b).norm2();
                double ac = (a - c).norm2();
                double bc = (b - c).norm2();
                if (ab <= bc && ac <= bc)
                    return Circle::from_two_points(b, c);
                if (ab <= ac && bc <= ac)
                    return Circle::from_two_points(a, c);
                if (bc <= ab && ac <= ab)
                    return Circle::from_two_points(a, b);
            }
            double num = F * C - G * B;

            double py = num / denom;
            double px = (0 == F) ? (B - py * D) / F : (C - py * E) / G;
            Point p(px, py);
            Point ap = p - a;
            double r2 = ap.norm2();

            return Circle(p, r2);
        }
};

Circle sed_welzl(std::vector<Point> *P, std::vector<Point> *R) {
    if (P->size() == 0 or R->size() == 3) {
        return Circle::from_points(*R);
    }

    int i = rand() % P->size();
    std::swap(P->at(i), P->back());
    Point p = P->back();
    P->pop_back();

    Circle D = sed_welzl(P, R);

    if (not D.contains(p)) {
        R->push_back(p);
        D = sed_welzl(P, R);
        R->pop_back();
    }

    P->push_back(p);

    return D;
}


int main(int argc, char **argv) {
    int n;
    std::cin >> n;
    std::vector<Point> xy(n), xz(n), yz(n);
    for (int i = 0; i < n; ++i) {
        double x, y, z;
        std::cin >> x >> y >> z;
        xy[i] = Point(x, y);
        xz[i] = Point(x, z);
        yz[i] = Point(y, z);
    }

    std::vector<Point> R;
    double smallest = sed_welzl(&xy, &R).r2;
    smallest = std::min(smallest, sed_welzl(&xz, &R).r2);
    smallest = std::min(smallest, sed_welzl(&yz, &R).r2);

    std::cout << sqrt(smallest) * 2 << std::endl;

    return 0;
}
