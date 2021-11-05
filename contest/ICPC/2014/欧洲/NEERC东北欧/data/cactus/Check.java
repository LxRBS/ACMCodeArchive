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
/* Checker                                                        */
/*                                                                */
/* Author                Roman Elizarov                           */
/******************************************************************/

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import java.util.*;

import static ru.ifmo.testlib.Outcome.Type.*;

/**
 * Checker for NEERC'2014 Problem C: Cactus Generator
 *
 * @author Roman Elizarov
 */
public class Check implements Checker {
    public static final int MAX_N = 50000;

    static class Graph {
        final Outcome.Type type;
        int n;
        int m;
        List<Set<Integer>> adjSet = new ArrayList<>();
        List<List<Integer>> adj = new ArrayList<>();

        Graph(InStream in, Outcome.Type type) {
            this.type = type;
            n = in.nextInt();
            if (n < 1 || n > MAX_N)
                throw new Outcome(type, String.format("n=%d exceeds limits", n));
            adjSet.add(null);
            adj.add(null);
            for (int i = 1; i <= n; i++) {
                adjSet.add(new LinkedHashSet<>());
                adj.add(new ArrayList<>());
            }
            m = in.nextInt();
            if (m < 1)
                throw new Outcome(type, String.format("Invalid m=%d", m));
            for (int i = 1; i <= m; i++) {
                int k = in.nextInt();
                if (k < 2)
                    throw new Outcome(type, String.format("Invalid k[%d]=%d", i, k));
                int u = nextV(in);
                for (int j = 2; j <= k; j++) {
                    int v = nextV(in);
                    if (u == v)
                        throw new Outcome(type, String.format("Invalid edge %d -- %d", u, v));
                    add(u, v);
                    add(v, u);
                    u = v;
                }
            }
            if (!in.seekEoF())
                throw new Outcome(type, "Extra data in file");
        }

        private int nextV(InStream in) {
            int v = in.nextInt();
            if (v < 1 || v > n)
                throw new Outcome(type, String.format("Invalid vertex number %d", v));
            return v;
        }

        private void add(int u, int v) {
            if (!adjSet.get(u).add(v))
                throw new Outcome(type, String.format("Edge %d -- %d repeats", u, v));
            adj.get(u).add(v);
        }
    }

    static class Vertex implements Comparable<Vertex> {
        final int index; // original index
        final Map<Vertex, Cycle> next = new HashMap<>(); // cycles handing at this vertex (keyed by the next vertex)

        int num;        // number in dfs order
        int nextAdjIdx; // next adj vertex to be scanned
        Vertex vUp;     // uplink in dfs

        boolean hasLastVertex; // when tree down from here contains last vertex (index == n)
        Cycle[] ordered; // ordered cycles

        Vertex(int index) {
            this.index = index;
        }

        @Override
        public String toString() {
            return "" + index;
        }

        int size() {
            return next.size();
        }

        void initOrder() {
            for (Cycle cycle : next.values()) {
                cycle.initOrder();
                hasLastVertex |= cycle.hasLastVertex;
            }
            ordered = next.values().toArray(new Cycle[size()]);
            Arrays.sort(ordered);
        }

        @Override
        public int compareTo(Vertex o) {
            int d = cmpLastVertex(hasLastVertex, o.hasLastVertex);
            if (d != 0)
                return d;
            d = o.size() - size();
            if (d != 0)
                return d;
            for (int i = 0; i < size(); i++) {
                d = o.ordered[i].compareTo(ordered[i]);
                if (d != 0)
                    return d;
            }
            return 0;
        }

    }

    static class Cycle implements Comparable<Cycle> {
        final List<Vertex> v = new ArrayList<>(); // list of vertices in a cycle, v(0) is up, v(1) is its key in up's next map

        boolean hasLastVertex; // when tree down from here contains last vertex (index == n)
        Vertex[] ordered; // ordered vertices

        @Override
        public String toString() {
            return v.toString();
        }

        int size() {
            return v.size();
        }

        int cmp(int i, int j) {
            return ordered[i].compareTo(ordered[j]);
        }

        void initOrder() {
            for (int i = 1; i < size(); i++) {
                hasLastVertex |= v.get(i).hasLastVertex;
            }
            ordered = v.toArray(new Vertex[size()]);
            int d = 0;
            for (int i = 1; i < (size() + 1) / 2; i++) {
                d = cmp(i, size() - i);
                if (d != 0)
                    break;
            }
            if (d < 0) // then flip around
                for (int i = 1; i < (size() + 1) / 2; i++) {
                    Vertex t = ordered[i];
                    ordered[i] = ordered[size() - i];
                    ordered[size() - i] = t;
                }
        }

