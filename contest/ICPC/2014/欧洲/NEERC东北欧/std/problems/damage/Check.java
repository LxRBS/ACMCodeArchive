/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem D. Damage Assessment                                   */
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
 * Checker for NEERC'2014 Problem D: Damage Assessment
 *
 * @author Roman Elizarov
 */
public class Check implements Checker {
    private static final double EPS = 0.15;

    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        double ja = ans.nextDouble();
        double pa = ouf.nextDouble();

        if (!ouf.seekEoF())
            return new Outcome(PE, String.format("Extra data in output file"));
        double delta = Math.abs(ja - pa);
        if (delta > EPS)
            return new Outcome(WA, String.format(Locale.US, "Expected %.2f, found %.2f, delta %.2f", ja, pa, delta));
        return new Outcome(OK, String.format(Locale.US, "%.2f delta %.2f", pa, delta));
    }
}

