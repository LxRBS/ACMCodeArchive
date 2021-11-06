import java.io.PrintWriter;
import java.util.*;
import java.util.stream.IntStream;

public class GenSpecial {

    public final static int SEED = "hidden-permutation".hashCode();
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
        int start = 0;
        if (args.length >= 2) {
            start = Integer.parseInt(args[1]);
        }
        printTest(generateSpecials(n, start));
    }

    static TestCase generateSpecials(int n, int start) {
        int remLength = MAX_N;
        List<int[]> permutations = new ArrayList<>();
        while (remLength >= n) {
            int[] perm;
            switch (start % 4) {
                case 0: perm = identity(n); break;
                case 1: perm = reverse(n); break;
                case 2: perm = cycle(n); break;
                default: perm = involution(n);
            }
            start++;
            permutations.add(perm);
            remLength -= n;
        }
        Collections.shuffle(permutations, rng);
        return new TestCase(permutations);
    }

    static int[] identity(int n) {
        return IntStream.range(0, n).toArray();
    }
    static int[] reverse(int n) {
        return IntStream.range(0, n).map(i -> n - i - 1).toArray();
    }

    static int[] cycle(int n) {
        int[] r = randomPermutation(n);
        int[] result = new int[n];
        for (int i = 0; i < n; i++ ){
            result[r[i]] = r[(i + 1) % n];
        }
        return result;
    }

    static int[] involution(int n) {
        int[] r = randomPermutation(n);
        int[] result = new int[n];
        for (int i = 0; i < n; i += 2) {
            if (i + 1 == n) {
                result[r[i]] = r[i];
            } else {
                result[r[i]] = r[i + 1];
                result[r[i + 1]] = r[i];
            }
        }
        return result;
    }

    private static int[] randomPermutation(int n) {
        int[] result = new int[n];
        for (int i = 0; i < n; i++) {
            int pos = rng.nextInt(i + 1);
            result[i] = result[pos];
            result[pos] = i;
        }
        return result;
    }

    static void printTest(TestCase test) {
        try (PrintWriter out = new PrintWriter(System.out)) {
            out.println(test.permutations.size());
            for (int[] p : test.permutations) {
                out.print(p.length);
                for (int i : p) {
                    out.print(" " + (i + 1));
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
