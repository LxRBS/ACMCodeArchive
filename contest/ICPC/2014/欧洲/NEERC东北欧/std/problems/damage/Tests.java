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
/* Tests                                                          */
/*                                                                */
/* Author                Roman Elizarov                           */
/******************************************************************/

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Locale;
import java.util.Random;

/**
 * NEERC 2014 Test generator for problem Damage Assessment
 *
 * @author Roman Elizarov
 */
public class Tests {
    static final String TEST_NAME_FORMAT = "%03d";
    static final File LST_FILE = new File("tests/tests.lst");
    static final Random RND = new Random(1);
    static int nTests = 0;

    static PrintWriter openTestFile(String desc) throws IOException {
        new File("tests").mkdir();
        PrintWriter out = new PrintWriter(String.format("tests/" + TEST_NAME_FORMAT, ++nTests));
        try (PrintWriter out1 = new PrintWriter(new FileWriter(LST_FILE, true))) {
            out1.printf(TEST_NAME_FORMAT + " %s%n", nTests, desc);
        }
        System.out.printf("Writing test " + TEST_NAME_FORMAT + ": %s%n", nTests, desc);
        return out;
    }

    static void write(String desc, int d, int l, int r, int t, int h) throws IOException {
        try (PrintWriter out = openTestFile(desc)) {
            out.printf("%d %d %d %d %d%n", d, l, r, t, h);
        }
    }

    private static int rnd(int from, int to) {
        return from + RND.nextInt(to - from + 1);
    }

    private static int rndD() {
        return rnd(100, 10000);
    }

    private static int rndL() {
        return rnd(100, 10000);
    }

    private static int rndR(int d, int l) {
        return rnd((d + 1) / 2, 10000);
    }

    private static int rndH(int d, int l, int r, int t) {
        return rnd(0, t + (int)(d * Math.sqrt(l * l - t * t) / l));
    }

    private static void writeRndHorizontal() throws IOException {
        int d = rndD();
        int l = rndL();
        int r = rndR(d, l);
        write("Random horizontal", d, l, r, 0, rndH(d, l, r, 0));
    }

    private static void writeRndVertical() throws IOException {
        int d = rndD();
        int l = rndL();
        int r = rndR(d, l);
        write("Random vertical", d, l, r, l, rndH(d, l, r, l));
    }

    private static void writeRnd() throws IOException {
        int d = rndD();
        int l = rndL();
        int r = rndR(d, l);
        int t = rnd(0, l);
        write("Random", d, l, r, t, rndH(d, l, r, t));
    }

