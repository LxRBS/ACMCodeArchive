import java.io.*;
import java.util.*;

public class SkipPoints {

    final static int MAX_L = 800_000;

    public static void main(String[] args) {
        if (args.length == 0) {
            System.err.println("Required one argument: number of points to retain");
        }
        int realN = Integer.parseInt(args[0]);
        FastScanner in = new FastScanner(System.in);
        int n = in.nextInt();
        Point[] points = new Point[n];
        for (int i = 0; i < n; i++) {
            points[i] = new Point(in.nextInt(), in.nextInt());
        }

        int perim = (int) Math.ceil(perimeter(Arrays.asList(points)) + 1e-3);
        Random rng = new Random(perim + Arrays.hashCode(args));
        boolean[] leave = new boolean[n];
        Arrays.fill(leave, 0, realN, true);
        for (int i = 1; i < leave.length; i++) {
            int pos = rng.nextInt(i + 1);
            boolean tmp = leave[pos];
            leave[pos] = leave[i];
            leave[i] = tmp;
        }

        try (PrintWriter out = new PrintWriter(System.out)) {
            out.println(realN);
            for (int i = 0; i < points.length; i++) {
                if (leave[i]) {
                    Point p = points[i];
                    out.println(p.x + " " + p.y);
                }
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
