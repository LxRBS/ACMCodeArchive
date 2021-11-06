import java.util.Arrays;
import java.util.Scanner;

/**
 * @author: pashka
 */
public class KeyboardConsensusPMwa {

    private void run() {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int[] pa = new int[n];
        for (int i = 0; i < n; i++) {
            pa[i] = in.nextInt() - 1;
        }
        int[] pb = new int[n];
        for (int i = 0; i < n; i++) {
            pb[i] = in.nextInt() - 1;
        }
        boolean[] z = new boolean[n];
        int res = solve(pa, pb, z);

        System.out.println(res + 1);
    }

    private int solve(int[] pa, int[] pb, boolean[] z) {
        int ia = pa.length - 1;
        int ib = pb.length - 1;
        int n = 0;
        for (int i = 0; i < z.length; i++) if (!z[i]) n++;
        for (int i = 0; i < n - 1; i++) {
            if (i % 2 == 0) {
                while (z[pa[ia]]) ia--;
                z[pa[ia]] = true;
            } else {
                while (z[pb[ib]]) ib--;
                z[pb[ib]] = true;
            }
        }
        for (int i = 0; i < z.length; i++) {
            if (!z[i]) return i;
        }
        return -1;
    }

    private int[] rev(int[] p) {
        int n = p.length;
        int[] res = new int[n];
        for (int i = 0; i < n; i++) {
            res[p[i]] = i;
        }
        return res;
    }

    public static void main(String[] args) {
        new KeyboardConsensusPMwa().run();
    }

}
