/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem I. Improvements                                        */
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
import java.util.Arrays;
import java.util.HashSet;
import java.util.Locale;
import java.util.Set;

/**
 * Solution for NEERC'2014 Problem I: Improvements
 * This solution checks correctness of the input.
 * This solution works in O(n log(n)).
 *
 * @author Roman Elizarov
 */
public class improvements_re {
    private static final String INPUT = "improvements.in";
    private static final String OUTPUT = "improvements.out";

    public static void main(String[] args) throws Exception {
        new improvements_re().go();
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
    int[] x;

    void read(Scanner in) {
        n = in.nextInt();
        in.nextLine();
        assert n >= 1 && n <= 200_000;
        x = new int[n + 1];
        Set<Integer> xs = new HashSet<>(); // for validation only
        for (int i = 1; i <= n; i++) {
            x[i] = in.nextInt();
            assert x[i] >= 1 && x[i] <= n;
            assert xs.add(x[i]);
        }
        in.nextLine();
    }

    static class FT {
        int[] ft;

        FT(int n) {
            ft = new int[n];
        }

        void update(int i, int v) {
            while (i < ft.length) {
                ft[i] = Math.max(ft[i], v);
                i |= i + 1;
            }
        }

        int getTo(int i) {
            int result = 0;
            while (i >= 0) {
                result = Math.max(result, ft[i]);
                i = (i & (i + 1)) - 1;
            }
            return result;
        }
    }

    int[] at;
    int[] rdn;
    int[] ldn;
    int answer;

    void solve() {
        at = new int[n + 1];
        for (int i = 1; i <= n; i++)
            at[x[i]] = i;
        rdn = new int[n + 2];
        Arrays.fill(rdn, 1, n + 1, 1);
        FT rft = new FT(n + 1);
        for (int i = n; i >= 1; i--) {
            rdn[i] = rft.getTo(at[i] - 1) + 1;
            rft.update(at[i], rdn[i]);
            rdn[i] = Math.max(rdn[i], rdn[i + 1]);
        }
        ldn = new int[n + 2];
        Arrays.fill(ldn, 1, n + 1, 1);
        FT lft = new FT(n + 1);
        for (int i = 1; i <= n; i++) {
            ldn[i] = lft.getTo(at[i] - 1) + 1;
            lft.update(at[i], ldn[i]);
            ldn[i] = Math.max(ldn[i], ldn[i - 1]);
        }
        for (int i = 1; i <= n + 1; i++)
            answer = Math.max(answer, ldn[i - 1] + rdn[i]);
    }

    void write(PrintWriter out) {
        out.println(answer);
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

