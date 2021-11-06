import ru.ifmo.validate.ValidatingScanner;
import ru.ifmo.validate.Validator;
import ru.ifmo.validate.ValidatorFramework;

import java.util.HashSet;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class Validate implements Validator {

    public static final int MAX_N = 94;
    public static final int MAX_SIZE = 30;
    public static final int MAX_S = 1000_000;
    public static final String CHARS = IntStream.rangeClosed(33, 126)
            .mapToObj(c -> Character.toString((char) c))
            .collect(Collectors.joining());

    @Override
    public void validate(ValidatingScanner in) {
        int n = in.nextInt("n", 1, MAX_N);
        int w = in.nextInt("w", 1, MAX_SIZE);
        int h = in.nextInt("h", 1, MAX_SIZE);
        int s = in.nextInt("s", 1, MAX_S);
        in.eoln();

        Set<Character> chars = new HashSet<>();
        for (int i = 0; i < n; i++) {
            char ch = in.next(CHARS, 1).charAt(0);
            if (!chars.add(ch)) {
                throw new AssertionError("Duplicate character");
            }
            in.eoln();
            int total = 0;
            for (int r = 0; r < h; r++) {
                total += in.next(".#", w).chars().filter(c -> c == '#').count();
                in.eoln();
            }
            if (total == 0) {
                throw new AssertionError("All pixels are off");
            }
        }

        in.close();
    }

    public static void main(String[] args) throws Exception {
        ClassLoader.getSystemClassLoader().setDefaultAssertionStatus(true);
        try {
            ValidatorFramework.main(args);
        } catch (Exception e) {
            System.err.println(e.getMessage());
            throw e;
        }
    }
}
