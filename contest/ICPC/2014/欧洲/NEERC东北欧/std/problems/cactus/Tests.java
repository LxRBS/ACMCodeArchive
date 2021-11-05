/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem C. Cactus Generator                                    */
/*                                                                */
/* Original idea         Roman Elizarov                           */
/* Problem statement     Roman Elizarov                           */
/* Test set              Roman Elizarov                           */
/******************************************************************/
/* Tests                                                          */
/*                                                                */
/* Author                Roman Elizarov                           */
/******************************************************************/

import java.io.*;
import java.lang.reflect.InvocationTargetException;
import java.util.*;

/**
 * NEERC 2014 Test generator for problem Cactus Generator.
 *
 * @author Roman Elizarov (based on the NEERC 2013 test generator)
 */
public class Tests {
    static final String TEST_NAME_FORMAT = "%03d";

    static int nTests = 0;
    static int MAX_N = 50000;
    static int MAX_LEN = 1000;
    static final File LST_FILE = new File("tests/tests.lst");

    static class Context {
        final Map<String, Integer> vars = new HashMap<>();
        final Map<String, NVR> defined = new HashMap<>();

        public int get(String name) {
            Integer res = vars.get(name);
            if (res == null)
                throw new AssertionError("Variable '" + name + "' is not bound");
            return res;
        }

        public void put(String name, int i) {
            assert !vars.containsKey(name);
            vars.put(name, i);
        }

        public void remove(String name) {
            assert vars.containsKey(name);
            vars.remove(name);
        }

        public boolean definedElsewhere(String name, NVR nvr) {
            NVR old = defined.put(name, nvr);
            return old != null && old != nvr;
        }
    }

    static abstract class NVR {
        abstract Result sumOver(Context ctx, Graph c, Op op);

        abstract int get(Context ctx);
    }

    static abstract class NV extends NVR {
    }

    static final int PATH_SINGLE = 1;
    static final int PATH_DOUBLE = 2;
    static final int PATH_FAIL = 3;

    static class Result {
        int n;
        int path;

        Result(int n, int path) {
            this.n = n;
            this.path = path;
        }
    }

    static final Result FAIL = new Result(Integer.MAX_VALUE, PATH_FAIL);

    enum Op {
        C(1, PATH_DOUBLE, PATH_SINGLE, 0),
        LOOP(2, PATH_SINGLE, PATH_DOUBLE, 1),
        T(1, PATH_DOUBLE, PATH_SINGLE, 0);

        int minN;
        int allowPath;
        int resPath;
        int loop;

        Op(int minN, int allowPath, int resPath, int loop) {
            this.minN = minN;
            this.allowPath = allowPath;
            this.resPath = resPath;
            this.loop = loop;
        }
    }

    static abstract class Graph {
        abstract Result verify(Context ctx);
    }

    // fined number
    static NV num(final int n) {
        return new NV() {
            @Override
            public String toString() {
                return Integer.toString(n);
            }

            @Override
            int get(Context ctx) {
                return n;
            }

            @Override
            Result sumOver(Context ctx, Graph c, Op op) {
                return Tests.sumOver(ctx, op, n, c);
            }
        };
    }

    // var value
    static NV var(final String name) {
        return new NV() {
            @Override
            public String toString() {
                return name;
            }

            @Override
            int get(Context ctx) {
                return ctx.get(name);
            }

            @Override
            Result sumOver(Context ctx, Graph c, Op op) {
                return Tests.sumOver(ctx, op, ctx.get(name), c);
            }
        };
    }

    static Result sumOver(Context ctx, Op op, int n, Graph c) {
        if (n < op.minN)
            return FAIL;
        Result res = c.verify(ctx);
        if (res.path > op.allowPath)
            return FAIL;
        Result ans = new Result(n * res.n - (n - 1) - op.loop, Math.max(res.path, op.resPath));
        if (ans.n <= 2 && op == Op.LOOP)
            return FAIL;
        return ans;
    }

    static Result sumOver(Context ctx, Op op, Graph... cs) {
        if (cs.length < op.minN)
            return FAIL;
        int sumN = 0;
        int resPath = op.resPath;
        for (int i = 0; i < cs.length; i++) {
            Graph c = cs[i];
            Result res = c.verify(ctx);
            sumN += res.n;
            if (res.path > op.allowPath)
                return FAIL;
            if (op != Op.T || i == 0)
                resPath = Math.max(resPath, res.path);
        }
        Result ans = new Result(sumN - (cs.length - 1) - op.loop, resPath);
        if (ans.n <= 2 && op == Op.LOOP)
            return FAIL;
        return ans;
    }

