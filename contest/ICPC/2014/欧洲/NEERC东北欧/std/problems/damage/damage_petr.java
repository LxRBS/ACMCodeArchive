/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem D. Damage Assessment                                   */
/*                                                                */
/* Original idea         Roman Elizarov                           */
/* Problem statement     Roman Elizarov                           */
/* Test set              Roman Elizarov                           */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Petr Mitrichev                           */
/******************************************************************/

import java.io.InputStreamReader;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.io.FileInputStream;
import java.util.StringTokenizer;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class damage_petr {
    public static void main(String[] args) {
        InputStream inputStream;
        try {
            inputStream = new FileInputStream("damage.in");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        OutputStream outputStream;
        try {
            outputStream = new FileOutputStream("damage.out");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Damage solver = new Damage();
        solver.solve(1, in, out);
        out.close();
    }
}

class Damage {
    static final int POINTS = 1 << 30;
    static final int MAX_STEP = 1 << 14;
    static final double BUBEN = 1e3;

    static interface Function {
        double f(double x);
    }

    public void solve(int testNumber, InputReader in, PrintWriter out) {
        int d = in.nextInt();
        int l = in.nextInt();
        int r = in.nextInt();
        int t = in.nextInt();
        int h = in.nextInt();
        double vx = Math.sqrt(l * l - t * t) / l;
        double vy = (double) t / l;
        double res = bottomSphere(d, r, h, vx, vy) + cylinder(d, l, h, vx, vy) + topSphere(d, r, h, l, vx, vy);
        out.println(res / 1e6);
    }

    private double topSphere(final int d, final int r, final int h, final int l, final double vx, final double vy) {
        final double rDist = Math.sqrt(r * (double) r - d * (double) d / 4.0);
        Function f = new Function() {
            @Override
            public double f(double x) {
                double dist = (x * (double) r + (1.0 - x) * rDist);
                double rad = Math.sqrt(r * r - dist * dist);
                double ymin = (l + dist - rDist) * vy - rad * vx + d / 2.0 * vx;
                double ymax = (l + dist - rDist) * vy + rad * vx + d / 2.0 * vx;
                double area;
                if (ymin > h) area = circleFrac(0.0); else if (ymax <= h) area = circleFrac(1.0); else {
                    double frac = (h - ymin) / (ymax - ymin);
                    area = circleFrac(frac);
                }
                area *= rad * rad;
                return area;
            }
        };
        double integ = integrate(f);
        return (r - rDist) * integ;
    }

    private double cylinder(final int d, final int l, final int h, final double vx, final double vy) {
        Function f = new Function() {
            @Override
            public double f(double x) {
                double offset = x * l;
                double rad = d / 2.0;
                double ymin = offset * vy;
                double ymax = offset * vy + d * vx;
                double area;
                if (ymin > h) area = circleFrac(0.0); else if (ymax <= h) area = circleFrac(1.0); else {
                    double frac = (h - ymin) / (ymax - ymin);
                    area = circleFrac(frac);
                }
                area *= rad * rad;
                return area;
            }
        };
        double integ = integrate(f);
        return l * integ;
    }

    private double integrate(Function f) {
        double num = 0;
        double den = 0;
        for (int i = 0; i < POINTS;) {
            int STEP = MAX_STEP;
            while (i + STEP > POINTS) STEP >>= 1;
            while (true) {
                double x0 = f.f(i / (double) POINTS);
                double x2 = f.f((i + STEP) / (double) POINTS);
                if (STEP == 2 || Math.abs(x0 - x2) < BUBEN) {
                    double x1 = f.f((i + STEP / 2) / (double) POINTS);
                    den += 6.0 * STEP;
                    num += (x0 + 4 * x1 + x2) * STEP;
                    i += STEP;
                    break;
                }
                STEP >>= 1;
            }
        }
        return num / den;
    }

    private double bottomSphere(final int d, final int r, final int h, final double vx, final double vy) {
        final double rDist = Math.sqrt(r * (double) r - d * (double) d / 4.0);
        Function f = new Function() {
            @Override
            public double f(double x) {
                double dist = (x * (double) r + (1.0 - x) * rDist);
                double rad = Math.sqrt(r * r - dist * dist);
                double ymin = -(dist - rDist) * vy - rad * vx + d / 2.0 * vx;
                double ymax = -(dist - rDist) * vy + rad * vx + d / 2.0 * vx;
                double area;
                if (ymin > h) area = circleFrac(0.0); else if (ymax <= h) area = circleFrac(1.0); else {
                    double frac = (h - ymin) / (ymax - ymin);
                    area = circleFrac(frac);
                }
                area *= rad * rad;
                return area;
            }
        };
        double integ = integrate(f);
        return (r - rDist) * integ;
    }

    private double circleFrac(double frac) {
        if (frac >= 1.0) return Math.PI;
        if (frac <= 0.0) return 0.0;
        if (frac > 0.5) return Math.PI - circleFrac(1.0 - frac);
        double outside = 2 * (0.5 - frac);
        double alpha = Math.acos(outside);
        return alpha - Math.sin(2 * alpha) / 2.0;
    }
}

class InputReader {
    public BufferedReader reader;
    public StringTokenizer tokenizer;

    public InputReader(InputStream stream) {
        reader = new BufferedReader(new InputStreamReader(stream), 32768);
        tokenizer = null;
    }

    public String next() {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            try {
                tokenizer = new StringTokenizer(reader.readLine());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        return tokenizer.nextToken();
    }

    public int nextInt() {
        return Integer.parseInt(next());
    }

}

