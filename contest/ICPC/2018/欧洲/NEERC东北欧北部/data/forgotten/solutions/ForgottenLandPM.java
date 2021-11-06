import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

/**
 * @author Pavel Mavrin
 */
public class ForgottenLandPM {

    private static final long MOD = 998244353;

    long res;

    private long dfs(int x, int p) {
        int j = head[x];
        long sMany = 1;
        long sOne = 0;
        while (j >= 0) {
            int y = dst[j];
            if (y != p) {
                long c = dfs(y, x);
                sMany = (sMany * (c + 1)) % MOD;
                sOne = (sOne + c) % MOD;
            }
            j = nx[j];
        }
        sMany = (sMany - 1 - sOne + MOD + MOD) % MOD;
        if (good[x]) {
            res = (res + 1 + sOne + sMany + sMany) % MOD;
            return (1 + sOne + sOne + sMany + sMany) % MOD;
        } else {
            return 0;
        }
    }

    private void solve() throws IOException {
        int n = nextInt();
        int k = nextInt();
        c = new int[n];
        for (int i = 0; i < n; i++) {
            c[i] = nextInt() - 1;
        }
        init(n);
        for (int i = 0; i < n - 1; i++) {
            int x = nextInt() - 1;
            int y = nextInt() - 1;
            addEdge(x, y);
        }
        good = new boolean[n];
        long[] cnt = new long[1 << k];
        for (int m = 0; m < (1 << k); m++) {
            for (int i = 0; i < n; i++) {
                good[i] = (m & (1 << c[i])) > 0;
            }
            res = 0;
            dfs(0, -1);
            cnt[m] = res;
        }
        for (int i = 0; i < k; i++) {
            for (int m = 0; m < (1 << k); m++) {
                if ((m & (1 << i)) > 0) continue;
                cnt[m | (1 << i)] = (cnt[m | (1 << i)] - cnt[m] + MOD) % MOD;
            }
        }
        long ans = 0;
        for (int m = 0; m < (1 << k); m++) {
            int c = Integer.bitCount(m);
            int coef = 0;
            for (int j = 0; j < c; j++) {
                coef += 1 << (k - j);
            }
            ans = (ans + coef * cnt[m]) % MOD;
        }
        out.println(ans);
    }

    int[] c;
    boolean[] good;

    int n, m;
    int[] head;
    int[] nx;
    int[] dst;
    int last;

    void init(int n) {
        this.n = n;
        this.m = (n - 1) * 2;
        last = 0;
        head = new int[n];
        nx = new int[m];
        dst = new int[m];
        Arrays.fill(head, -1);
    }


    void addEdge(int x, int y) {
        nx[last] = head[x];
        dst[last] = y;
        head[x] = last;
        last++;
        nx[last] = head[y];
        dst[last] = x;
        head[y] = last;
        last++;
    }

    // ------------------

    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st;
    PrintWriter out = new PrintWriter(System.out);

    String next() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(br.readLine());
        }
        return st.nextToken();
    }

    int nextInt() throws IOException {
        return Integer.parseInt(next());
    }

    public static void main(String[] args) throws IOException {
        new ForgottenLandPM().run();
    }

    private void run() throws IOException {
        solve();
        out.close();
    }

}
