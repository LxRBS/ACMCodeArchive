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

Point computeCentroid (Point* p, int n)
{
  double sumx = 0.0;
  double sumy = 0.0;
  for (int i = 0; i < n; ++i)
	{
	  sumx += p[i].x;
	  sumy += p[i].y;
	}
  return Point(sumx/(double)n, sumy/(double)n);
}

int ptFarthestFrom (Point* p, int n, const Point& from)
{
  double dmax = -1.0;
  int imax = -1;
  for (int i = 0; i < n; ++i)
	{
	  double d = p[i].distSqr(from);
	  if (d > dmax)
		{
		  dmax = d;
		  imax = i;
		}
	}
  return imax;
}

	


template <class Function>
double secantMethod (double tmin, double tmax, Function f, double epsilon)
{
    double t0 = tmin;
    double t1 = tmax;
    double f0 = f(t0);
    double f1 = f(t1);
    double mult = 1.0;
    if (f0 > 0.0) {
        if (f1 < 0.0) {
            mult = -1;
            f1 = -f1;
            f0 = -f0;
        }
        else
            return t1;
    }
    else {
        if (f1 > 0.0)
            mult = 1.0;
        else
            return t1;
        return tmin - epsilon;
    }
    const int limit = 1000;
    int cnt = 0;
    while ((t1 - t0 > epsilon) && (cnt < limit)) {
        ++cnt;
        double t2 = t0 - f0 * (t1 - t0) / (f1 - f0);
        if (t2 == t0 || t2 == t1)
            return t2;
        double f2 = mult * f(t2);
        if (f2 > 0.0) {
            t1 = t2;
            f1 = f2;
        } else if (f2 < 0.0) {
            t0 = t2;
            f0 = f2;
        } else
            return t2;
    }
    return 0.5 * (t0 + t1);
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


double centerShift (const Circle& c, const Point& preserve, const Point& toHit)
{
    CenterShiftF f(c.center, preserve, preserve, toHit);
    double alpha = secantMethod(0.0, 1.0, f, 0.0001);
    return alpha;
}

double centerShift (const Circle& c, const Point& preserve0, const Point& preserve1, const Point& toHit)
{
    Point mid ((preserve0.x + preserve1.x)/2.0, (preserve0.y + preserve1.y)/2.0);
    CenterShiftF f(c.center, mid, preserve1, toHit);
    double alpha = secantMethod(0.0, 1.0, f, 0.0001);
    return alpha;
}


Point midpt(const Point& p, const Point& q)
{
    return Point((p.x + q.x)/2.0, (p.y+q.y)/2.0);
}

int shiftTowardsMidpoint(Point* points, int nPts, Circle &c, const Point &p0, const Point &p1) {
    int i2 = -1;
    double alpha2 = 1.1;
    double rad = 0.0;
    Point newC;
    for (int i = 0; i < nPts; ++i) {
        Point& p = points[i];
        if (p != p0 && p != p1) {
            double alpha = centerShift(c, p0, p1, points[i]);
            Point newC0 = shiftPoint(alpha, c.center, midpt(p0, p1));
            double rad0 = sqrt(newC0.distSqr(p0));
            if (rad0 > rad) {
                alpha2 = alpha;
                i2 = i;
                rad = rad0;
                newC = newC0;
            }
        }
    }
    c = Circle(newC, rad);
    //sanityCheck(c, points, nPts);
    return i2;
}

int shiftTowardsMidpoint(Point* points, int nPts, Circle &c, const Point &p0, const Point &p1, const Point& inner) {
    int i2 = -1;
    double alpha2 = 1.1;
    double rad = 0.0;
    Point newC;
    for (int i = 0; i < nPts; ++i) {
        Point &p = points[i];
        if (p != p0 && p != p1) {
            double alpha = centerShift(c, p0, p1, points[i]);
            Point newC0 = shiftPoint(alpha, c.center, midpt(p0, p1));
            double rad0 = sqrt(newC0.distSqr(p0));
            double dInner = sqrt(newC0.distSqr(inner));
            if (rad0 > rad && dInner <= rad0) {
                alpha2 = alpha;
                i2 = i;
                rad = rad0;
                newC = newC0;
            }
        }
    }
    if (i2 >= 0) {
        c = Circle(newC, rad);
        //sanityCheck(c, points, nPts);
    }
    return i2;
}





const double PI = 3.14159265358979323846;

Circle minimumCoveringCircle() {
  hull = new Point[nPoints];
  int nHull = convexhull(pts, nPoints, hull);
  //cerr << "hull\n" << nHull << endl;
  //for (int i = 0; i < nHull; ++i)
  //    cerr << hull[i].x << ' ' << hull[i].y << endl;
  Point centroid = computeCentroid(hull, nHull);
  int i0 = ptFarthestFrom(hull, nHull, centroid);
  Point p0 = hull[i0];  // This point must be on the circle perimeter
  swap (hull[i0], hull[0]);
  Circle c(centroid, hypot(p0.x-centroid.x, p0.y-centroid.y));
  // Find next point by moving c's center towards p0 until we hit another point
  int i1 = 0;
  double alpha1 = 1.1;
  for (int i = 1; i < nHull; ++i)
  {
      double alpha = centerShift(c, p0, hull[i]);
      if (alpha < alpha1)
      {
          alpha1 = alpha;
          i1 = i;
      }
  }
  Point p1 = hull[i1];
  swap(hull[1], hull[i1]);
  c.center = shiftPoint(alpha1, c.center, p0);
  c.radius *= (1.0 - alpha1);
  //sanityCheck(c, hull, nHull);

  // If p0 and p1 are on a diameter, we are done
  if (sqrt(p0.distSqr(p1)) == 2*c.radius)
      return c;

  // Find 3rd point by shifting the center towards the midpoint of [p0,p1]
  int i2 = shiftTowardsMidpoint(hull, nHull, c, p0, p1);
  Point p2 = hull[i2];
  //sanityCheck(c, hull, nHull);

  bool changed = true;
  while (changed)
  {
      double oldRadius = c.radius;
      changed = false;

      // Try to replace p2
      int k = shiftTowardsMidpoint(hull, nHull, c, p0, p1, p2);
      if (k >= 0) {
          p2 = hull[k];
          changed = (c.radius < oldRadius);
      }

      // Try to replace p1
      k = shiftTowardsMidpoint(hull, nHull, c, p0, p2, p1);
      if (k >= 0) {
          p1 = hull[k];
          changed = changed || (c.radius < oldRadius);
      }

      // Try to replace p0
      k = shiftTowardsMidpoint(hull, nHull, c, p1, p2, p0);
      if (k >= 0) {
          p0 = hull[k];
          changed = changed || (c.radius < oldRadius);
      }
  }
  return c;
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
