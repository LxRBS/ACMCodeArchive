import java.io.*;
import java.util.StringTokenizer;

public class count_av {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        FastScanner in = new FastScanner(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        CountingPartitions solver = new CountingPartitions();
        solver.solve(1, in, out);
        out.close();
    }

    static class CountingPartitions {
        final int MOD = 998244353;

        public void solve(int testNumber, FastScanner in, PrintWriter out) {
            int MAX = 200_000;
            int[] result = new int[MAX + 1];
            int[] curCount = new int[MAX + 1];
            curCount[0] = 1;
            for (int h = 1; h * h <= MAX; h++) {
                for (int i = 0; i <= MAX; i++) {
                    if (i >= h) {
                        curCount[i] += curCount[i - h];
                        if (curCount[i] >= MOD) {
                            curCount[i] -= MOD;
                        }
                    }
                    if (i * 2 + h * h <= MAX) {
                        result[i * 2 + h * h] += curCount[i];
                        if (result[i * 2 + h * h] >= MOD) {
                            result[i * 2 + h * h] -= MOD;
                        }
                    }
                }
            }

            int T = in.nextInt();
            while (T-- > 0) {
                out.println(result[in.nextInt()]);
            }
        }

    }

    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;

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

