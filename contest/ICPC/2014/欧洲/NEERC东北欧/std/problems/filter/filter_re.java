/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem F. Filter                                              */
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
import java.util.Locale;

/**
 * Solution for NEERC'2014 Problem F: Filter
 * This solution checks correctness of the input.
 *
 * @author Roman Elizarov
 */
public class filter_re {
    private static final String INPUT = "filter.in";
    private static final String OUTPUT = "filter.out";

    public static void main(String[] args) throws Exception {
        new filter_re().go();
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

    int m;
    int f;
    int[] a;

    int n;
    byte[][] hex;

    int q;
    int[] u;

    void read(Scanner in) {
        m = in.nextInt();
        f = in.nextInt();
        assert m >= 1 && m <= 1000;
        assert f >= 1 && f <= 100;
        a = new int[f];
        for (int i = 0; i < f; i++) {
            a[i] = in.nextInt();
            assert a[i] >= 1;
        }
        in.nextLine();
        n = in.nextInt();
        in.nextLine();
        assert n >= 1 && n <= 1000;
        int sl = (m + 3) / 4;
        hex = new byte[n][sl];
        for (int d = 0; d < n; d++) {
            String s = in.next();
            in.nextLine();
            assert s.length() == sl;
            for (int p = 0; p < sl; p++) {
                char c = s.charAt(p);
                assert c >= '0' && c <= '9' || c >= 'a' && c <= 'f';
                hex[d][p] = (byte)(c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10);
                int usedBits = p < sl - 1 ? 4 : ((m - 1) % 4) + 1;
                assert (hex[d][p] & ~((1 << usedBits) - 1)) == 0;
            }
        }
        q = in.nextInt();
        assert q >= 1 && q <= 1000;
        u = new int[q];
        for (int k = 0; k < q; k++) {
            u[k] = in.nextInt();
            assert u[k] >= 1;
            for (int z = 0; z < k; z++)
                assert u[z] != u[k] : "u must be distinct";
        }
        in.nextLine();
    }

    int s;
    boolean[] b;

    void solve() {
        b = new boolean[n];
        int[] j = new int[f];
        for (int k = 0; k < q; k++) {
            for (int i = 0; i < f; i++) {
                j[i] = (int)(((long)u[k] * a[i]) % m);
            }
            for (int d = 0; d < n; d++) {
                boolean all = true;
                for (int i = 0; i < f; i++) {
                    if ((hex[d][j[i] / 4] & (1 << (j[i] % 4))) == 0)
                        all = false;
                }
                if (all && !b[d]) {
                    b[d] = true;
                    s++;
                }
            }
        }
    }

    void write(PrintWriter out) {
        out.print(s);
        for (int k = 0; k < n; k++) {
            if (b[k])
                out.print(" " + k);
        }
        out.println();
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

