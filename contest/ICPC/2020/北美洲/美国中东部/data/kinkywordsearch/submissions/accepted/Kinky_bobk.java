import java.util.Scanner;

public class Kinky_bobk {
    private static final int[]
        dR = {-1, -1, -1, 0, 1, 1, 1, 0},
        dC = {-1, 0, 1, 1, 1, 0, -1, -1};

    private int
        nRows, nCols,
        nKinks2,
        matchLen;

    private int encode(int r,int c,int k,int p,int d) {
        return r + nRows * (c + nCols * (k + nKinks2 * (p + matchLen * d)));
    }

    public boolean solve(Scanner in) {
        int
            nKinks,
            nCells,
            kLim;
        char[][]
            grid;
        String
            match;
        boolean
            acceptable = false;

        //
        // get inputs
        //

        nRows = in.nextInt();
        nCols = in.nextInt();

        grid = new char[nRows][nCols];

        for (int r=0;r<nRows;r++)
            for (int c=0;c<nCols;c++)
                grid[r][c] = in.next().charAt(0);

        nKinks = in.nextInt();

        match = in.next();

        //
        // some helper values
        //

        nKinks2 = nKinks + 2;
        matchLen = match.length();

        //
        // if this is true, then there are more kinks than we can possibly do, bail out
        //

        if (nKinks > 0 && nKinks > matchLen - 2)
            return false;

        //
        // create the array of flags
        //

        nCells = nRows * nCols * nKinks2 * matchLen * 8;

        boolean[]
            cells = new boolean[nCells];

        for (int i=0;i<nCells;i++)
            cells[i] = false;

        //
        // do the base cases... end of string
        //

        for (int r=0;r<nRows;r++)
            for (int c=0;c<nCols;c++)
                for (int d=0;d<8;d++)
                    if (grid[r][c] == match.charAt(matchLen-1))
                        cells[encode(r,c,0,matchLen-1,d)] = true;

        //
        // fill in the rest of the DP table
        //

        for (int pos=matchLen - 2;pos>=0;pos--) {
            //
            // first, the zero-kink plane
            //
            for (int r=0;r<nRows;r++)
                for (int c=0;c<nCols;c++)
                    if (grid[r][c] == match.charAt(pos))
                        for (int d=0;d<8;d++) {
                            int
                                r2 = r + dR[d],
                                c2 = c + dC[d];
                            if (r2 >= 0 && r2 < nRows && c2 >= 0 && c2 < nCols &&
                                cells[encode(r2,c2,0,pos+1,d)])
                                cells[encode(r,c,0,pos,d)] = true;
                        }

            //
            // next, the other planes of kinkiness
            //
            if (pos < matchLen - 2) {
                kLim = matchLen - pos;
                if (nKinks2 < kLim)
                    kLim = nKinks2;
                for (int k=1;k<kLim;k++)
                    for (int r=0;r<nRows;r++)
                        for (int c=0;c<nCols;c++)
                            if (grid[r][c] == match.charAt(pos))
                                for (int d1=0;d1<8;d1++) {
                                    int
                                        r2 = r + dR[d1],
                                        c2 = c + dC[d1];
                                    if (r2 >= 0 && r2 < nRows && c2 >= 0 && c2 < nCols)
                                        for (int d2=0;d2<8;d2++) {
                                            if (d1 != d2 && cells[encode(r2,c2,k-1,pos+1,d2)])
                                                cells[encode(r,c,k,pos,d1)] = true;
                                            if (d1 == d2 && cells[encode(r2,c2,k,pos+1,d2)])
                                                cells[encode(r,c,k,pos,d1)] = true;
                                        }
                                }
            }
        }

        //
        // finally, scan the pos == 0 plane for any raised flags
        //

        for (int r=0;r<nRows;r++)
            for (int c=0;c<nCols;c++)
                for (int d=0;d<8;d++)
                    if (cells[encode(r, c, nKinks, 0, d)]) {
                        acceptable = true;
                        break;
                    }

        return acceptable;
    }

    public static void main(String[] args) {
	// write your code here
        Scanner in = new Scanner(System.in);
        Kinky_bobk kinkajou = new Kinky_bobk();
        if (kinkajou.solve(in))
            System.out.println("YES");
        else
            System.out.println("NO");
    }
}
