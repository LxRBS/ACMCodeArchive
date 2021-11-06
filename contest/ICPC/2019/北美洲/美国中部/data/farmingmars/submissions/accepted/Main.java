import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	static class solver {
		class val {
			public int guess, cnt;
			public val(int _g, int _c) {
				guess = _g;
				cnt = _c;
			}
		};
		public val add(val a, val b) {
			int guess;
			if (a.cnt > b.cnt) guess = a.guess; else guess = b.guess;
			int cnt = 0;
			if (a.guess == guess) cnt += a.cnt; else cnt -= a.cnt;
			if (b.guess == guess) cnt += b.cnt; else cnt -= b.cnt;
			return new val(guess, cnt);
		}
		class node {
			public val guess;
			public Map<Integer, Integer> m;
			public node() {
				guess = new val(0, 0);
				m = new HashMap<Integer, Integer>();
			}
			public node(int x) {
				guess = new val(x, 1);
				m = new HashMap<Integer, Integer>();
				m.put(x, 1);
			}
		};
		int N = (int) 1e4 + 5;
		int[] a = new int[N];
		node[] tree = new node[N  * 4];
		void build(int x, int l, int r) {
			if (l == r) {
				tree[x] = new node(a[l]);
				return;
			}
			int mid = (l + r) / 2;
			build(x + x, l, mid);
			build(x + x + 1, mid + 1, r);
			tree[x] = new node();
			tree[x].guess = add(tree[x + x].guess, tree[x + x + 1].guess);
			for (Map.Entry<Integer, Integer> entry : tree[x + x].m.entrySet()) {
				Integer key = entry.getKey();
				Integer val = entry.getValue();
				if (tree[x].m.containsKey(key)) {
					tree[x].m.put(key, tree[x].m.get(key) + val);
				}
				else {
					tree[x].m.put(key, val);
				}
			}
			for (Map.Entry<Integer, Integer> entry : tree[x + x + 1].m.entrySet()) {
				Integer key = entry.getKey();
				Integer val = entry.getValue();
				if (tree[x].m.containsKey(key)) {
					tree[x].m.put(key, tree[x].m.get(key) + val);
				}
				else {
					tree[x].m.put(key, val);
				}
			}
		}
		val query_guess(int x, int l, int r, int ql, int qr) {
			if (l > qr || r < ql) return new val(0, 0);
			if (l >= ql && r <= qr) return tree[x].guess;
			int mid = (l + r) / 2;
			return add(query_guess(x + x, l, mid, ql, qr), query_guess(x + x + 1, mid + 1, r, ql, qr));
		}
		int query_cnt(int x, int l, int r, int ql, int qr, int target) {
			if (l > qr || r < ql) return 0;
			if (l >= ql && r <= qr) {
				if (!tree[x].m.containsKey(target)) return 0;
				return tree[x].m.get(target).intValue();
			}
			int mid = (l + r) / 2;
			return query_cnt(x + x, l, mid, ql, qr, target) + query_cnt(x + x + 1, mid + 1, r, ql, qr, target);
		}
		public void run(InputReader cin, PrintWriter out) {
			int n = cin.nextInt();
			int m = cin.nextInt();
			for (int i = 1; i <= n; ++ i) {
				int tmp = 0;
				String s = cin.next();
				for (int j = 0; j < s.length(); ++ j) {
					if (s.charAt(j) != '.') {
						tmp = tmp * 10 + (int) s.charAt(j) - (int) '0';
					}
				}
				a[i] = tmp;
			}
			build(1, 1, n);
			for (int i = 0; i < m; ++ i) {
				int l, r;
				l = cin.nextInt();
				r = cin.nextInt();
				val guess = query_guess(1, 1, n, l, r);
				int cnt = query_cnt(1, 1, n, l, r, guess.guess);
				if (cnt >= ((r - l + 1) / 2 + 1)) {
					out.println("usable");
				}
				else {
					out.println("unusable");
				}
			}
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

