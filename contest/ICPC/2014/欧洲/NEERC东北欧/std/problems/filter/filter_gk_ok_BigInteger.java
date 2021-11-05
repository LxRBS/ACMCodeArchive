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
/* Solution                                                       */
/*                                                                */
/* Author                Georgiy Korneev                          */
/******************************************************************/

import java.io.File;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.Scanner;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public class filter_gk_ok_BigInteger {
    static Scanner in;
    static PrintWriter out;

    void run() {
        int m = in.nextInt();
        int f = in.nextInt();
        int[] a = IntStream.generate(in::nextInt).limit(f).toArray();

        int n = in.nextInt();
        BigInteger[] files = Stream.generate(() -> new BigInteger(new StringBuilder(in.next()).reverse().toString(), 16))
                .limit(n).toArray(BigInteger[]::new);
        boolean[] found = new boolean[n];

        int q = in.nextInt();
        for (int i = 0; i < q; i++) {
            long u = in.nextInt();
            for (int j = 0; j < n; j++) {
                boolean hit = true;
                for (int k = 0; k < f; k++) {
                    if (!files[j].testBit((int) ((a[k] * u) % m))) {
                        hit = false;
                    }
                }
                if (hit) {
                    found[j] = true;
                }
            }
        }

        int c = 0;
        for (boolean b : found) {
            if (b) {
                c++;
            }
        }

        out.print(c);
        for (int i = 0; i < found.length; i++) {
            if (found[i]) {
                out.print(" " + i);
            }
        }
        out.println();
    }

    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("filter.in"));
        out = new PrintWriter("filter.out");

        new filter_gk_ok_BigInteger().run();

        in.close();
        out.close();
    }
}

