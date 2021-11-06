import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	static class solver {
		public void run(InputReader cin, PrintWriter out) {
			int MOD = 1000000007;
			int n = cin.nextInt();
			int m = cin.nextInt();
			int[] hint1 = new int[n + 1];
			int[] hint2 = new int[n + 1];
			for (int i = 1; i <= n; ++ i) {
				hint1[i] = i;
				hint2[i] = 0;
			}
			for (int i = 0; i < m; ++ i) {
				int l = cin.nextInt();
				int r = cin.nextInt();
				String s = cin.next();
				if (s.equals("same")) {
					hint1[r] = Math.min(hint1[r], l);
				}
				else {
					hint2[r] = Math.max(hint2[r], l);
				}
			}
			int[] dp = new int[n + 1];
			dp[0] = 1;
			for (int i = 1; i <= n; ++ i) {
				int h1 = i, h2 = 0;
				for (int j = i; j >= 1; -- j) {
					h2 = Math.max(h2, hint2[j]);
					h1 = Math.min(h1, hint1[j]);
					if (j > h2 && j <= h1) {
						dp[i] = (dp[i] + dp[j - 1]) % MOD;
					}
				}
			}
			out.println(dp[n] * 2 % MOD);
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

