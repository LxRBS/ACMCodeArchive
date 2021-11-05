/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem J. Jokewithpermutation                                 */
/*                                                                */
/* Original idea         Mikhail Dvorkin                          */
/* Problem statement     Mikhail Dvorkin                          */
/* Test set              Maxim Babenko                            */
/******************************************************************/
/* Checker                                                        */
/*                                                                */
/* Author                Mikhail Dvorkin                          */
/******************************************************************/

import java.util.*;

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;
import static ru.ifmo.testlib.Outcome.Type.*;

public class Check implements Checker {
    final int MAX = 1000;

    public static Outcome outcome(Outcome.Type type, String format, Object... args) {
        return new Outcome(type, String.format(format, args));
    }
    
    @Override
    public Outcome test(InStream inf, InStream ouf, @SuppressWarnings("unused") InStream ans) {
        List<Integer> p = new ArrayList<>();
        StringBuilder pString = new StringBuilder();
        while (!ouf.seekEoF()) {
            int x = ouf.nextInt();
            p.add(x);
            pString.append(x);
            if (p.size() > MAX) {
                return outcome(WA, "Too many numbers in output");
            }
        }
        String s = inf.nextToken();
        if (!pString.toString().equals(s)) {
            return outcome(WA, "Input != this permutation concatenated");
        }
        Collections.sort(p);
        for (int i = 0; i < p.size(); i++) {
            if (p.get(i) != i + 1) {
                return outcome(WA, "This is not a permutation");
            }
        }
        return outcome(OK, "Correct permutation of size %d", p.size());
    }
}

