import java.io.*;
import java.util.*;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class buttonlock_av_tsp_tl {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        FastScanner in = new FastScanner(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        ButtonLock2 solver = new ButtonLock2();
        solver.solve(1, in, out);
        out.close();
    }

    static class ButtonLock2 {

        public void solve(int testNumber, FastScanner in, PrintWriter out) {
            int bits = in.nextInt(), n = in.nextInt();
            int[] masks = new int[n];
            for (int i = 0; i < n; i++) {
                String line = in.next();
                for (int j = 0; j < line.length(); j++) {
                    masks[i] += (line.charAt(j) - '0') << j;
                }
            }

            int[][] dp = new int[1 << n][n];
            int[][] prev = new int[1 << n][n];
            int INF = Integer.MAX_VALUE / 3;
            for (int[] i : dp) {
                Arrays.fill(i, INF);
            }
            for (int i = 0; i < n; i++) {
                dp[1 << i][i] = Integer.bitCount(masks[i]);
            }
            for (int mask = 0; mask < 1 << n; mask++) {
                for (int last = 0; last < n; last++) {
                    if (dp[mask][last] != INF) {
                        int val = dp[mask][last];
                        for (int next = 0; next < n; next++) {
                            if ((mask & (1 << next)) == 0) {
                                int nextVal = val + (((masks[next] & masks[last]) == masks[last]) ? Integer.bitCount(masks[next] ^ masks[last]) : (Integer.bitCount(masks[next]) + 1));
                                if (dp[mask | (1 << next)][next] > nextVal) {
                                    dp[mask | (1 << next)][next] = nextVal;
                                    prev[mask | (1 << next)][next] = last;
                                }
                            }
                        }

                    }
                }
            }
            int curLast = 0;
            int curMask = (1 << n) - 1;
            for (int i = 0; i < n; i++) {
                if (dp[curMask][i] < dp[curMask][curLast]) {
                    curLast = i;
                }
            }
            out.println(dp[curMask][curLast]);
            List<Integer> path = new ArrayList<>();
            while (curMask > 0) {
                path.add(masks[curLast]);
                curMask ^= 1 << curLast;
                curLast = prev[curMask | (1 << curLast)][curLast];
            }
            path.add(0);
            Collections.reverse(path);
            for (int i = 0; i + 1 < path.size(); i++) {
                visit(path.get(i), path.get(i + 1), out);
            }
        }

        private void visit(int start, int finish, PrintWriter out) {
            if ((start & finish) != start) {
                out.print("R ");
                start = 0;
            }
            int bits = finish ^ start;
            while (bits > 0) {
                int bit = Integer.bitCount(Integer.lowestOneBit(bits) - 1);
                out.print(bit + " ");
                bits ^= 1 << bit;
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
                    throw new UnknownError();
                }
                if (line == null) {
                    throw new UnknownError();
                }
                st = new StringTokenizer(line);
            }
            return st.nextToken();
        }

    }

    static class Utils {
        public static <T> List<T>[] listArray(int size) {
            List<T>[] result = new List[size];
            for (int i = 0; i < size; i++) {
                result[i] = new ArrayList<>();
            }
            return result;
        }

    }
}

