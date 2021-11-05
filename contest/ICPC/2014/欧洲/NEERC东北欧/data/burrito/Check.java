/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem B. Burrito King                                        */
/*                                                                */
/* Original idea         Vitaliy Aksenov                          */
/* Problem statement     Vitaliy Aksenov                          */
/* Test set              Vitaliy Aksenov                          */
/******************************************************************/
/* Checker                                                        */
/*                                                                */
/* Author                Georgiy Korneev                          */
/******************************************************************/

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import java.util.Locale;

import static ru.ifmo.testlib.Outcome.Type.*;

public class Check implements Checker {

    public void check(double expected, double actual, String w) {
        double error = error(expected, actual);
        if (error > EPS) {
            throw new Outcome(WA, String.format(Locale.US, "Expected %s = %.17f, found %.17f, error = %.17f in %s", w, expected, actual, error, w));
        }
    }

    private double error(double expected, double actual) {
        double relativeError = Math.abs(expected - actual) / Math.max(Math.abs(expected), 1.0);
        double absoluteError = Math.abs(expected - actual);
        return Math.min(relativeError, absoluteError);
    }

    class Result {
        final double a, b;

        public Result(double a, double b) {
            this.a = a;
            this.b = b;
        }
    }

    @Override
    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        int n = inf.nextInt();
        int minA = inf.nextInt();
        int maxB = inf.nextInt();
        int[] g = new int[n];
        int[] a = new int[n];
        int[] b = new int[n];
        for (int i = 0; i < n; i++) {
            g[i] = inf.nextInt();
            a[i] = inf.nextInt();
            b[i] = inf.nextInt();
        }

        Result ansR = read(minA, maxB, g, a, b, ans, true);
        Result outR = read(minA, maxB, g, a, b, ouf, false);

        if (Math.abs(ansR.a + 1) < EPS) {
            if (Math.abs(outR.a + 1) < EPS) {
                return new Outcome(OK, "Impossible");
            }
            return new Outcome(FAIL, String.format(Locale.US, "Jury missed solution A = %.17f, B = %.17f", outR.a, outR.b));
        }

        double error = error(ansR.a, outR.a);
        if (error < EPS) {
            return new Outcome(OK, String.format(Locale.US, "A = %.17f, B = %.17f", outR.a, outR.b));
        }
        if (outR.a < ansR.a) {
            return new Outcome(WA, String.format(Locale.US, "Expected A = %.17f, found A = %.17f, B = %.17f", ansR.a, outR.a, outR.b));
        } else {
            return new Outcome(FAIL, String.format(Locale.US, "Expected A = %.17f, found A = %.17f, B = %.17f", ansR.a, outR.a, outR.b));
        }
    }

    static final double EPS = 2e-8;

    private Result read(int minA, int maxB, int[] g, int[] a, int[] b, InStream ouf, boolean failOnError) {
        Result r = new Result(ouf.nextDouble(), ouf.nextDouble());
        if (Math.abs(r.a + 1) < 0.1) {
            if (Math.abs(r.b + 1) < 0.1) {
                if (!ouf.seekEoF())
                    throw new Outcome(failOnError ? FAIL : PE, String.format("Extra data in output file"));
                return r;
            }
            throw new Outcome(failOnError ? FAIL: WA, String.format(Locale.US, "A = -1, B = %.3f", r.b));
        }

        double[] s = new double[g.length];
        for (int i = 0; i < s.length; i++) {
            s[i] = ouf.nextDouble();
        }
        if (!ouf.seekEoF())
            throw new Outcome(failOnError ? FAIL : PE, String.format("Extra data in output file"));

        double totalA = 0;
        double totalB = 0;
        for (int i = 0; i < s.length; i++) {
            if (s[i] < -EPS || g[i] + EPS < s[i]) {
                throw new Outcome(failOnError ? FAIL : WA, String.format(Locale.US, "Ingredient %d out of range [0, %d]: %.17f", i + 1, g[i], s[i]));
            }
            totalA += a[i] * s[i];
            totalB += b[i] * s[i];
        }

        check(r.a, totalA, "A");
        check(r.b, totalB, "B");

        if (r.a < minA - EPS) {
            throw new Outcome(failOnError ? FAIL : WA, String.format(Locale.US, "A should be at least %d, actual: %.17f", minA, r.a));
        }
        if (r.b > maxB + EPS) {
            throw new Outcome(failOnError ? FAIL : WA, String.format(Locale.US, "B should be at most %d, actual: %.17f", minA, r.b));
        }

        return r;
    }
}

