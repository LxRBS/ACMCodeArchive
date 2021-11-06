import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class SoilDrilling_sjz {

public static class Point3 {
    double x;
    double y;
    double z;

    Point3(double x0, double y0, double z0) {
        x = x0;
        y = y0;
        z = z0;
    }
    Point3() {}
}



public static class Point implements Comparable<Point>{
    
    public static Point p0; // used for orientation

    
    double x;
    double y;

    Point(double x0, double y0) {
        x = x0;
        y = y0;
    }

    Point() {}

    double distSqr(Point p) {
        double dx = x - p.x;
        double dy = y - p.y;
        return dx*dx + dy*dy;
    }

    public boolean equals (Object obj)
    {
        if (obj instanceof Point) {
            Point p = (Point)obj;
            return x == p.x && y == p.y;
        } else {
            return false;
        }
    }

    public String toString() {
        return "(" + x + "," + y + ")";
    }
    
    @Override
    public int compareTo(Point p) {
        double orient = orientation(this, p0,  p);
        if (orient != 0.0) {
            return (orient > 0.0) ? 1 : -1;
        } else {
            return (p0.distSqr(p) >= p0.distSqr(this)) ? -1 : 1;
        }
        
    }


    private static double orientation(Point p1, Point p2, Point  p3) {
        double d = ((double)p2.x - (double)p1.x)*((double)p3.y - (double)p1.y) 
                - ((double)p2.y - (double)p1.y)*((double)p3.x - (double)p1.x);
        return d;
    }

}


double side(Point a, Point b, Point c) {
  Point ab = new Point(b.x-a.x, b.y-a.y);
  Point ac = new Point(c.x-a.x, c.y-a.y) ;
  return ab.x*ac.y-ab.y*ac.x ;
}



private int pseudoHull(Point[] points) {
    // A quick and dirty replacement for a convex hull
    Point maxx = points[0];
    Point minx = points[0];
    Point maxy = points[0];
    Point miny = points[0];
    
    for (int i = 1; i < points.length; ++i) {
        Point p = points[i];
        if (p.x > maxx.x) 
            maxx = p;
        if (p.x < minx.x) 
            minx = p;
        if (p.y > maxy.y) 
            maxy = p;
        if (p.y < miny.y) 
            miny = p;
    }
    
    int hullEnd = points.length;
    if (!maxx.equals(minx)) {
        hullEnd = removeInteriorPoints(points, minx, miny, maxx, points.length);
        if (!miny.equals(maxy))
            hullEnd = removeInteriorPoints(points, minx, maxy, maxx, hullEnd);
    } else if (!maxy.equals(miny)) {
        hullEnd = removeInteriorPoints(points, miny, minx, maxy, points.length);
    }
    return hullEnd;
}

static class Line {
    Point p1;
    Point p2;
    Line (Point p1, Point p2) {this.p1 = p1; this.p2 = p2;}
    
    boolean onSameSide (Point a, Point b) {
        double v = (p1.y - p2.y)*(a.x - p1.x) + (p2.x - p1.x)*(a.y - p1.y);
        double w = (p1.y - p2.y) * (b.x - p1.x) + (p2.x - p1.x) * (b.y - p1.y);
        double c = v * w;
        return c > 0.0;
    }
}

private int removeInteriorPoints(Point[] points, Point p1, Point p2, Point p3, int length) {
    // Remove any points on the interior of the triangle formed by p1, p2, & p3
    Point centroid = new Point ((p1.x+p2.x+p3.x)/3.0, (p1.y+p2.y+p3.y)/3.0);
    Line line1 = new Line(p1, p2);
    Line line2 = new Line(p1, p3);
    Line line3 = new Line(p2, p3);
    
    int hullEnd = 0;
    for (int i = 0; i < length; ++i) {
        Point p = points[i];
        if (!line1.onSameSide(centroid, p) || !line2.onSameSide(centroid, p)
                || !line3.onSameSide(centroid, p)) {
            points[hullEnd] = p;
            ++hullEnd;
        }
    }
    return hullEnd;
}



int nPoints;
Point3[] pts3;
Point[] pts;
Point[] hull;

void read(BufferedReader in)
{
    Scanner input = new Scanner(in);
    nPoints = input.nextInt();
    pts3 = new Point3[nPoints];
    pts = new Point[nPoints];

    for (int i = 0; i < nPoints; ++i)
    {
        double x = input.nextDouble();
        double y = input.nextDouble();
        double z = input.nextDouble();
        pts3[i] = new Point3(x,y,z);
    }
    input.close();
}

void xyOrientation()
{
    for (int i = 0; i < nPoints; ++i)
    {
        pts[i] = new Point(pts3[i].x, pts3[i].y);
    }
}

void xzOrientation()
{
    for (int i = 0; i < nPoints; ++i)
    {
        pts[i] = new Point(pts3[i].x, pts3[i].z);
    }
}

void yzOrientation()
{
    for (int i = 0; i < nPoints; ++i)
    {
        pts[i] = new Point(pts3[i].y, pts3[i].z);
    }
}

public static class Circle {
    Point center;
    double radius;

    Circle (Point c, double r) {
        center = c;
        radius = r;
    }


    boolean contains (Point p) {
        double dx = p.x - center.x;
        double dy = p.y - center.y;
        return dx*dx + dy*dy <= 1.00001  *  radius*radius;
    }

    public String toString() {
        return center.toString() + ":" + radius;
    }
}

Point computeCentroid (Point[] p, int n)
{
  double sumx = 0.0;
  double sumy = 0.0;
  for (int i = 0; i < n; ++i)
	{
	  sumx += p[i].x;
	  sumy += p[i].y;
	}
  return new Point(sumx/(double)n, sumy/(double)n);
}

int ptFarthestFrom (Point[] p, int n, Point from)
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

	
public interface Function {
    double f (double alpha);
}

double secantMethod (double tmin, double tmax, Function f, double epsilon)
{
    double t0 = tmin;
    double t1 = tmax;
    double f0 = f.f(t0);
    double f1 = f.f(t1);
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
    final int limit = 1000;
    int cnt = 0;
    while ((t1 - t0 > epsilon) && (cnt < limit)) {
        ++cnt;
        double t2 = t0 - f0 * (t1 - t0) / (f1 - f0);
        if (t2 == t0 || t2 == t1)
            return t2;
        double f2 = mult * f.f(t2);
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


/*
void sanityCheck(const Circle& c, Point* points, int n)
{
    for (int i = 0; i < n; ++i) {
        if (!c.contains(points[i])) {
            double d = sqrt(points[i].distSqr(c.center));
            cerr << c << " does not contain " << points[i] << ", distance " << d << endl;
        }
    }
}
*/

Point shiftPoint (double alpha, Point p1, Point p2)
{
    Point p = new Point(p1.x + alpha*(p2.x - p1.x), p1.y + alpha*(p2.y - p1.y));
    return p;
}

class CenterShiftF implements Function{
    // Find the point q along the line [c,p] such that
    // distance from q to targetA = distance from q to targetB
    Point c;
    Point p;
    Point targetA;
    Point targetB;

    CenterShiftF (Point c0, Point p0, Point targetA0, Point targetB0) {
        c = c0;
        p = p0;
        targetA = targetA0;
        targetB = targetB0;
    }

    public double f (double t)  {
        Point q = shiftPoint(t, c, p);
        return q.distSqr(targetA) - q.distSqr(targetB);
    }
}


double centerShift (Circle c, Point preserve, Point toHit)
{
    CenterShiftF f = new CenterShiftF(c.center, preserve, preserve, toHit);
    double alpha = secantMethod(0.0, 1.0, f, 0.0001);
    return alpha;
}

double centerShift (Circle c, Point preserve0, Point preserve1, Point toHit)
{
    Point mid  = new Point((preserve0.x + preserve1.x)/2.0,
            (preserve0.y + preserve1.y)/2.0);
    CenterShiftF f = new CenterShiftF(c.center, mid, preserve1, toHit);
    double alpha = secantMethod(0.0, 1.0, f, 0.0001);
    return alpha;
}


Point midpt(Point p, Point q)
{
    return new Point((p.x + q.x)/2.0, (p.y+q.y)/2.0);
}

int shiftTowardsMidpoint(Point[] points, int nPts, Circle c, Point p0, Point p1) {
    int i2 = -1;
    double alpha2 = 1.1;
    double rad = 0.0;
    Point newC = new Point(0.0, 0.0);
    for (int i = 0; i < nPts; ++i) {
        Point p = points[i];
        if (!p.equals(p0) && !p.equals(p1)) {
            double alpha = centerShift(c, p0, p1, points[i]);
            Point newC0 = shiftPoint(alpha, c.center, midpt(p0, p1));
            double rad0 = Math.sqrt(newC0.distSqr(p0));
            if (rad0 > rad) {
                alpha2 = alpha;
                i2 = i;
                rad = rad0;
                newC = newC0;
            }
        }
    }
    c.center = newC;
    c.radius = rad;
    //sanityCheck(c, points, nPts);
    return i2;
}

int shiftTowardsMidpoint(Point[] points, int nPts, Circle c, Point p0, Point p1, Point inner) {
    int i2 = -1;
    double alpha2 = 1.1;
    double rad = 0.0;
    Point newC = new Point();
    for (int i = 0; i < nPts; ++i) {
        Point p = points[i];
        if (!p.equals(p0) && !p.equals(p1)) {
            double alpha = centerShift(c, p0, p1, points[i]);
            Point newC0 = shiftPoint(alpha, c.center, midpt(p0, p1));
            double rad0 = Math.sqrt(newC0.distSqr(p0));
            double dInner = Math.sqrt(newC0.distSqr(inner));
            if (rad0 > rad && dInner <= rad0) {
                alpha2 = alpha;
                i2 = i;
                rad = rad0;
                newC = newC0;
            }
        }
    }
    if (i2 >= 0) {
        c.center = newC;
        c.radius = rad;
        //sanityCheck(c, points, nPts);
    }
    return i2;
}



final double PI = 3.14159265358979323846;

double hypot(double x, double y) {
    return Math.sqrt(x*x + y*y);
}

Circle minimumCoveringCircle() {
  hull = pts;
  int nHull = pseudoHull(pts);
  //cerr << "hull\n" << nHull << endl;
  //for (int i = 0; i < nHull; ++i)
  //    cerr << hull[i].x << ' ' << hull[i].y << endl;
  Point centroid = computeCentroid(hull, nHull);
  int i0 = ptFarthestFrom(hull, nHull, centroid);
  Point p0 = hull[i0];  // This point must be on the circle perimeter
  hull[i0] = hull[0];
  hull[0] = p0;
  Circle c = new Circle(centroid, hypot(p0.x-centroid.x, p0.y-centroid.y));
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
  hull[i1] = hull[1];
  hull[1] = p1;
  c.center = shiftPoint(alpha1, c.center, p0);
  c.radius *= (1.0 - alpha1);
  //sanityCheck(c, hull, nHull);

  // If p0 and p1 are on a diameter, we are done
  if (Math.sqrt(p0.distSqr(p1)) == 2*c.radius)
      return c;

  // Find 3rd point by shifting the center towards the midpoint of [p0,p1]
  int i2 = shiftTowardsMidpoint(hull, nHull, c, p0, p1);
  Point p2 = hull[i2];
  //sanityCheck(c, hull, nHull);

  boolean changed = true;
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


void solve(BufferedReader in)
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
    double r = Math.min(r1, Math.min(r2, r3));
    System.out.println(2.0*r);
}



public static void main(String[] args) throws FileNotFoundException, IOException {
    if (args.length > 0) {
        for (int i = 0; i < args.length; ++i) {
            try (BufferedReader input 
                    = new BufferedReader(new FileReader(args[i])))
            {
                new SoilDrilling_sjz().solve(input);
            }
        }
    } else {
        BufferedReader input 
            = new BufferedReader (new InputStreamReader(System.in));
        new SoilDrilling_sjz().solve(input);
    }

}

}