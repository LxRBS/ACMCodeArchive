import java.util.*;


public class OreJohn
{
    public static final int MAXCARS = 50;
    public static final int MAXHOPPERS = 100;

    public static int[] a = new int[MAXCARS];
    public static int[] b = new int[MAXCARS];
    public static int[] t = new int[MAXHOPPERS];

    class Node {
        public long iA, iB, iT;

        public Node(long a, long b, long t)
        {
            iA = a;
            iB = b;
            iT = t;
        }
    }

    static class GCD
    {
        public long g, x, y;
    }

    public static Queue<Node> list = new LinkedList<>();

    public static void gcd(long a, long b, GCD ans)
    {
        if (b == 0) {
            ans.x = 1;
            ans.y = 0;
            ans.g = a;
            return;
        }
        gcd(b, a % b, ans);
        long sav = ans.x;
        ans.x = ans.y;
        ans.y = sav - ans.y* (a / b);
    }
/*
    public static boolean find_any_solution(long a, long b, long c, GCD ginfo)
    {
        gcd(abs(a), abs(b), ginfo);
        long g = ginfo.g;
        if (c % g) {
            return false;
        }

        ginfo.x *= c / g;
        ginfo.y *= c / g;
        if (a < 0) ginfo.x *= -1;
        if (b < 0) ginfo.y *= -1;
        return true;
    }
/**/
     public static boolean possible(long target, long totA, long totB, long x, long y, long g) {
        if (target % g != 0) {
            return false;
        }
        x *= target / g;
        y *= target / g;
        if (x < 0) {
            long d = y/(totA/g);
            x += d*totB/g;
            y -= d*totA/g;
        }
        else if (y < 0) {
            long d = x/(totB/g);
            y += d*totA/g;
            x -= d*totB/g;
        }
    //cout << totA << '*' <<  x << '+' << totB << '*' << y << '=' << target << endl;
        return (x >= 0 && y >= 0);
     }

    public static void main(String [] args)
    {
        int nA, nB, nT;
        long totA = 0, totB = 0;
        Scanner in = new Scanner(System.in);

        nA = in.nextInt();
        nB = in.nextInt();
        nT = in.nextInt();
        for(int i=0; i<nA; i++) {
            a[i] = in.nextInt();
            totA += a[i];
        }
        for(int i=0; i<nB; i++) {
            b[i] = in.nextInt();
            totB += b[i];
        }
        for(int i=0; i<nT; i++)
            t[i] = in.nextInt();
        long x, y, g;
        GCD ans = new GCD();
        gcd(totA, totB, ans);    // solve totA*x + totB*y = g
        x = ans.x;                    // g = gcd(totA, totB)
        y = ans.y;
        g = ans.g;

    //cout << x << ',' << y << endl;
        boolean [][] startconfig = new boolean[nA][nB];
        boolean [][] nextconfig = new boolean[nA][nB];
                                // startcondig[i][j] = start config of a[i] and b[j] positioned
                                //    over current train car possible
        for(int i=0; i<nA; i++)
            for(int j=0; j<nB; j++)
                startconfig[i][j] = false;
        startconfig[0][0] = true;
        int iT = 0;
        while (iT < nT) {
            for(int i=0; i<nA; i++)
                for(int j=0; j<nB; j++)
                    nextconfig[i][j] = false;
            long numLeft = nA*nB;
            for(int i=0; i<nA; i++) {
                for(int j=0; j<nB; j++) {
                    if (!startconfig[i][j])
                        continue;
    //cout << "start: " << a[i] << ' ' << b[j] << ' ' << t[iT] << endl;
                    long target = t[iT];
                    for(int ii=i; ii<i+nA; ii++) {
                        long modifiedTarget = target;
                        for(int jj=j; jj<j+nB; jj++) {
                            if (!nextconfig[ii%nA][jj%nB] && possible(modifiedTarget, totA, totB, x, y, g)) {
    //cout << "  through A car " << (ii+nA-1)%nA << " and B car " << (jj+nB-1)%nB << endl;
                                nextconfig[ii%nA][jj%nB] = true;
                                numLeft--;
                            }
                            modifiedTarget -= b[jj%nB];
                        }
                        if (numLeft == 0)
                            break;
                        target -= a[ii%nA];
                    }
                    if (numLeft == 0)
                        break;
                }
                if (numLeft == 0)
                    break;
            }
    //cout << iT << ' ' << numLeft << endl;
            if (numLeft == nA*nB)
                break;
            for(int i=0; i<nA; i++)
                for(int j=0; j<nB; j++)
                    startconfig[i][j] = nextconfig[i][j];
            iT++;
    /*
    if (iT == nT-1) {
    for(int i=0; i<nA; i++) {
    for(int j=0; j<nB; j++)
    cout << startconfig[i][j];
    cout << endl;
    }
    }
    /**/
        }
        if (iT == nT) {
            System.out.println("Yes");
        }
        else {
            System.out.println("No");
        }
    }
}
