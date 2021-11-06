import java.util.Random;

public class Gen {
    private static int[] genTest(final int n, final Random rnd, final String type) {
        final int[] res = new int[n];
        switch (type) {
            case "RAND":
                for (int i = 0; i < n; i++) {
                    int pos = rnd.nextInt(i + 1);
                    res[i] = res[pos];
                    res[pos] = i;
                }
                break;
            case "REV":
                for (int i = 0; i < n; i++) {
                    res[i] = n - i - 1;
                }
                break;
            case "TWO_PARTS":
                for (int i = 0; i < n; i++) {
                    res[i] = n / 2 - i;
                    if (res[i] < 0) {
                        res[i] += n;
                    }
                }
                break;
            default:
                throw new AssertionError("Unknown type: " + type);
        }
        return res;
    }

    private static void printTest(final int[] test) {
        System.out.println(test.length);
        for (int i = 0; i < test.length; i++) {
            System.out.print(1 + test[i]);
            if (i + 1 == test.length) {
                System.out.println();
            } else {
                System.out.print(" ");
            }
        }
    }

    public static void main(String[] args) {
        final Random rnd = new Random(Long.parseLong(args[args.length - 1]));
        final int n = Integer.parseInt(args[0]);
        final String type = args[1];
        final int[] test = genTest(n, rnd, type);
        printTest(test);
    }
}
