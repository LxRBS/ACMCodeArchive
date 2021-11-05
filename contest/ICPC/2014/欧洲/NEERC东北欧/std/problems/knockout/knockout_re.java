/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem K. Knockout Racing                                     */
/*                                                                */
/* Original idea         Vitaliy Aksenov                          */
/* Problem statement     Vitaliy Aksenov                          */
/* Test set              Vitaliy Aksenov                          */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Roman Elizarov                           */
/******************************************************************/

import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2014 Problem K: Knockout Racing
 * This solution checks correctness of the input.
 *
 * @author Roman Elizarov
 */
public class knockout_re {
    private static final String INPUT = "knockout.in";
    private static final String OUTPUT = "knockout.out";

    public static void main(String[] args) throws Exception {
        new knockout_re().go();
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

    int n;
    int m;
    int[] a;
    int[] b;
    int[] x;
    int[] y;
    int[] t;

    void read(Scanner in) {
        n = in.nextInt();
        m = in.nextInt();
        in.nextLine();
        assert n >= 1 && n <= 1000;
        assert m >= 1 && m <= 1000;
        a = new int[n];
        b = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = in.nextInt();
            b[i] = in.nextInt();
            in.nextLine();
            assert a[i] >= 0 && a[i] <= 1_000_000_000;
            assert b[i] >= 0 && b[i] <= 1_000_000_000;
            assert a[i] != b[i];
        }
        x = new int[m];
        y = new int[m];
        t = new int[m];
        for (int j = 0; j < m; j++) {
            x[j] = in.nextInt();
            y[j] = in.nextInt();
            t[j] = in.nextInt();
            in.nextLine();
            assert 0 <= x[j] && x[j] <= y[j] && y[j] <= 1_000_000_000;
            assert t[j] >= 0 && t[j] <= 1_000_000_000;
        }
    }

    int[] c;

    void solve() {
        c = new int[m];
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) {
                int di = Math.abs(a[i] - b[i]);
                int dd = b[i] > a[i] ? 1 : -1;
                int t0 = t[j] % (2 * di);
                if (t0 > di)
                    t0 = 2 * di - t0;
                int z = a[i] + dd * t0;
                if (z >= x[j] && z <= y[j])
                    c[j]++;
            }
        }

    }

    void write(PrintWriter out) {
        for (int j = 0; j < m; j++) {
            out.println(c[j]);
        }
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

