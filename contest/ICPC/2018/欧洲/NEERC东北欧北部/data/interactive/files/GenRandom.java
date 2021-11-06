import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

public class GenRandom {
    PrintWriter out;

    static int n = 10;
    static int maxLen = 10;
    static int maxValue = 10;
    static boolean randomConstraints = false;
    static Random rnd = new Random(123);

    void solve() {
        if (randomConstraints) {
            n = 1 + rnd.nextInt(n);
            maxLen = 1 + rnd.nextInt(maxLen);
            maxValue = 1 + rnd.nextInt(maxValue);
        }
        out.println(787788);
        out.println(n);
        int[] diffs = new int[]{1, 2, 5, 10, 20, 50, 100};
        int different = diffs[rnd.nextInt(diffs.length)];
        double alotofProb = (n - different + 0.) / n;
        for (int i = 0; i < n; i++) {
            List<Integer> arr = new ArrayList<>();
            int len = 1 + rnd.nextInt(maxLen);
            for (int j = 0; j < len; j++) {
                int newValue = 1 + rnd.nextInt(maxValue);
                if (!arr.contains(newValue)) {
                    arr.add(newValue);
                }
            }
            if (alotof != null && rnd.nextDouble() < alotofProb) {
                arr = Arrays.stream(alotof).boxed().collect(Collectors.toList());
            }
            out.print(arr.size());
            for (int x : arr) {
                out.print(" " + (rnd.nextBoolean() ? "" : "-") + x);
            }
            out.println();
        }
    }

    void runIO() {
        out = new PrintWriter(System.out);

        solve();

        out.close();
    }

    static int[] alotof;

    static void registerSpecOption(String s) {
        if (s.startsWith("alotof")) {
            alotof = Arrays.stream(s.substring(s.indexOf("[") + 1, s.length() - 1).split(",")).mapToInt(Integer::parseInt).toArray();
        } else {
            throw new AssertionError("Can't parse option : " + s);
        }
    }

    public static void main(String[] args) {
        if (args.length >= 5) {
            n = Integer.parseInt(args[0]);
            maxLen = Integer.parseInt(args[1]);
            maxValue = Integer.parseInt(args[2]);
            randomConstraints = args[3].equals("random");
            if (args.length >= 6) {
                for (int id = 4; id + 1 < args.length; id++) {
                    registerSpecOption(args[id]);
                }
            }
            rnd = new Random(Long.parseLong(args[args.length - 1]));
        }
        new GenRandom().runIO();
    }
}