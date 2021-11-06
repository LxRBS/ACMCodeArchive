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

    bool operator== (const Point& p) const {return x == p.x && y == p.y;}
    bool operator!= (const Point& p) const {return !operator==(p);}
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


double side(const Point &a, const Point &b, const Point &c) {
  Point ab(b.x-a.x, b.y-a.y);
  Point ac(c.x-a.x, c.y-a.y) ;
  return ab.x*ac.y-ab.y*ac.x ;
}

int convexhull(Point* pts, int nPoints, Point* hull) {
  int nHull = 0;
  int lowPoint = 0 ;
  for (int i=1; i<nPoints; i++)
	if (pts[i].y < pts[lowPoint].y)
	  lowPoint = i ;
  swap(pts[0], pts[lowPoint]) ;
  hull[nHull] = pts[0];
  ++nHull;
  sort(pts+1, pts+nPoints, [&pts](const Point &a, const Point &b) {
	  return side(pts[0], a, b) < 0 ;
	}) ;
  hull[nHull] = pts[1];
  ++nHull;

  for (int i=2; i<nPoints; i++) {
	while (side(hull[nHull-2], hull[nHull-1], pts[i]) > 0)
	  {
		--nHull;
	  }
	hull[nHull] = pts[i];
	++nHull;
  }
  return nHull;
}




int nPoints;
Point3* pts3;
Point* pts;
Point* hull;

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
	/*
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
	*/
}



bool Circle::contains(const Point& p) const
{
    double dx = p.x - center.x;
    double dy = p.y - center.y;
    return dx*dx + dy*dy <= 1.00001  *  radius*radius;
}


ostream& operator<< (ostream& out, const Circle& c) {
    out << c.center << ':' << c.radius;
    return out;
}

	





void sanityCheck(const Circle& c, Point* points, int n)
{
    for (int i = 0; i < n; ++i) {
        if (!c.contains(points[i])) {
            double d = sqrt(points[i].distSqr(c.center));
            cerr << c << " does not contain " << points[i] << ", distance " << d << endl;
        }
    }
}


Point shiftPoint (double alpha, const Point& p1, const Point& p2)
{
    Point p(p1.x + alpha*(p2.x - p1.x), p1.y + alpha*(p2.y - p1.y));
    return p;
}

struct CenterShiftF {
    // Find the point q along the line [c,p] such that
    // distance from q to targetA = distance from q to targetB
    Point c;
    Point p;
    Point targetA;
    Point targetB;

    CenterShiftF (const Point& c0, const Point& p0, const Point& targetA0, const Point& targetB0)
    : c(c0), p(p0), targetA(targetA0), targetB(targetB0)
    {}

    double operator() (double t) const {
        Point q = shiftPoint(t, c, p);
        return q.distSqr(targetA) - q.distSqr(targetB);
    }
};





const double PI = 3.14159265358979323846;

Circle minimumCoveringCircle() {
  hull = new Point[nPoints];
  int nHull = convexhull(pts, nPoints, hull);
  //cerr << "hull\n" << nHull << endl;
  //for (int i = 0; i < nHull; ++i)
  //    cerr << hull[i].x << ' ' << hull[i].y << endl;

  for (int i = 0; i < nHull - 2; ++i)
	for (int j = i + 1; j < nHull - 1; ++j)
	  for (int k = j + 1; k < nHull; ++k) {
		Circle c(hull[i], hull[j], hull[k]);
		bool OK = true;
		for (int m = 0; OK && m < nHull; ++m)
		  if (!c.contains(hull[m])) {
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


void solve(istream& in)
{
    read(in);
    xyOrientation();
    Circle c1 = minimumCoveringCircle();
    double r1 = c1.radius;
    //sanityCheck(c1, pts, nPoints);
    yzOrientation();
    Circle c2 = minimumCoveringCircle();
    double r2 = c2.radius;
    //sanityCheck(c2, pts, nPoints);
    xzOrientation();
    Circle c3 = minimumCoveringCircle();
    double r3 = c3.radius;
    //sanityCheck(c3, pts, nPoints);
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
