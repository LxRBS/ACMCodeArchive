import java.util.*;

public class OverTheHill2_John
{
    public static final int MAXSIZE = 10;
    public static final int BIG = 37*37;

    public static int[][] m = new int[MAXSIZE][MAXSIZE];

    public static char[] alphabet = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                       'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                       'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3',
                       '4', '5', '6', '7', '8', '9', ' '};

    public static int[] inverse = {-1,  1, 19, 25, 28, 15, 31, 16, 14, 33,
                       26, 27, 34, 20,  8,  5,  7, 24, 35,  2,
                       13, 30, 32, 29, 17,  3, 10, 11,  4, 23,
                       21,  6, 22,  9, 12, 18, 36};

    public static String plain, cipher;

    public static int[] convert(String s)
    {
        int[] ans = new int[s.length()];
        for(int i=0; i<s.length(); i++) {
            if (s.charAt(i) == ' ')
                ans[i] = 36;
            else if (s.charAt(i) <= '9')
                ans[i] = (s.charAt(i) - '0') + 26;
            else
                ans[i] = (s.charAt(i) - 'A');
        }
        return ans;
    }

    public static int calcFactor(int[] a1, int[] a2, int n)
    {
        int i=0;
        while (i<n && a1[i] == 0 && a2[i] == 0)
            i++;
        if (i == n || a1[i] == 0 || a2[i] == 0)
            return -1;
        int factor = (a2[i]*inverse[a1[i]] + BIG)%37;
        for( ; i<n; i++) {
            if ((a2[i]*inverse[a1[i]] + BIG)%37 != factor)
                return -1;
        }
        return factor;
    }

    public static boolean applyFactor(int[] a1, int[] a2, int factor, int n)
    {
        for(int i=0; i<n; i++) {
            if ((a1[i]*factor+BIG)%37 != a2[i])
                return false;
        }
        return true;
    }

    public static boolean allAs(String s)
    {
        for(int i=0; i<s.length(); i++)
            if (s.charAt(i) != 'A')
                return false;
        return true;
    }

    public static boolean process(int n)
    {
        String newPlain = "", newCipher = "";
        for(int i=0; i<plain.length(); i+= n) {
            String s1 = plain.substring(i, i+n);
            String s2 = cipher.substring(i, i+n);
            boolean s1AllA = allAs(s1);
            boolean s2AllA = allAs(s2);
            if (s1AllA && !s2AllA)         // special case - no solution possible
                return false;
            if (s1AllA && s2AllA)           // this string of no use
                continue;
            int[] v1 = convert(s1);
            int[] v2 = convert(s2);
            boolean use = true;
            for(int j=i+n; j<plain.length(); j+=n) {
                String s3 = plain.substring(j, j+n);
                String s4 = cipher.substring(j, j+n);
                int[] v3 = convert(s3);
                int[] v4 = convert(s4);
                int factor = calcFactor(v1, v3, n);
                if (factor != -1) {
                    if (!applyFactor(v2, v4, factor, n))
                        return false;                   // no solution possible
                    use = false;
                    break;
                }
            }
            if (use) {
                newPlain += s1;
                newCipher += s2;
            }
        }
        plain = newPlain;
        cipher = newCipher;
        return true;
    }

    public static boolean solve(String[] rows, String[] cols, int[][] b)
    {
        int n = rows[0].length();
        int[][] a = new int[n][n];

        for(int r=0; r<n; r++) {
            int[] vals = convert(rows[r]);
            for(int c=0; c<n; c++)
                a[r][c] = vals[c];
        }
        for(int r=0; r<n; r++) {
            int[] vals = convert(cols[r]);
            for(int c=0; c<n; c++)
                b[r][c] = vals[c];
        }
                                            // forward sub
        for(int r=0; r<n; r++) {
            int i=r;
            while(i < n && a[i][r] == 0)
                i++;
            if (i == n)
                return false;
            if (i != r) {
                for(int j=0; j<n; j++) {
                    int tmp = a[r][j];
                    a[r][j] = a[i][j];
                    a[i][j] = tmp;
                    tmp = b[r][j];
                    b[r][j] = b[i][j];
                    b[i][j] = tmp;
                }
            }
            int inv = inverse[a[r][r]];
            for(int j=0; j<n; j++) {
                a[r][j] = (a[r][j]*inv)%37;
                b[r][j] = (b[r][j]*inv)%37;
            }
            for(int k=r+1; k<n; k++) {
                int factor = a[k][r];
                for(int j=0; j<n; j++) {
                    a[k][j] = (a[k][j] - a[r][j]*factor + BIG)%37;
                    b[k][j] = (b[k][j] - b[r][j]*factor + BIG)%37;
                }
            }
        }
                                                // backwards sub
        for(int r=n-1; r>0; r--) {
            for(int i=r-1; i>=0; i--) {
                int factor = a[i][r];
                for(int j=0; j<n; j++) {
                    a[i][j] = (a[i][j] - a[r][j]*factor + BIG)%37;
                    b[i][j] = (b[i][j] - b[r][j]*factor + BIG)%37;
                }
            }
        }
        return true;
    }

    public static void main(String [] args)
    {
        int n;
        Scanner in = new Scanner(System.in);

        n = in.nextInt();
        in.nextLine();
        plain = in.nextLine();
        while (plain.length()%n != 0)
            plain += ' ';
        cipher = in.nextLine();
        if (!process(n)) {
            System.out.println("no solution");
            System.exit(0);
        }
        int len = cipher.length();
        if (len < n*n) {
            System.out.println("too many solutions");
            System.exit(0);
        }
        String[] rows = new String[n];
        String[] cols = new String[n];
        int[][] mat = new int[MAXSIZE][MAXSIZE];
        int[][] save = new int[MAXSIZE][MAXSIZE];
        boolean solFound = false;
                                                // solve each set, checking if
                                                //   results are the same
        boolean ok = true;
        for(int start=0; start < len; start+=n*n) {
            if (len-start < n*n)
                start = len-n*n;
            for(int i=0; i<n; i++) {
                rows[i] = plain.substring(start+i*n, start+i*n+n);
                cols[i] = cipher.substring(start+i*n, start+i*n+n);
            }
            if (solve(rows, cols, mat)) {
                if (!solFound) {
                    for(int r=0; r<n; r++)
                        for(int c=0; c<n; c++)
                            save[r][c] = mat[r][c];
                    solFound = true;
                }
                else {
                    for(int r=0; r<n; r++)
                        for(int c=0; c<n; c++) {
                            if (mat[r][c] != save[r][c])
                                ok = false;
                        }
                }
            }
            if (!ok)
                break;
        }
        if (ok) {
            if (solFound) {
                for(int c=0; c<n; c++) {
                    System.out.print(save[0][c]);
                    for(int r=1; r<n; r++)
                        System.out.print(" " + save[r][c]);
                    System.out.println();
                }
            }
            else
                System.out.println("too many solutions");
        }
        else
            System.out.println("no solution");
    }
}
