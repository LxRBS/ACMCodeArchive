import java.io.*;
import java.util.StringTokenizer;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class lostperm_av {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        FastScanner in = new FastScanner(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        ConjugateGuessing solver = new ConjugateGuessing();
        solver.solve(1, in, out);
        out.close();
    }

    static class ConjugateGuessing {
        public void solve(int testNumber, FastScanner in, PrintWriter out) {
            int tests = in.nextInt();
            for (int testN = 1; testN <= tests; testN++) {
                int n = in.nextInt();
                Interactor interactor = new StdinInteractor(in, out);
                solveOne(n, interactor);
            }
//        stress();
        }

        private void solveOne(int n, Interactor interactor) {
            int[] send = new int[n];
            for (int i = 0; i < n; i++) {
                send[i] = (i + 1) % n;
            }
            int[] cycle = interactor.query(send);
            send[0] = 0;
            send[n - 1] = 1;
            int[] cycleWithFixedPoint = interactor.query(send);
            int fixedPoint = -1;
            for (int i = 0; i < n; i++) {
                if (cycleWithFixedPoint[i] == i) {
                    fixedPoint = i;
                }
            }
            int[] result = new int[n];
            for (int i = 0; i < n; i++) {
                result[i] = fixedPoint;
                fixedPoint = cycle[fixedPoint];
            }
            interactor.answer(result);
        }

        interface Interactor {
            int[] query(int[] f);

            void answer(int[] pi);

        }

        static class StdinInteractor implements Interactor {
            FastScanner in;
            PrintWriter out;

            public StdinInteractor(FastScanner in, PrintWriter out) {
                this.in = in;
                this.out = out;
            }

            public int[] query(int[] f) {
                out.print("?");
                for (int i = 0; i < f.length; i++) {
                    out.print(" " + (f[i] + 1));
                }
                out.println();
                out.flush();
                int[] g = new int[f.length];
                for (int i = 0; i < g.length; i++) {
                    g[i] = in.nextInt() - 1;
                }
                return g;
            }

            public void answer(int[] pi) {
                out.print("!");
                for (int i = 0; i < pi.length; i++) {
                    out.print(" " + (pi[i] + 1));
                }
                out.println();
                out.flush();
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

