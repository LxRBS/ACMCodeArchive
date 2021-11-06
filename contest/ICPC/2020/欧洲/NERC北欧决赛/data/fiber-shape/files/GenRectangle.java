import java.io.PrintWriter;
import java.util.*;

public class GenRectangle {

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
        int maxA = Integer.parseInt(args[0]);
        int maxB = Integer.parseInt(args[1]);
        generateRandom(maxA, maxB).print();
    }

    static TestCase generateRandom(int a, int b) {
        List<Point> pts = new ArrayList<>();
        pts.add(new Point(0, 0));
        pts.add(new Point(a, 0));
        pts.add(new Point(a, b));
        pts.add(new Point(0, b));
        return new TestCase(pts);
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
