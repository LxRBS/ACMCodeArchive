/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem E. Epic Win!                                           */
/*                                                                */
/* Original idea         Mikhail Dvorkin                          */
/* Problem statement     Mikhail Dvorkin                          */
/* Test set              Mikhail Dvorkin                          */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Roman Elizarov                           */
/******************************************************************/

import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2014 Problem E: Epic Win!
 * This solution checks correctness of the input.
 *
 * @author Roman Elizarov
 */
public class epic_re {
    private static final String INPUT = "epic.in";
    private static final String OUTPUT = "epic.out";

    public static void main(String[] args) throws Exception {
        new epic_re().go();
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

    static final Move[] MOVES = Move.values();

    enum Move {
        R, P, S;
        Move win() {
            return MOVES[(ordinal() + 1) % 3];
        }
    }

    static class FSM {
        int n;
        Move[] move;
        int[] next;

        FSM(int n) {
            this.n = n;
            move = new Move[n];
            next = new int[3 * n];
        }
    }

    FSM op;
    FSM me;

    void read(Scanner in) {
        int n = in.nextInt();
        in.nextLine();
        assert n >= 1 && n <= 100;
        op = new FSM(n);
        for (int i = 0; i < op.n; i++) {
            op.move[i] = Move.valueOf(in.next());
            for (int j = 0; j < 3; j++) {
                int k = in.nextInt();
                assert k >= 1 && k <= op.n;
                op.next[3 * i + j] = k - 1;
            }
            in.nextLine();
        }
    }

    void solve() {
        me = new FSM(op.n * op.n);
        Arrays.fill(me.next, -1);
        for (int i = 0; i < op.n; i++) {
            for (int j = 0; j < op.n; j++) {
                int k = op.n * i + j;
                Move opm = op.move[j];
                Move mem = opm.win();
                me.move[k] = mem;
                me.next[3 * k + opm.ordinal()] = op.n * i + op.next[3 * j + mem.ordinal()];
            }
        }
        int layers = 1;
        int visAt[][] = new int[op.n][op.n * op.n];
        for (int start = 1; start < op.n; start++) {
            int j = start;
            int k = 0;
            while (visAt[j][k] != start) {
                visAt[j][k] = start;
                Move opm = op.move[j];
                Move mem = me.move[k];
                int jNext = op.next[3 * j + mem.ordinal()];
                int kNext = me.next[3 * k + opm.ordinal()];
                if (kNext < 0) {
                    me.next[3 * k + opm.ordinal()] = op.n * layers + jNext;
                    layers++;
                    break;
                }
                j = jNext;
                k = kNext;
            }
        }
        me.n = layers * op.n;
        me.move = Arrays.copyOf(me.move, me.n);
        me.next = Arrays.copyOf(me.next, 3 * me.n);
        for (int i = 0; i < me.n; i++) {
            for (int j = 0; j < 3; j++) {
                if (me.next[3 * i + j] < 0)
                    me.next[3 * i + j] = 0;
            }
        }
    }

    void write(PrintWriter out) {
        out.println(me.n);
        for (int i = 0; i < me.n; i++) {
            out.print(me.move[i]);
            for (int j = 0; j < 3; j++) {
                out.print(" ");
                out.print(me.next[3 * i + j] + 1);
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

