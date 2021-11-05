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
/* Solution                                                       */
/*                                                                */
/* Author                Georgiy Korneev                          */
/******************************************************************/

import java.io.File;
import java.io.PrintWriter;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class cactus_gk {
    static Scanner in;
    static PrintWriter out;

    final List<Vertex> vertices = new ArrayList<>();
    static class Edge {
        final Vertex v1, v2;
        final boolean fake;

        public Edge(Vertex v1, Vertex v2, boolean fake) {
            this.v1 = v1;
            this.v2 = v2;
            this.fake = fake;
            v1.edges.add(this);
            v2.edges.add(this);
        }

        public Vertex other(Vertex v) {
            return v1 == v ? v2 : v1;
        }
    }
    class Vertex {
        List<Edge> edges = new ArrayList<>();
        int index;

        public Vertex() {
            index = vertices.size();
            vertices.add(this);
        }

        public void walk() {
            while (!edges.isEmpty()) {
                Edge edge = edges.iterator().next();
                this.edges.remove(edge);
                Vertex v = edge.other(this);
                v.edges.remove(edge);
                v.walk();
                path.add(edge);
            }
        }
    }

    interface PGraph {
        void make(Vertex first, Vertex last);

        PGraph specialize();
    }

    interface PList {
        List<PGraph> make();

        PList specialize();
    }

    static final PGraph c = new PGraph() {
        @Override
        public void make(Vertex first, Vertex last) {
            new Edge(first, last, false);
        }

        @Override
        public PGraph specialize() {
            return this;
        }
    };

    class C implements PGraph {
        final PList list;

        public C(PList list) {
            this.list = list;
        }

        @Override
        public void make(Vertex first, Vertex last) {
            List<PGraph> graphs = list.make();
            Vertex f = first;
            for (int i = 0; i < graphs.size() - 1; i++) {
                Vertex l = new Vertex();
                graphs.get(i).make(f, l);
                f = l;
            }
            graphs.get(graphs.size() - 1).make(f, last);
        }

        @Override
        public PGraph specialize() {
            return new C(list.specialize());
        }
    }

    class L implements PGraph {
        final PList list;

        public L(PList list) {
            this.list = list;
        }

        @Override
        public void make(Vertex first, Vertex last) {
            List<PGraph> graphs = list.make();
            graphs.get(0).make(first, last);
            Vertex f = last;
            for (int i = 1; i < graphs.size() - 1; i++) {
                Vertex l = new Vertex();
                graphs.get(i).make(f, l);
                f = l;
            }
            graphs.get(graphs.size() - 1).make(f, first);
        }

        @Override
        public PGraph specialize() {
            return new L(list.specialize());
        }
    }

    class T implements PGraph {
        final PList list;

        public T(PList list) {
            this.list = list;
        }

        @Override
        public void make(Vertex first, Vertex last) {
            List<PGraph> graphs = list.make();
            graphs.get(0).make(first, last);
            for (int i = 1; i < graphs.size(); i++) {
                graphs.get(i).make(first, new Vertex());
            }
        }

        @Override
        public PGraph specialize() {
            return new T(list.specialize());
        }
    }

    static class GraphList implements PList {
        final List<PGraph> graphs;

        public GraphList(List<PGraph> graphs) {
            this.graphs = graphs;
        }

        @Override
        public List<PGraph> make() {
            return graphs;
        }

        @Override
        public PList specialize() {
            return new GraphList(graphs.stream().map(PGraph::specialize).collect(Collectors.toList()));
        }
    }

    static class NumVarList implements PList {
        final NumVar numVar;
        final PGraph graph;

        public NumVarList(NumVar numVar, PGraph graph) {
            this.numVar = numVar;
            this.graph = graph;
        }

        @Override
        public List<PGraph> make() {
            return Stream.generate(() -> graph).limit(numVar.getValue()).collect(Collectors.toList());
        }

        @Override
        public PList specialize() {
            return new NumVarList(new Num(numVar.getValue()), graph.specialize());
        }
    }

    class RangeList implements PList {
        final Var var;
        final NumVar from, to;
        final PGraph graph;

        public RangeList(Var var, NumVar from, NumVar to, PGraph graph) {
            this.var = var;
            this.from = from;
            this.to = to;
            this.graph = graph;
        }

        @Override
        public List<PGraph> make() {
            return specialize().make();
        }

        @Override
        public PList specialize() {
            int min = Math.min(from.getValue(), to.getValue());
            int max = Math.max(from.getValue(), to.getValue());
            List<PGraph> graphs = new ArrayList<>();
            for (int i = min; i <= max; i++) {
                var.setValue(i);
                graphs.add(graph.specialize());
            }
            return new GraphList(graphs);
        }
    }

    interface NumVar {
        int getValue();
    }

    static class Num implements NumVar {
        final int value;

        public Num(int value) {
            this.value = value;
        }

        @Override
        public int getValue() {
            return value;
        }
    }

    class Var implements NumVar {
        final int index;

        public Var(int index) {
            this.index = index;
        }

        @Override
        public int getValue() {
            return variableValues[index];
        }

        public void setValue(int value) {
            variableValues[index] = value;
        }
    }

    char[] s;
    int pos;
    int[] variableValues = new int[26];
    List<Edge> path = new ArrayList<>();
    void run() {
        s = (in.nextLine() + "$").toCharArray();

        Vertex first = new Vertex();
        Vertex last = new Vertex();
        parseGraph().specialize().make(first, last);
        expect('$');

        vertices.get(vertices.size() - 1).index = last.index;
        last.index = vertices.size() - 1;

        Vertex spare = null;
        Vertex f = first;
        for (Vertex v : vertices) {
            if (v.edges.size() % 2 == 1) {
                f = v;
                if (spare == null) {
                    spare = v;
                } else {
                    new Edge(v, spare, true);
                    spare = null;
                }
            }
        }

        for (Edge edge : f.edges) {
            if (edge.fake) {
                f.edges.remove(edge);
                edge.other(f).edges.remove(edge);
                break;
            }
        }

        f.walk();
        Collections.reverse(path);

        List<List<Integer>> paths = new ArrayList<>();
        List<Integer> p = new ArrayList<>();
        Vertex v = f;
        p.add(v.index);
        for (Edge edge : path) {
            if (edge.fake) {
                paths.add(p);
                p = new ArrayList<>();
            }
            v = edge.other(v);
            p.add(v.index);
        }
        paths.add(p);

        out.println(vertices.size() + " " + paths.size());
        for (List<Integer> path : paths) {
            out.print(path.size());
            for (Integer i : path) {
                out.print(" " + (i + 1));
            }
            out.println();
        }
    }

    private PGraph parseGraph() {
        if (next('c')) {
            if (!next('(')) {
                return c;
            }
            return new C(parseList());
        } else if (next('l')) { expect('o'); expect('o'); expect('p'); expect('(');
            return new L(parseList());
        } else if (next('t')) { expect('(');
            return new T(parseList());
        }
        throw new AssertionError();
    }

    private PList parseList() {
        final PList result;
        if ('1' <= s[pos] && s[pos] <= '9') {
            result = new NumVarList(parseNum(), parseTail());
        } else if (next('r')) { expect('a'); expect('n'); expect('g'); expect('e'); expect('(');
            Var var = parseVar();
            expect(',');
            NumVar a = parseNumVar();
            expect(',');
            NumVar b = parseNumVar();
            expect(')');
            result = new RangeList(var, a, b, parseTail());
        } else if ('A' <= s[pos] && s[pos] <= 'Z') {
            result = new NumVarList(parseVar(), parseTail());
        } else {
            List<PGraph> list = new ArrayList<>();
            list.add(parseGraph());
            while (next(',')) {
                list.add(parseGraph());
            }
            result = new GraphList(list);
        }
        expect(')');
        return result;
    }

    private PGraph parseTail() {
        if (next(',')) {
            return parseGraph();
        } else {
            return c;
        }
    }

    private Num parseNum() {
        int value = 0;
        while ('0' <= s[pos] && s[pos] <= '9') {
            value = value * 10 + s[pos++] - '0';
        }
        return new Num(value);
    }

    private NumVar parseNumVar() {
        if ('1' <= s[pos] && s[pos] <= '9') {
            return parseNum();
        } else if ('A' <= s[pos] && s[pos] <= 'Z') {
            return parseVar();
        }
        throw new AssertionError();
    }

    private Var parseVar() {
        return new Var(s[pos++] - 'A');
    }

    private void expect(char ch) {
        boolean found = next(ch);
        assert found : String.format("%d: Expected '%c', found '%c'", pos + 1, ch, s[pos]);
    }

    private boolean next(char ch) {
        if (s[pos] == ch) {
            pos++;
            return true;
        }
        return false;
    }

    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("cactus.in"));
        out = new PrintWriter("cactus.out");

        new cactus_gk().run();

        in.close();
        out.close();
    }
}

