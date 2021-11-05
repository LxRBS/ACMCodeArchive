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

public class damage_gk_simpson {
    static Scanner in;
    static PrintWriter out;

    double s(double r, double hh) {
        if (Math.abs(r) < 1e-100 || Double.isNaN(r)) {
            return 0;
        }
        double h = Math.min(r, Math.max(-r, hh));
        double v = h * Math.sqrt(r * r - h * h) + r * r * Math.acos(-h / r);
        return v;
    }

    double integrate(double x1, double x2, double v1, double v2, DoubleUnaryOperator f) {
        double xm = (x1 + x2) / 2;
        double vm = f.applyAsDouble(xm);
        if (x2 - x1 > 0.01) {
            return integrate(x1, xm, v1, vm, f) + integrate(xm, x2, vm, v2, f);
        }
        return (v1 + 4 * vm + v2) / 6 * (x2 - x1);
    }

    double integrate(double x1, double x2, DoubleUnaryOperator f) {
        return integrate(x1, x2, f.applyAsDouble(x1), f.applyAsDouble(x2), f);
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

        new damage_gk_simpson().run();

        in.close();
        out.close();
    }
}

