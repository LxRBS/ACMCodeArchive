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
/* Author                Georgiy Korneev                          */
/******************************************************************/

import java.io.*;
import java.util.*;
import java.util.stream.Stream;

public class hidden_gk {
    static Scanner in;
    static PrintWriter out;

    class Edge {
        int c;
        Vertex from, to;

        public Edge(int c, Vertex from, Vertex to) {
            this.c = c;
            this.from = from;
            this.to = to;
        }
    }
    class Vertex {
        List<Edge> edges = new ArrayList<>();
        Vertex parent;
        int h;
        int[] ways;
        int w = 1;

        public int hang(Vertex parent) {
            this.parent = parent;
            Vertex[] children = edges.stream().filter(e -> e.to != parent).map(e -> e.to).toArray(Vertex[]::new);
            h = Stream.of(children).mapToInt(v -> v.hang(this)).max().orElse(0);
            ways = new int[2 * h + 3];
            add(0, 1);
            for (Vertex child : children) {
                for (int i = 0; i < child.ways.length; i++) {
                    ways[i - child.h + 1 + h] += child.ways[i];
                }
            }
            return h + 1;
        }

        public int get(int i) {
            return ways[i + h + 1];
        }

        public void add(int i, int d) {
            ways[i + h + 1] += d;
        }
    }

    void run() {
        int n = in.nextInt();
        Vertex[] vertices = Stream.generate(Vertex::new).limit(n).toArray(Vertex[]::new);
        Edge[] edges = new Edge[n - 1];
        for (int i = 0; i < n - 1; i++) {
            Vertex u = vertices[in.nextInt() - 1];
            Vertex v = vertices[in.nextInt() - 1];
            int c = in.nextInt();
            edges[i] = new Edge(c, u, v);
            u.edges.add(edges[i]);
            v.edges.add(new Edge(c, v, u));
        }
        long start = System.currentTimeMillis();
        System.out.println("read " + (System.currentTimeMillis() - start));
        vertices[0].hang(null);
        System.out.println("hang " + (System.currentTimeMillis() - start));
        Arrays.sort(edges, Comparator.comparing(e -> e.c));
        System.out.println("sort " + (System.currentTimeMillis() - start));
        long total = 0;
        long count = 0;
        for (Edge edge : edges) {
            Vertex bottom = edge.from.h < edge.to.h ? edge.from : edge.to;

            long ways = 0;
            Vertex v = bottom;
            int balance = 0;
            while (v.parent != null) {
                for (int i = -bottom.h; i <= bottom.h; i++) {
                    ways += bottom.get(i) * (v.parent.get(-(i + balance)) - v.get(-(i + balance + v.w)));
                }

                v = v.parent;
                balance += v.w;
            }

            balance = 0;
            v = bottom.parent;
            while (v != null) {
                for (int i = -bottom.h; i <= bottom.h; i++) {
                    v.add(i + balance + 1, -bottom.get(i));
                    v.add(i + balance - 1, bottom.get(i));
                }
                balance += v.w;
                v = v.parent;
            }
            bottom.w = -1;

            total += ways * edge.c;
            count += ways;
        }
        System.out.println("done " + (System.currentTimeMillis() - start));
        out.println(total / (double) count);
    }

    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("hidden.in"));
        out = new PrintWriter("hidden.out");

        new hidden_gk().run();

        in.close();
        out.close();
    }

    static class Scanner {
        final BufferedReader reader;
        StringTokenizer tokenizer = new StringTokenizer("");

        public Scanner(File file) throws FileNotFoundException {
            reader = new BufferedReader(new FileReader(file));
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

        public String next() {
            while (!tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new AssertionError();
                }
            }
            return tokenizer.nextToken();
        }

        public void close() {
        }
    }
}

