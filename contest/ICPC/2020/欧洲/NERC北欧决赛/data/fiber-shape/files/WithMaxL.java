import java.io.*;
import java.util.Arrays;
import java.util.List;
import java.util.Random;
import java.util.StringTokenizer;

public class WithMaxL {

    final static int MAX_L = 800_000;

    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(System.in);
        int n;
        int perim = -1;
        String[] tokens = in.br.readLine().split(" ");
        n = Integer.parseInt(tokens[0]);
        if (tokens.length > 1) {
            perim = Integer.parseInt(tokens[1]);
        }
        Point[] points = new Point[n];
        for (int i = 0; i < n; i++) {
            points[i] = new Point(in.nextInt(), in.nextInt());
        }
        if (perim == -1) {
            perim = (int) Math.ceil(perimeter(Arrays.asList(points)) + 1e-3);
        }
        Random rng = new Random(perim);

        try (PrintWriter out = new PrintWriter(System.out)) {
            out.println(points.length + " " + MAX_L);
            int shift = rng.nextInt(points.length);
            for (int i = 0; i < points.length; i++) {
                Point p = points[(i + shift) % points.length];
                out.println(p.x + " " + p.y);
            }
        }
    }

    static double perimeter(List<Point> a) {
        double p = 0;
        for (int i = 0; i < a.size(); i++) {
            double dx = a.get((i + 1) % a.size()).x - a.get(i).x;
            double dy = a.get((i + 1) % a.size()).y - a.get(i).y;
            p += Math.sqrt(dx * dx + dy * dy);
        }
        return p;
    }

    static long vm(Point a, Point b, Point c) {
        return (long) (b.x - a.x) * (c.y - a.y) - (long) (b.y - a.y) * (c.x - a.x);
    }

    static class Point implements Comparable<Point> {
        int x, y;

        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public int compareTo(Point o) {
            if (x != o.x) {
                return x - o.x;
            }
            return y - o.y;
        }
    }

    static class FastScanner {
        public BufferedReader br;
        public StringTokenizer st;

        public FastScanner(InputStream in) {
            br = new BufferedReader(new InputStreamReader(in));
        }

        public FastScanner(String fileName) {
            try {
                br = new BufferedReader(new FileReader(fileName));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

        public String next() {
            while (st == null || !st.hasMoreElements()) {
                String line = null;
                try {
                    line = br.readLine();
                } catch (IOException e) {
                }
                st = new StringTokenizer(line);
            }
            return st.nextToken();
        }

    }
}
