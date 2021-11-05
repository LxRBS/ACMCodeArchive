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
/* Author                Roman Elizarov                           */
/******************************************************************/

import java.io.*;
import java.util.*;

/**
 * Solution for NEERC'2014 Problem C: Cactus Generator
 * This solution checks correctness of the input.
 *
 * @author Roman Elizarov
 */
public class cactus_re {
    private static final String INPUT = "cactus.in";
    private static final String OUTPUT = "cactus.out";
    private static final int MAX_LENGTH = 1000;
    private static final int MAX_N = 50000;

    public static void main(String[] args) throws Exception {
        new cactus_re().go();
    }

    void go() throws IOException {
        long time = System.currentTimeMillis();
        try (Scanner in = new Scanner(new File(INPUT))) {
            in.useLocale(Locale.US);
            read(in);
        }
        parse();
        solve();
        try (PrintWriter out = new PrintWriter(OUTPUT)) {
            write(out);
        }
        System.out.printf("Done in %d ms%n", System.currentTimeMillis() - time);
    }

    String s;

    void read(Scanner in) {
        s = in.next();
        in.nextLine();
        assert s.length() <= MAX_LENGTH;
    }

    int pos;
    TokenType tokenType;
    String token;
    int num;
    Set<String> definedVars = new HashSet<>();

    Graph g;

    void parse() {
        nextToken();
        GraphNode gn = parseGraph();
        assert tokenType == TokenType.EOF : "Extra token '" + token + "'";
        g = new Graph();
        gn.build(new Context(), g, g.next(), g.next());
        g.swap(1, g.n - 1);
    }

    class PathNode {
        final int i;
        PathNode prev;
        PathNode next;

        PathNode(int i) {
            this.i = i;
        }
    }

    List<PathNode> paths = new ArrayList<>();

    void solve() {
        Map<Integer,PathNode> nm = new LinkedHashMap<>();
        Set<Integer> odd = new LinkedHashSet<>();
        for (int i = 0; i < g.adj.size(); i++) {
            Set<Integer> a = g.adj.get(i);
            if (a.size() % 2 != 0)
                odd.add(i);
        }
        while (!odd.isEmpty()) {
            int i = odd.iterator().next();
            odd.remove(i);
            PathNode path = new PathNode(i);
            int j = buildPathFrom(path, odd, nm).i;
            odd.remove(j);
            paths.add(path);
        }
        if (paths.isEmpty()) {
            for (int i = 0; i < g.adj.size(); i++) {
                Set<Integer> a = g.adj.get(i);
                if (!a.isEmpty()) {
                    PathNode path = new PathNode(i);
                    buildPathFrom(path, Collections.singleton(i), nm);
                    paths.add(path);
                    break;
                }
            }
        }
        while (!nm.isEmpty()) {
            PathNode node = nm.values().iterator().next();
            int i = node.i;
            while (!g.adj.get(i).isEmpty()) {
                PathNode next = node.next;
                node = buildPathFrom(node, Collections.singleton(i), nm);
                if (next != null) {
                    node.next = next;
                    next.prev = node;
                }
            }
            nm.remove(i);
        }
    }

    private PathNode buildPathFrom(PathNode prev, Set<Integer> odd, Map<Integer, PathNode> nm) {
        nm.put(prev.i, prev);
        int i, j;
        do {
            i = prev.i;
            Set<Integer> a = g.adj.get(i);
            j = a.iterator().next();
            g.remove(i, j);
            PathNode next = new PathNode(j);
            nm.put(next.i, next);
            next.prev = prev;
            prev.next = next;
            prev = next;
        } while (!odd.contains(j));
        return prev;
    }

    private void nextToken() {
        token = "";
        if (pos >= s.length()) {
            tokenType = TokenType.EOF;
            return;
        }
        int start = pos;
        char c = s.charAt(pos++);
        if (c >= '1' && c <= '9') {
            tokenType = TokenType.NUM;
            num = c - '0';
            while (pos < s.length()) {
                c = s.charAt(pos);
                if (c < '0' || c > '9')
                    break;
                num = 10 * num + c - '0';
                assert num <= MAX_N : "Number too big: " + num;
                pos++;
            }
        } else if (c >= 'A' && c <= 'Z') {
            tokenType = TokenType.VAR;
        } else if (c >= 'a' && c <= 'z') {
            while (pos < s.length()) {
                c = s.charAt(pos);
                if (c < 'a' || c > 'z')
                    break;
                pos++;
            }
            String word = s.substring(start, pos);
            switch (word) {
                case "c":
                    tokenType = TokenType.C;
                    break;
                case "loop":
                    tokenType = TokenType.LOOP;
                    break;
                case "t":
                    tokenType = TokenType.T;
                    break;
                case "range":
                    tokenType = TokenType.RANGE;
                    break;
                default:
                    throw new AssertionError("Invalid word '" + word + "'");
            }
        } else switch (c) {
            case '(':
                tokenType = TokenType.OPEN;
                break;
            case ')':
                tokenType = TokenType.CLOSE;
                break;
            case ',':
                tokenType = TokenType.COMMA;
                break;
            default:
                throw new AssertionError("Illegal token char '" + c + "'");
        }
        token = s.substring(start, pos);
    }

