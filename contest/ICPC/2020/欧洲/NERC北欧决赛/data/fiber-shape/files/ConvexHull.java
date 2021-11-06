import java.io.*;
import java.util.*;

public class ConvexHull {

    final static int MAX_L = 800_000;

    public static void main(String[] args) {
        FastScanner in = new FastScanner(System.in);
        int n = in.nextInt();
        Point[] points = new Point[n];
        for (int i = 0; i < n; i++) {
            points[i] = new Point(in.nextInt(), in.nextInt());
        }
        Arrays.sort(points);
        List<Point> lower = new ArrayList<>(), upper = new ArrayList<>();
        for (Point p : points) {
            while (lower.size() >= 2 && vm(lower.get(lower.size() - 2), lower.get(lower.size() - 1), p) <= 0) {
                lower.remove(lower.size() - 1);
            }
            lower.add(p);
        }

        for (int i = points.length - 1; i >= 0; i--) {
            Point p = points[i];
            while (upper.size() >= 2 && vm(upper.get(upper.size() - 2), upper.get(upper.size() - 1), p) <= 0) {
                upper.remove(upper.size() - 1);
            }
            upper.add(p);
        }
        lower.remove(lower.size() - 1);
        upper.remove(upper.size() - 1);
        lower.addAll(upper);
        int perim = (int) Math.ceil(perimeter(lower) + 1e-3);
        Random rng = new Random(perim);
        perim += rng.nextInt(Math.min(MAX_L - perim + 1, perim));

        try (PrintWriter out = new PrintWriter(System.out)) {
            out.println(lower.size() + " " + perim);
            int shift = rng.nextInt(lower.size());
            for (int i = 0; i < lower.size(); i++) {
                Point p = lower.get((i + shift) % lower.size());
                out.println(p.x + " " + p.y);
            }
        }
    }

    static double perimeter(List<Point> a) {
        double p = 0;
        for (int i = 0; i < a.size(); i++) {
            double dx = a.get((i + 1) % a.size()).x - a.get(i).x;
            double dy = a.get((i + 1) % a.size()).y - a.get(i).y;
            p +=  Math.sqrt(dx * dx + dy * dy);
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
