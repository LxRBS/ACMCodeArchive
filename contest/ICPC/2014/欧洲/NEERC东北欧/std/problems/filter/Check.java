/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem F. Filter                                              */
/*                                                                */
/* Original idea         Roman Elizarov                           */
/* Problem statement     Roman Elizarov                           */
/* Test set              Roman Elizarov                           */
/******************************************************************/
/* Checker                                                        */
/*                                                                */
/* Author                Roman Elizarov                           */
/******************************************************************/

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import java.util.Locale;

import static ru.ifmo.testlib.Outcome.Type.*;

/**
 * Checker for NEERC'2014 Problem F: Filter
 *
 * @author Roman Elizarov
 */
public class Check implements Checker {
    final static int MAX = 1000;

    class Answer {
        int s;
        int[] d;

        Answer(InStream in, Outcome.Type type) {
            s = in.nextInt();
            if (s < 0)
                throw new Outcome(type, String.format("Invalid s=%d", s));
            if (s > MAX)
                throw new Outcome(WA, String.format("Invalid s=%d", s));
            d = new int[s];
            for (int t = 0; t < s; t++) {
                d[t] = in.nextInt();
            }
            if (!in.seekEoF())
                throw new Outcome(type, "Extra data in file");
        }
    }

    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        Answer ja = new Answer(ans, FAIL);
        Answer pa = new Answer(ouf, PE);

        if (ja.s != pa.s)
            return new Outcome(WA, String.format("Expected %d numbers, found %d", ja.s, pa.s));
        for (int t = 0; t < ja.s; t++) {
            if (ja.d[t] != pa.d[t])
                return new Outcome(WA, String.format("Number %d expected %d, found %d", t + 1, ja.s, pa.s));
        }

        return new Outcome(OK, String.format(Locale.US, "%d numbers", pa.s));
    }
}

