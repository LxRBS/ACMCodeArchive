import java.util.HashSet;
import java.util.Scanner;

/**
 * @author: pashka
 */
public class DistinctSubstringsPMBrute {

    private void run() {
        Scanner in = new Scanner(System.in);
        String s = in.next();
        int k = in.nextInt();
        int n = s.length();
        long res = calcBrute(s, k);
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
        new DistinctSubstringsPMBrute().run();
    }

}
