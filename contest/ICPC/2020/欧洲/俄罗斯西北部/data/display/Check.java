import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.CheckerFramework;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import java.util.stream.IntStream;

import static ru.ifmo.testlib.Outcome.Type.*;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class Check implements Checker {
    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        int n = inf.nextInt();
        int w = inf.nextInt();
        int h = inf.nextInt();
        int s = inf.nextInt();
        inf.nextLine();


        final StringBuilder characters = new StringBuilder();
        final int[][] images = new int[n][h];
        for (int i = 0; i < n; i++) {
            characters.append(inf.nextLine().charAt(0));
            for (int r = 0; r < h; r++) {
                images[i][r] = calc(inf.nextLine());
            }
        }

        final String chars = characters.toString();
        long jury = check(ans, FAIL, chars, images, s);
        long user = check(ouf, WA, chars, images, s);
        if (user != jury) {
            return new Outcome(user > jury ? WA : FAIL, String.format("Expected %d chars, found %d", jury, user));
        } else {
            return new Outcome(OK, String.format("%d", jury));
        }
    }

    private long check(final InStream f, final Outcome.Type o, final String chars, final int[][] images, final int s) {
        int length = 0;
        final int[] switches = new int[images[0].length];
        while (!f.isEoLn()) {
            int c = f.currChar();
            f.nextChar();
            int index = chars.indexOf((char) c);
            if (index < 0) {
                throw new Outcome(o, String.format("Unknown character '%c' (%d)", (char) c, c));
            }

            if (++length > s) {
                throw new Outcome(o, "Text too long");
            }

            for (int r = 0; r < switches.length; r++) {
                switches[r] += images[index][r];
            }
        }

        if (length == 0) {
            throw new Outcome(o, "Empty text");
        }

        final int maxSwitches = IntStream.of(switches).max().orElse(-1);
        if (s > maxSwitches) {
            throw new Outcome(o, String.format("Expected %d switches, found %s", s, maxSwitches));
        }

        return length;
    }

    private int calc(final String row) {
        int q = 0;
        for (int c = 0; c < row.length(); c++) {
            if ((row.charAt(c) == '.') != (q % 2 == 0)) {
                q++;
            }
        }
        if (q % 2 == 1) {
            q++;
        }
        return q;
    }

    public static void main(String[] args) {
        CheckerFramework.main(args);
    }
}
