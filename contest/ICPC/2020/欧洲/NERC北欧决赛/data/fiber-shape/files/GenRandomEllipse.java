import java.io.PrintWriter;
import java.util.*;

public class GenRandomEllipse {

    public final static int SEED = "ellipses".hashCode();
    public final static Random rng = new Random(SEED);
    public final static int ARGS_COUNT = 3;
    public final static int MAX = 100000;

    public static void main(String[] args) {
        if (args.length < ARGS_COUNT) {
            throw new IllegalArgumentException(
                    String.format("Expected %d arguments, but got %d instead", ARGS_COUNT, args.length));
        }
        rng.setSeed(Arrays.hashCode(args));
        int n = Integer.parseInt(args[0]);
        int maxA = Integer.parseInt(args[1]);
        int maxB = Integer.parseInt(args[2]);
        generateRandomEllipse(n, maxA, maxB).print();
    }

    static TestCase generateRandomEllipse(int n, int A, int B) {
        Set<Point> pts = new HashSet<>();
        double rotate = rng.nextDouble() * 2 * Math.PI;
        for (int i = 0; i < n; i++) {
            double angle = rng.nextDouble() * 2 * Math.PI;
            double curA = A * Math.cos(angle), curB = B * Math.sin(angle);
            pts.add(new Point((int) (curA * Math.cos(rotate) - curB * Math.sin(rotate)),
                              (int) (curA * Math.sin(rotate) + curB * Math.cos(rotate))));
        }
        return new TestCase(new ArrayList<>(pts));
    }

    private static int randRange(int min, int max) {
        return min + rng.nextInt(max - min + 1);
    }

    static class Point {
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
