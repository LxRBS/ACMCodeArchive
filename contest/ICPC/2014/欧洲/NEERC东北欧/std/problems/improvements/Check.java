/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem I. Improvements                                        */
/*                                                                */
/* Original idea         Vitaliy Aksenov                          */
/* Problem statement     Vitaliy Aksenov                          */
/* Test set              Vitaliy Aksenov                          */
/******************************************************************/
/* Checker                                                        */
/*                                                                */
/* Author                Standard                                 */
/******************************************************************/

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

public class Check implements Checker {
    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        int pa = ouf.nextInt();
        int ja = ans.nextInt();
        if (!ouf.seekEoF())
            throw new Outcome(Outcome.Type.PE, "Extra data in output file");
        if (pa != ja)
            throw new Outcome(Outcome.Type.WA, String.format("%d instead of %d", pa, ja));
        return new Outcome(Outcome.Type.OK, String.format("%d", pa));
    }
}

