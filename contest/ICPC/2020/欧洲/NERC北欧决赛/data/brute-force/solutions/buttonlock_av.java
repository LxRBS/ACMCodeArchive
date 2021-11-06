import java.io.*;
import java.util.*;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class buttonlock_av {
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
        List<Integer>[] graph;
        int[] match;
        int[] visited;
        int time;

        boolean dfs(int u) {
            visited[u] = time;
            for (int t = 0; t < graph[u].size(); t++) {
                int v = graph[u].get(t);
                if (match[v] == -1) {
                    match[v] = u;
                    return true;
                }
            }
            for (int t = 0; t < graph[u].size(); t++) {
                int v = graph[u].get(t);
                if (visited[match[v]] < time && dfs(match[v])) {
                    match[v] = u;
                    return true;
                }
            }
            return false;
        }

        public void solve(int testNumber, FastScanner in, PrintWriter out) {
            int bits = in.nextInt(), n = in.nextInt();
            int[] masks = new int[n];
            for (int i = 0; i < n; i++) {
                String line = in.next();
                for (int j = 0; j < line.length(); j++) {
                    masks[i] += (line.charAt(j) - '0') << j;
                }
            }
            // yikes
            masks = Arrays.stream(masks).boxed().sorted(Comparator.comparing(x -> Integer.bitCount(x))).mapToInt(x -> x).toArray();
            graph = Utils.listArray(n);
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    if ((masks[j] & masks[i]) == masks[i]) {
                        graph[i].add(j);
                    }
                }
            }

            match = new int[n];
            Arrays.fill(match, -1);
            visited = new int[n];
            time = 0;
            int ans = 0;
            for (int i = n - 1; i >= 0; i--) {
                time++;
                if (!dfs(i)) {
                    ans += Integer.bitCount(masks[i]) + 1;
                }
            }
            int[] next = new int[n];
            Arrays.fill(next, -1);
            for (int i = 0; i < n; i++) {
                if (match[i] != -1) {
                    next[match[i]] = i;
                }
            }

            out.println(ans - 1);
            boolean first = true;
            boolean[] used = new boolean[n];
            for (int i = 0; i < n; i++) {
                if (used[i]) {
                    continue;
                }
                if (!first) {
                    out.print("R ");
                } else {
                    first = false;
                }
                visit(0, masks[i], out);
                int cur = i;
                while (true) {
                    used[cur] = true;
                    if (next[cur] == -1) {
                        break;
                    }
                    visit(masks[cur], masks[next[cur]], out);
                    cur = next[cur];
                }
            }
            out.println();
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