    static final String A = "A";
    static final String B = "B";
    static final String C = "C";
    static final String D = "D";
    static final String E = "E";
    static final String F = "F";
    static final String G = "G";
    static final String H = "H";
    static final String I = "I";
    static final String J = "J";
    static final String K = "K";
    static final String L = "L";
    static final String M = "M";
    static final String N = "N";
    static final String O = "O";
    static final String P = "P";
    static final String Q = "Q";
    static final String R = "R";
    static final String S = "S";
    static final String T = "T";
    static final String U = "U";
    static final String V = "V";
    static final String W = "W";
    static final String X = "X";
    static final String Y = "Y";
    static final String Z = "Z";

    static NVR range(final String name, final NV from, final NV to) {
        return new NVR() {
            @Override
            public String toString() {
                return "range(" + name + "," + from + "," + to + ")";
            }

            @Override
            Result sumOver(Context ctx, Graph c, Op op) {
                if (ctx.definedElsewhere(name, this))
                    return FAIL;
                int a = from.get(ctx);
                int b = to.get(ctx);
                if (a > b) {
                    int t = a;
                    a = b;
                    b = t;
                }
                if (b - a + 1 < op.minN)
                    return FAIL;
                int sumN = 0;
                int resPath = op.resPath;
                for (int i = a; i <= b; i++) {
                    ctx.put(name, i);
                    Result res = c.verify(ctx);
                    sumN += res.n;
                    if (res.path > op.allowPath)
                        return FAIL;
                    if (op != Op.T || i == a)
                        resPath = Math.max(resPath, res.path);
                    if (i > a)
                        sumN--;
                    ctx.remove(name);
                }
                Result ans = new Result(sumN - op.loop, resPath);
                if (ans.n <= 2 && op == Op.LOOP)
                    return FAIL;
                return ans;
            }

            @Override
            int get(Context ctx) {
                int a = from.get(ctx);
                int b = to.get(ctx);
                return Math.abs(a - b) + 1;
            }
        };
    }

    static NVR range(String name, int from, int to) {
        return range(name, num(from), num(to));
    }

    static NVR range(String name, String from, int to) {
        return range(name, var(from), num(to));
    }

    static NVR range(String name, int from, String to) {
        return range(name, num(from), var(to));
    }

    static NVR range(String name, String from, String to) {
        return range(name, var(from), var(to));
    }

    static final Graph c = new Graph() {
        @Override
        public String toString() {
            return "c";
        }

        @Override
        Result verify(Context ctx) {
            return new Result(2, PATH_SINGLE);
        }
    };

    // ---------------------------- c(...) ----------------------------

    static Graph c(final NVR nvr, final Graph c) {
        return new Graph() {
            @Override
            public String toString() {
                return "c(" + nvr + "," + c + ")";
            }

            @Override
            Result verify(Context ctx) {
                return nvr.sumOver(ctx, c, Op.C);
            }
        };
    }

    static Graph c(final NVR nvr) {
        return new Graph() {
            @Override
            public String toString() {
                return "c(" + nvr + ")";
            }

            @Override
            Result verify(Context ctx) {
                return nvr.sumOver(ctx, c, Op.C);
            }
        };
    }

    static Graph c(final int n, final Graph c) {
        return c(num(n), c);
    }

    static Graph c(final String name, final Graph c) {
        return c(var(name), c);
    }

    static Graph c(final int n) {
        return c(num(n));
    }

    static Graph c(final String name) {
        return c(var(name));
    }

    static Graph c(final Graph... cs) {
        assert cs.length >= 1;
        return new Graph() {
            @Override
            public String toString() {
                StringBuilder sb = new StringBuilder();
                sb.append("c(");
                for (int i = 0; i < cs.length; i++) {
                    if (i > 0)
                        sb.append(",");
                    sb.append(cs[i]);
                }
                sb.append(")");
                return sb.toString();
            }

            @Override
            Result verify(Context ctx) {
                return sumOver(ctx, Op.C, cs);
            }
        };
    }

    // ---------------------------- loop(...) ----------------------------

    static Graph loop(final NVR nvr, final Graph c) {
        return new Graph() {
            @Override
            public String toString() {
                return "loop(" + nvr + "," + c + ")";
            }

            @Override
            Result verify(Context ctx) {
                return nvr.sumOver(ctx, c, Op.LOOP);
            }
        };
    }

