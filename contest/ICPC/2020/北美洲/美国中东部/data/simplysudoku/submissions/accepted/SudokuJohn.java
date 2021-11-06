import java.util.*;

public class SudokuJohn
{
    public static int[][] grid = new int[9][9];
    public static boolean[][][] used = new boolean[9][9][10];
    public static int numEmpty = 0;

    public static class RC {
        public int r, c;
    };

    public static void update(int row, int col, int val)
    {
        grid[row][col] = val;
        for(int v=1; v<=9; v++)
            used[row][col][v] = true;
        for(int r=0; r<9; r++)
            used[r][col][val] = true;
        for(int c=0; c<9; c++)
            used[row][c][val] = true;
        row = (row/3)*3;
        col = (col/3)*3;
        for(int r=row; r<row+3; r++)
            for(int c=col; c<col+3; c++)
                used[r][c][val] = true;
    }

    public static int checkForSingle(int r,int c)
    {
        int val = -1;
        for(int v=1; v<=9; v++) {
            if (!used[r][c][v]) {
                if (val != -1)
                    return -1;
                val = v;
            }
        }
        return val;
    }

    public static boolean foundUniqueRowLoc(int row, int val, RC rc)
    {
        rc.c = -1;
        for(int c=0; c<9; c++) {
            if (!used[row][c][val]) {
                if (rc.c != -1)
                    return false;
                rc.c = c;
            }
        }
        return (rc.c != -1);
    }

    public static boolean foundUniqueColLoc(int col, int val, RC rc)
    {
        rc.r = -1;
        for(int r=0; r<9; r++) {
            if (!used[r][col][val]) {
                if (rc.r != -1)
                    return false;
                rc.r = r;
            }
        }
        return (rc.r != -1);
    }

    public static boolean foundUniqueSubLoc(int row, int col, int val, RC rc)
    {
        rc.r = -1;
        for(int r=row; r<row+3; r++) {
            for(int c=col; c<col+3; c++) {
                if (!used[r][c][val]) {
                    if (rc.r != -1)
                        return false;
                    rc.r = r;
                    rc.c = c;
                }
            }
        }
        return (rc.r != -1);
    }

    public static void printgrid()
    {
        for(int r=0; r<9; r++) {
            if (grid[r][0] == 0)
                System.out.print(".");
            else
                System.out.print(grid[r][0]);
            for(int c=1; c<9; c++) {
                if (grid[r][c] == 0)
                    System.out.print(" .");
                else
                    System.out.print(" " + grid[r][c]);
            }
            System.out.println();
        }
    }

    public static void main(String [] args)
    {
        Scanner in = new Scanner(System.in);
        for(int r=0; r<9; r++) {
            for(int c=0; c<9; c++) {
                int val = in.nextInt();;
                if (val == 0)
                    numEmpty++;
                else
                    update(r, c, val);
            }
        }
        boolean change;
        do {
            change = false;
                            // check single value case
            for(int r=0; r<9; r++) {
                for(int c=0; c<9; c++) {
                    if (grid[r][c] != 0)
                        continue;
                    int val;
                    if ((val = checkForSingle(r,c)) > 0) {
                        update(r, c, val);
                        change = true;
                        numEmpty--;
                   }
                }
            }
    /**/
                            // check for unique location case
                            //  rows first
            RC rc = new RC();
            for(int r=0; r<9; r++) {
                for(int val=1; val<=9; val++) {
                    if (foundUniqueRowLoc(r, val, rc)) {
                        update(r, rc.c, val);
                        change = true;
                        numEmpty--;
                    }
                }
            }
                            //  cols next
            for(int c=0; c<9; c++) {
                for(int val=1; val<=9; val++) {
                    if (foundUniqueColLoc(c, val, rc)) {
                        update(rc.r, c, val);
                        change = true;
                        numEmpty--;
                    }
                }
            }
                            //  then subgrids
            for(int r=0; r<9; r+=3) {
                for(int c=0; c<9; c+=3) {
                    for(int val=1; val<=9; val++) {
                        if (foundUniqueSubLoc(r, c, val, rc)) {
                            update(rc.r, rc.c, val);
                            change = true;
                            numEmpty--;
                        }
                    }
                }
            }
    /**/
        } while (change);

        if (numEmpty == 0) {
            System.out.println("Easy");
        }
        else {
            System.out.println("Not easy");
        }
        printgrid();
    }
}
