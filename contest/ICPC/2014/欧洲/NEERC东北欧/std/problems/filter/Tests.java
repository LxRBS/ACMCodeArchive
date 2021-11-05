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
/* Tests                                                          */
/*                                                                */
/* Author                Roman Elizarov                           */
/******************************************************************/

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashSet;
import java.util.Random;
import java.util.Set;

/**
 * NEERC 2014 Test generator for problem Filter
 *
 * @author Roman Elizarov
 */
public class Tests {
    static final String TEST_NAME_FORMAT = "%02d";
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

    private static void setFilter(int[] a, int m, byte[] digits, int u) {
        for (int i = 0; i < a.length; i++) {
            int j = (int)(((long)u * a[i]) % m);
            digits[j / 4] |= 1 << (j % 4);
        }
    }
    static void write(String desc, int m, int[] a, int[][] du, int[] qu) throws IOException {
        int n = du.length;
        byte[][] d = new byte[n][(m + 3) / 4];
        for (int i = 0; i < n; i++) {
            int[] u = du[i];
            for (int j = 0; j < u.length; j++) {
                setFilter(a, m, d[i], u[j]);
            }
        }
        try (PrintWriter out = openTestFile(desc)) {
            out.print(m + " " + a.length);
            for (int ai : a) {
                out.print(" " + ai);
            }
            out.println();
            out.println(n);
            for (int i = 0; i < n; i++) {
                for (byte b : d[i]) {
                    out.print(Integer.toHexString(b));
                }
                out.println();
            }
            out.print(qu.length);
            for (int u : qu) {
                out.print(" " + u);
            }
            out.println();
        }
    }

    static void writeRnd(int m, int f, int maxA, int uSetSz, int maxU, int n, int recs, int q) throws IOException {
        int[] a = new int[f];
        for (int i = 0; i < f; i++) {
            a[i] = RND.nextInt(maxA) + 1;
        }
        assert uSetSz < maxU;
        Set<Integer> uSet = new HashSet<>();
        int[] u = new int[uSetSz];
        for (int i = 0; i < uSetSz; i++) {
            do {
                u[i] = RND.nextInt(maxU) + 1;
            } while (!uSet.add(u[i]));
        }
        int[][] du = new int[n][recs];
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < recs; k++) {
                du[j][k] = u[RND.nextInt(uSetSz)];
            }
        }
        int[] qu = new int[q];
        Set<Integer> qSet = new HashSet<>();
        for (int k = 0; k < q; k++) {
            do {
                qu[k] = u[RND.nextInt(uSetSz)];
            } while (!qSet.add(qu[k]));
        }
        write(String.format("Random m=%d, f=%d, maxA=%d, uSetSz=%d, maxU=%d, n=%d, recs=%d, q=%d",
                m, f, maxA, uSetSz, maxU, n, recs, q), m, a, du, qu);
    }


    public static void main(String[] args) throws IOException {
        LST_FILE.delete();

        write("Sample", 23, new int[] { 3, 5, 7, 11 }, new int[][] {
                { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                { 3, 5, 7 },
                { 6 }
        }, new int[] { 2, 4, 6 }) ;

        write("Empty", 1, new int[] { 1 }, new int[][] {{}}, new int[] { 1 } );
        write("One", 1, new int[] { 1 }, new int[][] {{1}}, new int[] { 1 } );
        write("Two", 1, new int[] { 1 }, new int[][] {{2}}, new int[] { 2 } );
        write("Three", 1, new int[] { 1 }, new int[][] {{3}}, new int[] { 3 } );

        write("One hex -- even only", 4, new int[] { 2, 4 }, new int[][] {
                { 1 },
                { 2 },
                { 3 },
                { 4 },
                { 5 },
                { 6 },
                { 7 },
                { 8 }
        }, new int[] { 1, 2, 3 });

        write("One hex -- prime", 4, new int[] { 3, 5 }, new int[][] {
                { 1 },
                { 2 },
                { 3 },
                { 4 },
                { 5 },
                { 6 },
                { 7 },
                { 8 }
        }, new int[] { 1, 2, 3 });

        writeRnd(10, 5, 100, 10, 100, 10, 1, 1);
        writeRnd(10, 5, 100, 10, 100, 10, 1, 2);
        writeRnd(10, 5, 100, 10, 100, 10, 1, 3);

        writeRnd(128, 16, 1000, 100, 1000, 100, 5, 5);
        writeRnd(128, 16, 1000, 100, 1000, 100, 5, 10);
        writeRnd(128, 16, 1000, 100, 1000, 100, 10, 10);
        writeRnd(128, 16, 1000, 100, 1000, 100, 10, 100);
        writeRnd(128, 16, 1000, 100, 1000, 100, 100, 100);

        writeRnd(997, 100, Integer.MAX_VALUE, 100, Integer.MAX_VALUE, 1000, 1, 1);
        writeRnd(997, 100, Integer.MAX_VALUE, 100, Integer.MAX_VALUE, 1000, 1, 2);
        writeRnd(997, 100, Integer.MAX_VALUE, 100, Integer.MAX_VALUE, 1000, 1, 3);
        writeRnd(997, 100, Integer.MAX_VALUE, 100, Integer.MAX_VALUE, 1000, 10, 1);
        writeRnd(997, 100, Integer.MAX_VALUE, 100, Integer.MAX_VALUE, 1000, 10, 5);
        writeRnd(997, 100, Integer.MAX_VALUE, 100, Integer.MAX_VALUE, 1000, 10, 10);
        writeRnd(997, 100, Integer.MAX_VALUE, 100, Integer.MAX_VALUE, 1000, 100, 100);

        writeRnd(1000, 100, Integer.MAX_VALUE, 100, Integer.MAX_VALUE, 1000, 1, 1);
        writeRnd(1000, 100, Integer.MAX_VALUE, 100, Integer.MAX_VALUE, 1000, 1, 2);
        writeRnd(1000, 100, Integer.MAX_VALUE, 100, Integer.MAX_VALUE, 1000, 1, 3);
        writeRnd(1000, 100, Integer.MAX_VALUE, 100, Integer.MAX_VALUE, 1000, 10, 1);
        writeRnd(1000, 100, Integer.MAX_VALUE, 100, Integer.MAX_VALUE, 1000, 10, 5);
        writeRnd(1000, 100, Integer.MAX_VALUE, 100, Integer.MAX_VALUE, 1000, 10, 10);
        writeRnd(1000, 100, Integer.MAX_VALUE, 100, Integer.MAX_VALUE, 1000, 100, 100);
    }
}