    static Graph loop(final NVR nvr) {
        return new Graph() {
            @Override
            public String toString() {
                return "loop(" + nvr + ")";
            }

            @Override
            Result verify(Context ctx) {
                return nvr.sumOver(ctx, c, Op.LOOP);
            }
        };
    }

    static Graph loop(final int n, final Graph c) {
        return loop(num(n), c);
    }

    static Graph loop(final String name, final Graph c) {
        return loop(var(name), c);
    }

    static Graph loop(final int n) {
        return loop(num(n));
    }

    static Graph loop(final String name) {
        return loop(var(name));
    }

    static Graph loop(final Graph... cs) {
        return new Graph() {
            @Override
            public String toString() {
                StringBuilder sb = new StringBuilder();
                sb.append("loop(");
                for (int i = 0; i < cs.length; i++) {
                    if (i > 0)
                        sb.append(",");
                    sb.append(cs[i]);
                }
                sb.append(")");
                return sb.toString();
            }

            @Override
            Result verify(Context ctx) {
                return sumOver(ctx, Op.LOOP, cs);
            }
        };
    }

    // ---------------------------- t(...) ----------------------------

    static Graph t(final NVR nvr, final Graph c) {
        return new Graph() {
            @Override
            public String toString() {
                return "t(" + nvr + "," + c + ")";
            }

            @Override
            Result verify(Context ctx) {
                return nvr.sumOver(ctx, c, Op.T);
            }
        };
    }

    static Graph t(final NVR nvr) {
        return new Graph() {
            @Override
            public String toString() {
                return "t(" + nvr + ")";
            }

            @Override
            Result verify(Context ctx) {
                return nvr.sumOver(ctx, c, Op.T);
            }
        };
    }

    static Graph t(final int n, final Graph c) {
        return t(num(n), c);
    }

    static Graph t(final String name, final Graph c) {
        return t(var(name), c);
    }

    static Graph t(final int n) {
        return t(num(n));
    }

    static Graph t(final String name) {
        return t(var(name));
    }

    static Graph t(final Graph... cs) {
        assert cs.length >= 1;
        return new Graph() {
            @Override
            public String toString() {
                StringBuilder sb = new StringBuilder();
                sb.append("t(");
                for (int i = 0; i < cs.length; i++) {
                    if (i > 0)
                        sb.append(",");
                    sb.append(cs[i]);
                }
                sb.append(")");
                return sb.toString();
            }

            @Override
            Result verify(Context ctx) {
                return sumOver(ctx, Op.T, cs);
            }
        };
    }

    static Graph[] times(int n, Graph c) {
        Graph[] a = new Graph[n];
        Arrays.fill(a, c);
        return a;
    }

    static Graph[] randomList(int n, int maxV, int maxLen, Random r) {
        Graph[] a = new Graph[n];
        int remV = maxV + (n - 1);
        int remLen = maxLen - (n - 1);
        for (int i = 0; i < n; i++) {
            int rem = n - i;
            a[i] = randomGraph(remV / rem, remLen / rem, r);
            Result res = a[i].verify(new Context());
            assert res.path != PATH_FAIL;
            remV -= res.n;
            remLen -= a[i].toString().length();
        }
        return a;
    }

    private static Graph[] allVarsList(Random r) {
        int vars = 26;
        Graph[] a = new Graph[vars];
        int maxDelta = (int)Math.sqrt(2 * MAX_N / vars);
        for (int i = 0; i < vars; i++) {
            String name = "" + (char)(i + 'A');
            int from;
            int to;
            do {
                from = r.nextInt(MAX_N) + 1;
                to = from + r.nextInt(2 * maxDelta + 1) - maxDelta;
            } while (to < 1 || to > MAX_N);
            a[i] = t(range(name, from, to), c);
        }
        return a;
    }
    private static Graph randomGraph(int maxV, int maxLen, Random r) {
        if (maxLen <= 4 || maxV <= 2)
            return c;
        retry:
        while (true) {
            Graph g;
            int n;
            switch (r.nextInt(9)) {
                case 0:
                    g = c(maxV - 1);
                    break;
                case 1:
                    g = loop(maxV - 1);
                    break;
                case 2:
                    g = t(maxV - 1);
                    break;
                case 3:
                    n = r.nextInt(Math.min(maxV, maxLen / 2)) + 1;
                    g = c(n, randomGraph((maxV + (n - 1)) / n, (maxLen - 3 - (n - 1)) / n, r));
                    break;
                case 4:
                    n = r.nextInt(Math.min(maxV, maxLen / 2)) + 1;
                    g = loop(n, randomGraph((maxV + (n - 1)) / n, (maxLen - 6 - (n - 1)) / n, r));
                    break;
                case 5:
                    n = r.nextInt(Math.min(maxV, maxLen / 2)) + 1;
                    g = t(n, randomGraph((maxV + (n - 1)) / n, (maxLen - 3 - (n - 1)) / n, r));
                    break;
                case 6:
                    n = r.nextInt(Math.min(maxV, maxLen / 2)) + 1;
                    g = c(randomList(n, maxV, maxLen - 3, r));
                    break;
                case 7:
                    n = r.nextInt(Math.min(maxV, maxLen / 2)) + 1;
                    g = loop(randomList(n, maxV, maxLen - 3, r));
                    break;
                case 8:
                    n = r.nextInt(Math.min(maxV, maxLen / 2)) + 1;
                    g = t(randomList(n, maxV, maxLen - 3, r));
                    break;
                default:
                    throw new AssertionError();
            }
            Result res = g.verify(new Context());
            if (res.path != PATH_FAIL && res.n <= maxV && g.toString().length() <= maxLen)
                return g;
        }
    }

