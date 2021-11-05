/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem B. Burrito King                                        */
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
import java.util.stream.Collectors;

/**
 * Solution for NEERC'2014 Problem T:
 * This solution checks correctness of the input.
 *
 * @author Roman Elizarov
 */
public class burrito_re {
    private static final String INPUT = "burrito.in";
    private static final String OUTPUT = "burrito.out";

    public static void main(String[] args) throws Exception {
        new burrito_re().go();
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

    static class Ing implements Comparable<Ing> {
        int i;
        int g;
        int a;
        int b;

        Ing(int i, int g, int a, int b) {
            this.i = i;
            this.g = g;
            this.a = a;
            this.b = b;
        }

        @Override
        public int compareTo(Ing o) {
            return b * o.a - a * o.b;
        }
    }

    int n;
    int A;
    int B;
    Ing[] is;

    void read(Scanner in) {
        n = in.nextInt();
        A = in.nextInt();
        B = in.nextInt();
        in.nextLine();
        assert n >= 1 && n <= 100_000;
        assert A >= 0 && A <= 1_000_000_000;
        assert B >= 0 && B <= 1_000_000_000;
        is = new Ing[n];
        for (int i = 0; i < n; i++) {
            int g = in.nextInt();
            int a = in.nextInt();
            int b = in.nextInt();
            in.nextLine();
            assert g >= 0 && g <= 100;
            assert a >= 0 && a <= 100;
            assert b >= 0 && b <= 100;
            is[i] = new Ing(i, g, a, b);
        }
    }

    double[] s;
    double ta;
    double tb;

    void solve() {
        s = new double[n];
        List<Ing> nz = Arrays.asList(is).stream()
                .filter(ing -> ing.g > 0 && ing.a > 0)
                .sorted()
                .collect(Collectors.toList());
        for (Ing ing : nz) {
            double pa = (double) ing.g * ing.a;
            double pb = (double) ing.g * ing.b;
            if (tb + pb <= B) {
                s[ing.i] = ing.g;
                ta += pa;
                tb += pb;
            } else {
                double f = (B - tb) / pb;
                s[ing.i] = ing.g * f;
                ta += ing.a * (B - tb) / ing.b; // pa * f; but 100% precise for integers
                tb = B;
                break;
            }
        }
    }

    void write(PrintWriter out) {
        if (ta < A)
            out.println("-1 -1");
        else {
            out.println(ta + " " + tb);
            for (int i = 0; i < n; i++) {
                if (i > 0)
                    out.print(' ');
                out.print(s[i]);
            }
            out.println();
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

