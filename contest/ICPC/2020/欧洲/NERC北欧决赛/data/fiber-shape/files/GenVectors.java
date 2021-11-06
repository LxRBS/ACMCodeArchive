import java.io.PrintWriter;
import java.util.*;

public class GenVectors {

    public final static int SEED = "ellipses".hashCode();
    public final static Random rng = new Random(SEED);
    public final static int ARGS_COUNT = 2;
    public final static int MAX = 100000;

    public static void main(String[] args) {
        if (args.length < ARGS_COUNT) {
            throw new IllegalArgumentException(
                    String.format("Expected %d arguments, but got %d instead", ARGS_COUNT, args.length));
        }
        rng.setSeed(Arrays.hashCode(args));
        int n = Integer.parseInt(args[0]);
        int max = Integer.parseInt(args[1]);
        generateRandom(n, max).print();
    }

    static int gcd(int a, int b) {
        if (a == 0) {
            return b;
        }
        return gcd(b % a, a);
    }

    static TestCase generateRandom(int n, int max) {
        Set<Point> set = new TreeSet<>();
        for (int i = 1; i <= max; i++) {
            for (int j = 0; j <= max; j++) {
                if (Math.abs(gcd(i, j)) == 1 ) {
                    set.add(new Point(i, j));
                }
            }
        }
        List<Point> sortedPoints = new ArrayList<>(set);
        Collections.sort(sortedPoints,
                Comparator.comparingLong(p -> (long) p.x * p.x + (long) p.y * p.y));
        sortedPoints = new ArrayList<>(sortedPoints.subList(0, n / 4));
        Collections.sort(sortedPoints);

        List<Point> p = new ArrayList<>();
        p.add(new Point(0, 0));
        for (int rot = 0; rot < 4; rot++) {
            for (Point vec : sortedPoints) {
                Point last = p.get(p.size() - 1);
                p.add(new Point(last.x + vec.x, last.y + vec.y));
                vec.rotate90();
            }
        }
        p.remove(p.size() - 1);
        return new TestCase(p);
    }

    private static int randRange(int min, int max) {
        return min + rng.nextInt(max - min + 1);
    }

    static class Point implements Comparable<Point> {
        int x, y;

        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        }

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

        int q() {
            if (y > 0 || y == 0 && x > 0) {
                return 1;
            }
            return 2;
        }

        @Override
        public int compareTo(Point o) {
            if (q() != o.q()) {
                return q() - o.q();
            }
            long vm = (long) x * o.y - (long) y * o.x;
            return -Long.signum(vm);
        }

        public void rotate90() {
            int oldX = x;
            x = -y;
            y = oldX;
        }
    }

    static class TestCase {
        List<Point> points;

        public TestCase(List<Point> points) {
            this.points = points;
        }

        public void print() {
            try (PrintWriter out = new PrintWriter(System.out)) {
                out.println(points.size());
                for (Point p : points) {
                    out.println(p.x + " " + p.y);
                }
            }
        }
    }
}
