import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	static class solver {
		class delta {
			public double x;
			public int add;
			public delta(double _x, int _add) {
				x = _x;
				add = _add;
			}
		}
		class cmp implements Comparator<delta> {
			public int compare(delta E1, delta E2) {
				if (E1.x < E2.x) return -1;
				if (E1.x > E2.x) return 1;
				return 0;
			}
		}
		public void run(InputReader cin, PrintWriter out) {
			int n = cin.nextInt();
			double[] x = new double[n];
			double[] y = new double[n];
			double[] r = new double[n];
			for (int i = 0; i < n; ++ i) {
				x[i] = cin.nextInt();
				y[i] = cin.nextInt();
				r[i] = cin.nextInt();
			}
			double b = cin.nextInt();
			double D = cin.nextInt();
			double[] L = new double[n];
			double[] R = new double[n];
			int cnt = 0;
			ArrayList<delta> all = new ArrayList<delta>();
			for (int i = 0; i < n; ++ i) {
				r[i] += b;
				double a0 = Math.atan2(y[i], x[i]);
				double d = Math.sqrt(x[i] * x[i] + y[i] * y[i]);
				double a1 = Math.asin(r[i] / d);
				if (r[i] + D <= d) continue;
				if (r[i] + d > D) {
					double a2 = Math.acos((D * D + d * d - r[i] * r[i]) / (2 * D * d));
					if (D < Math.sqrt(d * d - r[i] * r[i])) a1 = a2;
				}
				L[i] = a0 - a1;
				R[i] = a0 + a1;
				if (L[i] < -Math.PI) {
					L[i] += Math.PI * 2;
					R[i] += Math.PI * 2;
				}
				if (R[i] > Math.PI) {
					cnt ++;
					all.add(new delta(L[i], +1));
					all.add(new delta(R[i] - Math.PI * 2, -1));
				}
				else {
					all.add(new delta(L[i], 1));
					all.add(new delta(R[i], -1));
				}
			}
			Collections.sort(all, new cmp());
			all.add(new delta(Math.PI, 0));
			double las = -Math.PI, ans = 0;
			for (delta p : all) {
				if (cnt == 0) {
					ans += p.x - las;
				}
				las = p.x;
				cnt += p.add;
			}
			out.printf("%.10f\n", ans / Math.PI / 2);
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

