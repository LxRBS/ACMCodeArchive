import java.io.*;
import java.util.*;

public class joined_vessels_bm {
    FastScanner in;
    PrintWriter out;

    // start at        00:17
    // end   at        00:29
    // works at sample 00:34

    class SegmentTree {
        long[] setIt;
        long[] sum;

        SegmentTree(int n) {
            sum = new long[n * 4];
            setIt = new long[n * 4];
        }

        void set(int v, int l, int r, int needL, int needR, int value) {
            if (needL > needR) {
                return;
            }
            if (l == needL && r == needR) {
                sum[v] = (r - l + 1) * 1L * value;
                setIt[v] = value;
                return;
            }
            relax(v, l, r);
            int m = (l + r) >> 1;
            set(v * 2 + 1, l, m, needL, Math.min(m, needR), value);
            set(v * 2 + 2, m + 1, r, Math.max(needL, m + 1), needR, value);
            sum[v] = sum[v * 2 + 1] + sum[v * 2 + 2];
        }

        long getSum(int v, int l, int r, int needL, int needR) {
            if (needL == l && needR == r) {
                return sum[v];
            }
            if (needL > needR) {
                return 0;
            }
            relax(v, l, r);
            int m = (l + r) >> 1;
            return getSum(v * 2 + 1, l, m, needL, Math.min(needR, m)) + getSum(v * 2 + 2, m + 1, r, Math.max(needL, m + 1), needR);
        }

        void updateSum(int v, int l, int r) {
            sum[v] = setIt[v] * 1L * (r - l + 1);
        }

        void relax(int v, int l, int r) {
            if (setIt[v] == -1) {
                return;
            }
            setIt[v * 2 + 1] = setIt[v * 2 + 2] = setIt[v];
            int m = (l + r) >> 1;
            updateSum(v * 2 + 1, l, m);
            updateSum(v * 2 + 2, m + 1, r);
            setIt[v] = -1;
        }
    }

    void solve() {
        int n = in.nextInt();
        int[] h = new int[n - 1];
        for (int i = 0; i + 1 < n; i++) {
            h[i] = in.nextInt();
        }
        int tc = in.nextInt();
        TestCase[] tests = new TestCase[tc];
        for (int t = 0; t < tc; t++) {
            int fr = in.nextInt() - 1;
            int to = in.nextInt() - 1;
            tests[t] = new TestCase(t, fr, to);
        }
        long[] res = new long[tc];
        Arrays.fill(res, -1);
        for (int rev = 0; rev < 2; rev++) {
            List<TestCase>[] check = new List[n - 1];
            for (int i = 0; i < check.length; i++) {
                check[i] = new ArrayList<>();
            }
            for (int i = 0; i < tc; i++) {
                if (tests[i].fr < tests[i].to) {
                    check[tests[i].to - 1].add(tests[i]);
                }
            }
            SegmentTree st = new SegmentTree(n);
            for (int i = 0; i + 1 < n; i++) {
                int curH = h[i];
                int l = -1, r = i;
                while (r - l > 1) {
                    int mid = (l + r) >> 1;
                    if (st.getSum(0, 0, n - 1, mid, mid) <= curH) {
                        r = mid;
                    } else {
                        l = mid;
                    }
                }
                st.set(0, 0, n - 1, r, i, curH);
                for (TestCase t : check[i]) {
                    long valueAtFrom = st.getSum(0, 0, n - 1, t.fr, t.fr);
                    int le = -1, ri = t.fr;
                    while (ri - le > 1) {
                        int mi = (le + ri) >> 1;
                        if (st.getSum(0, 0, n - 1, mi, mi) == valueAtFrom) {
                            ri = mi;
                        } else {
                            le = mi;
                        }
                    }
                    res[t.id] = st.getSum(0, 0, n - 1, ri, n - 1);
                }
            }

            for (int i = 0, j = h.length - 1; i < j; i++, j--) {
                int tmp = h[i];
                h[i] = h[j];
                h[j] = tmp;
            }
            for (TestCase t : tests) {
                t.fr = n - t.fr - 1;
                t.to = n - t.to - 1;
            }
        }
        for (long z : res) {
            out.println(z);
        }
    }

    class TestCase {
        int id, fr, to;

        public TestCase(int id, int fr, int to) {
            this.id = id;
            this.fr = fr;
            this.to = to;
        }
    }

    void run() {
        try {
            in = new FastScanner(new File("joined_vessels_bm.in"));
            out = new PrintWriter(new File("joined_vessels_bm.out"));

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
        new joined_vessels_bm().runIO();
    }
}