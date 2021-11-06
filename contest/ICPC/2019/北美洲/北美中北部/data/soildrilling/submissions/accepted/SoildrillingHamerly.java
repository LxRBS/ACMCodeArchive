import java.util.*;
import java.io.*;

public class SoildrillingHamerly {
    public static Random rn = new Random();

    public static class Point {
        public double x, y;
        public Point(double _x, double _y) { x = _x; y = _y; }
        public double norm2() { return x * x + y * y; }
        public Point sub(Point other) { return new Point(x - other.x, y - other.y); }
        public Point add(Point other) { return new Point(x + other.x, y + other.y); }
        public Point mul(double z) { return new Point(x * z, y * z); }
        public Point div(double z) { return new Point(x / z, y / z); }

        public int hashCode() {
            return Double.valueOf(x).hashCode() * Double.valueOf(y).hashCode();
        }

        public boolean equals(Object o) {
            Point p = (Point)o;
            return x == p.x && y == p.y;
        }
    }


    public static class Circle {
        public Point c;
        public double r2;

        public Circle(Point _c, double _r2) { c = _c; r2 = _r2; }

        boolean contains(Point p) {
            return p.sub(c).norm2() <= r2;
        }

        static public Circle from_points(ArrayList<Point> points) {
            if (points.size() == 0)
                return new Circle(new Point(0, 0), 0);
            if (points.size() == 1)
                return new Circle(points.get(0), 0);
            if (points.size() == 2)
                return Circle.from_two_points(points.get(0), points.get(1));
            if (points.size() == 3)
                return Circle.from_three_points(points.get(0), points.get(1), points.get(2));
            return null;
        }

        static public Circle from_two_points(Point a, Point b) {
            Point c = a.add(b).div(2);
            double r2 = a.sub(c).norm2();
            return new Circle(c, r2);
        }

        static public Circle from_three_points(Point a, Point b, Point c) {
            double B = b.norm2() - a.norm2();
            double D = 2 * (b.y - a.y);
            double F = 2 * (b.x - a.x);

            double C = c.norm2() - a.norm2();
            double E = 2 * (c.y - a.y);
            double G = 2 * (c.x - a.x);

            double denom = F * E - G * D;
            if (denom == 0) {
                double ab = a.sub(b).norm2();
                double ac = a.sub(c).norm2();
                double bc = b.sub(c).norm2();
                if (ab <= bc && ac <= bc)
                    return Circle.from_two_points(b, c);
                if (ab <= ac && bc <= ac)
                    return Circle.from_two_points(a, c);
                if (ac <= ab && bc <= ab)
                    return Circle.from_two_points(a, b);
            }
            double num = F * C - G * B;

            double py = num / denom;
            double px = (F != 0) ? (B - py * D) / F : (C - py * E) / G;
            Point p = new Point(px, py);
            double r2 = p.sub(a).norm2();

            return new Circle(p, r2);
        }
    }

    public static Circle sed_welzl(ArrayList<Point> P, ArrayList<Point> R) {
        if (P.size() == 0 || R.size() == 3) {
            return Circle.from_points(R);
        }

        int last = P.size() - 1;
        int i = rn.nextInt(P.size());
        Point p = P.get(i);
        P.set(i, P.get(last));
        P.remove(last);

        Circle D = sed_welzl(P, R);

        if (!D.contains(p)) {
            R.add(p);
            D = sed_welzl(P, R);
            R.remove(R.size() - 1);
        }

        P.add(p);

        return D;
    }


    public static void main(String args[]) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();

        double x[] = new double[n];
        double y[] = new double[n];
        double z[] = new double[n];

        HashSet<Point> uxy = new HashSet<Point>();
        HashSet<Point> uxz = new HashSet<Point>();
        HashSet<Point> uyz = new HashSet<Point>();

        for (int i = 0; i < n; ++i) {
            x[i] = input.nextDouble();
            y[i] = input.nextDouble();
            z[i] = input.nextDouble();

            uxy.add(new Point(x[i], y[i]));
            uxz.add(new Point(x[i], z[i]));
            uyz.add(new Point(y[i], z[i]));
        }

        ArrayList<Point> xy = new ArrayList<Point>(uxy);
        ArrayList<Point> xz = new ArrayList<Point>(uxz);
        ArrayList<Point> yz = new ArrayList<Point>(uyz);

        Circle c1 = sed_welzl(xy, new ArrayList<Point>());
        Circle c2 = sed_welzl(xz, new ArrayList<Point>());
        Circle c3 = sed_welzl(yz, new ArrayList<Point>());

        double smallest = Math.min(Math.min(c1.r2, c2.r2), c3.r2);

        System.out.println(Math.sqrt(smallest) * 2);
    }
}
