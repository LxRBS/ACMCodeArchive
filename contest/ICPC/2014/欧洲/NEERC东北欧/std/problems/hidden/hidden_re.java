/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem H. Hidden Maze                                         */
/*                                                                */
/* Original idea         Alexander Kaluzhin                       */
/* Problem statement     Andrei Lopatin                           */
/* Test set              Andrei Lopatin                           */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Roman Elizarov                           */
/******************************************************************/

import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2014 Problem H: Hidden Maze
 * This solution checks correctness of the input.
 *
 * @author Roman Elizarov
 */
public class hidden_re {
    private static final String INPUT = "hidden.in";
    private static final String OUTPUT = "hidden.out";
    private static final boolean DEBUG = false;

    public static void main(String[] args) throws Exception {
        new hidden_re().go();
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

    static class Tun implements Comparable<Tun> {
        final int index;
        final int u;
        final int v;
        final int c;

        Tun(int index, int u, int v, int c) {
            this.index = index;
            this.u = u;
            this.v = v;
            this.c = c;
        }

        public int compareTo(Tun tun) {
            if (c < tun.c)
                return -1;
            if (c > tun.c)
                return 1;
            if (index < tun.index)
                return -1;
            if (index > tun.index)
                return 1;
            return 0;
        }
    }

    static List<List<Tun>> adj;
    static List<Set<Integer>> adjSet; // for validation

    void read(Scanner in) {
        n = in.nextInt();
        in.nextLine();
        assert n >= 2 && n <= 30_000;
        allocate();
        for (int i = 0; i < n - 1; i++) {
            int u = in.nextInt();
            int v = in.nextInt();
            int c = in.nextInt();
            in.nextLine();
            assert u >= 1 && u <= n;
            assert v >= 1 && v <= n;
            assert c >= 1 && c <= 1_000_000;
            add(i, u, v, c);
        }
    }

    void allocate() {
        adj = new ArrayList<>();
        adjSet = new ArrayList<>();
        adj.add(null);
        adjSet.add(null);
        for (int i = 0; i < n; i++) {
            adj.add(new ArrayList<>());
            adjSet.add(new HashSet<>());
        }
    }

    void add(int i, int u, int v, int c) {
        add0(i, u, v, c);
        add0(i, v, u, c);
    }

    void add0(int index, int u, int v, int c) {
        assert adjSet.get(u).add(v);
        adj.get(u).add(new Tun(index, u, v, c));
    }

    Tun[] up;
    int[] depth;
    int[][] bc;

    List<Tun> tuns;

    long sum;
    long cnt;

    void solve() {
        up = new Tun[n + 1];
        depth = new int[n + 1];
        bc = new int[n + 1][];
        tuns = new ArrayList<>();
        traverse(1, 0, 0);
        Collections.sort(tuns);
        for (Tun tun : tuns) {
            int v = tun.v;
            int dv = depth[v];
            int count = 0;
            int path = 0;
            int prevPath = 1;
            int prevU = v;
            // compute
            Tun cur = tun;
            while (true) {
                int u = cur.u;
                for (int t = -dv; t <= dv; t++) {
                    int tNeg = -path - t;
                    if (bc[v][dv + t] > 0) {
                        int delta = bc[v][dv + t] * (bcGet(u, tNeg) - bcGet(prevU, tNeg - prevPath));
                        if (DEBUG && delta > 0)
                            System.out.println("    " + u + " ... " + v + " += " + delta);
                        count += delta;
                    }
                }
                cur = up[u];
                if (cur == null)
                    break;
                prevPath = cur.compareTo(tun);
                path += prevPath;
                prevU = u;
            }
            sum += (double)count * tun.c;
            cnt += count;
            if (DEBUG)
                System.out.println("  " + tun.u + "  -<" + tun.c + ">-  " + tun.v + "    count=" + count);
            // adjust tun's contribution for next tun
            cur = tun;
            path = 0;
            while (true) {
                int u = cur.u;
                int du = depth[u];
                for (int t = -dv; t <= dv; t++) {
                    if (bc[v][dv + t] > 0) {
                        bc[u][du + t + 1 + path] -= bc[v][dv + t];
                        bc[u][du + t - 1 + path] += bc[v][dv + t];
                    }
                }
                cur = up[u];
                if (cur == null)
                    break;
                prevPath = cur.compareTo(tun);
                path += prevPath;
            }
        }
        if (DEBUG)
            System.out.println(sum + " / " + cnt);
    }

    int bcGet(int u, int t) {
        int du = depth[u];
        return Math.abs(t) <= du ? bc[u][du + t] : 0;

    }

    private int traverse(int u, int h, int prev) {
        int du = 0;
        for (Tun tun : adj.get(u)) {
            int v = tun.v;
            if (v != prev) {
                up[v] = tun;
                tuns.add(tun);
                du = Math.max(du, traverse(v, h + 1, u) + 1);
            }
        }
        depth[u] = du;
        bc[u] = new int[2 * du + 1];
        bc[u][du] = 1;
        for (Tun tun : adj.get(u)) {
            int v = tun.v;
            if (v != prev) {
                int dv = depth[v];
                for (int t = 0; t <= dv; t++) {
                    bc[u][du + t + 1] += bc[v][dv + t];
                }
            }
        }
        return du;
    }

    void write(PrintWriter out) {
        out.printf("%.9f%n", (double) sum / cnt);
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

