import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class heroes_of_coin_flip_av_full_bruteforce {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        FastScanner in = new FastScanner(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        CoinFlipTournament solver = new CoinFlipTournament();
        solver.solve(1, in, out);
        out.close();
    }

    static class CoinFlipTournament {
        boolean[] used;
        int[] order;
        double result = 0, count = 0;
        int k;

        void go(int pos) {
            if (pos == order.length) {
                int[][] parts = new int[k + 1][];
                for (int i = 0; i <= k; i++) {
                    parts[i] = new int[1 << (k - i)];
                }
                int[] seen = new int[1 << k];
                for (int mask = 0; mask < 1 << order.length; mask++) {
                    int ptr = 0;
                    for (int stage = 0; stage < k; stage++) {
                        for (int i = 0; i < 1 << (k - 1 - stage); i++) {
                            if (stage == 0) {
                                parts[stage][2 * i] = 2 * i;
                                parts[stage][2 * i + 1] = 2 * i + 1;
                            }
                            if ((mask & (1 << ptr)) != 0) {
                                parts[stage + 1][i] = parts[stage][2 * i];
                            } else {
                                parts[stage + 1][i] = parts[stage][2 * i + 1];
                            }
                        }
                    }
                    Arrays.fill(seen, -1);
                    count++;
                    for (int i = 0; i < order.length; i++) {
                        int stage = 31 - Integer.numberOfLeadingZeros(order[i]);
                        int match = order[i] - (1 << stage);
                        stage = (k - 1 - stage);
                        int p1 = parts[stage][2 * match], p2 = parts[stage][2 * match + 1];
                        if (seen[p1] > stage || seen[p2] > stage) {
                            // nothing
                        } else {
                            result++;
                        }
                        seen[p1] = Math.max(seen[p1], stage);
                        seen[p2] = Math.max(seen[p2], stage);
                    }
                }
                return;
            }
            for (int i = 1; i < used.length; i++) {
                if (!used[i]) {
                    order[pos] = i;
                    used[i] = true;
                    go(pos + 1);
                    used[i] = false;
                }
            }
        }

        public void solve(int testNumber, FastScanner in, PrintWriter out) {
            k = in.nextInt();
            int m = in.nextInt();
            order = new int[(1 << k) - 1];
            used = new boolean[(1 << k)];
            for (int i = 0; i < m; i++) {
                int st = k - in.nextInt(), ma = in.nextInt() - 1;
                order[i] = (1 << st) + ma;
                used[order[i]] = true;
            }
            go(m);
            out.println(result / count);
        }

        class Match {
            int stage, id;

            public Match(int stage, int id) {
                this.stage = stage;
                this.id = id;
            }
        }
    }

    static class FastScanner {
        public BufferedReader br;
        public StringTokenizer st;

        public FastScanner(InputStream in) {
            br = new BufferedReader(new InputStreamReader(in));
        }

        public FastScanner(String fileName) {
            try {
                br = new BufferedReader(new FileReader(fileName));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

        public String next() {
            while (st == null || !st.hasMoreElements()) {
                String line = null;
                try {
                    line = br.readLine();
                } catch (IOException e) {
                }
                st = new StringTokenizer(line);
            }
            return st.nextToken();
        }

    }
}

