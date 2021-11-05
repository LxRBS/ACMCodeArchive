/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem G. Gomoku                                              */
/*                                                                */
/* Original idea         Petr Mitrichev                           */
/* Problem statement     Petr Mitrichev                           */
/* Test set              Pavel Mavrin                             */
/******************************************************************/
/* Interactor                                                     */
/*                                                                */
/* Author                Pavel Mavrin                             */
/******************************************************************/

import java.io.*;
import java.util.Arrays;
import java.util.Random;
import java.util.StringTokenizer;

class Interact {
    private static final int EXIT_BAD = 10;
    FastScanner data;
    FastScanner in;
    PrintWriter out;
    PrintWriter report;

    boolean doLog = false;
    PrintWriter log;

    boolean halt = false;
    final static int SIZE = 19;

    void solve() throws FileNotFoundException {
        int seed = data.nextInt();
        BadStrategy badStrategy = new BadStrategy(seed);
        int[] board = new int[SIZE * SIZE];
        int move = (SIZE / 2) * SIZE + (SIZE / 2);
        out.println((move / SIZE + 1) + " " + (move % SIZE + 1));
        out.flush();
        board[move] = 1;
        int player = 2;
        int moves = 1;
        while (true) {
            int outcome = gameOutcome(board);
            if (outcome != 0) {
                out.println("-1 -1");
                out.flush();
                report.println(outcome);
                report.println(moves);
                return;
            }
            if (player == 1) {
                move = badStrategy.getMove(SIZE, board);
                out.println((move / SIZE + 1) + " " + (move % SIZE + 1));
                out.flush();
            } else {
                int x = in.nextInt() - 1;
                int y = in.nextInt() - 1;
                if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
                    report.println(4);
                    report.println(moves + 1);
                    halt = true;
                    return;
                }
                move = x * SIZE + y;
            }
            ++moves;
            if (move < 0 || move >= board.length) {
                if (player == 1) {
                    report.println(100500);
                    report.println(moves);
                } else {
                    report.println(4);
                    report.println(moves);
                }
                halt = true;
                return;
            }
            if (board[move] != 0) {
                if (player == 1) {
                    report.println(100500);
                    report.println(moves);
                } else {
                    report.println(4);
                    report.println(moves);
                }
                halt = true;
                return;
            }
            board[move] = player;
            player = 3 - player;
        }
    }

    public void run() {
        try {
            data = new FastScanner(new FileInputStream("gomoku.in"));
            report = new PrintWriter("gomoku.out");
            in = new FastScanner(System.in);
            out = new PrintWriter(System.out);

            solve();

            out.close();
            report.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(EXIT_BAD);
        }
        if (halt) {
            System.exit(EXIT_BAD);            
        }
    }

    class FastScanner {
        BufferedReader br;
        StringTokenizer st;

        FastScanner(InputStream is) {
            br = new BufferedReader(new InputStreamReader(is));
        }

        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    String s = br.readLine();
                    if (s == null) {
                        report.println(-2);
                        report.println("Unexpected end of file");
                        System.exit(EXIT_BAD);
                    }
                    st = new StringTokenizer(s);
                } catch (IOException e) {
                    e.printStackTrace();
                    report.println(-2);
                    report.println(e.getMessage());
                    System.exit(EXIT_BAD);
                }
            }
            return st.nextToken();
        }

        int nextInt() {
            String s = next();
            try {
                return Integer.parseInt(s);
            } catch (NumberFormatException e) {
                report.println(-2);
                report.println("Number expected instead of " + s);
                System.exit(EXIT_BAD);
                return 0;
            }
        }
    }

    public static void main(String[] arg) {
        new Interact().run();
    }

    public class BadStrategy {
        Random random;
        final long BASE = 50;
        final long[] score1;
        final long[] score2;

        public BadStrategy(long seed) {
            random = new Random(seed);
            score1 = new long[6];
            score2 = new long[6];
            long tmp = 1;
            for (int i = 1; i <= 5; ++i) {
                tmp *= BASE;
                score1[i] = tmp;
                tmp *= BASE;
                score2[i] = tmp;
            }
        }

        public int getMove(int size, int[] board) {
            if (board.length != size * size) throw new RuntimeException();
            int best = -1;
            long bestScore = Long.MIN_VALUE;
            long curScore = 0;
            for (int us = 0; us < board.length; ++us) if (board[us] == 0) {
                board[us] = 1;
                long worstScore = curScore + scoreDelta(us, size, board) + scoreRandomOnTop();
                board[us] = 0;
                if (worstScore > bestScore) {
                    bestScore = worstScore;
                    best = us;
                }
            }
            return best;
        }

        private long scoreDelta(int pos, int size, int[] board) {
            int r = pos / size;
            int c = pos % size;
            long res = 0;
            for (int dr = 0; dr <= 1; ++dr) {
                for (int dc = (dr == 0 ? 1 : -1); dc <= 1; ++dc) {
                    int[] seq = new int[9];
                    Arrays.fill(seq, 3);
                    for (int delta = -4; delta <= 4; ++delta) {
                        int pr = r + delta * dr;
                        int pc = c + delta * dc;
                        if (pr >= 0 && pr < size && pc >= 0 && pc < size) {
                            seq[4 + delta] = board[pr * size + pc];
                        }
                    }
                    res += scoreRowDelta(seq);
                }
            }
            return res;
        }

        private long scoreRowDelta(int[] seq) {
            int[] cntAfter = new int[4];
            int[] cntBefore = new int[4];
            long res = 0;
            for (int i = 0; i < 9; ++i) {
                if (seq[i] > 0) {
                    ++cntAfter[seq[i]];
                    if (i != 4)
                        ++cntBefore[seq[i]];
                }
                if (i >= 5 && seq[i - 5] > 0) {
                    --cntAfter[seq[i - 5]];
                    --cntBefore[seq[i - 5]];
                }
                if (i >= 4) {
                    res += scoreCnt(cntAfter);
                    res -= scoreCnt(cntBefore);
                }
            }
            return res;
        }

        private long scoreCnt(int[] cnt) {
            if ((cnt[1] == 0 ^ cnt[2] == 0) && cnt[3] == 0) {
                return score1[cnt[1]] - score2[cnt[2]];
            } else {
                return 0;
            }
        }

        private long scoreRandomOnTop() {
            return random.nextInt((int) (BASE * BASE));
        }
    }

    public static int gameOutcome(int[] board) {
        int[] cnt = new int[3];
        boolean hadEmpty = false;
        for (int r = 0; r < SIZE; ++r) {
            for (int c = 0; c < SIZE; ++c) {
                if (board[r * SIZE + c] == 0) hadEmpty = true;
                for (int dr = 0; dr <= 1; ++dr) {
                    for (int dc = (dr == 0 ? 1 : -1); dc <= 1; ++dc) {
                        int fr = r + dr * 4;
                        int fc = c + dc * 4;
                        if (fr >= 0 && fr < SIZE && fc >= 0 && fc < SIZE) {
                            Arrays.fill(cnt, 0);
                            for (int u = 0; u < 5; ++u) {
                                int ur = r + dr * u;
                                int uc = c + dc * u;
                                ++cnt[board[ur * SIZE + uc]];
                            }
                            if (cnt[1] == 5) return 1;
                            if (cnt[2] == 5) return 2;
                        }
                    }
                }
            }
        }
        return hadEmpty ? 0 : 3;
    }
}