    static Graph depth(int n, String method) {
        if (n == 0)
            return c;
        Graph[] rec = {depth(n - 1, method)};
        try {
            return (Graph) Tests.class.getDeclaredMethod(method, Graph[].class).invoke(null, (Object) rec);
        } catch (IllegalAccessException | InvocationTargetException | NoSuchMethodException e) {
            throw new RuntimeException(e);
        }
    }

    // balanced tree with custom edges
    static Graph bt(final int n, final int depth, final Graph edge) {
        assert depth >= 1;
        if (depth == 1)
            return t(n, edge);
        return t(n, c(edge, bt(n, depth - 1, edge)));
    }

    // balanced tree with simple edges
    static Graph bt(int n, int depth) {
        return bt(n, depth, c);
    }

    static PrintWriter openTestFile(String desc) throws IOException {
        new File("tests").mkdir();
        PrintWriter out = new PrintWriter(String.format("tests/" + TEST_NAME_FORMAT, ++nTests));
        PrintWriter out1 = new PrintWriter(new FileWriter(LST_FILE, true));
        out1.printf(TEST_NAME_FORMAT + " %s%n", nTests, desc);
        out1.close();
        System.out.printf("Writing test " + TEST_NAME_FORMAT + ": %s%n", nTests, desc);
        return out;
    }

    static void write(String desc, Graph g) {
        Result res = g.verify(new Context());
        assert res.path != PATH_FAIL : "Not a cactus";
        assert res.n <= MAX_N : "n is out of range " + res.n;
        String s = g.toString();
        assert s.length() <= MAX_LEN;
        try (PrintWriter out = openTestFile(desc)) {
            out.println(s);
        } catch (IOException ex) {
            ex.printStackTrace();
            System.exit(1);
        }
    }

    static void writeChain(int n) {
        write(String.format("Chain n=%d", n), c(n - 1));
    }

    static void writeOneCycle(int n) {
        write(String.format("OneCycle n=%d", n), loop(n));
    }

    static void writeCycleWithRegularIcicles(int n, int step) {
        assert n % step == 0;
        write(String.format("CycleWithRegularIcicles n=%d, step=%d", n, step),
                loop(n / step, t(c(step), c)));
    }

    static void writeCycleWithPeriodicIcicles(int n, int... def) {
        assert def.length % 2 == 0;
        List<Graph> cs = new ArrayList<>();
        int totalStep = 0;
        for (int j = 0; j < def.length; j += 2) {
            int len = def[j];
            int step = def[j + 1];
            totalStep += step;
            cs.add(t(c(step), c(len)));
        }
        assert n % totalStep == 0;
        write(String.format("CycleWithPeriodicIcicles n=%d, totalStep=%d, def=%s",
                n, totalStep, Arrays.toString(def)), loop(n / totalStep, c(cs.toArray(new Graph[cs.size()]))));
    }

