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

import java.io.File;
import java.io.PrintWriter;
import java.util.*;
import java.util.stream.Stream;

public class hidden_gk_slow {
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
            ways = new int[2 * h + 1];
            add(0, 1);

            for (int i = -h; i <= h; i++) {
                int ii = i;
                add(i, Stream.of(children).mapToInt(v -> v.get(ii - 1)).sum());
            }
            return h + 1;
        }

        public int get(int i) {
            return -h <= i && i <= h ? ways[i + h] : 0;
        }

        public void add(int i, int d) {
            ways[i + h] += d;
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
        vertices[0].hang(null);
        Arrays.sort(edges, Comparator.comparing(e -> e.c));
        long total = 0;
        long count = 0;
        for (Edge edge : edges) {
            Vertex bottom = edge.from.h < edge.to.h ? edge.from : edge.to;

            long ways = 0;
            Vertex v = bottom.parent;
            Vertex p = bottom;
            int pw = 1;
            int balance = 0;
            while (v != null) {
                for (int i = -bottom.h; i <= bottom.h; i++) {
                    ways += bottom.get(i) * (v.get(-(i + balance)) - p.get(-(i + balance + pw)));
                }

                balance += v.w;
                p = v;
                pw = v.w;
                v = v.parent;
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
        out.println(total / (double) count);
    }

    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("hidden.in"));
        out = new PrintWriter("hidden.out");

        new hidden_gk_slow().run();

        in.close();
        out.close();
    }
}

