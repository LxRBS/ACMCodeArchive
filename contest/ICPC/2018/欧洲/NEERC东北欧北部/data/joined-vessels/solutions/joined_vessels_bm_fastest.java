import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.StringTokenizer;

public class joined_vessels_bm_fastest {
    FastScanner in;
    PrintWriter out;

    class Stack {
        int[] h;
        int[] pos;
        long[] sumSq;
        int sz;

        Stack(int n) {
            sz = 0;
            h = new int[n];
            pos = new int[n];
            sumSq = new long[n];
        }

        int findFirstLessOrEq(int value) {
            int left = -1, right = sz;
            while (right - left > 1) {
                int mid = (left + right) >> 1;
                if (h[mid] <= value) {
                    right = mid;
                } else {
                    left = mid;
                }
            }
            return left == -1 ? 0 : (pos[left] + 1);
        }

        void set(int needR, int value) {
            while (sz > 0 && h[sz - 1] <= value) {
                sz--;
            }
            h[sz] = value;
            pos[sz] = needR;
            if (sz == 0) {
                sumSq[sz] = (needR + 1) * 1L * value;
            } else {
                sumSq[sz] = sumSq[sz - 1] + (pos[sz] - pos[sz - 1]) * 1L * value;
            }
            sz++;
        }

        long getSum(int r) {
            if (sz == 0) {
                return 0;
            }
            r = Math.min(r, pos[sz - 1]);
            int left = -1, right = sz;
            while (right - left > 1) {
                int mid = (left + right) >> 1;
                if (pos[mid] >= r) {
                    right = mid;
                } else {
                    left = mid;
                }
            }
            return sumSq[right] - (pos[right] - r) * 1L  * h[right];
        }

        long getSum(int needL, int needR) {
            return getSum(needR) - getSum(needL - 1);
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
            Stack st = new Stack(n);
            for (int i = 0; i + 1 < n; i++) {
                int curH = h[i];
                int r = st.findFirstLessOrEq(curH);
                st.set(i, curH);
                for (TestCase t : check[i]) {
                    long valueAtFrom = st.getSum(t.fr, t.fr);
                    int ri = st.findFirstLessOrEq((int) valueAtFrom);
                    res[t.id] = st.getSum(ri, n - 1);
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
        new joined_vessels_bm_fastest().runIO();
    }
}