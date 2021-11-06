import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

public class CorruptedSort_bm_nlogn {
    FastScanner in;
    PrintWriter out;

    boolean query(int i, int j) {
        boolean swapped = false;
        if (i > j) {
            int tmp = i;
            i = j;
            j = tmp;
            swapped = true;
        }
        out.println((i + 1) + " " + (j + 1));
        out.flush();
        String res = in.next();
        if (res.equals("WIN")) {
            out.close();
            System.exit(0);
        }
        return res.equals("SWAPPED") ^ swapped;
    }

    class Card implements Comparable<Card> {
        int pos;

        public Card(int pos) {
            this.pos = pos;
        }

        @Override
        public int compareTo(Card o) {
            int p1 = pos, p2 = o.pos;
            if (query(p1, p2)) {
                return 1;
            }
            return -1;
        }
    }

    Card[] cards;

    void solve() {
        int n = in.nextInt();
        cards = new Card[n];
        for (int i = 0; i < n; i++) {
            cards[i] = new Card(i);
        }
        while (true) {
            Arrays.sort(cards);

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
        new CorruptedSort_bm_nlogn().runIO();
    }
}