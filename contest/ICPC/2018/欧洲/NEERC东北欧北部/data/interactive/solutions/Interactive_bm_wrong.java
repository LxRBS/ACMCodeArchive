import java.io.*;
import java.util.*;

public class Interactive_bm_wrong {
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

    int[][] find(List<Integer> ids) {
        if (ids.size() == 0) {
            return new int[][]{};
        }
        int[] ask = new int[ids.size() * 2];
        for (int i = 0; i < ids.size(); i++) {
            ask[i * 2] = ask[i * 2 + 1] = ids.get(i);
        }
        int[] r = ask(ask);
        int[][] result = new int[ids.size()][];
        for (int i = 0; i < r.length; ) {
            int j = i + 1;
            while (r[i] != r[j]) {
                j++;
            }
            result[i] = Arrays.copyOfRange(r, i, j);
            i += (j - i) * 2;
        }
        return result;
    }

    void solve() {
        int n = in.nextInt();
        int[][] res = new int[n][];
        if (n % 2 == 1) {
            res[n - 1] = ask(new int[]{n - 1});
        }
        List<Integer> first = new ArrayList<>(), second = new ArrayList<>();
        for (int i = 0; i + 1 < n; i += 2) {
            first.add(i);
            second.add(i + 1);
        }
        for (List<Integer> check : new List[]{first, second}) {
            int[][] got = find(check);
            for (int i = 0; i < got.length; i++) {
                res[check.get(i)] = got[i];
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
        new Interactive_bm_wrong().runIO();
    }
}