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
/* Solution                                                       */
/*                                                                */
/* Author                Pavel Mavrin                             */
/******************************************************************/

import java.io.PrintWriter;
import java.util.*;

/**
 * @author: pashka
 */
public class gomoku_pm {

    private static final int SIZE = 19;
    private Scanner in;
    private PrintWriter out;

    public static void main(String[] args) {
        new gomoku_pm().run();
    }

    private void run() {
        in = new Scanner(System.in);
        out = new PrintWriter(System.out);
        solve();
    }

    private void solve() {
        int[] board = new int[SIZE * SIZE];
        while (true) {
            int x = in.nextInt() - 1;
            int y = in.nextInt() - 1;
            if (x == -2) break;
            int hisMove = x * SIZE + y;
            board[hisMove] = 2;
            int myMove = strategy.getMove(SIZE, board);
            board[myMove] = 1;
            out.println((myMove / SIZE + 1) + " " + (myMove % SIZE + 1));
            out.flush();
        }
    }

    BackTrackStrategy strategy = new BackTrackStrategy();

    public class BackTrackStrategy  {

        private static final int SIZE = 19;

        int player = 1;

        public int getMove(int size, int[] board) {
            int cnt = 0;
            for (int i : board) if (i == player) cnt++;
            if (cnt == 0) {
                return 2 * size + 3;
            }
            if (cnt == 1) {
                return 3 * size + 2;
            }
            return bt(board, 20);
        }

        class Move implements Comparable<Move> {
            int myMove;
            int[] hisMoves;

            public Move(int myMove, int[] hisMoves) {
                this.myMove = myMove;
                this.hisMoves = hisMoves;
            }

            @Override
            public int compareTo(Move o) {
                return Integer.compare(hisMoves.length, o.hisMoves.length);
            }
        }

        private int bt(int[] board, int limit) {
            if (limit == 0) return -1;
            List<Move> p = new ArrayList<Move>();
            for (int us : strategy2.getMoves(SIZE, board, 50 * 50 * 50)) {
                board[us] = player;
                int[] hisMoves = strategy.getMoves(SIZE, board, 50 * 50 - 1);
                p.add(new Move(us, hisMoves));
                board[us] = 0;
            }
            Collections.sort(p);
            for (Move move : p) {
                int us = move.myMove;
                board[us] = player;
                if (gameOutcome(board, us) == player) {
                    board[us] = 0;
                    return us;
                }
                boolean ok = true;
                for (int his : move.hisMoves) {
                    board[his] = 3 - player;
                    if (gameOutcome(board, his) == 3 - player) {
                        board[his] = 0;
                        board[us] = 0;
                        return -1;
                    }
                    int res = bt(board, limit - 1);
                    if (res < 0) {
                        board[his] = 0;
                        board[us] = 0;
                        ok = false;
                        break;
                    }
                    board[his] = 0;
                }
                board[us] = 0;
                if (ok) {
                    return us;
                }
            }
            return -1;
        }

        BadStrategy strategy = new BadStrategy(3 - player);
        BadStrategy strategy2 = new BadStrategy(player);

        public class BadStrategy {
            final long BASE = 50;
            int p;
            final long[] score1;
            final long[] score2;

            public BadStrategy(int p) {
                score1 = new long[6];
                score2 = new long[6];
                this.p = p;
                long tmp = 1;
                for (int i = 1; i <= 5; ++i) {
                    tmp *= BASE;
                    score1[i] = tmp;
                    tmp *= BASE;
                    score2[i] = tmp;
                }
            }

            public int[] getMoves(int size, int[] board, long gap) {
                if (board.length != size * size) throw new RuntimeException();
                long maxScore = Long.MIN_VALUE;
                long[] score = new long[board.length];
                for (int us = 0; us < board.length; ++us)
                    if (board[us] == 0) {
                        board[us] = p;
                        score[us] = scoreDelta(us, size, board);
                        maxScore = Math.max(maxScore, score[us]);
                        board[us] = 0;
                    }
                int cnt = 0;
                for (int us = 0; us < board.length; ++us)
                    if (board[us] == 0) {
                        if (score[us] >= maxScore - gap) {
                            cnt++;
                        }
                    }
                int[] res = new int[cnt];
                cnt = 0;
                for (int us = 0; us < board.length; ++us)
                    if (board[us] == 0) {
                        if (score[us] >= maxScore - gap) {
                            res[cnt++] = us;
                        }
                    }
                return res;
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
                    return score1[cnt[p]] - score2[cnt[3 - p]];
                } else {
                    return 0;
                }
            }
        }


        public int gameOutcome(int[] board, int move) {
            int r = move / SIZE;
            int c = move % SIZE;
            int p = board[move];
            for (int dr = 0; dr <= 1; ++dr) {
                for (int dc = (dr == 0 ? 1 : -1); dc <= 1; ++dc) {
                    int fr = r;
                    int fc = c;
                    int cc = 0;
                    while (fr >= 0 && fr < SIZE && fc >= 0 && fc < SIZE && board[fr * SIZE + fc] == p) {
                        cc++;
                        fr += dr;
                        fc += dc;
                    }
                    fr = r;
                    fc = c;
                    while (fr >= 0 && fr < SIZE && fc >= 0 && fc < SIZE && board[fr * SIZE + fc] == p) {
                        cc++;
                        fr -= dr;
                        fc -= dc;
                    }
                    cc--;
                    if (cc >= 5) return p;
                }
            }
            return 0;
        }
    }}

