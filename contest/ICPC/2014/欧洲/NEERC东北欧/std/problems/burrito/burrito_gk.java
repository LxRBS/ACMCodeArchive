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
/* Solution                                                       */
/*                                                                */
/* Author                Georgiy Korneev                          */
/******************************************************************/

import java.io.File;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Scanner;

public class burrito_gk {
    static Scanner in;
    static PrintWriter out;

    class I {
        int i;
        long g, a, b;

        public I(int i, int g, int a, int b) {
            this.i = i;
            this.g = g;
            this.a = a;
            this.b = b;
        }
    }

    void run() {
        int n = in.nextInt();
        int a = in.nextInt();
        int b = in.nextInt();

        I[] is = new I[n];
        for (int i = 0; i < n; i++) {
            is[i] = new I(i, in.nextInt(), in.nextInt(), in.nextInt());
        }
        Arrays.sort(is, (i1, i2) -> Double.compare(i2.a * (i1.b + 1e-100), i1.a * (i2.b + 1e-100)));
        double totalA = 0;
        double totalB = 0;
        double[] amount = new double[n];
        for (int i = 0; i < n; i++) {
            double q = amount[is[i].i] = is[i].b > 0 ? Math.min(is[i].g, (b - totalB) / is[i].b) : is[i].g ;
            totalA += q * is[i].a;
            totalB += q * is[i].b;
        }
        if (totalA < a - 1e-8) {
            out.println("-1 -1");
        } else {
            out.println(totalA + " " + totalB);
            for (double v : amount) {
                out.println(v);
            }
        }
    }

    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("burrito.in"));
        out = new PrintWriter("burrito.out");

        new burrito_gk().run();

        in.close();
        out.close();
    }
}

