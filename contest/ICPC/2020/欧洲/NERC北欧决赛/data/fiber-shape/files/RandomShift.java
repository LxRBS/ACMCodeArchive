import java.io.*;
import java.util.*;

public class RandomShift {

    final static int MAX_COORD = 100_000;

    public static void main(String[] args) {
        FastScanner in = new FastScanner(System.in);
        int n = in.nextInt();
        int l = in.nextInt();
        Point[] points = new Point[n];
        int minX = Integer.MAX_VALUE, minY = Integer.MAX_VALUE;
        int maxX = Integer.MIN_VALUE, maxY = Integer.MIN_VALUE;
        for (int i = 0; i < n; i++) {
            points[i] = new Point(in.nextInt(), in.nextInt());
            minX = Math.min(minX, points[i].x);
            minY = Math.min(minY, points[i].y);
            maxX = Math.max(maxX, points[i].x);
            maxY = Math.max(maxY, points[i].y);
        }
        Random rng = new Random(Arrays.hashCode(points));
        int shiftX = randRange(rng, -MAX_COORD - minX, MAX_COORD - maxX);
        int shiftY = randRange(rng, -MAX_COORD - minY, MAX_COORD - maxY);

        try (PrintWriter out = new PrintWriter(System.out)) {
            out.println(points.length + " " + l);
            for (Point p : points) {
                out.println((p.x + shiftX) + " " + (p.y + shiftY));
            }
        }
    }

    static int randRange(Random rng, int min, int max) {
        return min + rng.nextInt(max - min + 1);
    }

    static class Point implements Comparable<Point> {
        int x, y;

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Point point = (Point) o;
            return x == point.x && y == point.y;
        }

        @Override
        public int hashCode() {
            return Objects.hash(x, y);
        }

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
