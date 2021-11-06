import java.util.Scanner;

public class Ore_bobk_java {
    private long
        bzx, bzy,
        gcd,
        gcdA, gcdB;
    private boolean[][][]
        cells;
    private int
        nA, nB,
        dest;
    int[]
        aCap, bCap, tCap,
        partialB;

    private int[] extEuclid(int a, int b) {
        int
            oldr = a, r = b,
            olds = 1, s = 0,
            oldt = 0, t = 1,
            q,
            tmp;

        while (r != 0) {
            q = oldr / r;

            tmp = r;
            r = oldr - q * r;
            oldr = tmp;

            tmp = s;
            s = olds - q * s;
            olds = tmp;

            tmp = t;
            t = oldt - q * t;
            oldt = tmp;
        }

        return new int[]{oldr, olds, oldt};
    }

    private boolean isNNLinearCombination(long n) {
        long
            x, y,
            m;

        if (n % gcd != 0)
            return false;

        x = (bzx * n) / gcd;
        y = (bzy * n) / gcd;

        if (x < 0) {
            m = y / gcdA;
            y -= m * gcdA;
            x += m * gcdB;
        }

        if (y < 0) {
            m = x / gcdB;
            x -= m * gcdB;
            y += m * gcdA;
        }

        return x >= 0 && y >= 0;
    }

    private void fillPlane(int a, int b, int t) {
        int
            partialA = 0;

        //
        // set up the partial B array
        //

        partialB[0] = 0;
        for (int bb=0;bb<nB-1;bb++)
            partialB[bb+1] = partialB[bb] + bCap[(b+bb) % nB];

        for (int aa=0;aa<nA;aa++) {
            for (int bb=0;bb<nB;bb++) {
                if (!cells[dest][(a+aa) % nA][(b+bb) % nB])
                    cells[dest][(a+aa) % nA][(b+bb) % nB] = isNNLinearCombination(tCap[t]-partialA-partialB[bb]);
            }
            partialA += aCap[(a+aa) % nA];
        }
    }

    public boolean solve(Scanner in) {
        int
            aSum, bSum,
            nT,
            source;
        boolean
            acceptable = false;

        //
        // get the inputs
        //

        nA = in.nextInt();
        nB = in.nextInt();
        nT = in.nextInt();

        aCap = new int[nA];
        bCap = new int[nB];
        tCap = new int[nT];

        for (int i=0;i<nA;i++)
            aCap[i] = in.nextInt();

        for (int i=0;i<nB;i++)
            bCap[i] = in.nextInt();

        for (int i = 0; i< nT; i++)
            tCap[i] = in.nextInt();

        //
        // get sums and calculate Bezout coefficients
        //

        aSum = 0;
        for (int i=0;i<nA;i++)
            aSum += aCap[i];

        bSum = 0;
        for (int i=0;i<nB;i++)
            bSum += bCap[i];

        int[]
            tmp = extEuclid(aSum, bSum);

        gcd = tmp[0];
        bzx = tmp[1];
        bzy = tmp[2];

        gcdA = aSum / gcd;
        gcdB = bSum / gcd;

        //
        // create the planes, fill the first destination plane
        //

        cells = new boolean[2][nA][nB];

        for (int r=0;r<nA;r++)
            for (int c=0;c<nB;c++)
                cells[1][r][c] = false;

        source = 0;
        dest = 1;

        partialB = new int[nB];

        //
        // fill the first plane
        //

        fillPlane(0, 0, 0);

        //
        // fill the remaining planes
        //

        for (int t = 1; t< nT; t++) {
            //
            // flip source and dest planes
            //

            source = 1 - source;
            dest = 1 - dest;

            //
            // clear the dest plane
            //

            for (int r=0;r<nA;r++)
                for (int c=0;c<nB;c++)
                    cells[dest][r][c] = false;

            //
            // scan the source plane for good spots; use those to look for next layer of good spots
            //

            for (int r=0;r<nA;r++)
                for (int c=0;c<nB;c++)
                    if (cells[source][r][c])
                        fillPlane(r, c, t);
        }

        //
        // scan final dest plane for any good spot
        //

        for (int r=0;r<nA;r++)
            for (int c=0;c<nB;c++)
                if (cells[dest][r][c]) {
                    acceptable = true;
                    break;
                }

        return acceptable;
    }

    public static void main(String[] args) {
	// write your code here
        Scanner
            in = new Scanner(System.in);

        Ore_bobk_java
            solver = new Ore_bobk_java();

        if (solver.solve(in))
            System.out.println("Yes");
        else
            System.out.println("No");
    }
}
