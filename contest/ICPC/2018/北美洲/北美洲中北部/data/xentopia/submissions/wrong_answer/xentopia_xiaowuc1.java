import java.io.*;
import java.util.*;

public class xentopia_xiaowuc1 {
	private static BufferedReader br;
	private static StringTokenizer st;
	private static PrintWriter pw;

	public static void main(String[] args) throws IOException {
		br = new BufferedReader(new InputStreamReader(System.in));
		pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
		int n = readInt();
		int m = readInt();
		int red = readInt();
		int blue = readInt();
		wEdges = new LinkedList[n];
		rEdges = new LinkedList[n];
		bEdges = new LinkedList[n];
		for(int i = 0; i < n; i++) {
			wEdges[i] = new LinkedList<>();
			rEdges[i] = new LinkedList<>();
			bEdges[i] = new LinkedList<>();
		}
		while(m-- > 0) {
			int a = readInt()-1;
			int b = readInt()-1;
			int w = readInt();
			int c = readInt();
			LinkedList<Edge>[] source = null;
			if(c == WHITE) {
				source = wEdges;
			}
			else if(c == RED) {
				source = rEdges;
			}
			else if(c == BLUE) {
				source = bEdges;
			}
			else {
				throw new RuntimeException();
			}
			source[a].add(new Edge(b, w));
			source[b].add(new Edge(a, w));
		}
		int s = readInt()-1;
		int t = readInt()-1;
		long[][] dp = new long[n][blue+1];
		for(int i = 0; i < dp.length; i++) {
			Arrays.fill(dp[i], INF);
		}
		dp[s][0] = 0;
		for(int nr = 0; nr < red; nr++) {
			expand(dp);
			long[][] ndp = new long[n][blue+1];
			for(int i = 0; i < n; i++) {
				Arrays.fill(ndp[i], INF);
			}
			for(int i = 0; i < n; i++) {
				for(Edge out: rEdges[i]) {
					for(int j = 0; j <= blue; j++) {
						ndp[out.d][j] = Math.min(ndp[out.d][j], dp[i][j] + out.w);
					}
				}
			}
			dp = ndp;
		}
		long ret = dp[t][blue];
		if(ret == INF) ret = -1;
		pw.println(ret);
		exitImmediately();
	}

	static final long INF = 1 << 60;
	static LinkedList<Edge>[] wEdges;
	static LinkedList<Edge>[] rEdges;
	static LinkedList<Edge>[] bEdges;

	public static void expand(long[][] dp) {
		PriorityQueue<Vertex> q = new PriorityQueue<>();
		for(int i = 0; i < dp.length; i++) {
			for(int j = 0; j < dp[i].length; j++) {
				if(dp[i][j] == INF) continue;
				q.add(new Vertex(i, j, dp[i][j]));
			}
		}
		while(!q.isEmpty()) {
			Vertex curr = q.poll();
			if(dp[curr.v][curr.nb] != curr.w) continue;
			for(Edge out: wEdges[curr.v]) {
				if(dp[out.d][curr.nb] > curr.w + out.w) {
					dp[out.d][curr.nb] = curr.w + out.w;
					q.add(new Vertex(out.d, curr.nb, dp[out.d][curr.nb]));
				}
			}
			for(Edge out: bEdges[curr.v]) {
				if(curr.nb+1 < dp[out.d].length && dp[out.d][curr.nb+1] > curr.w + out.w) {
					dp[out.d][curr.nb+1] = curr.w + out.w;
					q.add(new Vertex(out.d, curr.nb+1, dp[out.d][curr.nb+1]));
				}
			}
		}
	}

	static final int WHITE = 0;
	static final int RED = 1;
	static final int BLUE = 2;

	static class Vertex implements Comparable<Vertex> {
		public int v;
		public int nb;
		public long w;
		public Vertex(int v, int nb, long w) {
			super();
			this.v = v;
			this.nb = nb;
			this.w = w;
		}
		public int compareTo(Vertex curr) {
			return Long.compare(w, curr.w);
		}
	}

	static class Edge {
		public int d, w;

		public Edge(int d, int w) {
			super();
			this.d = d;
			this.w = w;
		}

	}

	private static void exitImmediately() {
		pw.close();
		System.exit(0);
	}

	private static int readInt() throws IOException {
		return Integer.parseInt(readToken());
	}

	private static String readLine() throws IOException  {
		String s = br.readLine();
		if(s == null) {
			exitImmediately();
		}
		st = null;
		return s;
	}

	private static String readToken() throws IOException  {
		while(st == null || !st.hasMoreTokens())  {
			st = new StringTokenizer(readLine().trim());
		}
		return st.nextToken();
	}
}