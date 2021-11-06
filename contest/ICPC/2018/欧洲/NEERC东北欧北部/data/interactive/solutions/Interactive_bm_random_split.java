import java.io.*;
import java.util.*;

public class Interactive_bm_random_split {
    FastScanner in;
    PrintWriter out;

    int[] ask(int[] ids) {
        out.print("? " + ids.length);
        for (int i : ids) {
            out.print(" " + (1 + i));
        }
        out.println();
        out.flush();
        int len = in.nextInt();
        int[] res = new int[len];
        for (int i = 0; i < len; i++) {
            res[i] = in.nextInt();
        }
        return res;
    }

    void solve() {
        int n = in.nextInt();
        int[][] res = new int[n][];
        if (n <= 20) {
            for (int i = 0; i < n; i++) {
                res[i] = ask(new int[]{i});
            }
        } else {
            Random rnd = new Random(123);
            final int MAGIC = 10;
            int[] splitBy = new int[MAGIC - 1];
            for (int i = 0; i < splitBy.length; i++) {
                splitBy[i] = rnd.nextInt(n);
            }
            int[] splitter = ask(splitBy);
            for (int start = 0; start < MAGIC; start++) {
                List<Integer> check = new ArrayList<>();
                for (int i = start; i < n; i += MAGIC) {
                    check.add(i);
                    if (i + MAGIC < n) {
                        for (int v : splitBy) {
                            check.add(v);
                        }
                    }
                }
                int[] converted = ask(check.stream().mapToInt(Integer::intValue).toArray());
                int it = 0;
                for (int i = start; i < n; i += MAGIC) {
                    for (int startOfSplit = it + 1; startOfSplit <= converted.length; startOfSplit++) {
                        boolean ok = startOfSplit + splitter.length <= converted.length;
                        if (ok) {
                            for (int j = 0; j < splitter.length; j++) {
                                if (splitter[j] != converted[startOfSplit + j]) {
                                    ok = false;
                                    break;
                                }
                            }
                        }
                        if (ok || startOfSplit == converted.length) {
                            res[i] = Arrays.copyOfRange(converted, it, startOfSplit);
                            it = startOfSplit + splitter.length;
                            break;
                        }
                    }
                }
            }
        }
        out.print("!");
        for (int[] a : res) {
            out.print(" " + a.length);
            for (int val : a) {
                out.print(" " + val);
            }
        }
        out.println();
    }

    void run() {
        try {
            in = new FastScanner(new File("Interactive_bm.in"));
            out = new PrintWriter(new File("Interactive_bm.out"));

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
        new Interactive_bm_random_split().runIO();
    }
}