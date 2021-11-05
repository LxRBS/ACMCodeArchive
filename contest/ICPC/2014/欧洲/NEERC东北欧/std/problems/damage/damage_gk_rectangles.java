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
/* Solution                                                       */
/*                                                                */
/* Author                Georgiy Korneev                          */
/******************************************************************/

import java.io.File;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.function.DoubleUnaryOperator;

public class damage_gk_rectangles {
    static Scanner in;
    static PrintWriter out;
    static final int N = 1000_000;

    double s(double r, double hh) {
        double h = Math.min(r, Math.max(-r, hh));
        return h * Math.sqrt(r * r - h * h) + r * r * Math.acos(-h / r);
    }

    double integrate(double x1, double x2, DoubleUnaryOperator f) {
        double v = 0;
        for (int i = 0; i < N; i++) {
            v += f.applyAsDouble((x2 - x1) * (i + 0.5) / N + x1);
        }
        return v * (x2 - x1) / N;
    }

    void run() {
        double d = in.nextDouble();
        double l = in.nextDouble();
        double r = in.nextDouble();
        double t = in.nextDouble();
        double h = in.nextDouble();

        boolean vert = t == l;
        double sina = t / l;
        double cosa = Math.sqrt(1 - sina * sina);
        double a = -sina / cosa;
        double b = h / cosa - d / 2;
        final double q = r - Math.sqrt(r * r - d * d / 4);

        double v = integrate(-q, 0, x -> s(Math.sqrt(r * r - (x + q - r) * (x + q - r)), h(vert, a, b, x, h))) +
                integrate(0, l, x -> s(d / 2, h(vert, a, b, x, h))) +
                integrate(l, l + q, x -> s(Math.sqrt(r * r - (l - x + q - r) * (l - x + q - r)), h(vert, a, b, x, h)));
        out.println(v / 1e6);
    }

    private double h(boolean vert, double a, double b, double x, double h) {
        return vert ? (x > h ? Double.NEGATIVE_INFINITY : Double.POSITIVE_INFINITY) : a * x + b;
    }

    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("damage.in"));
        out = new PrintWriter("damage.out");

        new damage_gk_rectangles().run();

        in.close();
        out.close();
    }
}

