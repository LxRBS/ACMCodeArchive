import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	static class solver {
		int N = 1005, M = 10005;
		int[] u = new int [M * 2];
		int[] v = new int [M * 2];
		int[] t = new int [M * 2];
		int[] nex = new int [M * 2];
		int[] st = new int [N];
		int edge_cnt, n, m, q;
		int[] x = new int[N];
		int[] y = new int[N];
		void add_edge(int x, int y, int ti) {
			u[edge_cnt] = x;
			v[edge_cnt] = y;
			t[edge_cnt] = ti;
			nex[edge_cnt] = st[x];
			st[x] = edge_cnt;
			edge_cnt ++;
		}
		class state {
			public int mask, dis, at;
			public state(int _m, int _d, int _a) {
				mask = _m;
				dis = _d;
				at = _a;
			}
		}
		class cmp implements Comparator<state> {
			public int compare(state E1, state E2) {
				if (E1.dis < E2.dis) return -1;
				if (E1.dis > E2.dis) return 1;
				return 0;
			}
		}
		public void run(InputReader cin, PrintWriter out) {
			n = cin.nextInt();
			m = cin.nextInt();
			q = cin.nextInt();
			Random rnd = new Random(0);
			for (int i = 1; i <= n; ++ i) st[i] = -1;
			edge_cnt = 0;
			for (int i = 0; i < m; ++ i) {
				int x = cin.nextInt();
				int y = cin.nextInt();
				int t = cin.nextInt();
				add_edge(x, y, t);
				add_edge(y, x, t);
			}
			for (int i = 0; i < q; ++ i) {
				x[i] = cin.nextInt();
				y[i] = cin.nextInt();
			}
			int[] c = new int[n + 1];
			int[] d = new int[n + 1];
			int[][] dp = new int[1 << 7][n + 1];
			long ans = -1;
			for (int tries = 0; tries < 900; ++ tries) {
				PriorityQueue<state> Q = new PriorityQueue<state>(2 * m, new cmp());
				for (int i = 1; i <= n; ++ i) {
					c[i] = rnd.nextInt(7);
					d[i] = 0;
				}
				for (int i = 0; i < q; ++ i) {
					d[x[i]] = d[x[i]] | (1 << c[y[i]]);
				}
				for (int i = 0; i < (1 << 7); ++ i) {
					for (int j = 1; j <= n; ++ j) {
						dp[i][j] = -1;
					}
				}
				dp[d[1]][1] = 0;
				Q.add(new state(d[1], 0, 1));
				while (!Q.isEmpty()) {
					state p = Q.poll();
					if (dp[p.mask][p.at] != p.dis) continue;
					if (p.mask == (1 << 7) - 1) {
						if (ans == -1 || ans > p.dis) ans = p.dis;
						break;
					}
					if (ans != -1 && ans <= p.dis) break;
					for (int e = st[p.at]; e != -1; e = nex[e]) {
						int dis2 = t[e] + p.dis;
						int mask2 = d[v[e]] | p.mask;
						if (dp[mask2][v[e]] == -1 || dp[mask2][v[e]] > dis2) {
							dp[mask2][v[e]] = dis2;
							Q.add(new state(mask2, dis2, v[e]));
						}
					}
				}
			}
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

