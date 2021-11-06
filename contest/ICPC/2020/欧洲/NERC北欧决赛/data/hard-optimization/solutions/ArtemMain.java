import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;
import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Collections;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class ArtemMain {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        FastScanner in = new FastScanner(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        HardOpt solver = new HardOpt();
        solver.solve(1, in, out);
        out.close();
    }

    static class HardOpt {
        int n;
        List<Integer>[] tree;
        Segment[] segs;
        Segment[] ans;
        int[][][][] dp;
        int[][][][][] auxDp;
        int[][][][][] saveAux;

        void dfs(int u) {
            for (int v : tree[u]) {
                dfs(v);
            }
            auxDp[u] = new int[tree[u].size()][2][2][n + 1];
            saveAux[u] = new int[tree[u].size()][2][2][n + 1];
            dp[u] = new int[2][2][n + 1];
            int[][][][] auxDp = this.auxDp[u];

            if (tree[u].size() == 0) {
                int ans = segs[u].r - segs[u].l;
                for (int left = 0; left < 2; left++) {
                    for (int right = 0; right < 2; right++) {
                        Arrays.fill(dp[u][left][right], ans);
                    }
                }
            } else {
                int firstChild = tree[u].get(0);
                int lastChild = tree[u].get(tree[u].size() - 1);
                for (int left = 0; left < 2; left++) {
                    for (int right = 0; right < 2; right++) {
                        System.arraycopy(dp[firstChild][left][right], 0, auxDp[0][left][right], 0, n + 1);
                        for (int inside = 0; inside <= n; inside++) {
                            if (left == 1) {
                                auxDp[0][left][right][inside] += segs[firstChild].l - segs[u].l;
                            }
                        }
                    }
                }
                int last = segs[firstChild].r;
                for (int t = 1; t < tree[u].size(); t++) {
                    int v = tree[u].get(t);
                    mergeDP(auxDp[t - 1], dp[v], segs[v].l - last, auxDp[t], saveAux[u][t]);
                    last = segs[v].r;
                }
                int[][][] lastAuxDp = auxDp[tree[u].size() - 1];
                for (int left = 0; left < 2; left++) {
                    for (int right = 0; right < 2; right++) {
                        for (int inside = 0; inside <= n; inside++) {
                            if (right == 1) {
                                lastAuxDp[left][right][inside] += segs[u].r - segs[lastChild].r;
                            }
                        }
                    }
                }
                relax(lastAuxDp);


                for (int left = 0; left < 2; left++) {
                    for (int right = 0; right < 2; right++) {
                        dp[u][left][right][n] = lastAuxDp[left][right][n];
                        for (int inside = 1; inside <= n; inside++) {
                            dp[u][left][right][inside - 1] = lastAuxDp[left][right][inside];
                        }
                    }
                }
            }
        }

        Answer restore(int u, int left, int right, int inside) {
            if (tree[u].size() == 0) {
                Answer ret = new Answer();
                ans[u] = segs[u];
                if (left == 1) {
                    ret.left = new Segment(segs[u].l, segs[u].l, -1);
                }
                if (right == 1) {
                    ret.right = new Segment(segs[u].r, segs[u].r, -1);
                }
                while (ret.segments.size() < inside) {
                    ret.segments.add(new Segment(0, 0, -1));
                }
                return ret;
            }
            Answer cur = restoreRelaxed(u, left, right, inside + 1);
            ans[u] = cur.segments.get(0);
            cur.segments.remove(0);
            return cur;
        }

        private void relax(int[][][] array) {
            for (int inside = 0; inside <= n; inside++) {
                for (int left = 1; left >= 0; left--) {
                    for (int right = 1; right >= 0; right--) {
                        int val = array[left][right][inside];
                        if (left == 1 && inside + 1 <= n) {
                            array[1][right][inside + 1] = Math.max(array[1][right][inside + 1], val);
                            array[0][right][inside + 1] = Math.max(array[0][right][inside + 1], val);
                        }
                        if (right == 1 && inside + 1 <= n) {
                            array[left][0][inside + 1] = Math.max(array[left][0][inside + 1], val);
                            array[left][1][inside + 1] = Math.max(array[left][1][inside + 1], val);
                        }
                    }
                }
            }
        }

        private Answer restoreRelaxed(int u, int left, int right, int inside) {
            int[][][] lastAuxDp = auxDp[u][tree[u].size() - 1];
            if (left == 0 && inside > 0 && lastAuxDp[1][right][inside - 1] == lastAuxDp[left][right][inside]) {
                Answer answer = restoreRelaxed(u, 1, right, inside - 1);
                answer.segments.add(answer.left);
                answer.left = null;
                return answer;
            }
            if (left == 1 && inside > 0 && lastAuxDp[1][right][inside - 1] == lastAuxDp[left][right][inside]) {
                Answer answer = restoreRelaxed(u, 1, right, inside - 1);
                answer.segments.add(answer.left);
                answer.left = new Segment(segs[u].l, segs[u].l, -1);
                return answer;
            }
            if (right == 0 && inside > 0 && lastAuxDp[left][1][inside - 1] == lastAuxDp[left][right][inside]) {
                Answer answer = restoreRelaxed(u, left, 1, inside - 1);
                answer.segments.add(answer.right);
                answer.right = null;
                return answer;
            }
            if (right == 1 && inside > 0 && lastAuxDp[left][1][inside - 1] == lastAuxDp[left][right][inside]) {
                Answer answer = restoreRelaxed(u, left, 1, inside - 1);
                answer.segments.add(answer.right);
                answer.right = new Segment(segs[u].r, segs[u].r, -1);
                return answer;
            }
            Answer answer = restoreAux(u, tree[u].size() - 1, left, right, inside);
            if (right == 1) {
                answer.right.r = segs[u].r;
            }
            return answer;
        }

        Answer restoreAux(int u, int pos, int left, int right, int inside) {
            if (pos == 0) {
                Answer answer = restore(tree[u].get(0), left, right, inside);
                if (left == 1) {
                    answer.left.l = segs[u].l;
                }
                return answer;
            }
            int saved = saveAux[u][pos][left][right][inside];
            int ar = (saved >>> 29) & 1;
            int bl = (saved >>> 28) & 1;
            int inA = (saved >>> 14) & ((1 << 14) - 1);
            int inB = (saved >>> 0) & ((1 << 14) - 1);
            Answer fromLeft = restoreAux(u, pos - 1, left, ar, inA);
            Answer fromRight = restore(tree[u].get(pos), bl, right, inB);
            Answer newAns = new Answer();
            newAns.left = fromLeft.left;
            newAns.right = fromRight.right;
            newAns.segments.addAll(fromLeft.segments);
            newAns.segments.addAll(fromRight.segments);
            if (inA + inB + 1 == inside) {
                newAns.segments.add(new Segment(fromLeft.right.l, fromRight.left.r, -1));
            }
            return newAns;
        }

        private void mergeDP(int[][][] a, int[][][] b, int midDist, int[][][] result, int[][][] save) {
            for (int left = 0; left < 2; left++) {
                for (int right = 0; right < 2; right++) {
                    for (int ar = 0; ar < 2; ar++) {
                        for (int bl = 0; bl < 2; bl++) {
                            int aSize = getSize(a[left][ar]);
                            int bSize = getSize(b[bl][right]);
                            for (int inA = 0; inA <= aSize; inA++) {
                                for (int inB = 0; inB <= bSize; inB++) {
                                    int valA = a[left][ar][inA];
                                    int valB = b[bl][right][inB];
                                    if (ar == 0 && bl == 0 && inA + inB <= n && result[left][right][inA + inB] < valA + valB) {
                                        result[left][right][inA + inB] = valA + valB;
                                        save[left][right][inA + inB] = (ar << 29) + (bl << 28) + (inA << 14) + (inB << 0);
                                    }
                                    if (ar == 1 && bl == 1 && inA + inB + 1 <= n && result[left][right][inA + inB + 1] < valA + valB + midDist) {
                                        result[left][right][inA + inB + 1] = valA + valB + midDist;
                                        save[left][right][inA + inB + 1] = (ar << 29) + (bl << 28) + (inA << 14) + (inB << 0);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        private int getSize(int[] a) {
            for (int k = 0; k < a.length; k++) {
                if (k + 1 == a.length || a[k] >= a[k + 1]) {
                    return k;
                }
            }
            // never happens
            throw new AssertionError();
        }

        public void solve(int testNumber, FastScanner in, PrintWriter out) {
            n = in.nextInt();
            segs = new Segment[n];
            for (int i = 0; i < n; i++) {
                segs[i] = new Segment(in.nextInt(), in.nextInt(), i);
            }
            List<Event> events = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                events.add(new Event(-1, segs[i].l, i));
                events.add(new Event(1, segs[i].r, i));
            }
            Collections.sort(events);
            List<Integer> stack = new ArrayList<>();
            int[] parent = new int[n];
            tree = Utils.listArray(n);
            Arrays.fill(parent, -1);
            for (Event e : events) {
                if (e.type == -1) {
                    stack.add(e.id);
                } else {
                    stack.remove(stack.size() - 1);
                    if (stack.size() > 0) {
                        parent[e.id] = stack.get(stack.size() - 1);
                        tree[parent[e.id]].add(e.id);
                    }
                }
            }
            dp = new int[n][][][];
            auxDp = new int[n][][][][];
            saveAux = new int[n][][][][];
            ans = new Segment[n];
            int totalLength = 0;
            for (int i = 0; i < n; i++) {
                if (parent[i] == -1) {
                    dfs(i);
                    totalLength += dp[i][0][0][0];
                    restore(i, 0, 0, 0);
                }
            }
            out.println(totalLength);
            for (Segment s : ans) {
                out.println(s.l + " " + s.r);
            }
        }

        class Answer {
            Segment left;
            Segment right;
            List<Segment> segments;

            public Answer() {
                this.segments = new ArrayList<>();
            }

        }

        class Event implements Comparable<Event> {
            int type;
            int x;
            int id;

            public Event(int type, int x, int id) {
                this.type = type;
                this.x = x;
                this.id = id;
            }

            public int compareTo(Event o) {
                return Integer.compare(x, o.x);
            }

        }

        class Segment implements Comparable<Segment> {
            int l;
            int r;
            int i;

            public Segment(int l, int r, int i) {
                this.l = l;
                this.r = r;
                this.i = i;
            }

            public int compareTo(Segment o) {
                return Integer.compare(l, o.l);
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

