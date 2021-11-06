import java.util.*;

public class OverTheHill1_John
{
    public static final int MAXSIZE = 10;

    public static int[][] m = new int[MAXSIZE][MAXSIZE];

    public static char[] alphabet = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                       'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                       'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3',
                       '4', '5', '6', '7', '8', '9', ' '};

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

    public static int[] encrypt(int[] word, int start, int[][] m, int n)
    {
        int[] ans = new int[n];
        for(int r=0; r<n; r++) {
            ans[r] = 0;
            for(int c=0; c<n; c++) {
                ans[r] += m[r][c]*word[start+c];
            }
            ans[r] %= 37;
        }
        return ans;
    }

    public static void main(String [] args)
    {
        Scanner in = new Scanner(System.in);
        int n;

        n = in.nextInt();
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                m[i][j] = in.nextInt();
            }
        }
        String s;
        in.nextLine();
        s = in.nextLine();
        while (s.length()%n != 0)
            s += ' ';
        int[] vals = convert(s);
        String news = "";
        for(int i=0; i<s.length(); i+=n) {
            int[] encrypted = encrypt(vals, i, m, n);
            for(int j=0; j<n; j++)
                news += alphabet[encrypted[j]];
        }
        System.out.println(news);
    }
}
