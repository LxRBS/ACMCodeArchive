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
/* Tests                                                          */
/*                                                                */
/* Author                Vitaliy Aksenov                          */
/******************************************************************/

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Random;

public class Tests {
    static int MAXN = 1000;
    static int MAXQ = 1000;
    static int MAXL = 1000000000;
    static int MAXT = 1000000000;

    Random rnd = new Random(239);

    String folder;

    public static void main(String[] args) throws FileNotFoundException {
        new Tests().gen();
    }

    public int random(int l, int r) {
        if (r < l)
            return l;

        return l + rnd.nextInt(r - l + 1);
    }

    static int tests = 1;

    class Ingredient implements Comparable<Ingredient> {
        int g, x, y, ind;

        public Ingredient(int g, int x, int y, int ind) {
            this.x = x;
            this.y = y;
            this.g = g;
            this.ind = ind;
        }

        public int compareTo(Ingredient i) {
            return this.y * i.x - this.x * i.y;
        }

        public String toString() {
            return g + " " + x + " " + y;
        }
    }

    public void writeTest(int L, int[] l, int[] r, int[] x, int[] y, int[] t) {
        try {
            PrintWriter out = new PrintWriter(String.format(folder + "%02d", tests++));

            System.err.println("Writing test " + (tests - 1));

            out.println(l.length + " " + x.length);
            for (int i = 0; i < l.length; i++) {
                out.println(l[i] + " " + r[i]);
            }
            for (int i = 0; i < x.length; i++) {
                out.println(x[i] + " " + y[i] + " " + t[i]);
            }

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void testRandom(int n, int m, int L, int T) {
        int[] l = new int[n];
        int[] r = new int[n];
        for (int i = 0; i < n; i++) {
            l[i] = random(0, L - 1);
            r[i] = random(l[i] + 1, L);
        }

        int[] x = new int[m];
        int[] y = new int[m];
        int[] t = new int[m];
        for (int i = 0; i < m; i++) {
            x[i] = random(0, L - 1);
            y[i] = random(x[i], L);
            t[i] = random(0, T);
        }

        writeTest(L, l, r, x, y, t);
    }


    public void testMAX(int n, int m, int L, int T) {
        int[] l = new int[n];
        int[] r = new int[n];
        for (int i = 0; i < n; i++) {
            l[i] = random(0, L - 1);
            r[i] = random(l[i] + 1, L);
        }

        int[] x = new int[m];
        int[] y = new int[m];
        int[] t = new int[m];
        for (int i = 0; i < m; i++) {
            x[i] = random(0, L / 2);
            y[i] = L;
            t[i] = random(0, T);
        }

        writeTest(L, l, r, x, y, t);
    }


    public void testInteresting(int n, int m, int L, int T) {
        int k = 0;
        int LL = L;
        while (LL > 1) {
            LL >>= 1;
            k++;
        }

        int[] l = new int[Math.min(n, L)];
        int[] r = new int[Math.min(n, L)];
        for (int i = 0; i < Math.min(n, L); i++) {
            l[i] = i;
            r[i] = Math.min(i + (1 << (random(0, k))), L);
        }

        int[] x = new int[m];
        int[] y = new int[m];
        int[] t = new int[m];
        for (int i = 0; i < m; i++) {
            x[i] = i;
            y[i] = L;
            t[i] = random(1, T / (1 << k)) * (1 << k);
        }

        writeTest(L, l, r, x, y, t);
    }


    public void gen() {
        tests = 1;
        folder = "tests/";
        if (!new File(folder).exists())
            new File(folder).mkdir();

        writeTest(5, new int[]{0, 0, 2, 3, 4}, new int[]{1, 2, 3, 5, 5}, new int[]{0, 0, 0, 2, 2}, new int[]{5, 1, 2, 5, 5}, new int[]{0, 2, 1, 2, 3});

        testRandom(3, 3, 10, 10);
        testInteresting(3, 3, 10, 10);

        testRandom(100, 100, 10000, 10000);
        testInteresting(100, 100, 10000, 10000);
        testMAX(100, 100, 10000, 10000);
        testRandom(100, 100, 100 - 1, 10000);
        testInteresting(100, 100, 100 - 1, 10000);

        for (int i = 0; i < 3; i++) {
            testRandom(MAXN, MAXQ, MAXL, MAXT);
            testInteresting(MAXN, MAXQ, MAXL, MAXT);
        }

        testMAX(MAXN, MAXQ, MAXL, MAXT);
        for (int i = 0; i < 3; i++) {
            testRandom(MAXN, MAXQ, MAXN - 1, MAXT);
           testInteresting(MAXN, MAXQ, MAXN - 1, MAXT);
        }
    }
}

