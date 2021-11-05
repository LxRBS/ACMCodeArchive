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
/* Author                Petr Mitrichev                           */
/******************************************************************/

import java.io.PrintWriter;
import java.util.Scanner;

/**
 * @author: pashka
 */
public class gomoku_petr {

    private static final int SIZE = 19;
    private Scanner in;
    private PrintWriter out;

    public static void main(String[] args) {
        new gomoku_petr().run();
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
            int myMove = getMove(SIZE, board);
            board[myMove] = 1;
            out.println((myMove / SIZE + 1) + " " + (myMove % SIZE + 1));
            out.flush();
        }
    }

    public int getMove(int size, int[] board) {
        if (board.length != size * size) throw new RuntimeException();
        int[] counts = new int[3];
        for (int x : board) ++counts[x];
        // Verify that we move second.
        if (counts[1] != counts[2] - 1) throw new RuntimeException();
        // Use immediate wins.
        for (int r = 0; r < size; ++r)
            for (int c = 0; c < size; ++c)
                for (int dr = -1; dr <= 1; ++dr)
                    for (int dc = -1; dc <= 1; ++dc) {
                        if (r + 4 * dr >= 0 && r + 4 * dr < size && c + 4 * dc >= 0 && c + 4 * dc < size) {
                            int[] cnt = new int[3];
                            for (int i = 0; i <= 4; ++i) {
                                ++cnt[board[(r + i * dr) * size + (c + i * dc)]];
                            }
                            if (cnt[1] == 4 && cnt[2] == 0) {
                                for (int i = 0; i <= 4; ++i) {
                                    if (board[(r + i * dr) * size + (c + i * dc)] == 0) {
                                        return (r + i * dr) * size + (c + i * dc);
                                    }
                                }
                            }
                        }
                    }
        // Defend against immediate losses.
        for (int r = 0; r < size; ++r)
            for (int c = 0; c < size; ++c)
                for (int dr = -1; dr <= 1; ++dr)
                    for (int dc = -1; dc <= 1; ++dc) {
                        if (r + 4 * dr >= 0 && r + 4 * dr < size && c + 4 * dc >= 0 && c + 4 * dc < size) {
                            int[] cnt = new int[3];
                            for (int i = 0; i <= 4; ++i) {
                                ++cnt[board[(r + i * dr) * size + (c + i * dc)]];
                            }
                            if (cnt[2] == 4 && cnt[1] == 0) {
                                for (int i = 0; i <= 4; ++i) {
                                    if (board[(r + i * dr) * size + (c + i * dc)] == 0) {
                                        return (r + i * dr) * size + (c + i * dc);
                                    }
                                }
                            }
                        }
                    }
        // If we can create an undefended 4, do that.
        for (int r = 0; r < size; ++r)
            for (int c = 0; c < size; ++c)
                for (int dr = -1; dr <= 1; ++dr)
                    for (int dc = -1; dc <= 1; ++dc) {
                        if (r + 5 * dr >= 0 && r + 5 * dr < size && c + 5 * dc >= 0 && c + 5 * dc < size && board[r * size + c] == 0 && board[(r + 5 * dr) * size + (c + 5 * dc)] == 0) {
                            int[] cnt = new int[3];
                            for (int i = 1; i <= 4; ++i) {
                                ++cnt[board[(r + i * dr) * size + (c + i * dc)]];
                            }
                            if (cnt[1] == 3 && cnt[2] == 0) {
                                for (int i = 1; i <= 4; ++i) {
                                    if (board[(r + i * dr) * size + (c + i * dc)] == 0) {
                                        return (r + i * dr) * size + (c + i * dc);
                                    }
                                }
                            }
                        }
                    }
        // First two moves.
        if (board[3 * size + 4] == 0) {
            return 3 * size + 4;
        }
        if (board[4 * size + 3] == 0) {
            return 4 * size + 3;
        }
        // Defense on third move.
        if (board[2 * size + 5] == 0 && board[5 * size + 2] == 0) {
            for (int r = 0; r < size; ++r)
                for (int c = 0; c < size; ++c)
                    for (int dr = -1; dr <= 1; ++dr)
                        for (int dc = -1; dc <= 1; ++dc) {
                            int r1 = r + dr;
                            int c1 = c + dc;
                            int r2 = r1 + dr;
                            int c2 = c1 + dc;
                            if (r2 >= 0 && r2 < size && c2 >= 0 && c2 < size) {
                                if (board[r * size + c] == 0 && board[r1 * size + c1] == 2 && board[r2 * size + c2] == 2) {
                                    return r * size + c;
                                }
                            }
                        }
            throw new RuntimeException();
        }
        // First triple.
        if (board[2 * size + 5] == 0) {
            return 2 * size + 5;
        }
        if (board[5 * size + 2] == 0) {
            return 5 * size + 2;
        }
        // Know which of two symmetric situations we play.
        int cr;
        int cc;
        if (board[2 * size + 5] == 1) {
            cr = 3;
            cc = 4;
        } else {
            cr = 4;
            cc = 3;
        }
        // Second triple.
        if (board[(cr + 1) * size + (cc + 1)] == 0) {
            return (cr + 1) * size + (cc + 1);
        }
        if (board[(cr - 1) * size + (cc - 1)] == 0) {
            return (cr - 1) * size + (cc - 1);
        }
        // If we already had our 3x3, we have a winning 4x3 move now.
        if (board[(cr + 1) * size + cc] == 1 && board[(cr - 1) * size + cc] == 1) {
            if (board[(cr + 2) * size + cc] == 0) {
                return (cr + 2) * size + cc;
            }
            if (board[(cr - 2) * size + cc] == 0) {
                return (cr - 2) * size + cc;
            }
            throw new RuntimeException();
        }
        // Two moves to create a 3x3. One of the attacking cells might be taken, so there are a few cases here.
        if (board[(cr + 1) * size + cc] == 0 && board[(cr - 1) * size + cc] == 0) {
            return (cr + 1) * size + cc;
        }
        if (board[(cr + 1) * size + cc] == 1 && board[(cr - 1) * size + cc] == 0) {
            return (cr - 1) * size + cc;
        }
        throw new RuntimeException();
    }
}

