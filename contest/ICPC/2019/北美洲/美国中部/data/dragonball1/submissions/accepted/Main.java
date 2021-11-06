import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	static class solver {
		int N = 200005;
		int[] u = new int [N * 2];
		int[] v = new int [N * 2];
		int[] t = new int [N * 2];
		int[] nex = new int [N * 2];
		int[] dd = new int [N * 2];
		int[] st = new int [N];
		int edge_cnt, n, m;
		int[] d = new int [N];
		int[] x = new int[8];
		int[][] a = new int[8][8];
		class cmp implements Comparator<Integer> {
			public int compare(Integer E1, Integer E2) {
				int e1 = E1.intValue();
				int e2 = E2.intValue();
				if (dd[e1] < dd[e2]) return -1;
				if (dd[e1] > dd[e2]) return 1;
				return 0;
			}
		}
		void dijkstra(int src, PrintWriter out) {
			for (int i = 1; i <= n; ++ i) d[i] = -1;
			d[src] = 0;
			PriorityQueue<Integer> Q = new PriorityQueue<Integer>(2 * m, new cmp());
			for (int e = st[src]; e != -1; e = nex[e]) {
				if (d[v[e]] == -1 || d[v[e]] > t[e]) {
					d[v[e]] = t[e];
					dd[e] = t[e];
					Q.add(e);
				}
			}
			while (!Q.isEmpty()) {
				int p = Q.poll();
				if (dd[p] != d[v[p]]) continue;
				for (int e = st[v[p]]; e != -1; e = nex[e]) {
					dd[e] = d[u[e]] + t[e];
					if (d[v[e]] == -1 || dd[e] < d[v[e]]) {
						d[v[e]] = dd[e];
						Q.add(e);
					}
				}
			}
		}
		void add_edge(int x, int y, int ti) {
			u[edge_cnt] = x;
			v[edge_cnt] = y;
			t[edge_cnt] = ti;
			nex[edge_cnt] = st[x];
			st[x] = edge_cnt;
			edge_cnt ++;
		}
		long ans;
		boolean[] use = new boolean[8];
		void dfs(int u, int step, long dis) {
			if (step == 7) {
				if (ans == -1 || ans > dis) {
					ans = dis;
				}
				return;
			}
			for (int i = 1; i <= 7; ++ i) if (!use[i] && a[u][i] != -1) {
				use[i] = true;
				dfs(i, step + 1, dis + a[u][i]);
				use[i] = false;
			}
		}
		public void run(InputReader cin, PrintWriter out) {
			n = cin.nextInt();
			m = cin.nextInt();
			for (int i = 1; i <= n; ++ i) st[i] = -1;
			edge_cnt = 0;
			for (int i = 0; i < m; ++ i) {
				int x = cin.nextInt();
				int y = cin.nextInt();
				int t = cin.nextInt();
				add_edge(x, y, t);
				add_edge(y, x, t);
			}
			x[0] = 1;
			for (int i = 1; i <= 7; ++ i) x[i] = cin.nextInt();
			for (int i = 0; i <= 7; ++ i) {
				dijkstra(x[i], out);
				for (int j = 0; j <= 7; ++ j) {
					a[i][j] = d[x[j]];
				}
			}
			ans = -1;
			dfs(0, 0, 0);
			out.println(ans);
		}
	}
	public static void main(String[] args) {
		PrintWriter out = new PrintWriter(System.out);
		InputReader cin = new InputReader(System.in);
		solver Task = new solver();
		Task.run(cin, out);
		out.close();
	}
	static class InputReader { // Fast Reader
		public BufferedReader reader;
		public StringTokenizer tokenizer;
		public InputReader(InputStream stream) {
			reader = new BufferedReader(new InputStreamReader(stream), 32768);
			tokenizer = null;
		}
		public String next() {
			while (tokenizer == null || !tokenizer.hasMoreTokens()) {
				try {
					String line = reader.readLine();
					/* line == null ? end of file */
					tokenizer = new StringTokenizer(line);
				} catch (IOException e) {
					throw new RuntimeException(e);
				}
			}
			return tokenizer.nextToken();
		}
		public int nextInt() {
			return Integer.parseInt(next());
			// return Long.parseLong(next()); Double Integer
			// return new BigInteger(next(), 16); // as Hex
		}
	}
}

