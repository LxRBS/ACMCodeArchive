import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	static class solver {
		static int[] f = new int[400005];
		int fat(int x) {
			if (x == f[x]) return x;
			return f[x] = fat(f[x]);
		}
		void join(int x, int xi, int y, int yi) {
			x = x * 2 + xi;
			y = y * 2 + yi;
			f[fat(x)] = fat(y);
		}
		public void run(InputReader cin, PrintWriter out) {
			int MOD = 1000000007;
			int n = cin.nextInt();
			int[] b = new int[n];
			int[] L = new int[n];
			int[] R = new int[n];
			for (int i = 0; i < n; ++ i) {
				L[i] = cin.nextInt();
				R[i] = cin.nextInt();
				b[i] = cin.nextInt();
			}
			int ans = 0;
			for (int all = 0; all <= 1; ++ all) {
				for (int i = 0; i < 2 * (n + 1); ++ i) f[i] = i;
				for (int i = 0; i < n; ++ i) {
					int eq = b[i], l = i - L[i], r = i + R[i];
					if (l < 0) {
						r = i - L[i] + n - 1;
						l = i + R[i] + 1;
						eq = eq ^ all;
					}
					else if (r >= n) {
						r = i - L[i] - 1;
						l = i + R[i] - n + 1;
						eq = eq ^ all;
					}
					join(l, 0, r + 1, eq);
					join(l, 1, r + 1, eq ^ 1);
				}
				boolean gg = false;
				for (int i = 0; i <= n; ++ i) {
					if (fat(i * 2) == fat(i * 2 + 1)) gg = true;
				}
				if (fat(0) == fat(n * 2 + (all ^ 1))) gg = true;
				if (gg) continue;
				int res = 1;
				for (int i = 0; i <= n; ++ i) {
					if (f[i * 2] == i * 2) {
						if (fat(0) == fat(i * 2) || fat(n * 2 + all) == fat(i * 2)) continue;
						if (fat(0) == fat(i * 2 + 1) || fat(n * 2 + all) == fat(i * 2 + 1)) continue;
						res = (res + res) % MOD;
					}
				}
				ans = (ans + res) % MOD;
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

