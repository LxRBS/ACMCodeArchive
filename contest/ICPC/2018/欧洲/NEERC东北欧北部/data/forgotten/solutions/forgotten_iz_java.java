import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class forgotten_iz_java {
    public static void main(String[] args) {
        new forgotten_iz_java().run();
    }

    private final static int MOD = 998_244_353;

    long mul(long a, long b) {
        return a * b % MOD;
    }

    long sum(long a, long b) {
        a += b;
        if (a >= MOD) {
            a -= MOD;
        }
        return a;
    }

    long fct[], ofct[];

    long getC(int n, int k) {
        return mul(fct[n], mul(ofct[k], ofct[n - k]));
    }

    void run() {
        FastScanner in = new FastScanner(System.in);
        int n = in.nextInt();
        int k = in.nextInt();
        int a[] = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = in.nextInt() - 1;
        }
        ArrayList<Integer> e[] = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            e[i] = new ArrayList<>();
        }
        for (int i = 0; i < n - 1; i++) {
            int u = in.nextInt() - 1, v = in.nextInt() - 1;
            e[u].add(v);
            e[v].add(u);
        }
        int q[] = new int[n];
        int vis[] = new int[n];
        int par[] = new int[n];
        int qq = 0;
        q[qq++] = 0;
        vis[0] = 1;
        par[0] = -1;
        for (int i = 0; i < n; i++) {
            for (int to : e[q[i]]) {
                if (vis[to] == 0) {
                    vis[to] = 1;
                    q[qq++] = to;
                    par[to] = q[i];
                }
            }
        }
        int qr[] = new int[n];
        for (int i = 0; i < n; i++) {
            qr[i] = q[n - 1 - i];
        }
        q = qr;

        fct = new long[n + 1];
        ofct = new long[n + 1];
        fct[0] = 1;
        for (int i = 1; i <= n; i++) {
            fct[i] = mul(fct[i - 1], i);
        }
        ofct[n] = BigInteger.valueOf(fct[n]).modInverse(BigInteger.valueOf(MOD)).longValue();
        for (int i = n - 1; i >= 0; i--) {
            ofct[i] = mul(ofct[i + 1], i + 1);
        }
        long b[] = new long[n + 1];
        b[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                b[i] = sum(b[i], mul(b[j], getC(i - 1, j)));
            }
        }

        long res[] = new long[1 << k];
        for (int mask = 1; mask < (1 << k); mask++) {
            int sz[] = new int[n];
            long cnt[] = new long[n + 1];
            for (int v : q) {
                if (((mask >> a[v]) & 1) == 0) continue;
                sz[v]++;
                if (par[v] == -1 || ((mask >> a[par[v]]) & 1) == 0) {
                    for (int i = 1; i <= sz[v]; i++) {
                        cnt[i] = sum(cnt[i], getC(sz[v], i));
                    }
                } else {
                    sz[par[v]] += sz[v];
                }
            }
            for (int i = 1; i <= n; i++) {
                res[mask] = sum(res[mask], mul(cnt[i], b[n - i]));
            }
        }
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < (1 << k); j++) {
                if (((j >> i) & 1) == 1) continue;
                res[j | (1 << i)] = sum(res[j | (1 << i)], MOD - res[j]);
            }
        }
        long ans = 0;
        for (int mask = 0; mask < (1 << k); mask++) {
            int coef = 0, bits = Integer.bitCount(mask);
            for (int i = 0; i < bits; i++) {
                coef += 1 << (k - i);
            }
            ans = sum(ans, mul(coef, res[mask]));
        }
        System.out.println(ans);
    }


    class FastScanner {
        BufferedReader br;
        StringTokenizer st;

        FastScanner() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }
        FastScanner(File f) {
            try {
                br = new BufferedReader(new FileReader(f));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }

        FastScanner(InputStream stream) {
            br = new BufferedReader(new InputStreamReader(stream));
        }

        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        long nextLong() {
            return Long.parseLong(next());
        }
    }

}
