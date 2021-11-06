import java.util.Scanner;

/**
 * @author: pashka
 */
public class KeyboardConsensusPMwa2 {

    void run() {
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

        int[] ra = rev(pa);
        int[] rb = rev(pb);

        int[] a = new int[n];
        for (int i = 0; i < n; i++) {
            a[n - 1 - ra[i]] = n - 1 - rb[i];
        }

        int[] st = new int[n];
        int m = 0;
        for (int i = 0; i < n; i++) {
            while (m > 0 && a[i] > a[st[m - 1]]) m--;
            st[m++] = i;
        }

        int k = n - 1 - st[m / 2];

        for (int i = 0; i < n; i++) {
            if (ra[i] == k) {
                System.out.println(i + 1);
                break;
            }
        }
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
        new KeyboardConsensusPMwa2().run();
    }

}
