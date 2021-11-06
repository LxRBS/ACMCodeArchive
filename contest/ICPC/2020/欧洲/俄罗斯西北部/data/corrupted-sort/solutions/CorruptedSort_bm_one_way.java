import java.io.*;
import java.util.Random;
import java.util.StringTokenizer;

public class CorruptedSort_bm_one_way {
    FastScanner in;
    PrintWriter out;

    void query(int i, int j) {
        out.println((i + 1) + " " + (j + 1));
        out.flush();
        String res = in.next();
        if (res == null || res.equals("WIN")) {
            out.close();
            System.exit(0);
        }
    }

    void solve() {
        int n = in.nextInt();
        while (true) {
            for (int i = 0; i + 1 < n; i++) {
                query(i, i + 1);
            }
        }
    }

    void run() {
        try {
            in = new FastScanner(new File("CorruptedSort_bm_ok.in"));
            out = new PrintWriter(new File("CorruptedSort_bm_ok.out"));

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
        new CorruptedSort_bm_one_way().runIO();
    }
}