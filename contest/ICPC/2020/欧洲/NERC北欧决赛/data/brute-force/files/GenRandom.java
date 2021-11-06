import java.io.PrintWriter;
import java.util.*;

public class GenRandom {

    public final static int SEED = "button-lock".hashCode();
    public final static Random rng = new Random(SEED);
    public final static int ARGS_COUNT = 2;

    public final static int MAX_D = 10;

    public static void main(String[] args) {
        if (args.length < ARGS_COUNT) {
            throw new IllegalArgumentException(
                    String.format("Expected %d arguments, but got %d instead", ARGS_COUNT, args.length));
        }
        rng.setSeed(Arrays.hashCode(args));
        int d = Integer.parseInt(args[0]);
        int n = Integer.parseInt(args[1]);
        random(d, n).print();
    }

    static TestCase random(int d, int n) {
        Set<Integer> used = new HashSet<>();
        List<Integer> masks=  new ArrayList<>();
        while (used.size() < n) {
            used.add(rng.nextInt((1 << d) - 1) + 1);
        }
        return new TestCase(d, new ArrayList<>(used));
    }

    static class TestCase {
        int d;
        List<Integer> masks;

        public TestCase(int d, List<Integer> masks) {
            this.d = d;
            this.masks = masks;
        }

        TestCase shuffled() {
            Collections.shuffle(masks, rng);
            return this;
        }

        void print() {
            try (PrintWriter out = new PrintWriter(System.out)) {
                out.println(d + " " + masks.size());
                for (int mask : masks) {
                    for (int i = 0; i < d; i++) {
                        out.print((mask >> i) & 1);
                    }
                    out.println();
                }
            }
        }
    }
}