    public static void main(String[] args) throws IOException {
        LST_FILE.delete();

        write("Sample 1 full gas, vol=" + fmt(fullVol(3000, 6000, 1600)), 3000, 6000, 1600, 0, 3000);
        write("Sample 2 as pictured", 3000, 6000, 1600, 3441, 4228);
        write("Sample no gas", 3000, 6000, 1600, 0, 0);
        write("Sample horizontal 1/2 gas, vol=" +  fmt(fullVol(3000, 6000, 1600) / 2), 3000, 6000, 1600, 0, 1500);
        write("Sample horizontal 1/3 lvl", 3000, 6000, 1600, 0, 1000);
        write("Sample horizontal 2/3 lvl", 3000, 6000, 1600, 0, 2000);
        write("Sample vertical min gas, vol=" + fmt(capVol(3000, 1600)), 3000, 6000, 1600, 6000, 0);
        write("Sample vertical max gas, vol=" + fmt(capVol(3000, 1600) + cylVol(3000, 6000)), 3000, 6000, 1600, 6000, 6000);
        write("Sample vertical 1/2 gas, vol=" + fmt(fullVol(3000, 6000, 1600) / 2), 3000, 6000, 1600, 6000, 3000);

        write("Min horizontal max gas, vol=" + fmt(fullVol(100, 100)), 100, 100, 50, 0, 100);
        write("Min horizontal 1/2 gas, vol=" + fmt(fullVol(100, 100) / 2), 100, 100, 50, 0, 50);
        write("Min horizontal no gas", 100, 100, 50, 0, 0);
        write("Min horizontal 10% lvl", 100, 100, 50, 0, 10);
        write("Min horizontal 30% lvl", 100, 100, 50, 0, 30);
        write("Min horizontal 70% lvl", 100, 100, 50, 0, 70);
        write("Min horizontal 90% lvl", 100, 100, 50, 0, 90);

        write("Min vertical min gas, vol=" + fmt(halfSpVol(100)), 100, 100, 50, 100, 0);
        write("Min vertical max gas, vol=" + fmt(fullVol(100, 100) - halfSpVol(100)), 100, 100, 50, 100, 100);
        write("Min vertical 1/2 gas, vol=" + fmt(fullVol(100, 100) / 2), 100, 100, 50, 100, 50);
        write("Min vertical 25% lvl, vol=" + fmt(cylVol(100, 100) * 0.25 + halfSpVol(100)), 100, 100, 50, 100, 25);
        write("Min vertical 73% lvl, vol=" + fmt(cylVol(100, 100) * 0.73 + halfSpVol(100)), 100, 100, 50, 100, 73);

        write("Min ~45% min gas", 100, 100, 50, 71, 0);
        write("Min ~45% 1/2 gas", 100, 100, 50, 71, 71);
        write("Min ~45% max gas", 100, 100, 50, 71, 141);
        write("Min ~45% 13% gas", 100, 100, 50, 71, 18);
        write("Min ~45% 98% gas", 100, 100, 50, 71, 138);

        write("Min~cyl horizontal max gas, vol=" + fmt(fullVol(100, 100, 10000)), 100, 100, 10000, 0, 100);
        write("Min~cyl horizontal 1/2 gas, vol=" + fmt(fullVol(100, 100, 10000) / 2), 100, 100, 10000, 0, 50);
        write("Min~cyl horizontal no gas", 100, 100, 10000, 0, 0);
        write("Min~cyl horizontal 87% lvl", 100, 100, 10000, 0, 87);
        write("Min~cyl horizontal 13% lvl", 100, 100, 10000, 0, 13);

        write("Min~cyl vertical min gas", 100, 100, 10000, 100, 0);
        write("Min~cyl vertical max gas", 100, 100, 10000, 100, 100);
        write("Min~cyl vertical 1/2 gas", 100, 100, 10000, 100, 50);
        write("Min~cyl vertical 6% gas", 100, 100, 10000, 100, 6);
        write("Min~cyl vertical 94% gas", 100, 100, 10000, 100, 94);

        write("Min~cyl 30% min gas", 100, 100, 10000, 50, 0);
        write("Min~cyl 30% max gas", 100, 100, 10000, 50, 136);
        write("Min~cyl 30% at right gas", 100, 100, 10000, 50, 50);
        write("Min~cyl 30% at left gas", 100, 100, 10000, 50, 86);

        write("Max horizontal max gas, vol=" + fmt(fullVol(10000, 10000)), 10000, 10000, 5000, 0, 10000);
        write("Max horizontal 1/2 gas, vol=" + fmt(fullVol(10000, 10000) / 2), 10000, 10000, 5000, 0, 5000);
        write("Max horizontal no gas", 10000, 10000, 5000, 0, 0);
        write("Max horizontal eps gas", 10000, 10000, 5000, 0, 1);
        write("Max horizontal 1/2-eps gas", 10000, 10000, 5000, 0, 4999);
        write("Max horizontal 1/2+eps gas", 10000, 10000, 5000, 0, 5001);
        write("Max horizontal 1-eps gas", 10000, 10000, 5000, 0, 9999);

        write("Max vertical min gas, vol=" + fmt(halfSpVol(10000)), 10000, 10000, 5000, 10000, 0);
        write("Max vertical max gas, vol=" + fmt(fullVol(10000, 10000) - halfSpVol(10000)), 10000, 10000, 5000, 10000, 10000);
        write("Max vertical 1/2 gas, vol=" + fmt(fullVol(10000, 10000) / 2), 10000, 10000, 5000, 10000, 5000);
        write("Max vertical eps gas, vol=" + fmt(halfSpVol(10000) + cylVol(10000, 1)), 10000, 10000, 5000, 10000, 1);
        write("Max vertical 1-eps gas, vol=" + fmt(halfSpVol(10000) + cylVol(10000, 9999)), 10000, 10000, 5000, 10000, 9999);

        write("Max vertical-eps min gas", 10000, 10000, 5000, 9999, 0);
        write("Max vertical-eps ~max gas", 10000, 10000, 5000, 9999, 10000);
        write("Max vertical-eps ~1/2 gas", 10000, 10000, 5000, 9999, 5000);

        write("Max 30% min gas", 10000, 10000, 5000, 5000, 0);
        write("Max 30% max gas", 10000, 10000, 5000, 5000, 13660);
        write("Max 30% at right gas", 10000, 10000, 5000, 5000, 5000);
        write("Max 30% at left gas", 10000, 10000, 5000, 5000, 8660);
        write("Max 30% min+eps gas", 10000, 10000, 5000, 5000, 1);
        write("Max 30% max-eps gas", 10000, 10000, 5000, 5000, 13659);

        for (int i = 0; i < 10; i++)
            writeRndHorizontal();
        for (int i = 0; i < 10; i++)
            writeRndVertical();
        for (int i = 0; i < 20; i++)
            writeRnd();
    }

    private static String fmt(double v) {
        return String.format(Locale.US, "%.4f", v);
    }

    private static double fullVol(int d, int l) {
        double r = d / 2.0;
        return (Math.PI * r * r * l + Math.PI * r * r * r * 4 / 3) * 1e-6;
    }

    private static double cylVol(int d, int l) {
        double r = d / 2.0;
        return (Math.PI * r * r * l) * 1e-6;
    }

    private static double halfSpVol(int d) {
        double r = d / 2.0;
        return (Math.PI * r * r * r * 4 / 3 / 2) * 1e-6;
    }

    private static double capVol(int d, int r) {
        double h = r - Math.sqrt((double)r * r - 0.25 * d * d);
        return (Math.PI * h * h / 3 * (3 * r - h)) * 1e-6;
    }

    private static double fullVol(int d, int l, int r) {
        return 2 * capVol(d, r) + cylVol(d, l);
    }


}

