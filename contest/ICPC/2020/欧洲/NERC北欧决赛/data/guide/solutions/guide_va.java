import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.StringTokenizer;

/**
 * Created by vaksenov on 16.03.2021.
 */
public class guide_va {

    BufferedReader br;
    StringTokenizer st;
    PrintWriter out;

    public String nextToken() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(br.readLine());
        }
        return st.nextToken();
    }

    public int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    ArrayList<Integer> path;
    ArrayList<Integer>[] e;
    int k;

    public void dfs(int u, int forbidden) {
        if (k <= 0) return;
        for (int v : e[u]) {
            if (forbidden == v)
                continue;
            k--;
            path.add(v);
            dfs(v, -1);
            path.add(u);
            if (k <= 0) return;
        }
    }

    public void solve() throws IOException {
        int n = nextInt();
        k = nextInt();
        e = new ArrayList[n];

        for (int i = 0; i < n; i++) {
            e[i] = new ArrayList<>();
        }

        int target = 0;

        int[] p = new int[n];
        int[] h = new int[n];
        p[0] = -1;
        h[0] = 1;
        for (int i = 1; i < n; i++) {
            p[i] = nextInt() - 1;
            e[p[i]].add(i);
            h[i] = h[p[i]] + 1;
            if (h[target] < h[i] && h[i] <= k) {
                target = i;
            }
        }
        System.err.println(target);

        path = new ArrayList<>();
        int x = target;
        int prev = target;
        k -= h[x];
        while (x >= 0) {
            path.add(x);
            dfs(x, prev);
            System.err.println(path + " " + k);
            prev = x;
            x = p[x];
        }

        Collections.reverse(path);

        out.println(path.size() - 1);
        for (int u : path) {
            out.print((u + 1) + " ");
        }
        out.println();
    }

    public void run() {
        try {
            br = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);

            int t = nextInt();
            for (int i = 0; i < t; i++) {
                solve();
            }

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        new guide_va().run();
    }
}
