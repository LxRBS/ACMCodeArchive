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
/* Solution                                                       */
/*                                                                */
/* Author                Andrei Lopatin                           */
/******************************************************************/

import java.io.*;
import java.util.*;

/**
 * Reference solution for NEERC'2014 Problem H: Hidden Maze
 * This solution checks correctness of the input.
 *
 * @author Andrei Lopatin
 */
public class hidden_al {
    private static final String INPUT = "hidden.in";
    private static final String OUTPUT = "hidden.out";

    public static void main(String[] args) throws Exception {
        new hidden_al().go();
    }

    void go() throws IOException {
        long time = System.currentTimeMillis();
        try (Scanner in = new Scanner(new File(INPUT))) {
            in.useLocale(Locale.US);
            read(in);
        }
        solve();
        try (PrintWriter out = new PrintWriter(OUTPUT)) {
            write(out);
        }
        System.out.printf("Done in %d ms%n", System.currentTimeMillis() - time);
    }

    static final int MAXN = 30000;
    static final int MAXC = (int)1e6;


    static class Edge implements Comparable<Edge> {
	int b, e, v;
	Edge(int _b, int _e, int _v) {
	    b = _b;
	    e = _e;
	    v = _v;
	}
	public int compareTo(Edge e2) {
	    return v - e2.v;
	}
    }

    Edge [] el;

    int n;
    ArrayList <Integer> e[];
    ArrayList <Integer> value[];

    void read(Scanner in) {
	n = in.nextInt();
	in.nextLine();
	assert 1 <= n && n <= MAXN;
	allocate();

	for (int i = 1; i < n; i++) {
	    int a = in.nextInt(), b = in.nextInt(), c = in.nextInt();
	    in.nextLine();
	    assert 1 <= a && a <= n && 1 <= b && b <= n && 1 <= c && c <= MAXC;
	    el[i - 1] = new Edge(a, b, c);
	}
    }

    void allocate() {
        e = new ArrayList[n + 1];
        value = new ArrayList[n + 1];
        el = new Edge[n - 1];
    }

    boolean[] f;
    int MaxD;
    int[][] S;
    int[] u, d, cu;

    void v_dfs(int v, int d) {
	if (d > MaxD) {
	    throw new AssertionError("Tree depth more than " + MaxD);
	}
	f[v] = true;
	for (int i = 0; i < e[v].size (); i++) {
	    int w = e[v].get(i);
	    if (!f[w]) {
		v_dfs(w, d + 1);
	    }
	}
    }

    void validate() {
	f = new boolean [n + 1];
	MaxD = 2 * (int)Math.sqrt(n) + 10;
	v_dfs(1, 0);
	for (int i = 1; i <= n; i++) {
	    if (!f[i]) {
		throw new AssertionError("Vertex " + i + " not reachable");
	    }
	}
    }

    int dfs_init(int v) {
	int cnt = 1, subd = 0;
	f[v] = true;
	for (int i = 0; i < e[v].size (); i++) {
	    int w = e[v].get(i);
	    if (!f[w]) {
		u[w] = v;
		cu[w] = value[v].get(i);
		subd = Math.max(subd, dfs_init(w) + 1);
		for (int j = 0; j < MaxD; j++) {
		    S[v][MaxD + j + 1] += S[w][MaxD + j];
		}
	    }
	}
	S[v][MaxD + 0] = 1;
	d[v] = subd;
	return subd;
    }

    void build_graph() {
	for (int i = 1; i <= n; i++) {
	    e[i] = new ArrayList <Integer>();
	    value[i] = new ArrayList <Integer>();
	}
	for (int i = 0; i < el.length; i++) {
	    e[el[i].b].add(el[i].e);
	    e[el[i].e].add(el[i].b);
	    value[el[i].b].add(i + 1);
	    value[el[i].e].add(i + 1);
	}
    }

    long sum, cnt;

