import java.util.HashSet;
import java.util.Scanner;

/**
 * @author: pashka
 */
public class DistinctSubstringsPMbug2 {

    private void run() {
        Scanner in = new Scanner(System.in);
        String s = in.next();

        int n = s.length();

        int[] p = new int[n + 1];
        p[0] = -1;
        for (int i = 2; i <= n; i++) {
            int k = p[i - 1];
            while (k >= 0 && s.charAt(i - 1) != s.charAt(k)) {
                k = p[k];
            }
            p[i] = k + 1;
        }
        int period = n - p[n];
        int k = in.nextInt();

        s = s.substring(0, period);
        n = s.length();

        long res;
        if (k <= 2 * s.length()) {
            res = calcBrute(s, k);
        } else {
            res = calcBrute(s, 2 * s.length());
            res += (long) n * (k - 2 * s.length());
        }
//        System.out.println(calcVeryBrute(s, k));
        System.out.println(res);
    }

    private long calcVeryBrute(String s, int k) {
        String ss = "";
        for (int i = 0; i < k; i++) {
            ss += s.charAt(i % s.length());
        }
        s = ss;
        int n = s.length();
        HashSet<String> set = new HashSet<>();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j <= n; j++) {
                set.add(s.substring(i, j));
            }
        }
        return set.size();
    }

    private long calcBrute(String s, int k) {
        String ss = "";
        for (int i = 0; i < k; i++) {
            ss += s.charAt(i % s.length());
        }
        s = ss;
        int n = s.length();
        int[][] d = new int[n + 1][n + 1];
        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (i == j) continue;
                if (s.charAt(i) == s.charAt(j)) {
                    d[i][j] = d[i + 1][j + 1] + 1;
                }
            }
        }
        long res = 0;
        for (int i = 0; i < n; i++) {
            int max = 0;
            for (int j = 0; j < i; j++) {
                max = Math.max(max, d[i][j]);
            }
            res += (n - i) - max;
        }
        return res;
    }

    public static void main(String[] args) {
        new DistinctSubstringsPMbug2().run();
    }

}
