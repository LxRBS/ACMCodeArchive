import java.io.*;
import java.util.StringTokenizer;

public class build_av {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        FastScanner in = new FastScanner(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        BuildingPartitions solver = new BuildingPartitions();
        solver.solve(1, in, out);
        out.close();
    }

    static class BuildingPartitions {
        public void solve(int testNumber, FastScanner in, PrintWriter out) {
            int n = in.nextInt();
            if (n == 2) {
                out.println(-1);
                return;
            }
            char[][] result = new char[n][n];
            out.println(n);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i == 0 && j <= (n - 1) / 2 || (j == 0 && i <= (n - 1) / 2) || (i == 1 && j == 1 && n % 2 == 0)) {
                        result[i][j] = 'o';
                    } else {
                        result[i][j] = '.';
                    }
                }
            }
            for (int i = n - 1; i >= 0; i--) {
                out.println(new String(result[i]));
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