    public static void main(String[] args) throws IOException {
        LST_FILE.delete();

        // ----------- tests from the problem statement -----------

        write("Sample 1", c(c, t(loop(3), c(c, loop(6))), loop(c, c, t(c, loop(4)))));
        write("Sample 2", c);
        write("Sample 3", c(2));
        write("Sample 4", c(3));
        write("Sample 5", t(c(3), c, c));
        write("Sample 6", c(2, t(c(2), c, c)));
        write("Sample 7", loop(c, c, c));
        write("Sample 8", loop(c(3), c, c));
        write("Sample 9", loop(4));
        write("Sample 10", loop(2, t(c(3), c, c)));
        write("Sample 11", t(2));
        write("Sample 12", t(c, c(2)));
        write("Sample 13", c(c, t(2)));
        write("Sample 14", c(c(2), t(3)));
        write("Sample 15", t(range(A, 1, 3)));
        write("Sample 16", t(range(A, 1, 3), c(A)));
        write("Sample 17", c(range(N, 2, 3), t(c(N), c, c)));
        write("Sample 18", t(range(X, 1, 3), t(range(Y, 3, X), c(X))));
        write("Sample 19", loop(range(N, 1, 4), t(c, c(2))));
        write("Sample 20", c(range(I, 1, 3), loop(c, c, c(range(J, I, 2)))));


        // ----------- various simple range uses -----------

        write("c-range1-c", c(range(A, 2, 10), c(A)));
        write("c-range1-t", c(range(B, 3, 11), t(B)));
        write("c-range1-loop", c(range(C, 4, 12), loop(C)));
        write("loop-range1-c", loop(range(D, 5, 15), c(D)));
        write("loop-range1-t", loop(range(E, 16, 6), t(E)));
        write("t-range1-c", t(range(F, 7, 17), c(F)));
        write("t-range1-t", t(range(G, 18, 8), t(G)));
        write("t-range1-loop", t(range(H, 19, 9), loop(H)));

        write("loop-range1-t-loop", loop(range(I, 10, 20), t(c, loop(I))));

        // ----------- using vars twice -----------

        write("c-range2-t-loop", c(range(J, 11, 21), t(J, loop(J))));
        write("loop-range2-c-t", loop(range(K, 22, 12), c(K, t(K))));
        write("t-range2-loop-l", t(range(L, 13, 23), loop(L, c(L))));

        // ----------- using two vars -----------

        write("2vars c-t-loop-c", c(range(M, 5, 13), t(range(N, 17, 12), loop(M, c(N)))));
        write("2vars t-loop-c-t", t(range(O, 1, 3), loop(range(P, 8, 4), c(P, t(O)))));
        write("2vars var range loop-c-t-c", loop(range(Q, 8, 13), c(range(R, Q, 10), t(Q, c(R)))));
        write("2vars var range loop-t-t-c-loop", loop(range(S, 15, 7), t(c(S), t(range(T, 10, S), c(T, loop(S))))));

        // ----------- 3-4 vars -----------

        write("3vars c-loop-t-c", c(range(T, 3, 18), loop(range(U, T, 2), t(range(V, U, T), c(V)))));
        write("4vars t-c-t-c-loop-t", t(range(W, 11, 5), c(range(X, 8, W), t(range(Y, W, X), c(range(Z, X, Y), loop(t(W), t(X), t(Y), t(Z)))))));

        // ---- all vars at the same time ---

        write("c all vars", c(allVarsList(new Random(10))));
        write("t all vars", t(allVarsList(new Random(11))));
        write("loop all vars", loop(allVarsList(new Random(12))));

        // ----------- long random chain -----------

        write("c1 rand max", c(randomList(1, MAX_N, MAX_LEN - 3, new Random(1))));
        write("t1 rand max", t(randomList(1, MAX_N, MAX_LEN - 3, new Random(2))));
        write("c10 rand max", c(randomList(10, MAX_N, MAX_LEN - 3, new Random(3))));
        write("t10 rand max", t(randomList(10, MAX_N, MAX_LEN - 3, new Random(4))));
        write("c100 rand max", c(randomList(100, MAX_N, MAX_LEN - 3, new Random(5))));
        write("t100 rand max", t(randomList(100, MAX_N, MAX_LEN - 3, new Random(6))));

        // ----------- max len strings -----------

        write("maxlen c", c(times((MAX_LEN - 2) / 2, c)));
        write("maxlen t", t(times((MAX_LEN - 2) / 2, c)));
        write("maxlen loop", loop(times((MAX_LEN - 5) / 2, c)));

        // ----------- max depth strings -----------

        write("maxdepth c", depth((MAX_LEN - 1) / 3, "c"));
        write("maxdepth t", depth((MAX_LEN - 1) / 3, "t"));

        // ----------- applicable tests from NEERC'2013 -----------

        write("loop that has only 3 possible rotations (no flip)", loop(3,
                c(
                        t(c, c(2)), // icicle with length 2
                        t(c, c(1)), // icicle with length 1
                        c            // segment
                )));

        // ----------- handcrafted cyclical bit strings with special symmetries ------------

        write("Bit cycle 100: can't rotate, flips in any way", loop(t(c, c), c, c));
        write("Bit cycle 1000: can't rotate, flips over vertex only", loop(t(c, c), c, c, c));
        write("Bit cycle 1100: can't rotate, flips over edge only", loop(t(c, c), t(c, c), c, c));
        write("Bit cycle 1010: rotates, flips over vertex only", loop(t(c, c), c, t(c, c), c));
        write("Bit cycle 10000: can't rotate, flips in any way", loop(t(c, c), c, c, c, c));
        write("Bit cycle 110100: can't rotate, can't flip", loop(t(c, c), t(c, c), c, t(c, c), c, c));
        write("Bit cycle 11001100: rotates, flips over edge only", loop(t(c, c), t(c, c), c, c, t(c, c), t(c, c), c, c));
        write("Bit cycle 110100110100: rotates (x2), can't flip", loop(2, c(t(c, c), t(c, c), c, t(c, c), c, c)));
        write("Bit cycle 110100110100110100: rotates (x3), can't flip", loop(3, c(t(c, c), t(c, c), c, t(c, c), c, c)));

        // ----------- chains ------------

        writeChain(100);
        writeChain(113);
        writeChain(MAX_N - 1);
        writeChain(MAX_N);

        // ----------- cycles ------------

        writeOneCycle(100);
        writeOneCycle(101);
        writeOneCycle(239);
        writeOneCycle(49140); // 49140 = 2^2?3^3?5?7?13  (8 prime factors, 5 distinct)
        writeOneCycle(MAX_N - 1);
        writeOneCycle(MAX_N);

        // ----------- cycles with special symmetry cases and algo effectiveness tests ------------

        write("One big(max) cycle with a small icicle (flip only)",
                loop(
                        c(MAX_N - 2),
                        t(c, c)
                ));
        write("One big(max) cycle with two small icicles (flip only)",
                loop(
                        c(MAX_N - 4),
                        t(c, c),
                        t(c, c)
                ));
        write("One big(max) cycle with two small icicles far away symmetric (flip+rotate)",
                loop(
                        c((MAX_N - 4) / 2),
                        t(c, c),
                        c((MAX_N - 4) / 2),
                        t(c, c)
                ));
        write("One big(max) cycle with two small icicles far away (flip only)",
                loop(
                        c((MAX_N - 4) / 2 - 1),
                        t(c, c),
                        c((MAX_N - 4) / 2 + 1),
                        t(c, c)
                ));
        write("One big(max) cycle with two directional icicle groups far away (rotate only)",
                loop(
                        c((MAX_N - 18) / 2),
                        t(c, c(2)),
                        t(c, c),
                        c((MAX_N - 18) / 2),
                        t(c, c(2)),
                        t(c, c)
                ));
        write("One big(max) cycle with three small icicles far away symmetric (flip+rotate)",
                loop(
                        c((MAX_N - 6) / 3),
                        t(c, c),
                        c((MAX_N - 6) / 3),
                        t(c, c),
                        c((MAX_N - 6) / 3),
                        t(c, c)
                ));
        write("One big(max) cycle with three directional icicle groups far away symmetric (rotate only)",
                loop(
                        c((MAX_N - 27) / 3),
                        t(c, c(2)),
                        t(c, c),
                        c((MAX_N - 27) / 3),
                        t(c, c(2)),
                        t(c, c),
                        c((MAX_N - 27) / 3),
                        t(c, c(2)),
                        t(c, c)
                ));
        write("One big(max) cycle with three small icicles far away (flip only)",
                loop(
                        c((MAX_N - 12) / 3 - 1),
                        t(c, c),
                        c((MAX_N - 12) / 3 - 1),
                        t(c, c),
                        c((MAX_N - 12) / 3),
                        t(c, c)
                ));
        write("One big(max) cycle with three small icicles far away (no flip)",
                loop(
                        c((MAX_N - 12) / 3 - 1),
                        t(c, c),
                        c((MAX_N - 12) / 3 + 1),
                        t(c, c),
                        c((MAX_N - 12) / 3),
                        t(c, c)
                ));

        // ------- big (max) bit cycles with special symmetries -----

        write("Bit cycle 110100 repeated max times (no flip)", loop(MAX_N / 9, c(t(c, c), t(c, c), c, t(c, c), c, c)));
        write("Bit cycle 111000 repeated max times (flips over vertex)", loop(MAX_N / 9, c(t(c, c), t(c, c), t(c, c), c, c, c)));
        write("Bit cycle 1100 repeated max times (flips over edge)", loop(MAX_N / 6, c(t(c, c), t(c, c), c, c)));
        write("Bit cycle 10 repeated max times + extra 0 (can't rotate, flips over vertex)", loop(c, c((MAX_N - 1) / 3, c(t(c, c), c))));
        write("Bit cycle 10 repeated max times + extra 00 (can't rotate, flips over edge)", loop(c, c, c((MAX_N - 2) / 3, c(t(c, c), c))));
        write("Bit cycle 10 repeated max times + extra 01 (can't rotate, can't flip)", loop(c, t(c, c), c((MAX_N - 3) / 3, c(t(c, c), c))));

        // ------- cycle with regular icicles -----

        writeCycleWithRegularIcicles(100, 2);
        writeCycleWithRegularIcicles(99, 3);
        writeCycleWithRegularIcicles(4444, 4);
        writeCycleWithRegularIcicles(MAX_N / 2, 1);
        writeCycleWithRegularIcicles(MAX_N / 2, 2);
        writeCycleWithRegularIcicles(MAX_N / 2, 5);
        writeCycleWithRegularIcicles(45000, 10);

        // ------- cycle with periodic icicles -----

        writeCycleWithPeriodicIcicles(20, 1, 2, 1, 3);
        writeCycleWithPeriodicIcicles(9, 2, 1, 2, 2);
        writeCycleWithPeriodicIcicles(20, 5000, 2, 5000, 3);
        writeCycleWithPeriodicIcicles(9999, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2);
        writeCycleWithPeriodicIcicles(100, 2, 2, 3, 3);
        writeCycleWithPeriodicIcicles(7777, 8, 3, 9, 4);
        writeCycleWithPeriodicIcicles(773 * 47, 3, 10, 4, 30, 3, 7);
        writeCycleWithPeriodicIcicles(MAX_N / 4, 1, 1, 2, 1);
        writeCycleWithPeriodicIcicles(10000, 50, 51, 50, 49);

        // ------- cycles with complex stuff handing from it -------

        write("Triangle with 3 longest icicles", loop(3, t(c, c(16665))));
        write("Triangle with 2 longest icicles + one bit smaller", loop(c(2, t(c, c(16666))), t(c, c(16665))));
        write("Triangle with 3 long and different icicles", loop(t(c, c(16666)), t(c, c(16665)), t(c, c(16664))));

        write("Cycle with 10000 triangles hanging", loop(10000, t(c, loop(3))));
        write("Cycle with 10000 boxes hanging", loop(10000, t(c, loop(4))));
        write("Cycle with 10000 pentas hanging", loop(10000, t(c, loop(5))));
        write("Cycle with 10000 triangle pairs hanging", loop(10000, t(c, loop(3), loop(3))));

        write("Regular cycle with various stuff hanging",
                loop(1913, c(
                        t(c, c, c),                   // two short icicles hanging                (3 nodes)
                        t(c, loop(3)),                    // triangle hanging                         (3 nodes)
                        t(c, loop(3), c),               // triangle and icicle                      (4 nodes)
                        t(c, c(2), c(2)),                 // two longer icicles                       (5 nodes)
                        t(c, c(loop(c(2), c(2)), c(2))), // box with longer icicle at the end        (6 nodes)
                        t(c, c(loop(c, c(2)), c(2)))   // triangle with longer icicle at the end   (5 nodes)
                )));

        // ------- Balanced trees -------

        write("2^8 tree", bt(2, 8));
        write("2^14 tree", bt(2, 14));
        write("3^9 tree", bt(3, 9));
        write("4^7 tree", bt(4, 7));
        write("5^6 tree", bt(5, 6));
        write("7^5 tree", bt(7, 5));
        write("2^13 tree with c(2) edges", bt(2, 13, c(2)));
        write("2^13 tree with triangle edges", bt(2, 13, loop(c, c(2))));
        write("2^13 tree with box edges", bt(2, 13, loop(c(2), c(2))));
        write("6 x 2^12 trees hanging from a loop at 139 edge intervals", loop(6, t(c(139), bt(2, 12))));
        write("3^6 tree with very fancy edges",
                bt(3, 6, c(
                        loop(c(2), c(2)),                          // box
                        t(loop(c, c(2)), c, c, c(2), c(3),  // triangle with a lot of icicles
                                c(c(5), loop(c(3), c(3)), c(5)),       // .. including some fancy ones #1
                                c(c(3), loop(c(2), c(4)), c(6))        // .. including some fancy ones #2
                        )
                )));
        write("4^6 tree with spiky and loopy edges", bt(4, 6, c(c, t(c, c, loop(3)))));

        // ------- stars -------

        write("Star with 223 small rays", t(223, c));
        write("Star with 223 rays of len 223", t(223, c(223)));
        write("Star with max small rays", t(MAX_N - 1, c));
        write("Star with 223 rays of len 221+fork3 at the end", t(223, c(c(221), t(3, c))));
        write("Star with 222 rays of len 221+fork3 at the end + one(other) 222 ray", t(t(222, c(c(221), t(3, c))), c(222)));
        write("Star with 107 rays of len 223 and 109 rays of len 222", t(t(107, c(223)), t(109, c(222))));
        write("Star with 20k-1 small rays and 15k len 2 rays", t(t(19999, c), t(15000, c(2))));

        write("Star with different rays lens 1-315", t(range(N, 1, 315), c(N)));
        write("Star with different rays lens 1-223 (twice each)", t(2, t(range(N, 1, 223), c(N))));

        // ------- varying forks -------

        write("Star with different forks spans 1-314", t(range(N, 1, 314), c(c, t(N, c))));
        write("Loop with different forks spans 1-313", loop(range(N, 1, 313), t(c, c(c, t(N, c)))));
        write("Loop with different forks spans 1-221 (twice each)", loop(2, c(range(N, 1, 221), t(c, c(c, t(N, c))))));
        write("Loop with different forks spans 1-221 (twice, second time rev order, can flip)",
                loop(
                        c(range(N, 1, 221), t(c, c(c, t(N, c)))),
                        c(range(M, 221, 1), t(c, c(c, t(M, c))))
                ));

        // ------- Hanging loops -------

        write("223 x 223 loops hanging from loop", loop(223, t(c, loop(223))));
        write("223 x 222 loops with sym tail hanging from loop", loop(223, t(c, loop(c(111), t(c(111), c)))));
        write("223 x 223 loops with asym tail hanging from loop", loop(223, t(c, loop(c(111), t(c(112), c)))));
        write("223 x 223 loops hanging from vertex", t(223, loop(223)));
        write("223 x 222 loops with sym tail hanging from vertex", t(223, loop(c(111), t(c(111), c))));
        write("223 x 223 loops with asym tail hanging from vertex", t(223, loop(c(111), t(c(112), c))));

        write("37*34=1258 loops with tails in various places (only 34 can flip) hanging from loop",
                loop(range(N, 1, 37), c(range(M, 2, 35), t(c, loop(c(N), t(c(M), c))))));
        write("37*34=1258 loops with tails in various places (only 34 can flip) hanging from vertex",
                t(range(N, 1, 37), t(range(M, 2, 35), loop(c(N), t(c(M), c)))));

        write("313 loops of lens 3-315 on a loop", loop(range(N, 3, 315), t(c, loop(N))));
        write("221x2 loops of lens 3-223 on a loop (twice each, can rotate)", loop(2, c(range(N, 3, 223), t(c, loop(N)))));
        write("221x2 loops of lens 3-223 on a loop (twice each, second time rev order, can flip)",
                loop(
                        c(range(N, 3, 223), t(c, loop(N))),
                        c(range(M, 223, 3), t(c, loop(M)))
                ));
        write("180x3 loops of lens 3-182 on a loop (3x each, can rotate)", loop(3, c(range(N, 3, 182), t(c, loop(N)))));

        // ------- anti gk_wa tests found by stress -------

        write("Anti gk_wa", c(c(14,c),loop(36,c),c(316),c(66,c),loop(49,c)));
        write("Anti gk_wa", c(loop(5,t(c,c(73))),t(8,t(1,t(c))),loop(39,c),t(16,t(c)),t(35,c),c(844),loop(97,c),loop(1593)));
        write("Anti gk_wa", c(c(999),loop(30,c),c(1121),t(1121),c(c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c(c),t(c),t(352),c(1,c),c(3,c)),c(1261),c(t(3,c),c(c),c(57),c(1,c),t(c),t(63),c(2,c),t(c,c,c),loop(70),loop(70),t(4,c),t(c,c,c),c(c,c,c),c(t(c)),c(98),c(2,c),c(110),t(2,c),loop(128),c(4,c),t(c(2,c)),c(1,c(212)),c(212),loop(7,c)),c(c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c(56),t(56),t(56),t(56),c(c),c(59),c(59),c(59),c(59),t(59),t(59),c(60),t(60),t(60),t(60),c(60),t(60),t(c),c(c),t(89),c(89),c(90),c(2,c)),c(1375),loop(1375)));
    }

}

