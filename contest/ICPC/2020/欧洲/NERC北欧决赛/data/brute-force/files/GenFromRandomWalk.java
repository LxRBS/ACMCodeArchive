import java.io.PrintWriter;
import java.util.*;

public class GenFromRandomWalk {

    public final static int SEED = "button-lock".hashCode();
    public final static Random rng = new Random(SEED);
    public final static int ARGS_COUNT = 3;

    public final static int MAX_D = 10;

    public static void main(String[] args) {
        if (args.length < ARGS_COUNT) {
            throw new IllegalArgumentException(
                    String.format("Expected %d arguments, but got %d instead", ARGS_COUNT, args.length));
        }
        rng.setSeed(Arrays.hashCode(args));
        int d = Integer.parseInt(args[0]);
        int n = Integer.parseInt(args[1]);
        double prob = Double.parseDouble(args[2]);
        randomWalk(d, n, prob).print();
    }

    static TestCase randomWalk(int d, int n, double prob) {
        Set<Integer> used = new HashSet<>();
        int mask = 0;
        while (true) {
            if (mask > 0 && rng.nextDouble() < prob) {
                used.add(mask);
                if (used.size() == n) {
                    break;
                }
            }
            List<Integer> next = new ArrayList<>();
            next.add(0);
            for (int bit = 0; bit < d; bit++) {
                if ((mask & (1 << bit)) == 0) {
                    next.add(mask | (1 << bit));
                }
            }
            mask = next.get(rng.nextInt(next.size()));
        }

        return new TestCase(d, new ArrayList<>(used)).shuffled();
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
