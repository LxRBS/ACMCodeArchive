import java.io.PrintWriter;
import java.util.*;

public class GenShallow {

    public final static int SEED = "coin-flipping".hashCode();
    public final static Random rng = new Random(SEED);
    public final static int ARGS_COUNT = 2;

    public final static int MAX_K = 30;
    public final static int MAX_M = 100000;
    
    public static void main(String[] args) {
        if (args.length < ARGS_COUNT) {
            throw new IllegalArgumentException(
                    String.format("Expected %d arguments, but got %d instead", ARGS_COUNT, args.length));
        }
        rng.setSeed(Arrays.hashCode(args));
        int k = Integer.parseInt(args[0]);
        int m = Integer.parseInt(args[1]);
        if (m >= 1 << k) {
            throw new AssertionError();
        }
        printTest(generate(k, m));
    }

    static TestCase generate(int k, int m) {
        Set<Integer> used = new HashSet<>();
        List<Integer> stages = new ArrayList<>(), matches = new ArrayList<>();
        for (int i = 0; i < m; i++) {
            int curS = i + 1;
            do {
                curS = i + 1;
//                curS = 1 + rng.nextInt((1 << k) - 1);
            } while (used.contains(curS));
            used.add(curS);
            int stage = 31 - Integer.numberOfLeadingZeros(curS);
            stages.add(k - stage);
            matches.add(curS - (1 << stage) + 1);
        }

        return new TestCase(k, stages, matches).shuffled();
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
            out.println(test.k + " " + test.s.size());
            for (int i = 0; i < test.s.size(); i++) {
                out.println(test.s.get(i) + " " + test.m.get(i));
            }
        }
    }

    static class TestCase {
        int k;
        List<Integer> s, m;

        public TestCase(int k, List<Integer> s, List<Integer> m) {
            this.k = k;
            this.s = s;
            this.m = m;
        }

        public TestCase shuffled() {
            int[] perm = randomPermutation(s.size());
            List<Integer> newS = new ArrayList<>(), newM = new ArrayList<>();
            for (int i = 0; i < perm.length; i++) {
                newS.add(s.get(perm[i]));
                newM.add(m.get(perm[i]));
            }
            return new TestCase(k, newS, newM);
        }
    }
}