    private void ensureToken(TokenType expected) {
        if (tokenType != expected)
            throw new AssertionError("Expected " + expected + ", but found " + tokenType + " '" + token + "'");
    }

    private void skipToken(TokenType expected) {
        ensureToken(expected);
        nextToken();
    }

    GraphNode parseGraph() {
        TokenType word = tokenType;
        nextToken();
        if (word == TokenType.C && tokenType != TokenType.OPEN)
            return C;
        skipToken(TokenType.OPEN);
        GraphNode gn;
        switch (word) {
            case C:
                gn = new C(parseList());
                break;
            case LOOP:
                gn = new Loop(parseList());
                break;
            case T:
                gn = new T(parseList());
                break;
            default:
                throw new AssertionError("Invalid word '" + word + "'");
        }
        skipToken(TokenType.CLOSE);
        return gn;
    }

    ListNode parseList() {
        switch (tokenType) {
            case NUM:
            case VAR:
                NumVar nv = parseNumVar();
                if (tokenType == TokenType.COMMA) {
                    nextToken();
                    return new NumList(nv, parseGraph());
                } else
                    return new NumList(nv, C);
            case RANGE:
                nextToken();
                skipToken(TokenType.OPEN);
                ensureToken(TokenType.VAR);
                String var = token;
                boolean notPresent = definedVars.add(var);
                assert notPresent : "Variable '" + var + "' is defined more than once";
                nextToken();
                skipToken(TokenType.COMMA);
                NumVar anv = parseNumVar();
                skipToken(TokenType.COMMA);
                NumVar bnv = parseNumVar();
                skipToken(TokenType.CLOSE);
                if (tokenType == TokenType.COMMA) {
                    nextToken();
                    return new RangeList(var, anv, bnv, parseGraph());
                } else
                    return new RangeList(var, anv, bnv, C);
        }
        // explicit graph list
        List<GraphNode> list = new ArrayList<>();
        list.add(parseGraph());
        while (tokenType == TokenType.COMMA) {
            nextToken();
            list.add(parseGraph());
        }
        return new GraphList(list);
    }

    private NumVar parseNumVar() {
        NumVar nv;
        switch (tokenType) {
            case NUM:
                nv = new Num(num);
                break;
            case VAR:
                nv = new Var(token);
                break;
            default:
                throw new AssertionError("numvar expected");
        }
        nextToken();
        return nv;
    }


    void write(PrintWriter out) {
        out.println(g.n + " " + paths.size());
        for (PathNode path : paths) {
            int k = 0;
            PathNode node = path;
            do {
                k++;
                node = node.next;
            } while (node != null);
            out.print(k);
            node = path;
            do {
                out.print(" " + (node.i + 1));
                node = node.next;
            } while (node != null);
            out.println();
        }
    }

    enum TokenType { NUM, VAR, C, LOOP, T, RANGE, OPEN, CLOSE, COMMA, EOF }

    class Graph {
        int n;
        List<Set<Integer>> adj = new ArrayList<>();

        void swap(int i, int j) {
            Set<Integer> set = adj.get(i);
            adj.set(i, adj.get(j));
            adj.set(j, set);
            for (Set<Integer> a : adj) {
                if (a.contains(i) != a.contains(j)) {
                    if (a.remove(i)) {
                        a.add(j);
                    } else if (a.remove(j))
                        a.add(i);
                }
            }
        }

        int next() {
            adj.add(new LinkedHashSet<>());
            return n++;
        }

        void edge(int i, int j) {
            boolean ok = adj.get(i).add(j);
            ok &= adj.get(j).add(i);
            assert ok : "There are no multiple edges between vertices -- violated";
        }

        public void remove(int i, int j) {
            adj.get(i).remove(j);
            adj.get(j).remove(i);
        }
    }

    class Context {
        Map<String, Integer> vars = new HashMap<>();

        int get(String var) {
            Integer result = vars.get(var);
            assert result != null : "Not bound variable '" + var + "'";
            return result;
        }

        void assertUnused(String var) {
            assert !vars.containsKey(var) : "var cannot be bound more than once '" + var + "'";
        }

        void put(String var, int n) {
            vars.put(var, n);
        }

        void remove(String var) {
            vars.remove(var);
        }
    }

    interface GraphNode {
        // return true when there are multiple simple paths between first and last
        boolean build(Context ctx, Graph g, int first, int last);
    }

