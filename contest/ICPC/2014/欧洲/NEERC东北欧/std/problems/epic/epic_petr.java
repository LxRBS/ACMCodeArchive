/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem E. Epic Win!                                           */
/*                                                                */
/* Original idea         Mikhail Dvorkin                          */
/* Problem statement     Mikhail Dvorkin                          */
/* Test set              Mikhail Dvorkin                          */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Petr Mitrichev                           */
/******************************************************************/


import java.io.InputStreamReader;
import java.io.IOException;
import java.util.Arrays;
import java.io.BufferedReader;
import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.util.Random;
import java.io.FileInputStream;
import java.util.StringTokenizer;
import java.io.InputStream;
 
/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class epic_petr {
    public static void main(String[] args) {
        InputStream inputStream;
        try {
            inputStream = new FileInputStream("epic.in");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        OutputStream outputStream;
        try {
            outputStream = new FileOutputStream("epic.out");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Epic solver = new Epic();
        solver.solve(1, in, out);
        out.close();
    }

    static class Epic {

        public static final int COPIES = 10;
        public static final int BUBEN = 10000;

        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            int[] what = new int[n];
            int[][] jump = new int[n][3];
            for (int i = 0; i < n; ++i) {
                what[i] = "RPS".indexOf(in.next().charAt(0));
                for (int j = 0; j < 3; ++j) jump[i][j] = in.nextInt() - 1;
            }
            int[][] resjump = new int[COPIES * n][3];
            int[] reswhat = new int[COPIES * n];
            for (int i = 0; i < reswhat.length; ++i) reswhat[i] = (what[i % n] + 1) % 3;
            for (int[] x : resjump) Arrays.fill(x, -1);
            for (int i = 0; i < COPIES * n; ++i) {
                int j = i % n;
                int offset = i - j;
                resjump[i][what[j]] = offset + jump[j][reswhat[i]];
            }
            Random random = new Random(54731543531L);
            int[] perm = new int[n - 1];
            for (int i = 0; i < n - 1; ++i) perm[i] = i + 1;
            for (int i = 0; i < n - 1; ++i) {
                int j = random.nextInt(n - 1 - i) + i;
                int t = perm[i];
                perm[i] = perm[j];
                perm[j] = t;
            }
            outer:
            for (int toFail : perm) {
                int him = toFail;
                int us = 0;
                int stable = 0;
                int total = 0;
                while (true) {
                    int heSays = what[him];
                    int weSay = reswhat[us];
                    ++total;
                    if (weSay == (heSays + 1) % 3) {
                        int nhim = jump[him][weSay];
                        int nus = resjump[us][heSays];
                        him = nhim;
                        us = nus;
                        ++stable;
                        if (stable >= BUBEN) {
                            continue outer;
                        }
                        continue;
                    }
                    if (resjump[us][heSays] < 0) {
                        int offset = us - (us % n);
                        offset += n;
                        if (offset >= reswhat.length) offset = 0;
                        resjump[us][heSays] = offset + jump[him][weSay];
                        continue outer;
                    }
                    {
                        int nhim = jump[him][weSay];
                        int nus = resjump[us][heSays];
                        him = nhim;
                        us = nus;
                        if (total > BUBEN) throw new RuntimeException();
                    }
                }
            }
            out.println(reswhat.length);
            for (int i = 0; i < reswhat.length; ++i) {
                out.print("RPS".charAt(reswhat[i]));
                for (int k = 0; k < 3; ++k) {
                    out.print(" ");
                    out.print(Math.max(0, resjump[i][k]) + 1);
                }
                out.println();
            }
        }
    }

    static class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;

        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }

        public String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

    }
}
