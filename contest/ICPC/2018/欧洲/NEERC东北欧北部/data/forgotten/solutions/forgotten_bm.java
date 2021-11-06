import java.io.*;
import java.util.*;

public class forgotten_bm {
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

    int[] color;
    List<Integer>[] g;
    int[] dp;
    int[] pow2;

    void count(int mask, int size) {
        dp[mask] = add(dp[mask], sub(pow2[size], 1));
    }

    int go(int v, int p, int mask) {
        boolean inside = ((1 << color[v]) & mask) != 0;
        int curSize = inside ? 1 : 0;
        for (int to : g[v]) {
            if (to == p) {
                continue;
            }
            int chSize = go(to, v, mask);
            if (inside) {
                curSize += chSize;
            } else {
                count(mask, chSize);
            }
        }
        if (p == -1) {
            count(mask, curSize);
        }
        return curSize;
    }

    void solve() {
        int n = in.nextInt();
        int k = in.nextInt();
        color = new int[n];
        for (int i = 0; i < n; i++) {
            color[i] = in.nextInt() - 1;
        }
        g = new List[n];
        for (int i = 0; i < n; i++) {
            g[i] = new ArrayList<>();
        }
        for (int i = 0; i + 1 < n; i++) {
            int fr = in.nextInt() - 1;
            int to = in.nextInt() - 1;
            g[fr].add(to);
            g[to].add(fr);
        }
        dp = new int[1 << k];
        pow2 = new int[n + 1];
        pow2[0] = 1;
        for (int i = 1; i < pow2.length; i++) {
            pow2[i] = mul(pow2[i - 1], 2);
        }
        int res = 0;
        for (int mask = 1; mask < 1 << k; mask++) {
            go(0, -1, mask);
            for (int subMask = 1; subMask < mask; subMask++) {
                if ((mask & subMask) == subMask) {
                    dp[mask] = sub(dp[mask], dp[subMask]);
                }
            }
            int colors = Integer.bitCount(mask);
            for (int i = 0; i < colors; i++) {
                res = add(res, mul(dp[mask], (1 << (k - i))));
            }
        }
        out.println(res);
    }

    void run() {
        try {
            in = new FastScanner(new File("forgotten_bm.in"));
            out = new PrintWriter(new File("forgotten_bm.out"));

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
        new forgotten_bm().runIO();
    }
}