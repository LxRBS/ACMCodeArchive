import java.io.*;
import java.util.*;

public class Pokegene_xiaowuc1 {
	private static BufferedReader br;
	private static StringTokenizer st;
	private static PrintWriter pw;

	public static void main(String[] args) throws IOException {
		br = new BufferedReader(new InputStreamReader(System.in));
		pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
		int n = readInt();
		int qq = readInt();
		mapping = new int[n];
		l = new State[n];
		for(int i = 0; i < n; i++) {
			l[i] = new State(readToken(), i);
		}
		Arrays.sort(l);
		hash = new long[n][];
		for(int i = 0; i < n; i++) {
			hash[i] = new long[l[i].s.length()+1];
			for(int a = 0; a < l[i].s.length(); a++) {
				hash[i][a+1] = hash[i][a] * HASH + l[i].s.charAt(a);
				hash[i][a+1] %= MOD;
			}
		}
		for(int i = 0; i < n; i++) {
			mapping[l[i].i] = i;
		}
		while(qq-- > 0) {
			pw.println(solve());
		}
		exitImmediately();
	}

	static int[] mapping;
	static State[] l;
	static long[][] hash;
	static final int HASH = 3137;
	static final int MOD = 1000000007;
	
	public static int match(int lhs, int rhs) {
		int lowLen = 0;
		int highLen = Math.min(l[lhs].s.length(), l[rhs].s.length());
		while(lowLen != highLen) {
			int mid = (lowLen+highLen+1)/2;
			if(hash[lhs][mid] == hash[rhs][mid]) {
				lowLen = mid;
			}
			else {
				highLen = mid-1;
			}
		}
		return lowLen;
	}
	
	public static long solve() throws IOException {
		int n = readInt();
		int k = readInt();
		int[] have = new int[n];
		for(int i = 0; i < n; i++) {
			have[i] = mapping[readInt()-1];
		}
		Arrays.sort(have);
		long ret = 0;
		for(int i = 0; i + k <= n; i++) {
			int lhs = have[i];
			int rhs = have[i+k-1];
			int matchLen = match(lhs, rhs);
			int border = 0;
			if(i > 0) {
				border = Math.max(border, match(have[i-1], have[i]));
			}
			if(i + k < n) {
				border = Math.max(border, match(have[i+k-1], have[i+k]));
			}
			ret += Math.max(0, matchLen - border);
		}
		return ret;
	}
	
	static class State implements Comparable<State> {
		public String s;
		public int i;
		public State(String s, int i) {
			super();
			this.s = s;
			this.i = i;
		}
		public int compareTo(State state) {
			return s.compareTo(state.s);
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