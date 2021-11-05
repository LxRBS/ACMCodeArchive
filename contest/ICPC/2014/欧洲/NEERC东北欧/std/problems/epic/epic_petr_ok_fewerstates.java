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
public class epic_petr_ok_fewerstates {
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
        Epic solver = new Epic(5431754371541L);
        solver.solve(1, in, out);
        out.close();
    }

    static class Epic {

        public static final int BUBEN = 10000;
        
        static class FSM {
            int[] what;
            int[][] jump;

            FSM(int[] what, int[][] jump) {
                this.what = what;
                this.jump = jump;
            }
        }

        Random random;

        public Epic(long seed) {
            random = new Random(seed);
        }

        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            int[] what = new int[n];
            int[][] jump = new int[n][3];
            for (int i = 0; i < n; ++i) {
                what[i] = "RPS".indexOf(in.next().charAt(0));
                for (int j = 0; j < 3; ++j) jump[i][j] = in.nextInt() - 1;
            }
            FSM input = new FSM(what, jump);
            FSM res = solveIt(n, input);
            out.println(res.what.length);
            for (int i = 0; i < res.what.length; ++i) {
                out.print("RPS".charAt(res.what[i]));
                for (int k = 0; k < 3; ++k) {
                    out.print(" ");
                    out.print(Math.max(0, res.jump[i][k]) + 1);
                }
                out.println();
            }
        }

        public FSM solveIt(int n, FSM input) {
            FSM res = new FSM(new int[n * n], new int[n * n][3]);
            for (int i = 0; i < res.what.length; ++i) res.what[i] = (input.what[i % n] + 1) % 3;
            for (int[] x : res.jump) Arrays.fill(x, -1);
            for (int i = 0; i < n * n; ++i) {
                int j = i % n;
                int offset = i - j;
                res.jump[i][input.what[j]] = offset + input.jump[j][res.what[i]];
            }
            int[] perm = new int[n - 1];
            for (int i = 0; i < n - 1; ++i) perm[i] = i + 1;
            for (int i = 0; i < n - 1; ++i) {
                int j = random.nextInt(n - 1 - i) + i;
                int t = perm[i];
                perm[i] = perm[j];
                perm[j] = t;
            }
            int maxstate = 0;
            outer:
            for (int toFail : perm) {
                int him = toFail;
                int us = 0;
                int stable = 0;
                int total = 0;
                while (true) {
                    int heSays = input.what[him];
                    int weSay = res.what[us];
                    ++total;
                    if (weSay == (heSays + 1) % 3) {
                        int nhim = input.jump[him][weSay];
                        int nus = res.jump[us][heSays];
                        him = nhim;
                        us = nus;
                        ++stable;
                        if (stable >= BUBEN) {
                            continue outer;
                        }
                        continue;
                    }
                    if (res.jump[us][heSays] < 0) {
                        int offset = us - (us % n);
                        offset += n;
                        int dest = offset + input.jump[him][weSay];
                        res.jump[us][heSays] = dest;
                        maxstate = Math.max(maxstate, dest);
                        continue outer;
                    }
                    {
                        int nhim = input.jump[him][weSay];
                        int nus = res.jump[us][heSays];
                        him = nhim;
                        us = nus;
                        if (total > BUBEN) throw new RuntimeException();
                    }
                }
            }
            while (maxstate % n != n - 1) ++maxstate;
            res.what = Arrays.copyOf(res.what, maxstate + 1);
            res.jump = Arrays.copyOf(res.jump, maxstate + 1);
            return res;
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
