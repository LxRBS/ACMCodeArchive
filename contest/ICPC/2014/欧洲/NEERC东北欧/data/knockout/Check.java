/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem K. Knockout Racing                                     */
/*                                                                */
/* Original idea         Vitaliy Aksenov                          */
/* Problem statement     Vitaliy Aksenov                          */
/* Test set              Vitaliy Aksenov                          */
/******************************************************************/
/* Checker                                                        */
/*                                                                */
/* Author                Vitaliy Aksenov                          */
/******************************************************************/

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import static ru.ifmo.testlib.Outcome.Type.*;

public class Check implements Checker {

    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        inf.nextInt();
        int m = inf.nextInt();

        int[] ja = read(ans, m, true);
        int[] pa = read(ouf, m, false);

        for (int i = 0; i < m; i++) {
            if (ja[i] != pa[i]) {
                return new Outcome(WA, String.format("Expected %s, found %s in position %d", ja[i], pa[i], (i + 1)));
            }
        }
        return new Outcome(OK, String.format("%d answers", m));
    }

    private int[] read(InStream ouf, int m, boolean failOnError) {
        int[] a = new int[m];
        for (int i = 0; i < m; i++)
            a[i] = ouf.nextInt();
        if (!ouf.seekEoF())
            throw new Outcome(failOnError ? FAIL : PE, String.format("Extra data in output file"));
        return a;
    }
}

