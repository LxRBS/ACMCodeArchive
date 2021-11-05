/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem J. Jokewithpermutation                                 */
/*                                                                */
/* Original idea         Mikhail Dvorkin                          */
/* Problem statement     Mikhail Dvorkin                          */
/* Test set              Maxim Babenko                            */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Roman Elizarov                           */
/******************************************************************/

import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2014 Problem J: Jokewithpermutation
 * This solution checks correctness of the input.
 *
 * @author Roman Elizarov
 */
public class joke_re {
    private static final String INPUT = "joke.in";
    private static final String OUTPUT = "joke.out";

    public static void main(String[] args) throws Exception {
        new joke_re().go();
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

    char[] s;

    void read(Scanner in) {
        s = in.next().toCharArray();
        in.nextLine();
    }

    static int fitness(String s) {
        joke_re solver = new joke_re();
        solver.s = s.toCharArray();
        solver.solve();
        return solver.cnt;
    }

    int n;
    int m;

    int cnt = 0;

    static class NI {
        int i;
        char[] nc;
        int nl;
        int cc;
        int[] cp;

        NI(int i) {
            this.i = i;
        }
    }

    NI[] nis;
    int[] pu;

    void solve() {
        while (m < s.length) {
            n++;
            m += n < 10 ? 1 : 2;
        }
        assert m == s.length;
        assert n >= 1 && n <= 50;
        nis = new NI[n];
        for (int i = 1; i <= n; i++) {
            NI ni = new NI(i);
            ni.nc = String.valueOf(i).toCharArray();
            ni.nl = ni.nc.length;
            ni.cp = new int[m];
            for (int p = 0; p <= m - ni.nl; p++) {
                boolean match = s[p] == ni.nc[0];
                if (ni.nl == 2)
                    match &= s[p + 1] == ni.nc[1];
                if (match) {
                    ni.cp[ni.cc++] = p;
                }
            }
            nis[i - 1] = ni;
        }
        Arrays.sort(nis, Comparator.comparing(ni -> ni.cc));
        pu = new int[m + 1];
        pu[m] = 3;
        boolean found = find(0);
        assert found;
        assert pu[0] == 1;
    }

    boolean find(int i) {
        ++cnt;
        if (i >= n)
            return true;
        NI ni = nis[i];
        for (int j = 0; j < ni.cc; j++) {
            int p = ni.cp[j];
            boolean u = pu[p] != 0;
            if (ni.nl == 2)
                u |= pu[p + 1] != 0;
            if (!u) {
                pu[p] = 1;
                if (ni.nl == 2)
                    pu[p + 1] = 2;
                if (find(i + 1))
                    return true;
                pu[p] = 0;
                if (ni.nl == 2)
                    pu[p + 1] = 0;
            }
        }
        return false;
    }

    void write(PrintWriter out) {
        for (int p = 0; p < m; p++) {
            if (p > 0 && pu[p] == 1)
                out.print(' ');
            out.print(s[p]);
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