    interface ListNode {
        void visit(Context ctx, Graph g, GraphVisitor v);
    }

    interface GraphVisitor {
        void accept(Context ctx, Graph g, GraphNode gn, int i, int n);
    }

    interface NumVar {
        int get(Context ctx);
    }

    class Num implements NumVar {
        final int num;

        Num(int num) {
            this.num = num;
        }

        @Override
        public int get(Context ctx) {
            return num;
        }
    }

    class Var implements NumVar {
        final String var;

        Var(String var) {
            this.var = var;
        }

        @Override
        public int get(Context ctx) {
            return ctx.get(var);
        }
    }

    class NumList implements ListNode {
        final NumVar numvar;
        final GraphNode gn;

        NumList(NumVar numvar, GraphNode gn) {
            this.numvar = numvar;
            this.gn = gn;
        }

        @Override
        public void visit(Context ctx, Graph g, GraphVisitor v) {
            int n = numvar.get(ctx);
            for (int i = 0; i < n; i++) {
                v.accept(ctx, g, gn, i, n);
            }
        }
    }

    class RangeList implements ListNode {
        final String var;
        final NumVar anv;
        final NumVar bnv;
        final GraphNode gn;

        RangeList(String var, NumVar anv, NumVar bnv, GraphNode gn) {
            this.var = var;
            this.anv = anv;
            this.bnv = bnv;
            this.gn = gn;
        }

        @Override
        public void visit(Context ctx, Graph g, GraphVisitor v) {
            int a = anv.get(ctx);
            int b = bnv.get(ctx);
            if (a > b) {
                int t = a;
                a = b;
                b = t;
            }
            int n = b - a + 1;
            for (int i = 0; i < n; i++) {
                ctx.put(var, a + i);
                v.accept(ctx, g, gn, i, n);
            }
            ctx.remove(var);
        }
    }

    class GraphList implements ListNode {
        final List<GraphNode> list;

        GraphList(List<GraphNode> list) {
            this.list = list;
        }

        @Override
        public void visit(Context ctx, Graph g, GraphVisitor v) {
            int n = list.size();
            for (int i = 0; i < n; i++) {
                GraphNode gn = list.get(i);
                v.accept(ctx, g, gn, i, n);
            }
        }
    }

    static final C0 C = new C0();

    static class C0 implements GraphNode {
        @Override
        public boolean build(Context ctx, Graph g, int first, int last) {
            g.edge(first, last);
            return false;
        }
    }

    static class C implements GraphNode, GraphVisitor {
        final ListNode list;
        boolean multi;
        int prev;
        int last;

        C(ListNode list) {
            this.list = list;
        }

        @Override
        public boolean build(Context ctx, Graph g, int first, int last) {
            multi = false;
            this.prev = first;
            this.last = last;
            list.visit(ctx, g, this);
            return multi;
        }

        @Override
        public void accept(Context ctx, Graph g, GraphNode gn, int i, int n) {
            int next = i == n - 1 ? last : g.next();
            multi |= gn.build(ctx, g, prev, next);
            prev = next;
        }
    }

    static class Loop implements GraphNode, GraphVisitor {
        final ListNode list;
        int first;
        int prev;

        Loop(ListNode list) {
            this.list = list;
        }

        @Override
        public boolean build(Context ctx, Graph g, int first, int last) {
            this.first = first;
            this.prev = last;
            list.visit(ctx, g, this);
            return true;
        }

        @Override
        public void accept(Context ctx, Graph g, GraphNode gn, int i, int n) {
            assert n > 1 : "Loop can be applied only to lists with more than one graph";
            if (i == 0)
                gn.build(ctx, g, first, prev);
            else {
                int next = i == n - 1 ? first : g.next();
                boolean multi = gn.build(ctx, g, prev, next);
                assert !multi : "Every edge belongs to at most one simple cycle -- violated";
                prev = next;
            }
        }
    }

    static class T implements GraphNode, GraphVisitor {
        final ListNode list;
        boolean multi;
        int first;
        int last;


        T(ListNode list) {
            this.list = list;
        }

        @Override
        public boolean build(Context ctx, Graph g, int first, int last) {
            multi = false;
            this.first = first;
            this.last = last;
            list.visit(ctx, g, this);
            return multi;
        }

        @Override
        public void accept(Context ctx, Graph g, GraphNode gn, int i, int n) {
            int next = i == 0 ? last : g.next();
            gn.build(ctx, g, first, next);
        }
    }

//----------------- just for validation ------------------

    /**
     * Strict scanner to verify 100% correspondence between input files and input file format specification.
     * It is a drop-in replacement for {@link java.util.Scanner} that could be added to a solution source
     * (cut-and-paste) without breaking its ability to work with {@link java.util.Scanner}.
     */
    static class Scanner implements Closeable {
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

