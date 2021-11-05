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
/* Author                Roman Elizarov                           */
/******************************************************************/

import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2014 Problem D: Damage Assessment
 * This solution checks correctness of the input.
 *
 * @author Roman Elizarov
 */
public class damage_re {
    private static final String INPUT = "damage.in";
    private static final String OUTPUT = "damage.out";

    private static final double MAX_ERR = 1e-1 * 10e6; // max err in mm^3

    public static void main(String[] args) throws Exception {
        new damage_re().go();
    }

    void go() throws IOException {
        long time = System.currentTimeMillis();
        try (Scanner in = new Scanner(new File(INPUT))) {
            in.useLocale(Locale.US);
            read(in);
        }
        solve();
        try (PrintWriter out = new PrintWriter(OUTPUT)) {
            write(out);
        }
        System.out.printf("Done in %d ms%n", System.currentTimeMillis() - time);
    }

    int d;
    int l;
    int r;
    int t;
    int h;

    void read(Scanner in) {
        d = in.nextInt();
        l = in.nextInt();
        r = in.nextInt();
        t = in.nextInt();
        h = in.nextInt();
        in.nextLine();
        assert d >= 100 && l >= 100;
        assert d <= 10000 && l <= 10000 && r <= 10000;
        assert 2*r >= d;
        assert t >= 0 && t <= l;
        assert h >= 0 && (h <= t || sqr(h - t) * sqr(l) <= sqr(d) * (sqr(l) - sqr(t)));
    }

    private static long sqr(long x) {
        return x * x;
    }

    private static double sqr(double x) {
        return x * x;
    }


    double d2;
    double c;
    double sin;
    double cos;
    boolean hor; // when horizontal
    boolean ver; // when vertical
    double xc;

    double v;

    void solve() {
        d2 = d / 2.0;
        c = Math.sqrt(sqr(r) - sqr(d2));
        sin = (double) t / l;
        cos = Math.sqrt(1 - sqr(sin));
        hor = t == 0;
        ver = t == l;
        xc = hor ? Double.NaN : h / sin - d2 / sin * cos;

        double x1 = c - r;
        double x2 = ver ? h : l - c + r;

        int steps = (int)Math.round(x2 - x1); // integrate millimeters initially
        double dx = (x2 - x1) / steps;

        // max error we can afford per initial integration step
        double maxErr = MAX_ERR / steps;

        double xa = x1;
        double sa = sq(xa);
        for (int i = 0; i < steps; i++) {
            double xb = x1 + (i + 1) * dx;
            double sb = sq(xb);
            v += integrate(xa, xb, sa, sb, maxErr);
            xa = xb;
            sa = sb;
        }
    }

    private double integrate(double xa, double xb, double sa, double sb, double maxErr) {
        double dx = xb - xa;
        if (Math.abs(sa - sb) * dx / 2 < maxErr)
            return (sa + sb) * dx / 2;
        double xc = (xa + xb) / 2;
        double sc = sq(xc);
        return integrate(xa, xc, sa, sc, maxErr / 2) + integrate(xc, xb, sc, sb, maxErr / 2);
    }

    private double sq(double x) {
        double rx;
        if (x >= 0 && x <= l) {
            rx = d2;
        } else {
            double b = x <= 0 ? -x : x - l;
            double rx2 = sqr(r) - sqr(c + b);
            if (rx2 <= 0)
                return 0;
            rx = Math.sqrt(rx2);
        }
        double yh =
            ver ? Double.POSITIVE_INFINITY :
            hor ? h - d2 : (xc - x) / cos * sin;
        double sq;
        double a = yh / rx;
        if (a <= -1)
            sq = 0;
        else if (a >= 1)
            sq = Math.PI * sqr(rx);
        else {
            sq = (Math.PI - Math.acos(a)) * sqr(rx) + yh * rx * Math.sqrt(1 - sqr(a));
        }
        assert !Double.isNaN(sq);
        return sq;
    }

    void write(PrintWriter out) {
        out.printf(Locale.US, "%.2f%n", v / 1e6);
    }

//----------------- just for validation ------------------

    /**
     * Strict scanner to verify 100% correspondence between input files and input file format specification.
     * It is a drop-in replacement for {@link java.util.Scanner} that could be added to a solution source
     * (cut-and-paste) without breaking its ability to work with {@link java.util.Scanner}.
     */
    public class Scanner implements Closeable {
        private final BufferedReader in;
        private String line = "";
        private int pos;
        private int lineNo;
        private boolean localeset;

        public Scanner(File source) throws FileNotFoundException {
            in = new BufferedReader(new FileReader(source));
            nextLine();
        }

        public void close() {
            assert line == null : "Extra data at the end of file";
            try {
                in.close();
            } catch (IOException e) {
                throw new AssertionError("Failed to close with " + e);
            }
        }

        public void nextLine() {
            assert line != null : "EOF";
            assert pos == line.length() : "Extra characters on line " + lineNo;
            try {
                line = in.readLine();
            } catch (IOException e) {
                throw new AssertionError("Failed to read line with " + e);
            }
            pos = 0;
            lineNo++;
        }

        public String next() {
            assert line != null : "EOF";
            assert line.length() > 0 : "Empty line " + lineNo;
            if (pos == 0)
                assert line.charAt(0) > ' ' : "Line " + lineNo + " starts with whitespace";
            else {
                assert pos < line.length() : "Line " + lineNo + " is over";
                assert line.charAt(pos) == ' ' : "Wrong whitespace on line " + lineNo;
                pos++;
                assert pos < line.length() : "Line " + lineNo + " is over";
                assert line.charAt(pos) > ' ' : "Line " + lineNo + " has double whitespace";
            }
            StringBuilder sb = new StringBuilder();
            while (pos < line.length() && line.charAt(pos) > ' ')
                sb.append(line.charAt(pos++));
            return sb.toString();
        }

        public int nextInt() {
            String s = next();
            assert s.length() == 1 || s.charAt(0) != '0' : "Extra leading zero in number " + s + " on line " + lineNo;
            assert s.charAt(0) != '+' : "Extra leading '+' in number " + s + " on line " + lineNo;
            try {
                return Integer.parseInt(s);
            } catch (NumberFormatException e) {
                throw new AssertionError("Malformed number " + s + " on line " + lineNo);
            }
        }

        public double nextDouble() {
            assert localeset : "Locale must be set with useLocale(Locale.US)";
            String s = next();
            assert s.length() == 1 || s.startsWith("0.") || s.charAt(0) != '0' : "Extra leading zero in number " + s + " on line " + lineNo;
            assert s.charAt(0) != '+' : "Extra leading '+' in number " + s + " on line " + lineNo;
            try {
                return Double.parseDouble(s);
            } catch (NumberFormatException e) {
                throw new AssertionError("Malformed number " + s + " on line " + lineNo);
            }
        }

        public void useLocale(Locale locale) {
            assert locale == Locale.US;
            localeset = true;
        }
    }
}

