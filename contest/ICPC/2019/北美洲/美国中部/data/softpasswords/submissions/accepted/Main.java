import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	static class solver {
		public void run(InputReader cin, PrintWriter out) {
			String s = cin.next();
			String p = cin.next();
			if (s.equals(p)) {
				out.println("Yes");
				return;
			}
			for (int i = 0; i <= 9; ++ i) if ((i + p).equals(s) || (p + i).equals(s)) {
				out.println("Yes");
				return;
			}
			StringBuilder sb = new StringBuilder(s);
			for (int i = 0; i < s.length(); ++ i) {
				char tmp = s.charAt(i);
				if (tmp >= 'A' && tmp <= 'Z') {
					sb.setCharAt(i, (char) ((int) tmp - (int) 'A' + (int) 'a'));
				}
				else if (tmp >= 'a' && tmp <= 'z') {
					sb.setCharAt(i, (char) ((int) tmp - (int) 'a' + (int) 'A'));
				}
			}
			if (sb.toString().equals(p)) {
				out.println("Yes");
				return;
			}
			out.println("No");
			return;
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
