#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;



struct Point3 {
    double x;
    double y;
    double z;

    Point3(double x0, double y0, double z0) : x(x0), y(y0), z(z0) {}
    Point3() {}
};

struct Point {
    double x;
    double y;

    Point(double x0, double y0) : x(x0), y(y0) {}
    Point() {}

    double distSqr(const Point& p) const;
};

double Point::distSqr(const Point& p) const
{
    double dx = x - p.x;
    double dy = y - p.y;
    return dx*dx + dy*dy;
}

ostream& operator<< (ostream& out, const Point& p) {
    out << '(' << p.x << ',' << p.y << ')';
    return out;
}


int nPoints;
Point3* pts3;
Point* pts;

void read(istream& in)
{
    in >> nPoints;
    pts3 = new Point3[nPoints];
    pts = new Point[nPoints];

    for (int i = 0; i < nPoints; ++i)
    {
        double x, y, z;
        in >> x >> y >> z;
        pts3[i] = Point3(x,y,z);
    }
}

void xyOrientation()
{
    for (int i = 0; i < nPoints; ++i)
    {
        pts[i].x = pts3[i].x;
        pts[i].y = pts3[i].y;
    }
}

void xzOrientation()
{
    for (int i = 0; i < nPoints; ++i)
    {
        pts[i].x = pts3[i].x;
        pts[i].y = pts3[i].z;
    }
}

void yzOrientation()
{
    for (int i = 0; i < nPoints; ++i)
    {
        pts[i].x = pts3[i].y;
        pts[i].y = pts3[i].z;
    }
}

struct Circle {
    Point center;
    double radius;

    Circle (const Point& c, double r) : center(c), radius(r) {}

    Circle(const Point& p1, const Point& p2, const Point& p3);

    bool contains (const Point& p) const;
};

bool Circle::contains(const Point& p) const
{
    double dx = p.x - center.x;
    double dy = p.y - center.y;
    return dx*dx + dy*dy <= 1.00001 * radius*radius;
}

Circle::Circle(const Point& p1, const Point& p2, const Point& p3)
{
    double dsqr1 = p1.distSqr(p2);
    double dsqr2 = p1.distSqr(p3);
    double dsqr3 = p2.distSqr(p3);
    if (dsqr1 > dsqr2 && dsqr1 > dsqr3) {
        // form circle with two points on a diameter and third inside
        center = Point((p1.x+p2.x)/2.0, (p1.y+p2.y)/2.0);
        radius = sqrt(dsqr1)/2.0;
        if (contains(p3))
            return;
    } else if (dsqr2 > dsqr1 && dsqr2 > dsqr3) {
        // form circle with two points on a diameter and third inside
        center = Point((p1.x+p3.x)/2.0, (p1.y+p3.y)/2.0);
        radius = sqrt(dsqr2)/2.0;
        if (contains(p2))
            return;
    } else if (dsqr3 > dsqr1 && dsqr3 > dsqr2) {
        // form circle with two points on a diameter and third inside
        center = Point((p2.x + p3.x) / 2.0, (p2.y + p3.y) / 2.0);
        radius = sqrt(dsqr3)/2.0;
        if (contains(p1))
            return;
    }
    /*
    // Form circle with all three points on perimeter
    double ax = (p1.x + p2.x) / 2;
    double ay = (p1.y + p2.y) / 2;
    double ux = (p1.y - p2.y);
    double uy = (p2.x - p1.x);
    double bx = (p2.x + p3.x) / 2;
    double by = (p2.y + p3.y) / 2;
    double vx = (p2.y - p3.y);
    double vy = (p3.x - p2.x);
    double dx = ax - bx;
    double dy = ay - by;
    double vu = vx * uy - vy * ux;
    double g = (dx * uy - dy * ux) / vu;
    center.x = bx + g * vx;
    center.y = by + g * vy;
    double rx = p1.x - center.x;
    double ry = p1.y - center.y;
    radius = sqrt(rx*rx + ry*ry);
     */

    double a = p1.x * (p2.y - p3.y) - p1.y * (p2.x - p3.x) + p2.x * p3.y - p3.x * p2.y;

    double b = (p1.x * p1.x + p1.y * p1.y) * (p3.y - p2.y)
            + (p2.x * p2.x + p2.y * p2.y) * (p1.y - p3.y)
            + (p3.x * p3.x + p3.y * p3.y) * (p2.y - p1.y);

    double c = (p1.x * p1.x + p1.y * p1.y) * (p2.x - p3.x)
            + (p2.x * p2.x + p2.y * p2.y) * (p3.x - p1.x)
            + (p3.x * p3.x + p3.y * p3.y) * (p1.x - p2.x);

    center.x = -b / (2 * a);
    center.y = -c / (2 * a);
    radius = sqrt(center.distSqr(p1));
}

ostream& operator<< (ostream& out, const Circle& c) {
    out << c.center << ':' << c.radius;
    return out;
}



Circle minimumCoveringCircle(int startingFrom) {
    for (int i = 0; i < nPoints - 2; ++i)
        for (int j = i + 1; j < nPoints - 1; ++j)
            for (int k = j + 1; k < nPoints; ++k) {
                Circle c(pts[i], pts[j], pts[k]);
                bool OK = true;
                for (int m = 0; OK && m < nPoints; ++m)
                    if (!c.contains(pts[m])) {
                        OK = false;
                    }
                if (OK) {
				    cerr << "radius " << c.radius << " from " <<
						 i << ' ' << j << ' ' << k << endl;

                    return c;
				}
            }
    return Circle(Point(0, 0), 1.0);
}

void sanityCheck(const Circle& c)
{
    for (int i = 0; i < nPoints; ++i) {
        if (!c.contains(pts[i])) {
            double d = sqrt(pts[i].distSqr(c.center));
            cerr << c << " does not contain " << pts[i] << ", distance " << d << endl;
        }
    }
}

void solve(istream& in)
{
    read(in);
    xyOrientation();
    Circle c1 = minimumCoveringCircle(0);
    double r1 = c1.radius;
    sanityCheck(c1);
    yzOrientation();
    Circle c2 = minimumCoveringCircle(0);
    double r2 = c2.radius;
    sanityCheck(c2);
    xzOrientation();
    Circle c3 = minimumCoveringCircle(0);
    double r3 = c3.radius;
    sanityCheck(c3);
    double r = min(r1, min(r2, r3));
    cout << 2.0*r << endl;
}




int main(int argc, char** argv) {

    if (argc != 1) {
        ifstream input(argv[1]);
        solve(input);
    } else
        solve(cin);
    return 0;
}
