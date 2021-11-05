/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem A. Alter Board                                         */
/*                                                                */
/* Original idea         Egor Kulikov                             */
/* Problem statement     Egor Kulikov                             */
/* Test set              Egor Kulikov                             */
/******************************************************************/
/* Checker                                                        */
/*                                                                */
/* Author                Egor Kulikov                             */
/******************************************************************/

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;
import static ru.ifmo.testlib.Outcome.Type.*;

public class Check implements Checker {
    private static final int MAX_MOVES = 10000;

    int moves;
    int[] fromRowA;
    int[] toRowA;
    int[] fromColumnA;
    int[] toColumnA;

    void parse(InStream ouf) {
        moves = ouf.nextInt();
        if (moves < 0) {
            throw new Outcome(PE, "Negative number of moves: " + moves);
        }
        if (moves > MAX_MOVES) {
            throw new Outcome(WA, "Too many moves: " + moves);
        }

        fromRowA = new int[moves];
        toRowA = new int[moves];
        fromColumnA = new int[moves];
        toColumnA = new int[moves];

        for (int i = 0; i < moves; i++) {
            fromRowA[i] = ouf.nextInt();
            fromColumnA[i] = ouf.nextInt();
            toRowA[i] = ouf.nextInt();
            toColumnA[i] = ouf.nextInt();
        }
        if (!ouf.seekEoF())
            throw new Outcome(PE, String.format("Extra data in output file"));
    }

    @Override
    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        int rowCount = inf.nextInt();
        int columnCount = inf.nextInt();

        parse(ouf);

        long[] board = new long[rowCount];
        long even = 0;
        long odd = 0;
        for (int i = 0; i < columnCount; i++) {
            if ((i & 1) == 0) {
                even += 1L << i;
            } else {
                odd += 1L << i;
            }
        }
        for (int i = 0; i < rowCount; i++) {
            board[i] = ((i & 1) == 0) ? even : odd;
        }
        for (int i = 0; i < moves; i++) {
            int fromRow = fromRowA[i];
            int toRow = toRowA[i];
            int fromColumn = fromColumnA[i];
            int toColumn = toColumnA[i];
            if (fromRow > toRow) {
                int temp = fromRow;
                fromRow = toRow;
                toRow = temp;
            }
            if (fromColumn > toColumn) {
                int temp = toColumn;
                toColumn = fromColumn;
                fromColumn = temp;
            }
            if (fromRow < 1) {
                return new Outcome(WA, "Row with index less than 1: " + fromRow);
            }
            if (toRow > rowCount) {
                return new Outcome(WA, "Row with index more than number of rows: " + toRow + ", number of rows: " + rowCount);
            }
            if (fromColumn < 1) {
                return new Outcome(WA, "Column with index less than 1: " + fromColumn);
            }
            if (toColumn > columnCount) {
                return new Outcome(WA, "Column with index more than number of columns: " + toColumn + ", number of columns: " + columnCount);
            }
            long mask = (1L << toColumn) - (1L << (fromColumn - 1));
            for (int j = fromRow - 1; j < toRow; j++) {
                board[j] ^= mask;
            }
        }
        if (board[0] != 0 && board[0] != (1L << columnCount) - 1) {
            return new Outcome(WA, "First row is not of same color");
        }
        for (int i = 1; i < rowCount; i++) {
            if (board[i] != board[0]) {
                return new Outcome(WA, "Row number " + (i + 1) + " is not same as first row");
            }
        }
        int answerMoves = ans.nextInt();
        if (answerMoves < moves) {
            return new Outcome(WA, "Too many moves - expected: " + answerMoves + ", found: " + moves);
        }
        if (answerMoves > moves) {
            return new Outcome(FAIL, "Better solution found - expected: " + answerMoves + ", found: " + moves);
        }
        return new Outcome(OK, "Correct: " + moves);
    }

}