    void solve() {
	Arrays.sort(el);

	build_graph();
	validate();

	S = new int[n + 1][MaxD * 2 + 1];
	u = new int[n + 1];
	d = new int[n + 1];
	cu = new int[n + 1];

	f = new boolean [n + 1];
	dfs_init(1);

	for (int i = 0; i < el.length; i++) {
	    int a = el[i].b, b = el[i].e;
	    if (u[a] == b) {
		int t = a;
		a = b;
		b = t;
	    }
	    // a - upper vertex, b - lower vertex
	    assert cu[b] == i + 1 && u[b] == a;
	    int ca = a, cb = b, cd = 0, ccnt = 0;
	    while (ca > 0) {

		int lb = Math.max(MaxD - d[ca], MaxD - d[b] - cd);
		int ub = Math.min(MaxD + d[ca], MaxD + d[b] - cd);

		int dd;
		if (cu[cb] > i) {
		    dd = 1;
		} else {
		    dd = -1;
		}

		for (int k = lb; k <= ub; k++) {
//		    System.out.println(b + " " + cb + " " + dd + " " + MaxD + " " + k + " " + S[ca][k] + " " + S[cb][k - dd] + " " + (2 * MaxD - k - cd) + " " + S[b][2 * MaxD - k - cd]);
		    assert S[ca][k] >= S[cb][k - dd];
		    ccnt += (S[ca][k] - S[cb][k - dd]) * S[b][2 * MaxD - k - cd];
		}

		if (cu[ca] > i + 1) {
		    ++cd;
		} else {
		    --cd;
		}
		cb = ca;
		ca = u[cb];
	    }
	    sum += (long)ccnt * el[i].v;
	    cnt += ccnt;

	    ca = a; cb = b; cd = 1;
	    while (ca > 0) {
		int lb = Math.max(MaxD - d[ca], MaxD - d[b] + cd);
		int ub = Math.min(MaxD + d[ca], MaxD + d[b] + cd);
		for (int k = lb; k <= ub; k++) {
		    S[ca][k] -= S[b][k - cd];
		    assert S[ca][k] >= 0;
		    S[ca][k - 2] += S[b][k - cd];
		}
		if (cu[ca] > i + 1) {
		    ++cd;
		} else {
		    --cd;
		}
		cb = ca;
		ca = u[cb];
	    }
	}
	//System.out.println(sum + " " + cnt);
    }

    void write(PrintWriter out) {
	out.println(1.0 * sum / cnt);
	out.close();
    }

//----------------- just for validation ------------------

    /**
     * Strict scanner to verify 100% correspondence between input files and input file format specification.
     * It is a drop-in replacement for {@link java.util.Scanner} that could be added to a solution source
     * (cut-and-paste) without breaking its ability to work with {@link java.util.Scanner}.
     */
    public class Scanner implements Closeable {
        private final BufferedReader in;
        private String line = "";
        private int pos;
        private int lineNo;
        private boolean localeset;

        public Scanner(File source) throws FileNotFoundException {
            in = new BufferedReader(new FileReader(source));
            nextLine();
        }

        public void close() {
            assert line == null : "Extra data at the end of file";
            try {
                in.close();
            } catch (IOException e) {
                throw new AssertionError("Failed to close with " + e);
            }
        }

        public void nextLine() {
            assert line != null : "EOF";
            assert pos == line.length() : "Extra characters on line " + lineNo;
            try {
                line = in.readLine();
            } catch (IOException e) {
                throw new AssertionError("Failed to read line with " + e);
            }
            pos = 0;
            lineNo++;
        }

        public String next() {
            assert line != null : "EOF";
            assert line.length() > 0 : "Empty line " + lineNo;
            if (pos == 0)
                assert line.charAt(0) > ' ' : "Line " + lineNo + " starts with whitespace";
            else {
                assert pos < line.length() : "Line " + lineNo + " is over";
                assert line.charAt(pos) == ' ' : "Wrong whitespace on line " + lineNo;
                pos++;
                assert pos < line.length() : "Line " + lineNo + " is over";
                assert line.charAt(pos) > ' ' : "Line " + lineNo + " has double whitespace";
            }
            StringBuilder sb = new StringBuilder();
            while (pos < line.length() && line.charAt(pos) > ' ')
                sb.append(line.charAt(pos++));
            return sb.toString();
        }

        public int nextInt() {
            String s = next();
            assert s.length() == 1 || s.charAt(0) != '0' : "Extra leading zero in number " + s + " on line " + lineNo;
            assert s.charAt(0) != '+' : "Extra leading '+' in number " + s + " on line " + lineNo;
            try {
                return Integer.parseInt(s);
            } catch (NumberFormatException e) {
                throw new AssertionError("Malformed number " + s + " on line " + lineNo);
            }
        }

        public double nextDouble() {
            assert localeset : "Locale must be set with useLocale(Locale.US)";
            String s = next();
            assert s.length() == 1 || s.startsWith("0.") || s.charAt(0) != '0' : "Extra leading zero in number " + s + " on line " + lineNo;
            assert s.charAt(0) != '+' : "Extra leading '+' in number " + s + " on line " + lineNo;
            try {
                return Double.parseDouble(s);
            } catch (NumberFormatException e) {
                throw new AssertionError("Malformed number " + s + " on line " + lineNo);
            }
        }

        public void useLocale(Locale locale) {
            assert locale == Locale.US;
            localeset = true;
        }
    }
}

