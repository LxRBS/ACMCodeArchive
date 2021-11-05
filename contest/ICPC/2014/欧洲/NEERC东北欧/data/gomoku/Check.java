/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem G. Gomoku                                              */
/*                                                                */
/* Original idea         Petr Mitrichev                           */
/* Problem statement     Petr Mitrichev                           */
/* Test set              Pavel Mavrin                             */
/******************************************************************/
/* Checker                                                        */
/*                                                                */
/* Author                Pavel Mavrin                             */
/******************************************************************/

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import static ru.ifmo.testlib.Outcome.Type.*;

public class Check implements Checker {

    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        int outcome = ouf.nextInt();
        int moves = ouf.nextInt();
        if (outcome == 1) {
            return new Outcome(WA, "Contestant lose after " + moves + " moves.");
        } else if (outcome == 2) {
            return new Outcome(OK, "Contestant win after " + moves + " moves.");
        } else if (outcome == 3) {
            return new Outcome(WA, "Draw after " + moves + " moves.");
        } else if (outcome == 4) {
            return new Outcome(WA, "Contestant make bad move after " + moves + " moves.");
        } else {
            return new Outcome(FAIL, "Invalid outcome: " + outcome);
        }
    }

}