        @Override
        public int compareTo(Cycle o) {
            int d = cmpLastVertex(hasLastVertex, o.hasLastVertex);
            if (d != 0)
                return d;
            d = o.size() - size();
            if (d != 0)
                return d;
            for (int i = 1; i < size(); i++) {
                d = o.ordered[i].compareTo(ordered[i]);
                if (d != 0)
                    return d;
            }
            return 0;
        }
    }

    static int cmpLastVertex(boolean hasLastVertex, boolean other) {
        if (hasLastVertex && !other)
            return 1;
        if (!hasLastVertex && other)
            return -1;
        return 0;
    }

    class DFS {
        final Graph g;
        final Outcome.Type type;

        final Vertex[] v;     // all vertices
        final Stack<Vertex> st = new Stack<>();   // dfs stack of vertices
        final Vertex v1;

        int curNum;  // current dfs vertex number

        DFS(Graph g, Outcome.Type type) {
            this.g = g;
            this.type = type;
            v = new Vertex[g.n + 1];
            for (int i = 1; i <= g.n; i++)
                v[i] = new Vertex(i);
            // mark a distinguished last vertex
            v[g.n].hasLastVertex = true;
            // start dfs at vertex 1 (first)
            v1 = v[1];
            pushV(v1);
            while (!st.isEmpty()) {
                Vertex s = st.peek();
                List<Integer> sAdj = g.adj.get(s.index);
                int i = s.nextAdjIdx++;
                if (i >= sAdj.size()) { // done with it -- backtrack
                    s.initOrder();
                    st.pop();
                    continue;
                }
                Vertex t = v[sAdj.get(i)];
                visit(s, t);
            }
            if (curNum != g.n)
                throw new Outcome(type, "Graph is not connected");
        }

        // add vertex to stack
        void pushV(Vertex t) {
            t.num = ++curNum;
            st.push(t);
        }

        // visits edge from s to t in dfs
        Cycle visit(Vertex s, Vertex t) {
            if (t.num > 0) {
                if (s.num < t.num)
                    return null; // already processed
                if (s.vUp == t)
                    return null; // one back -- skip (cycle code will not change anything)
                // cycle
                Cycle c = new Cycle();
                Vertex j = s;
                while (j != t) {
                    c.v.add(j);
                    j = j.vUp;
                }
                c.v.add(t);
                Collections.reverse(c.v);
                // now from t to s
                for (int i = 1; i < c.v.size(); i++) {
                    Vertex p = c.v.get(i - 1);
                    Vertex q = c.v.get(i);
                    Cycle oldC = p.next.remove(q);
                    if (oldC.v.size() != 2)
                        throw new Outcome(type, String.format("Not a cactus. Edge %s -- %s in more than one loop", s, t));
                }
                t.next.put(c.v.get(1), c);
                return c;
            }
            // push fresh vertex onto stack
            pushV(t);
            t.vUp = s;
            // create simple cycle (two vertices)
            Cycle c = new Cycle();
            c.v.add(s);
            c.v.add(t);
            s.next.put(t, c);
            return c;
        }
    }

    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        Graph ja = new Graph(ans, FAIL);
        Graph pa = new Graph(ouf, PE);

        if (ja.n != pa.n)
            return new Outcome(WA, String.format("Expected %d vertices, found %d", ja.n, pa.n));
        if (ja.m < pa.m)
            return new Outcome(WA, String.format("Expected %d paths, found %d", ja.m, pa.m));

        // Now need deep stack
        Comparer comparer = new Comparer(ja, pa);
        comparer.start();
        try {
            comparer.join();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        if (comparer.result != 0)
            throw new Outcome(WA, "Different graph");

        if (ja.m > pa.m)
            return new Outcome(FAIL, String.format("Expected %d paths, found %d with the same graph!", ja.m, pa.m));

        return new Outcome(OK, String.format("%d %d", pa.n, pa.m));
    }

    private class Comparer extends Thread {
        private final Graph ja;
        private final Graph pa;
        int result;

        public Comparer(Graph ja, Graph pa) {
            this.ja = ja;
            this.pa = pa;
        }

        @Override
        public void run() {
            Vertex jv1 = new DFS(ja, FAIL).v1;
            Vertex pv1 = new DFS(pa, WA).v1;
            result = jv1.compareTo(pv1);
        }
    }
}

