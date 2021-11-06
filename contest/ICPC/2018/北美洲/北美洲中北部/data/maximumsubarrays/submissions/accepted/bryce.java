import java.util.*;

public class bryce {

    static long INF = 1000000000000000000L;

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n, k;
        n = in.nextInt();
        k = in.nextInt();

        long[] A = new long[n];
        for (int i = 0; i < n; ++i) {
            A[i] = in.nextInt();
        }

        long[][] Best = new long[n][k+1];
        for (long[] arr : Best) {
            Arrays.fill(arr, -INF);
        }
        long[][] BestInclude = new long[n][k+1];
        for (long[] arr : BestInclude) {
            Arrays.fill(arr, -INF);
        }

        for (int i = 0; i < n; ++i) {
            Best[i][0] = 0;
        }
        Best[0][1] = BestInclude[0][1] = A[0];

        for (int i = 1; i < n; ++i) {
            for (int j = 1; j <= k; ++j) {
                BestInclude[i][j] = Math.max(BestInclude[i-1][j], Best[i-1][j-1]) + A[i];
                Best[i][j] = Math.max(Best[i-1][j], BestInclude[i][j]);
            }
        }

        System.out.println(Best[n-1][k]);
    }

}
