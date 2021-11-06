import java.io.PrintWriter;
import java.util.*;

public class GenRandomSameLength {

    public final static int SEED = "lost-permutation".hashCode();
    public final static Random rng = new Random(SEED);
    public final static int ARGS_COUNT = 1;

    public final static int MAX_N = 10000;
    
    public static void main(String[] args) {
        if (args.length < ARGS_COUNT) {
            throw new IllegalArgumentException(
                    String.format("Expected %d arguments, but got %d instead", ARGS_COUNT, args.length));
        }
        rng.setSeed(Arrays.hashCode(args));
        int n = Integer.parseInt(args[0]);
        printTest(generateRandom(n));
    }

    static TestCase generateRandom(int n) {
        int remLength = MAX_N;
        List<int[]> permutations = new ArrayList<>();
        while (remLength >= n) {
            permutations.add(randomPermutation(n));
            remLength -= n;
        }
        return new TestCase(permutations);
    }

    private static int[] randomPermutation(int n) {
        int[] result = new int[n];
        for (int i = 0; i < n; i++) {
            int pos = rng.nextInt(i + 1);
            result[i] = result[pos];
            result[pos] = i + 1;
        }
        return result;
    }

    static void printTest(TestCase test) {
        try (PrintWriter out = new PrintWriter(System.out)) {
            out.println(test.permutations.size());
            for (int[] p : test.permutations) {
                out.print(p.length);
                for (int i : p) {
                    out.print(" " + i);
                }
                out.println();
            }
        }
    }

    static class TestCase {
        List<int[]> permutations;

        public TestCase(List<int[]> permutations) {
            this.permutations = permutations;
        }
    }
}
