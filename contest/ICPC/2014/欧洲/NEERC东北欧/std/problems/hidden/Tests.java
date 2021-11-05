/******************************************************************/
/* ACM ICPC 2014-2015                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tbilisi - Tashkent, December 7, 2014 */
/******************************************************************/
/* Problem H. Hidden Maze                                         */
/*                                                                */
/* Original idea         Alexander Kaluzhin                       */
/* Problem statement     Andrei Lopatin                           */
/* Test set              Andrei Lopatin                           */
/******************************************************************/
/* Tests                                                          */
/*                                                                */
/* Author                Andrei Lopatin                           */
/******************************************************************/

import java.io.*;
import java.util.*;
import java.util.Map.Entry;

public class Tests {
	private static File dir = new File("tests");
	private int curTest = 1;
	private static boolean verbose = true;

	private String testName;
	private PrintWriter out;
	private Random r = new Random(55166813829613814L);

        static final int MAXN = 30000;
	static final int MAXC = (int)1e6;

	public void run() {
		test(random_values(2, 1, 1), false);
		test(random_values(5, 1, 5), false);
		r.setSeed(946626534479450714L);
		test(sample3_values(5), false);
		test(random_values(3, 1, 5), false);
		test(random_values(4, 1, 5), false);
		test(random_values(10, 1, 10), true);
		test(random_values(100, 1, 1000), true);
		test(random_values(1000, 1, 10000), true);
		test(random_values(MAXN / 3, 1, MAXC / 10), true);
		test(random_values(MAXN - 10000, 1, MAXC / 2), true);
		test(random_values(MAXN, 1, MAXC), false);
		test(random_values(MAXN, 1, MAXC), true);
		test(random_values(MAXN, 1, MAXC), true);
		test(random_values(MAXN, 1, 1), true);
		test(random_values(MAXN, 1, 2), true);
		test(random_values(MAXN, MAXC - 100, MAXC), true);
		test(random_values(MAXN, MAXC, MAXC), true);
		test(ascending_values(MAXN), false);
		test(ascending_values(MAXN), true);
		test(descending_values(MAXN), false);
		test(descending_values(MAXN), true);
		test(interlacing_values(MAXN), false);
		test(interlacing_values(MAXN), true);
	}

	int u[], d[];

	int up(int p) {
		if (u[p] != p) {
			u[p] = up(u[p]);
		}
		return u[p];
	}


	void merge (int a, int b) {
		if (d[a] < d[b]) {
			u[a] = b;
		} else {
			u[b] = a;
			if (d[a] == d[b]) {
				++d[a];
			}
		}
	}

        class Edge {
	        int b, e, c;
	        Edge(int _b, int _e, int _c) {
		        b = _b; e = _e; c = _c;
	        }
	}

	ArrayList<Edge> edges;

	private void shuffle_edges() {
		int s = edges.size();
		int a[] = new int [s];
		for (int i = 0; i < s; i++) {
			int t = r.nextInt(i + 1);
			a[i] = a[t];
			a[t] = i;
		}
		ArrayList<Edge> new_edges = new ArrayList<Edge>();
		for (int i = 0; i < s; i++) {
			new_edges.add(edges.get(a[i]));
		}
		edges = new_edges;
	}

	private void output_edges() {
		for (Edge e:edges) {
			out.println(e.b + " " + e.e + " " + e.c);
		}
	}

	private ArrayList<Integer> random_values(int n, int minv, int maxv) {
		ArrayList<Integer> res = new ArrayList<Integer>();
		for (int i = 1; i < n; i++) {
			res.add(r.nextInt(maxv - minv + 1) + minv);
		}
		return res;
	}

	private ArrayList<Integer> ascending_values(int n) {
		ArrayList<Integer> res = new ArrayList<Integer>();
		for (int i = 1; i < n; i++) {
			res.add(i);
		}
		return res;
	}

	private ArrayList<Integer> descending_values(int n) {
		ArrayList<Integer> res = new ArrayList<Integer>();
		for (int i = 1; i < n; i++) {
			res.add(MAXC - i + 1);
		}
		return res;
	}

	private ArrayList<Integer> interlacing_values(int n) {
		ArrayList<Integer> res = new ArrayList<Integer>();
		for (int i = 1; i < n; i++) {
			res.add((i & 1) == 0 ? MAXC : 1);
		}
		return res;
	}

	private ArrayList<Integer> sample3_values(int n) {
		assert n == 5;
		return new ArrayList<Integer>(Arrays.asList(2, 2, 3, 7));
	}

	private void test(ArrayList<Integer> values, boolean shuffle) {
		int n = values.size () + 1;
		open();
		out.println(n);
		u = new int[n + 1];
		d = new int[n + 1];
		edges = new ArrayList<Edge>();
		for (int i = 1; i <= n; i++) {
			u[i] = i;
			d[i] = 1;
		}
		for (int i = 1; i < n; i++) {
			int a = -1, b = -1, c = -1, d = -1;
			while (c == d) {
				a = r.nextInt (n) + 1;
				b = r.nextInt (n) + 1;
				c = up(a);
				d = up(b);
			}
			merge(c, d);
			edges.add(new Edge(a, b, values.get(i - 1)));
		}
		if (shuffle) {
			shuffle_edges();
		}
		output_edges();
		close();
	}


	private void open() {
		try {
			testName = "" + curTest / 10 + curTest % 10;
			out = new PrintWriter(new File(dir, testName));
			if (verbose) { 
				System.out.print("Generating " + testName + "...");
			}
		} catch (IOException e) {
			throw new RuntimeException("Unable to open " + testName + " for writing", e);
		}
	}

	private void close() {
		out.close();
		if (verbose) {
			System.out.println(" done.");
		}
		curTest++;
	}

	public static void main(String[] args) {
		Locale.setDefault(Locale.US);
		dir.mkdirs();
		new Tests().run();
	}
}

