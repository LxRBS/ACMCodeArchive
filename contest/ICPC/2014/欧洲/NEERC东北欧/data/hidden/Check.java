/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem H. Hidden Maze                                         */
/*                                                                */
/* Original idea         Elena Andreeva                           */
/* Problem statement     Andrei Lopatin                           */
/* Test set              Andrei Lopatin                           */
/******************************************************************/
/* Checker                                                        */
/*                                                                */
/* Author                Andrei Lopatin                           */
/******************************************************************/

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import java.util.Locale;

import static ru.ifmo.testlib.Outcome.Type.*;

/**
 * Checker for NEERC'2014 Problem H: Hidden Maze
 *
 * @author Andrei Lopatin
 */
public class Check implements Checker {
    private static final double EPS = 1.1e-9;

    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        double ja = ans.nextDouble();
        double pa = ouf.nextDouble();

        if (!ouf.seekEoF())
            return new Outcome(PE, String.format("Extra data in output file"));
        double delta = Math.abs(ja - pa);
        double delta_rel = Math.abs((ja - pa) / ja);
        if (delta > EPS && delta_rel > EPS)
            return new Outcome(WA, String.format(Locale.US, "Expected %.3f, found %.3f, absolute error %.10f, relative error %.10f", ja, pa, delta, delta_rel));
        return new Outcome(OK, String.format(Locale.US, "%.3f absolute error=%.10f relative error=%.10f", pa, delta, delta_rel));
    }
}

