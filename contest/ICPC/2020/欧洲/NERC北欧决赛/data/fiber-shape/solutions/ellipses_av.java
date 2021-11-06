import java.io.*;
import java.util.StringTokenizer;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class ellipses_av {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        FastScanner in = new FastScanner(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        EllipticCurves solver = new EllipticCurves();
        solver.solve(1, in, out);
        out.close();
    }

    static class EllipticCurves {
        final static double EPS = 1e-9;

        public void solve(int testNumber, FastScanner in, PrintWriter out) {
            int n = in.nextInt();
            double len = in.nextInt();
            Point[] a = new Point[n];
            for (int i = 0; i < n; i++) {
                a[i] = new Point(in.nextInt(), in.nextInt());
            }
            out.printf("%.15f\n", solve(a, len));
        }

        public double solve(Point[] a, double len) {
            int n = a.length;
            double[] sumDist = new double[n + 1];

        Printer printer = new Printer("plot.tex");
//            Printer printer = new Printer(null);

            printer.addPolygon(a);

            for (int i = 0; i < n; i++) {
                sumDist[i + 1] = sumDist[i] + a[i].distTo(a[(i + 1) % n]);
            }
//            System.err.println(len + " " + sumDist[n]);
            Point startPoint;
            {
                double left = 0, right = 1e6;
                Point vec = new Point(a[n - 1], a[0]);
                vec.normalize();
                for (int IT = 0; IT < 100; IT++) {
                    double mid = (left + right) / 2;
                    Point check = new Point(a[0].x + vec.x * mid, a[0].y + vec.y * mid);
                    double P = findPerimeter(a, sumDist, check);
                    if (P > len) {
                        right = mid;
                    } else {
                        left = mid;
                    }
                }
                left = (left + right) / 2;
                startPoint = new Point(a[0].x + vec.x * left, a[0].y + vec.y * left);
            }
            int[] ts = findTangents(a, startPoint);
//            if (ts == null || ts[0] != 0) {
//                throw new AssertionError();
//            }

//            System.err.println(startPoint);
            double area = 0;
            int j = ts[1];
            for (int i = 0; i < n; i++) {
                while (true) {
                    Ellipse ellipse = new Ellipse(a[i], a[j], len - slicePerimeter(sumDist, j, i));
                    double alpha = ellipse.angleFromPoint(startPoint);
                    double beta1 = ellipse.intersectRay(a[j], new Point(a[(j + 1) % n], a[j]).normalized());
                    double beta2 = ellipse.intersectRay(a[i], new Point(a[i], a[(i + 1) % n]).normalized());

                    Point nextPoint = ellipse.pointFromAngle(Math.min(beta1, beta2));
                    area += ellipse.getArea(alpha, Math.min(beta1, beta2), startPoint, nextPoint);
                    printer.addCurve(ellipse, alpha, Math.min(beta1, beta2));
                    startPoint = nextPoint;
                    if (beta1 < beta2) {
                        j = (j + 1) % n;
                    } else {
                        break;
                    }
                }
            }
//            System.err.println(startPoint);
            printer.close();
            return area;
        }

        private double[] solveQuadratic(double A, double B, double C) {
            double D = B * B - 4 * A * C;
            if (D < -EPS) {
                return new double[]{};
            }
//            if (D < EPS) {
//                return new double[]{-B / 2 / A};
//            }
            D = Math.sqrt(D);
            assert A > 0;
            return new double[]{(-B - D) / 2 / A, (-B + D) / 2 / A};
        }

        private int[] findTangents(Point[] a, Point check) {
            // result[0] is the "left" tangent index, result[1] is the "right" tangent index, if we look from $check
            int[] result = new int[2];
            boolean found = false;
            for (int i = 0; i < a.length; i++) {
                int prev = (i + a.length - 1) % a.length;
                int next = (i + 1) % a.length;
                int prevSide = side(a[i], check, a[prev]);
                int nextSide = side(a[i], check, a[next]);
                if (prevSide >= -EPS & nextSide > EPS) {
                    found = true;
                    result[0] = i;
                }
                if (prevSide < -EPS && nextSide <= EPS) {
                    found = true;
                    result[1] = i;
                }
            }
            if (!found) {
                return null;
            } else {
                return result;
            }
        }

        private int side(Point a, Point b, Point c) {
            double vm = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
            if (Math.abs(vm) < EPS) {
                return 0;
            }
            return (int) Math.signum(vm);
        }

        private double findPerimeter(Point[] a, double[] sumDist, Point check) {
            int[] t = findTangents(a, check);
            if (t == null) {
                return sumDist[sumDist.length - 1];
            }
            return check.distTo(a[t[0]]) + check.distTo(a[t[1]]) + slicePerimeter(sumDist, t[1], t[0]);
        }

        double slicePerimeter(double[] sumDist, int from, int to) {
            if (from > to) {
                double compl = sumDist[from] - sumDist[to];
                return sumDist[sumDist.length - 1] - compl;
            }
            return sumDist[to] - sumDist[from];
        }

        class Point {
            double x;
            double y;

            public String toString() {
                return "(" + x + ", " + y +
                        ')';
            }

            public Point(double x, double y) {
                this.x = x;
                this.y = y;
            }

            public Point(Point a, Point b) {
                this.x = b.x - a.x;
                this.y = b.y - a.y;
            }

            public double distTo(Point other) {
                double dx = x - other.x, dy = y - other.y;
                return Math.sqrt(dx * dx + dy * dy);
            }

            public void normalize() {
                double d = Math.sqrt(x * x + y * y);
                x /= d;
                y /= d;
            }

            public Point normalized() {
                double d = Math.sqrt(x * x + y * y);
                return new Point(x / d, y / d);
            }

            public double vm(Point other) {
                return x * other.y - y * other.x;
            }

        }

        class Ellipse {
            Point f1;
            Point f2;
            double distSum;
            Point o;
            Point v1;
            Point v2;
            double A;
            double B;

            public Ellipse(Point f1, Point f2, double distSum) {
                this.f1 = f1;
                this.f2 = f2;
                this.distSum = distSum;

                this.o = new Point((f1.x + f2.x) / 2, (f1.y + f2.y) / 2);
                this.v1 = new Point(o, f1);
                v1.normalize();
                this.v2 = new Point(-v1.y, v1.x);
                double d = f1.distTo(f2);
                this.A = distSum / 2;
                this.B = Math.sqrt(distSum * distSum - d * d) / 2;
            }

            public double angleFromPoint(Point startPoint) {
                double cosAngle = ((startPoint.x - o.x) * v1.x + (startPoint.y - o.y) * v1.y) / A;
                double sinAngle = ((startPoint.x - o.x) * v2.x + (startPoint.y - o.y) * v2.y) / B;
                double angle = Math.atan2(sinAngle, cosAngle);
                while (angle < -EPS) {
                    angle += 2 * Math.PI;
                }
                return angle;
            }

            public Point pointFromAngle(double angle) {
                double cosAngle = Math.cos(angle), sinAngle = Math.sin(angle);
                return new Point(o.x + A * v1.x * cosAngle + B * v2.x * sinAngle, o.y + A * v1.y * cosAngle + B * v2.y * sinAngle);
            }

            public double intersectRay(Point s, Point d) {
                // s + d * t = o + v1 * A * cos(alpha) + v2 * B * sin(alpha)
                // take scalar product with v1 and v2:
                // (s - o) * v1 + d * v1 * t = A * cos(alpha)
                // (s - o) * v2 + d * v2 * t = B * sin(alpha)
                // divide by a or b, square, and add
                double sov1 = ((s.x - o.x) * v1.x + (s.y - o.y) * v1.y) / A;
                double dv1 = (d.x * v1.x + d.y * v1.y) / A;
                double sov2 = ((s.x - o.x) * v2.x + (s.y - o.y) * v2.y) / B;
                double dv2 = (d.x * v2.x + d.y * v2.y) / B;

                double[] t = solveQuadratic(
                        dv1 * dv1 + dv2 * dv2,
                        2 * sov1 * dv1 + 2 * sov2 * dv1,
                        sov1 * sov1 + sov2 * sov2 - 1
                );
                // t[0] should be < 0, t[1] should be > 0, take the positive root
                if (t.length == 0 || (t.length == 1 && t[0] < EPS) || (t.length == 2 && (t[0] > -EPS || t[1] < EPS))) {
                    throw new AssertionError();
                }
                return angleFromPoint(new Point(s.x + d.x * t[t.length / 2], s.y + d.y * t[t.length / 2]));
            }

            public double getArea(double alpha, double beta, Point startPoint, Point nextPoint) {
                // Green's formula applied to area: integrate from alpha to beta: 1/2 (x(t), y(t))*(x'(t), y'(t)) dt
                // (x(t), y(t)) = o + A * v1 * cos(t) + B * v2 * sin(t)
                // (x'(t), y'(t)) = B * v2 * cos(t) - A * v1 * sin(t)
                // (x(t), y(t)) * (x'(t), y'(t)) = (o*v2) * B * cos(t) - (o*v1) * A * sin(t) + A * B * (v1 * v2 * cos(t)^2 - v2 * v1 * sin(t)^2)
                // which further simplifies to (o*v2) * B * cos(t) - (o*v1) * A * sin(t) + A * B
                // integrate this for t in [alpha, beta]
                double ov2b = o.vm(v2) * B;
                double ov1a = o.vm(v1) * A;
                return 0.5 * A * B * (beta - alpha) + 0.5 * ov2b * (Math.sin(beta) - Math.sin(alpha)) - 0.5 * ov1a * (-Math.cos(beta) + Math.cos(alpha));
            }

        }

        class Printer {
            PrintWriter out;

            public Printer(String fileName) {
                if (fileName == null) {
                    return;
                }
                try {
                    out = new PrintWriter(fileName);
                    out.print(
                            "\\begin{tikzpicture}\n" +
                                    "\\begin{axis}[grid=both,trig format plots=rad, axis equal]\n");
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                }
            }

            public void addCurve(Ellipse e, double from, double to) {
                if (out == null) {
                    return;
                }
                out.printf("\\addplot [domain=%.8f:%.8f,samples=50]" +
                                "({%.8f + %.8f*cos(\\x) + %.8f * sin(\\x)}," +
                                "{%.8f + %.8f*cos(\\x) + %.8f * sin(\\x)}); \n",
                        from, to,
                        e.o.x, e.A * e.v1.x, e.B * e.v2.x,
                        e.o.y, e.A * e.v1.y, e.B * e.v2.y
                );
            }

            public void close() {
                if (out == null) {
                    return;
                }
                out.print(
                        "\\end{axis}\n" +
                                "\\end{tikzpicture}");
                out.close();
            }

            public void addPolygon(Point[] a) {
                if (out == null) {
                    return;
                }
                out.println("\\draw[thick] " + a[0]);
                for (int i = 1; i < a.length; i++) {
                    out.println("-- " + a[i]);
                }
                out.println("-- cycle;");
            }

        }

    }

    static class FastScanner {
        public BufferedReader br;
        public StringTokenizer st;

        public FastScanner(InputStream in) {
            br = new BufferedReader(new InputStreamReader(in));
        }

        public FastScanner(String fileName) {
            try {
                br = new BufferedReader(new FileReader(fileName));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

        public String next() {
            while (st == null || !st.hasMoreElements()) {
                String line = null;
                try {
                    line = br.readLine();
                } catch (IOException e) {
                    throw new UnknownError();
                }
                if (line == null) {
                    throw new UnknownError();
                }
                st = new StringTokenizer(line);
            }
            return st.nextToken();
        }

    }
}

