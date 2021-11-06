import java.io.*;
import java.util.*;

public class count_partitions_bm {
    FastScanner in;
    PrintWriter out;

    final int mod = 998244353;

    int add(int x, int y) {
        x += y;
        return x >= mod ? (x - mod) : x;
    }

    int sub(int x, int y) {
        x -= y;
        return x < 0 ? (x + mod) : x;
    }

    int mul(int x, int y) {
        return (int) (x * 1L * y % mod);
    }

    void solve() {
        final int MAX_N = (int) 2e5 + 10;
        final int MAX_SIDE = (int) Math.sqrt(MAX_N) + 5;
        // [max side][sum_len] -> ways
        int[][] dp = new int[MAX_SIDE][MAX_N];
        dp[0][0] = 1;
        for (int side = 1; side < MAX_SIDE; side++) {
            for (int sumLen = 0; sumLen < MAX_N; sumLen++) {
                dp[side][sumLen] = dp[side - 1][sumLen];
                if (sumLen >= side) {
                    dp[side][sumLen] = add(dp[side][sumLen], dp[side][sumLen - side]);
                }
            }
        }
        int tc = in.nextInt();
        for (int t = 0; t < tc; t++) {
            int n = in.nextInt();
            int res = 0;
            for (int sqSide = 1; sqSide * sqSide <= n; sqSide++) {
                int more = n - sqSide * sqSide;
                if (more % 2 == 0) {
                    res = add(res, dp[sqSide][more / 2]);
                }
            }
            out.println(res);
        }
    }

    void run() {
        try {
            in = new FastScanner(new File("count_partitions_bm.in"));
            out = new PrintWriter(new File("count_partitions_bm.out"));

            solve();

            out.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    void runIO() {

        in = new FastScanner(System.in);
        out = new PrintWriter(System.out);

        solve();

        out.close();
    }

    class FastScanner {
        BufferedReader br;
        StringTokenizer st;

        public FastScanner(File f) {
            try {
                br = new BufferedReader(new FileReader(f));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }

        public FastScanner(InputStream f) {
            br = new BufferedReader(new InputStreamReader(f));
        }

        String next() {
            while (st == null || !st.hasMoreTokens()) {
                String s = null;
                try {
                    s = br.readLine();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                if (s == null)
                    return null;
                st = new StringTokenizer(s);
            }
            return st.nextToken();
        }

        boolean hasMoreTokens() {
            while (st == null || !st.hasMoreTokens()) {
                String s = null;
                try {
                    s = br.readLine();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                if (s == null)
                    return false;
                st = new StringTokenizer(s);
            }
            return true;
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        long nextLong() {
            return Long.parseLong(next());
        }

        double nextDouble() {
            return Double.parseDouble(next());
        }
    }

    public static void main(String[] args) {
        new count_partitions_bm().runIO();
    }
}