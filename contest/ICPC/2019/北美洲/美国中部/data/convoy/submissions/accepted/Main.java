import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	static class solver {
		public void run(InputReader cin, PrintWriter out) {
			long n = cin.nextInt();
			long k = cin.nextInt();
			long[] t = new long[(int) n];
			for (int i = 0; i < n; ++ i) t[i] = cin.nextInt();
			Arrays.sort(t);
			long l = 0, r = (long) 1e12, ans = r;
			while (l <= r ) {
				long mid = (l + r) / 2;
				long cnt = 0;
				for (int i = 0; i < Math.min(n, k) && t[i] <= mid; ++ i) {
					cnt += 1 + (mid / t[i] + 1) / 2 * 4;
					if (cnt >= n) break;
				}
				if (cnt >= n) {
					ans = mid;
					r = mid - 1;
				}
				else {
					l = mid + 1;
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

